#include "gm_negocioteste.h"

// Domínios
#include "escrituracao/dominio/escrituracao_escrituracao.h"

// Negocios
#include "arquivos/negocio/arquivo_arquivonegocio.h"
#include "escrituracao/negocio/escrituracao_escrituracaonegocio.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"
#include "infraestrutura/banco/dbmanager.h"
#include "infraestrutura/banco/gm_dbconnection.h"

using namespace gm;
using namespace gm_arquivo;
using namespace gm_escrituracao;

NegocioTeste::NegocioTeste(QObject *parent) : QObject(parent)
{

}

void NegocioTeste::testeDoDaniel()
{
    /*Inicialização conexão SECUNDÁRIA*/
    gm::DbConnection* conexao = new gm::DbConnection();
    QThread* thread = new QThread;

    QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    QObject::connect(thread, &QThread::finished, conexao, &QObject::deleteLater);

    QObject::connect(thread, &QThread::started, conexao, &gm::DbConnection::criarConexao);

    conexao->moveToThread(thread);
    thread->start();

    //    QSqlDatabase db = gm::DBUtil::conexao();
    //    EscrituracaoNegocio escrituracaoNegocio;
    //    QStringList pathsArquivosSpedFiscal = QFileDialog::getOpenFileNames(nullptr, "Abrir Arquivos", QDir::homePath(), "Arquivos SPED (*.txt)");
    //    escrituracaoNegocio.gerarEscrituracoesMaster(pathsArquivosSpedFiscal);

    //    int ano = 2018;
    //    QString cnpjRaizEmpresa = "03995515";
    //    QString cnpj = "03995515002372";

    //    Escrituracao* escrituracao = escrituracaoNegocio.recuperarEscrituracao(ano, cnpjRaizEmpresa, cnpj);

    //    if (escrituracao != nullptr && !escrituracao->nomeDatabase().isEmpty()){
    //        QString nomeArquivoDatabase = escrituracao->nomeDatabase();
    //        QSqlDatabase dbConexao = gm::DBUtil::conexao(nomeArquivoDatabase);
    //    }
}

void NegocioTeste::testeCriacaoDatabase()
{
    //db.removeDatabase("MASTER");
    //QSqlDatabase conexao = gm::DBUtil::conexao();

    DbManager manager;
    QSqlDatabase dbTeste = gm::DBUtil::criarDatabase(QApplication::applicationDirPath() + QDir::separator() + "DADOS", "ABERTOS", "TESTE");
    manager.setDatabase(dbTeste);

    QList<DbManager::InformacoesCampos> listaInformacoes;
    listaInformacoes << manager.getInformacoesCampos("ano", DbManager::BIGINT, 4);
    listaInformacoes << manager.getInformacoesCampos("mes", DbManager::BIGINT, 2);

    manager.criarTabela("testandocriacao", listaInformacoes);

    if(manager.lastError().isErro())
        qDebug() << manager.lastError().mensagem();
    else
        qDebug() << "criou tabela com sucesso";

    exit(0);
}

void NegocioTeste::outPutDebug(QVariant value1, QVariant value2)
{
    qDebug() << value1.toString() << value2.toString();
}

