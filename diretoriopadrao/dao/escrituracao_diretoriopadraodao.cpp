#include "escrituracao_diretoriopadraodao.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"
#include "infraestrutura/banco/dbmanager.h"

#include "diretoriopadrao/dominio/escrituracao_diretoriopadrao.h"

using namespace gm;

const QString TABELA_DIRETORIO_PADRAO = "DIRETORIO_PADRAO";

namespace gm_escrituracao
{
    DiretorioPadraoDAO::DiretorioPadraoDAO(QObject *parent) : QObject(parent)
    {
        _db = DBUtil::conexao();
        _lastError = GMErro();
    }

    DiretorioPadraoDAO::DiretorioPadraoDAO(QSqlDatabase& db, QObject *parent) : QObject(parent)
    {
        _db = db;
        _lastError = GMErro();
    }

    gm::GMErro DiretorioPadraoDAO::lastError()
    {
        return _lastError;
    }

    void DiretorioPadraoDAO::salvarDiretorioPadrao(DiretorioPadrao *diretorio)
    {
        DbManager dbManager(_db);
        QList<DbManager::InformacoesCampos> listaCampos = montarCamposDiretorioPadrao(diretorio);

        if(diretorio->id() == 0)
            long long id = dbManager.addRegistro(TABELA_DIRETORIO_PADRAO, listaCampos);
        else
            dbManager.updateRegistro(TABELA_DIRETORIO_PADRAO, listaCampos, diretorio->id());

        if(dbManager.lastError().isErro())
        {
            _lastError = dbManager.lastError();
        }

        qDebug() << "id do diretorio" << diretorio->id();
    }

    DiretorioPadrao *DiretorioPadraoDAO::recuperar()
    {
        DbManager dbManager(_db);
        DiretorioPadrao* diretorio = nullptr;

        if (!dbManager.isTabelaExiste(TABELA_DIRETORIO_PADRAO)){
            _lastError = GMErro("A tabela DIRETORIO_PADRAO ainda não existe. Crie antes para inserir nela.", GMErro::VALIDACAO);
            return nullptr;
        }

        QSqlQuery query(_db);
        QString queryStringSQL = " SELECT * FROM DIRETORIO_PADRAO;  ";

        if(!query.exec(queryStringSQL))
        {
            _lastError = GMErro("Erro recuperar DIRETORIO_PADRAO: " + query.lastError().text(), GMErro::BANCO);
            qDebug() << "DiretorioPadraoDAO::recuperar erro:  " + _lastError.mensagem();
        }

        while(query.next())
        {
            diretorio = new DiretorioPadrao;
            diretorio->setId(query.value(0).toLongLong());
            diretorio->setCaminho(query.value(1).toString());
            diretorio->setData(query.value(2).toDateTime());
        }

        query.finish();
        return diretorio;
    }

    QList<DbManager::InformacoesCampos> DiretorioPadraoDAO::montarCamposDiretorioPadrao(DiretorioPadrao *diretorio)
    {
        QList<DbManager::InformacoesCampos> listaCampos;
        DbManager::InformacoesCampos campo;

        campo.nomeCampo = "caminho";
        campo.valor = diretorio->caminho();
        campo.tipoCampo = DbManager::TEXTO;
        listaCampos << campo;

        campo.nomeCampo = "data";
        campo.valor = QDateTime::currentDateTime();
        campo.tipoCampo = DbManager::DATA_HORA;
        listaCampos << campo;

        return listaCampos;
    }

} // namespace gm_escrituracao
