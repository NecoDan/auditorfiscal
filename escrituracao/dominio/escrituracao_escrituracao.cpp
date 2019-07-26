#include "escrituracao_escrituracao.h"

// Infraestrutura
#include "infraestrutura/stringutil.h"

// Constantes
#define POSICAO_REGISTRO_PERIODO_INICIO   4
#define POSICAO_REGISTRO_PERIODO_FIM      5
#define POSICAO_REGISTRO_DESCRICAO_FILIAL 6
#define POSICAO_REGISTRO_CNPJ             7
#define POSICAO_REGISTRO_IE               9

namespace gm_escrituracao
{
    const QString Escrituracao::NOME_TABELA = "ESCRITURACAO";

    Escrituracao::Escrituracao(QObject *parent) : QObject(parent)
    {
        this->inicializar();
    }

    int Escrituracao::id() const
    {
        return _id;
    }

    void Escrituracao::setId(int id)
    {
        _id = id;
    }

    QString Escrituracao::descricaoFilial() const
    {
        return _descricaoFilial;
    }

    void Escrituracao::setDescricaoFilial(const QString& descricaoFilial)
    {
        _descricaoFilial = descricaoFilial;
    }

    QString Escrituracao::cnpjRaizEmpresa() const
    {
        return _cnpjRaizEmpresa;
    }

    void Escrituracao::setCnpjRaizEmpresa(const QString& cnpjRaizEmpresa)
    {
        _cnpjRaizEmpresa = cnpjRaizEmpresa;
    }

    QString Escrituracao::cnpj() const
    {
        return _cnpj;
    }

    void Escrituracao::setCnpj(const QString& cnpj)
    {
        _cnpj = cnpj;
    }

    int Escrituracao::ano() const
    {
        return _ano;
    }

    void Escrituracao::setAno(int ano)
    {
        _ano = ano;
    }

    QString Escrituracao::nomeDatabase() const
    {
        return _nomeDatabase;
    }

    void Escrituracao::setNomeDatabase(const QString& nomeDatabase)
    {
        _nomeDatabase = nomeDatabase;
    }

    long long Escrituracao::inscricaoEstadual() const
    {
        return _inscricaoEstadual;
    }

    void Escrituracao::setInscricaoEstadual(long long inscricaoEstadual)
    {
        _inscricaoEstadual = inscricaoEstadual;
    }

    QDateTime Escrituracao::data() const
    {
        return _data;
    }

    void Escrituracao::setData(const QDateTime& data)
    {
        _data = data;
    }

    bool Escrituracao::contemArquivoLidoImportado() const
    {
        return _contemArquivoLidoImportado;
    }

    void Escrituracao::setContemArquivoLidoImportado(bool contemArquivoLidoImportado)
    {
        _contemArquivoLidoImportado = contemArquivoLidoImportado;
    }

    QString Escrituracao::pathCaminhoArquivo() const
    {
        return _pathCaminhoArquivo;
    }

    void Escrituracao::setPathCaminhoArquivo(const QString& pathCaminhoArquivo)
    {
        _pathCaminhoArquivo = pathCaminhoArquivo;
    }

    int Escrituracao::mes() const
    {
        return _mes;
    }

    void Escrituracao::setMes(int mes)
    {
        _mes = mes;
    }

    bool Escrituracao::fechado() const
    {
        return _fechado;
    }

    void Escrituracao::setFechado(bool fechado)
    {
        _fechado = fechado;
    }

    QDate Escrituracao::dataInicio() const
    {
        return _dataInicio;
    }

    void Escrituracao::setDataInicio(const QDate& dataInicio)
    {
        _dataInicio = dataInicio;
    }

    QDate Escrituracao::dataFim() const
    {
        return _dataFim;
    }

    void Escrituracao::setDataFim(const QDate& dataFim)
    {
        _dataFim = dataFim;
    }

    /*################################################# Métodos de Ação #########################################################*/

    QString Escrituracao::toStringNomeArquivoEscrituracao()
    {
        bool parametrosValidosEscrita = (_ano > 0 && !_cnpjRaizEmpresa.isEmpty() && !_cnpj.isEmpty() && !_descricaoFilial.isEmpty());

        if (!parametrosValidosEscrita)
            return QString();

        return QString::number(_ano) + "_" + _cnpjRaizEmpresa + "_" + _cnpj;
    }

    QString Escrituracao::toStringNomeArquivoEscrituracaoCompleto()
    {
        QString nomeEscrituracao = this->toStringNomeArquivoEscrituracao();

        if (!this->_descricaoFilial.isEmpty())
            nomeEscrituracao.append("_" + this->_descricaoFilial);

        return nomeEscrituracao;
    }

    void Escrituracao::inicializar(int id)
    {
        _id = id;
        _ano = 0;
        _inscricaoEstadual = 0;
        _contemArquivoLidoImportado = false;
        _fechado = false;
    }
    
    /*############################################### Escrituracao Buider ##############################################*/

    EscrituracaoBuilder::EscrituracaoBuilder(QObject* parent) : QObject(parent)
    {
        _escrituracao = new Escrituracao();
    }

    EscrituracaoBuilder::EscrituracaoBuilder(Escrituracao* escrituracao, QObject* parent) : QObject(parent)
    {
        _escrituracao = escrituracao;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::umNovaEscrituracao()
    {
        EscrituracaoBuilder* escrituracaoBuilder = new EscrituracaoBuilder();
        return escrituracaoBuilder;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::umNovaEscrituracao(QMap<int, QString> mapPosicoesRegistroArquivoSped)
    {
        EscrituracaoBuilder* escrituracaoBuilder = new EscrituracaoBuilder();

        escrituracaoBuilder->comOSeguinteCnpj(mapPosicoesRegistroArquivoSped.value(POSICAO_REGISTRO_CNPJ));
        escrituracaoBuilder->comARaizCnjpEmpresa(StringUtil::cnpjRaiz(escrituracaoBuilder->_escrituracao->cnpj()));
        escrituracaoBuilder->comAInscricaoEstadual(mapPosicoesRegistroArquivoSped.value(POSICAO_REGISTRO_IE).toLongLong());
        escrituracaoBuilder->carregadaComADescricaoFilial(mapPosicoesRegistroArquivoSped.value(POSICAO_REGISTRO_DESCRICAO_FILIAL));
        escrituracaoBuilder->deAcordoComADataLancamento(QDateTime::currentDateTime());

        QDate dtPeriodoApuracaoInicio = QDate::fromString(mapPosicoesRegistroArquivoSped.value(POSICAO_REGISTRO_PERIODO_INICIO), "ddMMyyyy");
        QDate dtPeriodoApuracaoFim = QDate::fromString(mapPosicoesRegistroArquivoSped.value(POSICAO_REGISTRO_PERIODO_FIM), "ddMMyyyy");

        if (dtPeriodoApuracaoInicio.isValid()){
            escrituracaoBuilder->inicializandoPeloAno(dtPeriodoApuracaoInicio.year());
            escrituracaoBuilder->inicializadoPeloMes(dtPeriodoApuracaoInicio.month());
            escrituracaoBuilder->iniciaPelaData(dtPeriodoApuracaoInicio);
        }

        if (dtPeriodoApuracaoFim.isValid())
            escrituracaoBuilder->finalizaPelaData(dtPeriodoApuracaoFim);

        return escrituracaoBuilder;
    }

    Escrituracao* EscrituracaoBuilder::constroi()
    {
        return this->_escrituracao;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::comARaizCnjpEmpresa(QString cnpjRaizEmpresa)
    {
        this->_escrituracao->setCnpjRaizEmpresa(cnpjRaizEmpresa);
        return this;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::inicializandoPeloAno(int ano)
    {
        this->_escrituracao->setAno(ano);
        return this;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::inicializadoPeloMes(int mes)
    {
        this->_escrituracao->setMes(mes);
        return this;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::comOSeguinteCnpj(QString cnpj)
    {
        this->_escrituracao->setCnpj(cnpj);
        return this;
    }

    EscrituracaoBuilder*EscrituracaoBuilder::iniciaPelaData(QDate dataInicio)
    {
        this->_escrituracao->setDataInicio(dataInicio);
        return this;
    }

    EscrituracaoBuilder*EscrituracaoBuilder::finalizaPelaData(QDate dataFim)
    {
        this->_escrituracao->setDataFim(dataFim);
        return this;
    }

    EscrituracaoBuilder*EscrituracaoBuilder::fechada(bool fechado)
    {
        this->_escrituracao->setFechado(fechado);
        return this;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::deAcordoComADataLancamento(QDateTime data)
    {
        this->_escrituracao->setData(data);
        return this;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::comAInscricaoEstadual(long long inscricaoEstadual)
    {
        this->_escrituracao->setInscricaoEstadual(inscricaoEstadual);
        return this;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::carregadaComADescricaoFilial(QString descricaoFilial)
    {
        this->_escrituracao->setDescricaoFilial(descricaoFilial);
        return this;
    }

    EscrituracaoBuilder* EscrituracaoBuilder::definidaComNomeDatabase(QString nomeDatabase)
    {
        this->_escrituracao->setNomeDatabase(nomeDatabase);
        return this;
    }
}
