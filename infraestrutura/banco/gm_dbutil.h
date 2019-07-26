#ifndef GM_DBUTIL_H
#define GM_DBUTIL_H

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQuery>

static const QString driverODBCFreeTDS = "QSQLITE";
static const QString driverODBCMicrosoft = "QSQLITE";

namespace gm
{
    class DBUtil
    {

     public:

        /* ############################## Constantes ############################ */

        enum BancoDados { DEFAULT = 0, MASTER  = 1 };

        static const QString DIRETORIO_DATABASE;

        static const QString DIRETORIO_DATABASE_ABERTOS;

        static const QString DIRETORIO_DATABASE_FECHADOS;

        /*#################################### Métodos de Ação ###################################*/

        /**
         * @author  Ueider Moraes, Daniel Santos
         * @author  03/07/2018
         * @brief   conexao função que retorna uma conexão com o banco de dados especificado
         * @param   banco o banco de dados ao qual deseja-se estabelecer uma conexão
         * @return  uma conexão com o banco de dados especificado
         */
        static QSqlDatabase conexao(QString databaseName="");

        /**
         * @author  Ueider Moraes, Daniel Santos
         * @date    03/07/2018
         * @brief   nomeConexao função que retorna o nome da conexão que será definida com um determinado banco de dados
         * @param   banco o enum do tipo BancoDados
         * @return  o nome da conexão que será definida com um determinado banco de dados
         */
        static QString nomeConexao(QString nome);

        /**
         * @author  Ueider Moraes, Daniel Santos
         * @date    03/07/2018
         * @brief   configurarBanco função que define as configuracoes necessarias para conexao com o banco de dados,
         *          tais como: usuario, senha, porta, etc
         * @param   banco o enum do tipo BancoDados
         * @return  um objeto QSqlDatabase configurado e pronto para conexão com o banco especificado
         */
        static QSqlDatabase configurarBanco(QString database="", BancoDados banco=BancoDados::DEFAULT);

        /**
         * @author  Ueider Moraes, Daniel Santos
         * @date    03/07/2018
         * @brief   configurarBanco função que define as configuracoes necessarias para conexao com o banco de dados,
         *          tais como: usuario, senha, porta, etc
         * @param   banco o enum do tipo BancoDados
         * @return  um objeto QSqlDatabase configurado e pronto para conexão com o banco especificado
         */
        static QSqlDatabase configurarBancoSecundario(QString database="", QString pathBancoLeitura = QString());

        /**
         * @author  Daniel Santos
         * @date    03/07/2018
         * @brief   getDatabaseName
         * @return  um objeto QString
         */
        static QString getDatabaseName();

        static QSqlDatabase criarDatabase(QString caminho, QString nomePasta, QString database);

        static QString getDiretorioDatabase(QString caminho, QString nomePasta);

        static QSqlDatabase definirParametrosConexao(QSqlDatabase conexao, QString databaseName);

        static QString getDiretorioPadraoDataBase();

        private:

            DBUtil();
    };
}

#endif // GM__H
