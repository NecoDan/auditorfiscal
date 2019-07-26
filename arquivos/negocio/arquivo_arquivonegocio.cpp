#include "arquivo_arquivonegocio.h"

// Negocio
#include "escrituracao/negocio/escrituracao_escrituracaonegocio.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"

// Constantes
const QString BLOCO_PAI_ABERTURA_ARQUIVO_SPED = "|0000|";

using namespace gm;
using namespace gm_escrituracao;

namespace gm_arquivo
{
    ArquivoNegocio::ArquivoNegocio(QObject *parent) : QObject(parent)
    {
        _db = DBUtil::conexao();
        _lastError = GMErro();
    }

    ArquivoNegocio::ArquivoNegocio(QSqlDatabase& db, QObject *parent) : QObject(parent)
    {
        _db = db;
        _lastError = GMErro();
    }

    GMErro ArquivoNegocio::lastError()
    {
        return _lastError;
    }

    void ArquivoNegocio::gerarEscrituracoesMaster(QStringList pathsCaminhosArquivo)
    {
        if (pathsCaminhosArquivo.isEmpty()){
            _lastError = GMErro("Não foram encontrados ou localizado(s) as pasta(s) para leitura dos arquivo(s)");
            return;
        }

        EscrituracaoNegocio escrituracaoNegocio;

        for (auto pathCaminhoArquivo : pathsCaminhosArquivo) {
            QStringList linhas = this->gerarLinhasRegistrosEscrituracao(pathCaminhoArquivo);

            escrituracaoNegocio.salvarEscrituracaoPaiPor(linhas);

            if(escrituracaoNegocio.lastError().isErro())
                _lastError = GMErro(escrituracaoNegocio.lastError().mensagem(), GMErro::NEGOCIO);
        }
    }

    QStringList ArquivoNegocio::gerarLinhasRegistrosEscrituracao(QString pathCaminhoArquivo)
    {
        QStringList linhas = this->efetuarLeituraArquivo(pathCaminhoArquivo, BLOCO_PAI_ABERTURA_ARQUIVO_SPED, false);
        return linhas;
    }

    QStringList ArquivoNegocio::efetuarLeituraArquivo(QString pathCaminhoArquivo, QString chaveBuscaRegistro, bool lerTodoArquivo)
    {
        QStringList linhas;

        if (pathCaminhoArquivo.isEmpty()){
            _lastError = GMErro();
            return linhas;
        }

        QScopedPointer<QFile> arquivoTemp(new QFile(pathCaminhoArquivo));

        if (!arquivoTemp->exists()){
            _lastError = GMErro();
            return linhas;
        }

        bool abertoArquivo = arquivoTemp->open(QIODevice::ReadOnly | QIODevice::Text);
        if (abertoArquivo){
            while (true){
                QString linhaArquivo = QString::fromLatin1(arquivoTemp->readLine());

                if (linhaArquivo.isNull() || linhaArquivo.isEmpty())
                    break;

                if (linhaArquivo.startsWith(chaveBuscaRegistro)){
                    linhas.append(linhaArquivo);

                    if (!lerTodoArquivo)
                        break;
                }
            }
        }

        arquivoTemp->close();
        return linhas;
    }

    void ArquivoNegocio::outPutDebug(QVariant value1, QVariant value2)
    {
        qDebug() << value1.toString() << value2.toString();
    }
}
