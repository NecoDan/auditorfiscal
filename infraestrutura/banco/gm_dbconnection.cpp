#include "gm_dbconnection.h"

#include <QDebug>

namespace gm
{
    const QString DbConnection::driverODBCFreeTDS = "QSQLITE";

    DbConnection::DbConnection(QObject *parent) : QObject(parent)
    {

    }

    void DbConnection::criarConexao()
    {
        _dbConexao = QSqlDatabase::addDatabase(driverODBCFreeTDS, "MASTER");
        _dbConexao.setDatabaseName("MASTER");
        _dbConexao.open();

        if(!_dbConexao.isOpen())
            qDebug() << "Nao foi possivel estabelecer uma ligacao com a base de dados.";
    }

    void DbConnection::executeQuery(QString queryString)
    {
        QSqlQuery query(_dbConexao);
        query.exec(queryString);
    }

    QSqlDatabase DbConnection::database(QString nomeDatabase)
    {
        Q_UNUSED(nomeDatabase);
    }
}
