#include "dbmanager.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"
#include "infraestrutura/banco/gm_dsqlquery.h"
#include "infraestrutura/banco/gm_sqlutil.h"

const QString NAME_TABELA_ESCRITURACAO      = "ESCRITURACAO";
const QString NAME_TABELA_DIRETORIO_PADRAO  = "DIRETORIO_PADRAO";
const QString NAME_TABELA_ESCRITURACAO_SPED = "ESCRITURACAO_SPED";
const QString NAME_TABELA_ESCRITURACAO_SPED_MOVIMENTOS = "ESCRITURACAO_SPED_MOVIMENTOS";

using namespace gm;

DbManager::DbManager()
{
}

DbManager::DbManager(QSqlDatabase &db)
{
    _db = db;
}

DbManager::DbManager(QSqlDatabase &db, bool carregaAmbientePadrao)
{
    _db = db;

    if (carregaAmbientePadrao)
        this->criarAmbienteDatabasePadrao();
}

GMErro DbManager::lastError()
{
    return _lastError;
}

void DbManager::setDatabase(QSqlDatabase &db)
{
    _db = db;
}

void DbManager::closeDatabase()
{
    _db.close();
}

void DbManager::criarAmbienteDatabasePadrao()
{
    if (!isTabelaExiste(NAME_TABELA_ESCRITURACAO))
        this->criarTabelaEscrituracaoMaster(NAME_TABELA_ESCRITURACAO);

    if (!isTabelaExiste(NAME_TABELA_DIRETORIO_PADRAO))
        this->criarTabelaDiretorioPadraoMaster(NAME_TABELA_DIRETORIO_PADRAO);
}

void DbManager::criarAmbienteApuracaoEscrituracao()
{
    if (!_db.open())
        return;

    if (!isTabelaExiste(NAME_TABELA_ESCRITURACAO_SPED)){
        QList<InformacoesCampos> informacoesCampo;

        informacoesCampo << getInformacoesCampos("ano", INT, 4, true);
        informacoesCampo << getInformacoesCampos("mes", INT, 2, true, true);
        informacoesCampo << getInformacoesCampos("cnpj", TEXTO, 14, true);
        informacoesCampo << getInformacoesCampos("fiscal", BOOLEAN, 1);
        informacoesCampo << getInformacoesCampos("nao_fiscal_saldo", BOOLEAN, 1);
        informacoesCampo << getInformacoesCampos("nao_fiscal_movimentacao", BOOLEAN, 1);
        informacoesCampo << getInformacoesCampos("caminho_arquivo", TEXTO, 100);
        informacoesCampo << getInformacoesCampos("data", DATA_HORA);

        if (!criarTabela(NAME_TABELA_ESCRITURACAO_SPED, informacoesCampo))
            this->outPutDebug("Erro ao criar TABELA " + NAME_TABELA_ESCRITURACAO_SPED + ".");
    }

    if (!isTabelaExiste(NAME_TABELA_ESCRITURACAO_SPED_MOVIMENTOS)){
        QList<InformacoesCampos> informacoesCampo;

        informacoesCampo << getInformacoesCampos("cod_produto", BIGINT, 4, true);
        informacoesCampo << getInformacoesCampos("desc_produto", TEXTO, 300, true);
        informacoesCampo << getInformacoesCampos("qtde", NUMERICO, 15);
        informacoesCampo << getInformacoesCampos("unidade_medida", TEXTO, 2);
        informacoesCampo << getInformacoesCampos("valor_total", NUMERICO, 15);
        informacoesCampo << getInformacoesCampos("data", DATA_HORA);

        if (!criarTabela(NAME_TABELA_ESCRITURACAO_SPED_MOVIMENTOS, informacoesCampo))
            this->outPutDebug("Erro ao criar TABELA " + NAME_TABELA_ESCRITURACAO_SPED_MOVIMENTOS + ".");
    }
}

bool DbManager::criarTabela(QString nomeTabela, QList<InformacoesCampos> listaInformacoesCampos)
{
    if (isTabelaExiste(nomeTabela)){
        _lastError = GMErro("Tabela " + nomeTabela + " já existe. Tente outro nome.", GMErro::VALIDACAO);
        this->outPutDebug(_lastError.mensagem());
        return false;
    }

    bool success = false;
    int numRows = 0;

    QSqlQuery query(_db);
    QString queryStringSQL = "CREATE TABLE :name (";
    queryStringSQL.append("id INTEGER PRIMARY KEY AUTOINCREMENT, ");

    foreach (InformacoesCampos informacoes, listaInformacoesCampos){
        double size = informacoes.tamanhoCampo;
        bool invalidoTamanhoCampo = (size <= 0 && informacoes.tipoCampo != TiposCampos::DATA
                && informacoes.tipoCampo != TiposCampos::DATA_HORA && informacoes.tipoCampo != TiposCampos::BOOLEAN);

        if (invalidoTamanhoCampo){
            _lastError = GMErro("Tamanho do campo " + informacoes.nomeCampo + " é inválido.", GMErro::BANCO);
            return success;
        }

        queryStringSQL.append(informacoes.nomeCampo);
        queryStringSQL.append(getTipoCampo(informacoes.tipoCampo, size));
        queryStringSQL.append(informacoes.notNull ? " NOT NULL " : " ");
        queryStringSQL.append(informacoes.chaveUnica ? " UNIQUE " : " ");

        if (++numRows < listaInformacoesCampos.size())
            queryStringSQL.append(", ");
    }

    queryStringSQL.append(");");
    queryStringSQL.replace(":name", nomeTabela);
    this->outPutDebug(queryStringSQL);

    if (query.exec(queryStringSQL))
        success = true;

    if (!success){
        _lastError = GMErro("Erro ao criar tabela: " + query.lastError().text(), GMErro::BANCO);
        this->outPutDebug("criarTabela erro:  " + query.lastError().text());
    }

    query.finish();
    return success;
}

bool DbManager::isTabelaExiste(QString nomeTabela)
{
    bool success = false;
    QSqlQuery query(_db);
    QString sql = "SELECT name FROM sqlite_master WHERE type='table' AND name=':nomeTabela';";

    sql.replace(":nomeTabela", nomeTabela);

    if (!query.exec(sql)){
        _lastError = GMErro("Erro ao verificar se tabela existe: " + query.lastError().text(), GMErro::BANCO);
        this->outPutDebug("verificarSeTabelaExiste erro:  " + query.lastError().text());
    }

    while (query.next())
        success = true;

    query.finish();
    return success;
}

long long DbManager::addRegistro(QString nomeTabela, QList<InformacoesCampos> listaCampos)
{
    long long id = 0;
    bool successInsert = false;

    if (!isTabelaExiste(nomeTabela)){
        _lastError = GMErro("A tabela " + nomeTabela + " ainda não existe. Crie antes para inserir nela.", GMErro::VALIDACAO);
        return false;
    }

    // bool isConexaoValida = queryParam.isValid();
    // QSqlQuery query;

    // if(!isConexaoValida){
    //     query = QSqlQuery(_db);
    // }

    int numRows = 0;
    QSqlQuery query(_db);
    QString sql = " INSERT INTO " + nomeTabela + " ( ";

    foreach (InformacoesCampos campo, listaCampos){
        numRows++;
        sql.append(campo.nomeCampo);
        sql.append(toStringAppendLimitadorSqlQuery(numRows, listaCampos.size()));
    }

    this->outPutDebug(sql);
    numRows = 0;
    sql.append("VALUES (");
    this->outPutDebug(sql);

    foreach (InformacoesCampos campo, listaCampos){
        numRows++;
        sql.append(toStringValueSqlQuery(campo));
        sql.append(toStringAppendLimitadorSqlQuery(numRows, listaCampos.size()));
    }

    this->outPutDebug("insert " + sql);
    successInsert = query.exec(sql);

    if (!successInsert){
        _lastError = GMErro("Erro ao criar addRegistro: " + query.lastError().text(), GMErro::BANCO);
        this->outPutDebug("addRegistro erro:  " + _lastError.mensagem());
    }

    if (successInsert)
        id = query.lastInsertId().toLongLong();

    //if (!isConexaoValida)
    query.finish();

    return id;
}

bool DbManager::updateRegistro(QString nomeTabela, QList<DbManager::InformacoesCampos> listaCampos, long long id)
{
    bool successUpdate = false;

    if (!isTabelaExiste(nomeTabela)){
        _lastError = GMErro("A tabela " + nomeTabela + " ainda não existe. Crie antes para inserir nela.", GMErro::VALIDACAO);
        return successUpdate;
    }

    if (id <= 0){
        _lastError = gm::GMErro("O id do registro está zerado. Para executar o UPDATE, insira um id válido.", gm::GMErro::VALIDACAO);
        return successUpdate;
    }

    int numRows = 0;
    QSqlQuery query(_db);
    QString queryStringSQL = " UPDATE " + nomeTabela + " SET ";

    foreach (InformacoesCampos campo, listaCampos){
        numRows++;
        queryStringSQL.append(campo.nomeCampo + " = ");
        queryStringSQL.append(toStringValueSqlQuery(campo));

        if (numRows < listaCampos.size())
            queryStringSQL.append(", ");
    }

    queryStringSQL.append(" WHERE id = " + QString::number(id) + ";");
    successUpdate = query.exec(queryStringSQL);

    if (!successUpdate){
        _lastError = GMErro("Erro ao atualizar updateRegistro: " + query.lastError().text(), GMErro::BANCO);
        this->outPutDebug("updateRegistro erro:  " + _lastError.mensagem());
    }

    query.finish();
    return successUpdate;
}

bool DbManager::removeRegistro(QString nomeTabela, long long id)
{
    bool successRemove = false;

    if (!isTabelaExiste(nomeTabela)){
        _lastError = GMErro("A tabela " + nomeTabela + " ainda não existe. Crie antes para inserir nela.", GMErro::VALIDACAO);
        return successRemove;
    }

    QSqlQuery query(_db);
    QString queryStringSQL = " DELETE ESCRITURACAO WHERE id = " + QString::number(id) + ";";
    successRemove = query.exec(queryStringSQL);

    if (!successRemove){
        _lastError = gm::GMErro("Erro deletar registro em ESCRITURACAO: " + query.lastError().text(), gm::GMErro::BANCO);
        this->outPutDebug("removeRegistroEscrituracao erro:  " + _lastError.mensagem());
    }

    query.finish();
    return successRemove;
}

//long long DbManager::addRegistro(QString nomeTabela, QList<DbManager::InformacoesCampos> listaCampos)
//{
//    QSqlQuery query(_db);
//    bool isSuccess = addRegistro(nomeTabela, listaCampos, query);
//    query.finish();

//    if(!isSuccess)
//        return 0;
//    else
//        return query.lastInsertId().toLongLong();
//}

void DbManager::criarTabelaEscrituracaoMaster(QString nomeTabela)
{
    QList<InformacoesCampos> listaInformacoes;

    listaInformacoes << getInformacoesCampos("ano", BIGINT, 4, true);
    listaInformacoes << getInformacoesCampos("cnpjRaizEmpresa", TEXTO, 14, true);
    listaInformacoes << getInformacoesCampos("cnpj", TEXTO, 14, true);
    listaInformacoes << getInformacoesCampos("descricaoFilial", TEXTO, 150);
    listaInformacoes << getInformacoesCampos("inscricaoEstadual", BIGINT, 15);
    listaInformacoes << getInformacoesCampos("nomeDatabase", TEXTO, 100);
    listaInformacoes << getInformacoesCampos("fechado", BOOLEAN);
    listaInformacoes << getInformacoesCampos("data", DATA_HORA);

    if (!criarTabela(nomeTabela, listaInformacoes))
        this->outPutDebug("Erro ao criar TABELA " + nomeTabela + ".");
}

void DbManager::criarTabelaDiretorioPadraoMaster(QString nomeTabela)
{
    QList<InformacoesCampos> informacoesCampo;
    informacoesCampo << getInformacoesCampos("caminho", TEXTO, 200);
    informacoesCampo << getInformacoesCampos("data", DATA_HORA);

    if (!criarTabela(nomeTabela, informacoesCampo))
        this->outPutDebug("erro ao criar TABELA " + nomeTabela + ".");
}

DbManager::InformacoesCampos DbManager::getInformacoesCampos(QString nomeCampo, DbManager::TiposCampos tipoCampo,
                                                             long long tamanhoCampo, bool notNull, bool chaveUnica)
{
    InformacoesCampos informacoes;

    informacoes.nomeCampo = nomeCampo;
    informacoes.tipoCampo = tipoCampo;
    informacoes.tamanhoCampo = tamanhoCampo;
    informacoes.notNull = notNull;
    informacoes.chaveUnica = chaveUnica;

    return informacoes;
}

QString DbManager::getTipoCampo(DbManager::TiposCampos tipo, long long tamanho)
{
    QString tipoString;

    switch(tipo)
    {
    case NUMERICO:
        tipoString = " NUMERIC (" + QString::number(tamanho) + ",2) ";
        break;
    case TEXTO:
        tipoString = " VARCHAR (" + QString::number(tamanho) + ",5) ";
        break;
    case DATA:
        tipoString = " DATE ";
        break;
    case DATA_HORA:
        tipoString = " DATETIME DEFAULT CURRENT_TIMESTAMP ";
        break;
    case BIGINT:
        tipoString = " BIGINT (" + QString::number(tamanho) + ") ";
        break;
    case INT:
        tipoString = " INTEGER ";
        break;
    case BOOLEAN:
        tipoString = " SMALLINT ";
        break;
    }

    return tipoString;
}

QString DbManager::toStringValueSqlQuery(InformacoesCampos campo)
{
    QString strValue;

    switch(campo.tipoCampo){
        case NUMERICO:
            strValue = QString::number(campo.valor.toInt());
            break;
        case BIGINT:
            strValue = QString::number(campo.valor.toLongLong());
            break;
        case TEXTO:
            strValue = gm::SqlUtil::quoteValue(campo.valor.toString());
            break;
        case BOOLEAN:
            strValue = (campo.valor.isValid() && campo.valor.toBool() == Qt::Checked) ? strValue = QString::number(1) : strValue = QString::number(0);
            break;
        case DATA:
            (!campo.valor.isValid()) ? strValue = "DATE('NOW')" : strValue = gm::SqlUtil::quoteValue(gm::SqlUtil::dateToSqlFormat(campo.valor.toDate()));
            break;
        case DATA_HORA:
            (!campo.valor.isValid()) ? strValue = "DATE('NOW')" : strValue = gm::SqlUtil::quoteValue(gm::SqlUtil::dateToSqlFormat(campo.valor.toDateTime()));
            break;
    }

    return strValue;
}

QString DbManager::toStringAppendLimitadorSqlQuery(int valorColunaTabela, int tamanho)
{
    QString strValueDelimitador;
    (valorColunaTabela < tamanho) ? strValueDelimitador = ", " : strValueDelimitador = ") ";

    return strValueDelimitador;
}

void DbManager::outPutDebug(QVariant value)
{
    qDebug() << value.toString();
}
