#include "gm_dbutil.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static QString _defaultDriver = driverODBCFreeTDS;
static bool initDriver = false;
static int _staticPID = 0;

static QString HOSTNAME      = "localhost";
static QString NOME_DATABASE = "MASTER";
static QString USERNAME      = "root";
static QString SENHA         = "admin";

namespace gm
{
    DBUtil::DBUtil() {}

    const QString DBUtil::DIRETORIO_DATABASE          = "DADOS";

    const QString DBUtil::DIRETORIO_DATABASE_ABERTOS  = "ABERTOS";

    const QString DBUtil::DIRETORIO_DATABASE_FECHADOS = "FECHADOS";

    QSqlDatabase DBUtil::configurarBanco(QString database, BancoDados banco)
    {
        QSqlDatabase conexao;
        static bool jaPasseiAqui = false;

        if (jaPasseiAqui)
            return conexao;

        if (banco == MASTER)
            database = NOME_DATABASE;

        QString diretorioDatabase = DIRETORIO_DATABASE;
        QString diretorioAplicacao = QApplication::applicationDirPath() + QDir::separator() + diretorioDatabase;

        QDir diretorio;

        if (!QDir(diretorioAplicacao).exists())
            diretorio.mkdir(diretorioDatabase);

        diretorio.setPath(diretorioDatabase);

        QString databaseName = diretorio.path() + QDir::separator() + database;
        conexao = QSqlDatabase::database(databaseName, true);

        if (!conexao.isValid()){
            if (!initDriver) {
                initDriver = true;
#ifdef Q_OS_LINUX
                _defaultDriver = driverODBCFreeTDS;
#else
                _defaultDriver = driverODBCMicrosoft;
#endif
            }

            if(!conexao.database().isValid())
                conexao = QSqlDatabase::addDatabase(_defaultDriver);

            conexao = definirParametrosConexao(conexao, databaseName);
            conexao.open();

            if(!conexao.isOpen())
                qDebug() << "Nao foi possivel estabelecer uma ligacao com a base de dados.";

#ifdef QT_DEBUG
            qDebug() << QString("Inicializado com sucesso. Parâmetros de conexão: %1").arg(conexao.databaseName());
#endif

            jaPasseiAqui = true;
        }

        return conexao;
    }

    QSqlDatabase DBUtil::configurarBancoSecundario(QString database, QString pathBancoLeitura)
    {
        QSqlDatabase conexao;
        static bool jaPasseiAquiSecond = false;

        if (jaPasseiAquiSecond)
            return conexao;

        QString diretorioDatabase = DIRETORIO_DATABASE;
        // QString diretorioAplicacao = QApplication::applicationDirPath() + QDir::separator() + diretorioDatabase;

        QString databaseName = diretorioDatabase + QDir::separator() + pathBancoLeitura + QDir::separator() + database;
        conexao = QSqlDatabase::database(databaseName, true);

        if (!conexao.isValid()){
            if (!initDriver) {
                initDriver = true;
#ifdef Q_OS_LINUX
                _defaultDriver = driverODBCFreeTDS;
#else
                _defaultDriver = driverODBCMicrosoft;
#endif
            }

            // if (!conexao.database().isValid())
            conexao = QSqlDatabase::addDatabase(_defaultDriver);
            conexao = definirParametrosConexao(conexao, databaseName);
            conexao.open();

            if (!conexao.isOpen())
                qDebug() << "Nao foi possivel estabelecer uma ligacao com a base de dados.";

#ifdef QT_DEBUG
            qDebug() << QString("Inicializado com sucesso. Parâmetros de conexão: %1").arg(conexao.databaseName());
#endif

            jaPasseiAquiSecond = true;
        }

        return conexao;
    }

    QString DBUtil::getDatabaseName()
    {
        QString strDiretorio;

        QString diretorioDatabase = DIRETORIO_DATABASE;
        QString diretorioAplicacao = DBUtil::getDiretorioPadraoDataBase() + diretorioDatabase;

        QDir diretorio;

        if (!QDir(diretorioAplicacao).exists())
            diretorio.mkdir(diretorioAplicacao);

        diretorio.setPath(diretorioAplicacao);

        strDiretorio = diretorio.path() + QDir::separator();
        return strDiretorio;
    }

    QSqlDatabase DBUtil::criarDatabase(QString caminho, QString nomePasta, QString database)
    {
        QSqlDatabase conexao;

        if (!initDriver) {
            initDriver = true;
#ifdef Q_OS_LINUX
            _defaultDriver = "QSQLITE";
#else
            _defaultDriver = driverODBCMicrosoft;
#endif
        }

        conexao = QSqlDatabase::addDatabase(_defaultDriver, database);

        QDir diretorio;
        diretorio.setPath(getDiretorioDatabase(caminho, nomePasta));

        conexao = definirParametrosConexao(conexao, diretorio.path() + QDir::separator() + database);

        if (!conexao.open()){
            qDebug() << "Nao foi possivel estabelecer uma ligacao com a base de dados.";
        } else{
#ifdef QT_DEBUG
        qDebug() << QString("parâmetros de conexão: %1").arg(conexao.databaseName());
#endif
        }

        return conexao;
    }

    QString DBUtil::getDiretorioDatabase(QString caminho, QString nomePasta)
    {
        QString strDiretorio;
        QString diretorioAplicacao = caminho + DIRETORIO_DATABASE + QDir::separator() + nomePasta;

        QDir diretorio;

        if(!QDir(diretorioAplicacao).exists())
            diretorio.mkdir(diretorioAplicacao);

        diretorio.setPath(diretorioAplicacao);

        strDiretorio = diretorio.path() + QDir::separator();
        return strDiretorio;
    }

    QSqlDatabase DBUtil::definirParametrosConexao(QSqlDatabase conexao, QString databaseName)
    {
        conexao.setHostName(HOSTNAME);
        conexao.setDatabaseName(databaseName);
        conexao.setUserName(USERNAME);
        conexao.setPassword(SENHA);
        return conexao;
    }

    QString DBUtil::getDiretorioPadraoDataBase()
    {
        QString diretorioPadrao = QApplication::applicationDirPath() + QDir::separator();
        return diretorioPadrao;
    }

    QSqlDatabase DBUtil::conexao(QString databaseName)
    {
        if (databaseName.isEmpty())
            return configurarBanco(databaseName, MASTER);

        return configurarBancoSecundario(databaseName, DIRETORIO_DATABASE_ABERTOS);
    }

    QString DBUtil::nomeConexao(QString nome)
    {
        return nome;
    }
}
