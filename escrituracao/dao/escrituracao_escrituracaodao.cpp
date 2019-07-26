#include "escrituracao_escrituracaodao.h"

// Domínios
#include "escrituracao/dominio/escrituracao_escrituracao.h"
#include "escrituracao/dominio/escrituracao_escrituracaosped.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"
#include "infraestrutura/banco/gm_sqlutil.h"
#include "infraestrutura/banco/dbmanager.h"
#include "infraestrutura/banco/gm_dsqlquery.h"

using namespace gm;

namespace gm_escrituracao
{
    const QString SELECT_PRINCIPAL_ESCRITURACAO = "SELECT * FROM ESCRITURACAO";

    EscrituracaoDao::EscrituracaoDao(QObject *parent) : QObject(parent)
    {
        _db = DBUtil::conexao();
        _lastError = GMErro();
    }

    EscrituracaoDao::EscrituracaoDao(QSqlDatabase& db, QObject *parent) : QObject(parent)
    {
        _db = db;
        _lastError = GMErro();
    }

    GMErro EscrituracaoDao::lastError()
    {
        return _lastError;
    }

    void EscrituracaoDao::salvarEscrituracao(Escrituracao* escrituracao)
    {
        if (escrituracao == nullptr){
            _lastError = GMErro("Escrituração inválida e/ou inexistente.", GMErro::BANCO, metaObject()->className());
            return;
        }

        DbManager dbManager(_db);
        long long idPersistido = dbManager.addRegistro(Escrituracao::NOME_TABELA, this->montarCamposEscrituracao(escrituracao));

        if (dbManager.lastError().isErro()){
            _lastError = GMErro(dbManager.lastError().mensagem(), GMErro::BANCO, metaObject()->className());
            return;
        }

        escrituracao->setId(idPersistido);
        _lastError = GMErro("Salvo com sucesso.");
    }

    void EscrituracaoDao::salvarEscrituracaoSped(EscrituracaoSped* escrituracaoSped)
    {
        if (escrituracaoSped == nullptr){
            _lastError = GMErro("Escrituração SPEDFISCAL inválida e/ou inexistente.", GMErro::BANCO, metaObject()->className());
            return;
        }

        DbManager dbManager(_db);
        long long idPersistido = dbManager.addRegistro(EscrituracaoSped::NOME_TABELA, QList<DbManager::InformacoesCampos>());

        if (dbManager.lastError().isErro()){
            _lastError = GMErro(dbManager.lastError().mensagem(), GMErro::BANCO, metaObject()->className());
            return;
        }

        escrituracaoSped->setId(idPersistido);
        _lastError = GMErro("Salvo com sucesso.");
    }

    void EscrituracaoDao::atualizarEscrituracao(Escrituracao* escrituracao)
    {
        if (escrituracao == nullptr){
            _lastError = GMErro("Escrituração inválida e/ou inexistente.", GMErro::BANCO, metaObject()->className());
            return;
        }

        DbManager dbManager(_db);
        dbManager.updateRegistro(Escrituracao::NOME_TABELA,  this->montarCamposEscrituracao(escrituracao), escrituracao->id());

        if (dbManager.lastError().isErro()){
            _lastError = GMErro(dbManager.lastError().mensagem(), GMErro::BANCO, metaObject()->className());
            return;
        }

        _lastError = GMErro("Atualizado com sucesso.");
    }

    Escrituracao* EscrituracaoDao::recuperarEscrituracao(int ano, QString cnpjRaizEmpresa, QString cnpj)
    {
        Escrituracao* escrituracao = nullptr;
        QString queryString = SELECT_PRINCIPAL_ESCRITURACAO;

        if (ano > 0)
            SqlUtil::appendValue(queryString, "ano", ano);

        if (!cnpjRaizEmpresa.isEmpty())
            SqlUtil::appendValue(queryString, "cnpjRaizEmpresa", cnpjRaizEmpresa);

        if (!cnpj.isEmpty())
            SqlUtil::appendValue(queryString, "cnpj", cnpj);

        DSqlQuery query(_db);
        query.exec(queryString);

        if (query.next())
            escrituracao = this->montarObjEscrituracao(query);

        query.finish();
        return escrituracao;
    }

    Escrituracao*EscrituracaoDao::recuperarEscrituracaoPor(int ano, QString cnpjRaizEmpresa, QString cnpj, long long inscricaoEstadual)
    {
        Escrituracao* escrituracao = nullptr;
        QString queryString = SELECT_PRINCIPAL_ESCRITURACAO;

        if (ano > 0)
            SqlUtil::appendValue(queryString, "ano", ano);

        if (!cnpjRaizEmpresa.isEmpty())
            SqlUtil::appendValue(queryString, "cnpjRaizEmpresa", cnpjRaizEmpresa);

        if (!cnpj.isEmpty())
            SqlUtil::appendValue(queryString, "cnpj", cnpj);

        if (inscricaoEstadual > 0)
            SqlUtil::appendValue(queryString, "inscricaoEstadual", inscricaoEstadual);

        DSqlQuery query(_db);
        query.exec(queryString);

        if (query.next())
            escrituracao = this->montarObjEscrituracao(query);

        query.finish();
        return escrituracao;
    }

    Escrituracao*EscrituracaoDao::recuperarPorId(long long id)
    {
        Escrituracao* escrituracao = nullptr;
        QString queryString = SELECT_PRINCIPAL_ESCRITURACAO;

        if (id > 0)
            SqlUtil::appendValue(queryString, "id", id);

        DSqlQuery query(_db);
        query.exec(queryString);

        if (query.next())
            escrituracao = this->montarObjEscrituracao(query);

        query.finish();
        return escrituracao;
    }

    Escrituracao*EscrituracaoDao::recuperarPorId(int id)
    {
        Escrituracao* escrituracao = nullptr;
        QString queryString = SELECT_PRINCIPAL_ESCRITURACAO;

        if (id > 0)
            SqlUtil::appendValue(queryString, "id", id);

        DSqlQuery query(_db);
        query.exec(queryString);

        if (query.next())
            escrituracao = this->montarObjEscrituracao(query);

        query.finish();
        return escrituracao;
    }

    QList<Escrituracao*> EscrituracaoDao::recuperarEscrituracoes()
    {
        QList<Escrituracao*> listaEscrituracoes;
        QString queryString = SELECT_PRINCIPAL_ESCRITURACAO;

        DSqlQuery query(_db);
        query.exec(queryString);

        while(query.next())
            listaEscrituracoes << this->montarObjEscrituracao(query);

        query.finish();
        return listaEscrituracoes;
    }

    QList<DbManager::InformacoesCampos> EscrituracaoDao::montarCamposEscrituracao(Escrituracao* escrituracao)
    {
        QList<DbManager::InformacoesCampos> informacoesCampo;
        DbManager::InformacoesCampos campo;

        campo.nomeCampo = "ano";
        campo.valor = escrituracao->ano();
        campo.tipoCampo = DbManager::NUMERICO;
        informacoesCampo << campo;

        campo.nomeCampo = "cnpjRaizEmpresa";
        campo.valor = escrituracao->cnpjRaizEmpresa();
        campo.tipoCampo = DbManager::TEXTO;
        informacoesCampo << campo;

        campo.nomeCampo = "cnpj";
        campo.valor = escrituracao->cnpj();
        campo.tipoCampo = DbManager::TEXTO;
        informacoesCampo << campo;

        campo.nomeCampo = "descricaoFilial";
        campo.valor = escrituracao->descricaoFilial();
        campo.tipoCampo = DbManager::TEXTO;
        informacoesCampo << campo;

        campo.nomeCampo = "inscricaoEstadual";
        campo.valor = escrituracao->inscricaoEstadual();
        campo.tipoCampo = DbManager::BIGINT;
        informacoesCampo << campo;

        campo.nomeCampo = "nomeDatabase";
        campo.valor = escrituracao->nomeDatabase();
        campo.tipoCampo = DbManager::TEXTO;
        informacoesCampo << campo;

        campo.nomeCampo = "fechado";
        campo.valor = escrituracao->fechado();
        campo.tipoCampo = DbManager::BOOLEAN;
        informacoesCampo << campo;

        campo.nomeCampo = "data";
        campo.valor = escrituracao->data();
        campo.tipoCampo = DbManager::DATA_HORA;
        informacoesCampo << campo;

        return informacoesCampo;
    }

    Escrituracao* EscrituracaoDao::montarObjEscrituracao(DSqlQuery& query)
    {
        Escrituracao* escrituracao = new Escrituracao();

        escrituracao->setId(query.getInt("id"));
        escrituracao->setAno(query.getInt("ano"));
        escrituracao->setCnpjRaizEmpresa(query.getString("cnpjRaizEmpresa"));
        escrituracao->setCnpj(query.getString("cnpj"));
        escrituracao->setDescricaoFilial(query.getString("descricaoFilial"));
        escrituracao->setInscricaoEstadual(query.getLongLong("inscricaoEstadual"));
        escrituracao->setNomeDatabase(query.getString("nomeDatabase"));
        escrituracao->setData(query.getDateTime("data"));

        return escrituracao;
    }

}
