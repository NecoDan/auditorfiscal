#include "arquivo_configuracaoarquivonegocio.h"

// Dominios
#include "arquivos/dominios/registro.h"

// Infraestrutura
#include "infraestrutura/stringutil.h"

namespace gm_arquivo
{
    ConfiguracaoArquivoNegocio::ConfiguracaoArquivoNegocio(QObject *parent) : QObject(parent)
    {
        this->inicializar();
    }

    ConfiguracaoArquivoNegocio::ConfiguracaoArquivoNegocio(bool comDelimitador, QObject *parent) : QObject(parent)
    {
        this->inicializar(comDelimitador);
    }

    ConfiguracaoArquivoNegocio::ConfiguracaoArquivoNegocio(QString titulo, QObject *parent) : QObject(parent)
    {
        this->inicializar();
        _arquivo = new QFile(titulo);
        _arquivo->open(QIODevice::WriteOnly| QIODevice::Text);
    }

    ConfiguracaoArquivoNegocio::ConfiguracaoArquivoNegocio(QFile *&arquivo, QObject *parent) : QObject(parent)
    {
        this->inicializar();
        _arquivo = arquivo;
        _arquivo->open(QIODevice::WriteOnly | QIODevice::Text);
    }

    void ConfiguracaoArquivoNegocio::inicializar(bool comDelimitador)
    {
        _arquivo = nullptr;
        _comDelimitador = comDelimitador;
        _existeArquivoSecundarioCarregado = false;
        _blocoPaiEFilhos = "";
    }

    QFile *ConfiguracaoArquivoNegocio::arquivo() const
    {
        return _arquivo;
    }

    void ConfiguracaoArquivoNegocio::setArquivo(QFile *arquivo)
    {
        _arquivo = arquivo;
    }

    QByteArray ConfiguracaoArquivoNegocio::conteudoArquivo() const
    {
        return _conteudoArquivo;
    }

    void ConfiguracaoArquivoNegocio::setConteudoArquivo(const QByteArray &conteudoArquivo)
    {
        _conteudoArquivo = conteudoArquivo;
    }

    QStringList ConfiguracaoArquivoNegocio::linhasConteudoArquivo()
    {
        return _linhasConteudoArquivo;
    }

    void ConfiguracaoArquivoNegocio::addLinhaConteudoArquivo(QString linha)
    {
        _linhasConteudoArquivo.append(linha);
    }

    void ConfiguracaoArquivoNegocio::addLinhasConteudosArquivos(QStringList linhas)
    {
        for (auto linha : linhas)
            this->addLinhaConteudoArquivo(linha);
    }

    bool ConfiguracaoArquivoNegocio::existeArquivoSecundarioCarregado() const
    {
        return _existeArquivoSecundarioCarregado;
    }

    void ConfiguracaoArquivoNegocio::setExisteArquivoSecundarioCarregado(bool existeArquivoSecundarioCarregado)
    {
        _existeArquivoSecundarioCarregado = existeArquivoSecundarioCarregado;

        if (existeArquivoSecundarioCarregado && _arquivo != nullptr && _arquivo->exists()){
            QString tituloNovoArquivo = _arquivo->fileName();
            tituloNovoArquivo.replace(".txt", "_AUXILIAR.txt");

            _arquivoNovoAGerar = new QFile(tituloNovoArquivo);
            _arquivoNovoAGerar->open(QIODevice::WriteOnly| QIODevice::Text);
        }
    }

    ConfiguracaoArquivoNegocio::TipoEscrita ConfiguracaoArquivoNegocio::tipoEscrita()
    {
        return _tipoEscrita;
    }

    void ConfiguracaoArquivoNegocio::setTipoEscrita(TipoEscrita tipoEscrita)
    {
        _tipoEscrita = tipoEscrita;
    }

    void ConfiguracaoArquivoNegocio::defineBlocoPaiEFilhos(QString blocoPaiEFilhos)
    {
       _blocoPaiEFilhos = blocoPaiEFilhos;
    }

    bool ConfiguracaoArquivoNegocio::isArqConstruidoOuFinalizado()
    {
        if (_arquivo->isOpen())
            return true;

        return false;
    }

    QStringList ConfiguracaoArquivoNegocio::extrairLinhasConteudoArquivo(QList<RegistroArquivo*> registros)
    {
        QStringList linhas;

        if (comDelimitador()){
            for (auto registro : registros)
                linhas << registro->toString();
        } else {
            for (auto registro :registros)
                linhas << registro->toStringSemSeparadores();
        }

        return linhas;
    }

    QStringList ConfiguracaoArquivoNegocio::extrairLinhasConteudoArquivo(RegistroArquivo *registro)
    {
        QStringList linhas;
        linhas << registro->toString();
        return linhas;
    }

    void ConfiguracaoArquivoNegocio::fechaArquivoNovoGerado()
    {
        if (_existeArquivoSecundarioCarregado && (_arquivo != nullptr && _arquivo->exists())
                && (_arquivoNovoAGerar != nullptr && _arquivoNovoAGerar->exists())){
            QString tituloNovoArquivo = _arquivo->fileName();

            _arquivo->remove();
            _arquivoNovoAGerar->rename(tituloNovoArquivo);
            _arquivoNovoAGerar->close();
        }
    }

    bool ConfiguracaoArquivoNegocio::flush(QList<RegistroArquivo*> registros, bool flushArquivoAuxiliarNovo)
    {
        bool escritaGerada = false;

        if (registros.isEmpty())
            return escritaGerada;

        if (!flushArquivoAuxiliarNovo){
            escritaGerada = flush(this->extrairLinhasConteudoArquivo(registros));
        } else{
            QString strConteudo = this->extrairLinhasConteudoArquivo(registros).join("\r\n").append("\r\n");
            QByteArray arquivoStrConteudo = strConteudo.toLatin1();

            escritaGerada = this->flushArquivoNovo(arquivoStrConteudo);
        }

        return escritaGerada;
    }

    bool ConfiguracaoArquivoNegocio::flush(RegistroArquivo* registro)
    {
        QStringList linhas = this->extrairLinhasConteudoArquivo(registro);

        if (this->existeArquivoSecundarioCarregado())
            this->addLinhasConteudosArquivos(linhas);

        QByteArray arquivoString = linhas.join("\r\n").append("\r\n").toUtf8();
        return this->flush(arquivoString);
    }

    bool ConfiguracaoArquivoNegocio::flush(QFile* arquivo)
    {
        while (!arquivo->atEnd())
            _arquivo->write(arquivo->readLine());

        return _arquivo->flush();
    }

    bool ConfiguracaoArquivoNegocio::flush(QStringList linhasRegistros, QString bloco, bool ignoraValidacaoBloco)
    {
        QByteArray arquivoString;

        if (this->existeArquivoSecundarioCarregado()){
            if (bloco.isEmpty())
                this->addLinhasConteudosArquivos(linhasRegistros);
        }

        if (bloco.isEmpty() && !ignoraValidacaoBloco){
            arquivoString = linhasRegistros.join("\r\n").append("\r\n").toUtf8();
            return this->flush(arquivoString);
        } else {
            if (ignoraValidacaoBloco){
                QString str = linhasRegistros.join("\r\n").append("\r\n");
                arquivoString = str.toLatin1();
            } else{
                QString str = linhasRegistros.join("");
                arquivoString = str.toLatin1();
            }

            return this->flushArquivoNovo(arquivoString);
        }
    }

    bool ConfiguracaoArquivoNegocio::flush(QByteArray arquivoString)
    {
        bool escritaGerada = false;

        if (!arquivoString.isEmpty()){
            _conteudoArquivo.append(arquivoString);
            _arquivo->write(arquivoString);
            escritaGerada = _arquivo->flush();
        }

        return escritaGerada;
    }

    bool ConfiguracaoArquivoNegocio::flushArquivoNovo(QByteArray arquivoString)
    {
        bool escritaGerada = false;

        if (!arquivoString.isEmpty()){
            _arquivoNovoAGerar->write(arquivoString);
            escritaGerada = _arquivoNovoAGerar->flush();
        }

        return escritaGerada;
    }

    bool ConfiguracaoArquivoNegocio::comDelimitador()
    {
        return _comDelimitador;
    }

    QByteArray ConfiguracaoArquivoNegocio::extrairConteudoArquivo()
    {
        QByteArray conteudoArquivo;

        _arquivo->open(QIODevice::ReadWrite | QIODevice::Text);

        while (!arquivo()->atEnd()){
            conteudoArquivo.append(_arquivo->readLine());
        }

        return conteudoArquivo;
    }

    void ConfiguracaoArquivoNegocio::removeLinhasConteudoArquivo()
    {
        if (!_linhasConteudoArquivo.isEmpty())
            _linhasConteudoArquivo.clear();
    }

    bool ConfiguracaoArquivoNegocio::isContemBloco(QString linha, QString bloco)
    {
        bool contem = false;
        QStringList blocos;
        QString separador = "||";

        if (bloco.contains(separador)){
            blocos = StringUtil::extrairListStringToStringListPor(separador, bloco);

            for (QString blocoPes : blocos){
                if (linha.contains(blocoPes))
                    contem = true;
            }
        } else {
            if (linha.contains(bloco))
                contem = true;
        }

        return contem;
    }

}
