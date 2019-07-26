#ifndef GM_DBCONNECTION_H
#define GM_DBCONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace gm
{
    class DbConnection : public QObject
    {
            Q_OBJECT

        public:

            explicit DbConnection(QObject *parent = nullptr);

            static const QString driverODBCFreeTDS;

        public slots:

            void criarConexao();

            void executeQuery(QString queryString = QString());

        private:

            QSqlDatabase _dbConexao;

            QSqlDatabase database(QString nomeDatabase);

        signals:

    };
}


#endif // GM_DBCONNECTION_H
