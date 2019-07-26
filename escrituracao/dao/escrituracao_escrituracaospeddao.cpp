#include "escrituracao_escrituracaospeddao.h"

// Domínios
#include "escrituracao/dominio/escrituracao_escrituracao.h"
#include "escrituracao/dominio/escrituracao_escrituracaosped.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"
#include "infraestrutura/banco/gm_sqlutil.h"
#include "infraestrutura/banco/gm_dsqlquery.h"

using namespace gm;

namespace gm_escrituracao
{
    EscrituracaoSpedDao::EscrituracaoSpedDao(QSqlDatabase& db, QObject *parent) : QObject(parent)
    {
        _db = db;
    }

    GMErro EscrituracaoSpedDao::lastError()
    {
        return _lastError;
    }

    void EscrituracaoSpedDao::atualizarEscrituracaoSped(EscrituracaoSped* escrituracaoSped)
    {
        if (escrituracaoSped == nullptr){
            _lastError = GMErro("Escrituração inválida e/ou inexistente.", GMErro::BANCO, metaObject()->className());
            return;
        }

        DbManager dbManager(_db);
        dbManager.updateRegistro(EscrituracaoSped::NOME_TABELA, this->montarCamposEscrituracaoSped(escrituracaoSped), escrituracaoSped->id());

        if (dbManager.lastError().isErro()){
            _lastError = GMErro(dbManager.lastError().mensagem(), GMErro::BANCO, metaObject()->className());
            return;
        }

        _lastError = GMErro("Atualizado com sucesso.");
    }

    void EscrituracaoSpedDao::salvarEscrituracaoSped(EscrituracaoSped* escrituracaoSped)
    {
        if (escrituracaoSped == nullptr){
            _lastError = GMErro("Escrituração inválida e/ou inexistente.", GMErro::BANCO, metaObject()->className());
            return;
        }

        DbManager dbManager(_db);
        long long idPersistido = dbManager.addRegistro(EscrituracaoSped::NOME_TABELA, this->montarCamposEscrituracaoSped(escrituracaoSped));

        if (dbManager.lastError().isErro()){
            _lastError = GMErro(dbManager.lastError().mensagem(), GMErro::BANCO, metaObject()->className());
            return;
        }

        escrituracaoSped->setId(idPersistido);
        _lastError = GMErro("Salvo com sucesso.");
    }

    EscrituracaoSped* EscrituracaoSpedDao::recuperarEscrituracaoSped(Escrituracao* escrituracao)
    {
        EscrituracaoSped* escrituracaoSped = nullptr;
        QString queryString = " SELECT * FROM ESCRITURACAO_SPED";

        if (escrituracao->ano() > 0)
            SqlUtil::appendValue(queryString, "ano", escrituracao->ano());

        if (escrituracao->mes())
            SqlUtil::appendValue(queryString, "mes", escrituracao->mes());

        if (!escrituracao->cnpj().isEmpty())
            SqlUtil::appendValue(queryString, "cnpj", escrituracao->cnpj());

        DSqlQuery query(_db);
        query.exec(queryString);

        if (query.next())
            escrituracaoSped = this->montarObjEscrituracaoSped(query);

        query.finish();
        return escrituracaoSped;
    }

    QList<EscrituracaoSped*> EscrituracaoSpedDao::recuperarEscrituracoesSped()
    {
         QList<EscrituracaoSped*> escrituracoesSped;
         QString queryString = " SELECT * FROM ESCRITURACAO_SPED";

         DSqlQuery query(_db);
         query.exec(queryString);

         while (query.next())
            escrituracoesSped << this->montarObjEscrituracaoSped(query);

         query.finish();
         return escrituracoesSped;
    }

    QList<DbManager::InformacoesCampos> EscrituracaoSpedDao::montarCamposEscrituracaoSped(EscrituracaoSped* escrituracaoSped)
    {
        QList<DbManager::InformacoesCampos> informacoesCampo;
        DbManager::InformacoesCampos campo;

        campo.nomeCampo = "ano";
        campo.valor = escrituracaoSped->ano();
        campo.tipoCampo = DbManager::BIGINT;
        informacoesCampo << campo;

        campo.nomeCampo = "mes";
        campo.valor = escrituracaoSped->mes();
        campo.tipoCampo = DbManager::BIGINT;
        informacoesCampo << campo;

        campo.nomeCampo = "cnpj";
        campo.valor = escrituracaoSped->cnpj();
        campo.tipoCampo = DbManager::TEXTO;
        informacoesCampo << campo;

        campo.nomeCampo = "fiscal";
        campo.valor = escrituracaoSped->fiscal();
        campo.tipoCampo = DbManager::BOOLEAN;
        informacoesCampo << campo;

        campo.nomeCampo = "nao_fiscal_saldo";
        campo.valor = escrituracaoSped->naoFiscalSaldo();
        campo.tipoCampo = DbManager::BOOLEAN;
        informacoesCampo << campo;

        campo.nomeCampo = "nao_fiscal_movimentacao";
        campo.valor = escrituracaoSped->naoFiscalMovimentacao();
        campo.tipoCampo = DbManager::BOOLEAN;
        informacoesCampo << campo;

        campo.nomeCampo = "caminho_arquivo";
        campo.valor = escrituracaoSped->caminhoArquivo();
        campo.tipoCampo = DbManager::TEXTO;
        informacoesCampo << campo;

        campo.nomeCampo = "data";
        campo.valor = escrituracaoSped->data();
        campo.tipoCampo = DbManager::DATA_HORA;
        informacoesCampo << campo;

        return informacoesCampo;
    }

    EscrituracaoSped* EscrituracaoSpedDao::montarObjEscrituracaoSped(DSqlQuery& query)
    {
        EscrituracaoSped* escrituracaoSped = new EscrituracaoSped();

        escrituracaoSped->setId(query.getInt("id"));
        escrituracaoSped->setAno(query.getInt("ano"));
        escrituracaoSped->setMes(query.getInt("mes"));
        escrituracaoSped->setCnpj(query.getString("cnpj"));
        escrituracaoSped->setCaminhoArquivo(query.getString("caminho_arquivo"));
        escrituracaoSped->setData(query.getDateTime("data"));
        escrituracaoSped->setFiscal(query.value("fiscal").toBool());
        escrituracaoSped->setNaoFiscalSaldo(query.value("nao_fiscal_saldo").toBool());
        escrituracaoSped->setNaoFiscalMovimentacao(query.value("nao_fiscal_movimentacao").toBool());

        return escrituracaoSped;
    }
}
