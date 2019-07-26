#include "gm_dsqlquery.h"

#include <QDebug>
#include <QSqlRecord>

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"
#include "infraestrutura/conversor.h"

const QString CURRENT_IDENT  = "SELECT @@IDENTITY";

namespace gm
{

    DSqlQuery::DSqlQuery() : QSqlQuery()
    {
        this->setForwardOnly(true);
    }

    DSqlQuery::DSqlQuery(QSqlDatabase db) : QSqlQuery(db)
    {
        _db = db;
        this->setForwardOnly(true);
    }

    /* ############################ Gets e Sets ############################ */

    QStringList DSqlQuery::colunas()
    {
        if(_colunas.isEmpty()) {
            for(int i = 0; i < record().count(); i++) {
                _colunas << record().fieldName(i);
            }
        }
        return _colunas;
    }

    QDate DSqlQuery::getDate(const QString &nomeColuna)
    {
        return value(nomeColuna).toDate();
    }

    QDateTime DSqlQuery::getDateTime(const QString &nomeColuna)
    {
        return value(nomeColuna).toDateTime();
    }

    double DSqlQuery::getDouble(const QString &nomeColuna)
    {
        return value(nomeColuna).toDouble();
    }

    int DSqlQuery::getInt(const QString &nomeColuna)
    {
        return value(nomeColuna).toInt();
    }

    long long DSqlQuery::getLongLong(const QString &nomeColuna)
    {
        return value(nomeColuna).toLongLong();
    }

    QString DSqlQuery::getString(const QString &nomeColuna)
    {
        return value(nomeColuna).toString();
    }

    QTime DSqlQuery::getTime(const QString &nomeColuna)
    {
        return value(nomeColuna).toTime();
    }

    GMErro DSqlQuery::gmErro()
    {
        return _gmErro;
    }

    QVariant DSqlQuery::value(int indexColuna)
    {
        return QSqlQuery::value(indexColuna);
    }

    QVariant DSqlQuery::value(const QString &nomeColuna)
    {
        if(record().indexOf(nomeColuna) < 0) {
#ifdef MODO_HARD
            // qFatal("Campo %s nao especificado na query %s", qPrintable(nomeColuna), qPrintable(lastQuery()));
#else
            return QVariant();
#endif
        }
#if QT_VERSION < 0x050000
        return QSqlQuery::value(record().indexOf(nomeColuna));
#else
        return QSqlQuery::value(nomeColuna);
#endif
    }

    /* ########################## Métodos de Ação ########################## */

    void DSqlQuery::close()
    {
        this->finish();
        this->clear();

        foreach (QString tabela, _tabelasTemporarias){
            QSqlQuery qDeleteTemporarias(_db);
            qDeleteTemporarias.prepare("DROP TABLE " + tabela);

            if (!qDeleteTemporarias.exec()){
                //TODO REVER QDEBUG
                //qDebug() << "Erro ao dropar tabela temporaria:" << tabela << _db.lastError().text();
            }
        }
    }

    QVariant DSqlQuery::currentIdent(QSqlDatabase& db, QString tabela)
    {
        QVariant id = 0;

        if(!db.lastError().isValid()){
            QSqlQuery qLastVal(db);
            qLastVal.prepare(CURRENT_IDENT);
            qLastVal.bindValue(0, tabela);
            qLastVal.exec();

            if(qLastVal.next()){
                id = qLastVal.value(0);
            }

            qLastVal.finish();
        }

        return id;
    }

    void DSqlQuery::debug()
    {
        qDebug() << (executedQuery());
        qDebug() << (lastError().text());
        qDebug() << (boundValues());
    }

    bool DSqlQuery::exec()
    {
        return exec("");
    }

    bool DSqlQuery::exec(const QString& queryString)
    {
        if (headerComments.isEmpty())
            headerComments; // = traceMethod_DSQLQuery(3,"--");

        bool result = false;

        if (queryString.isEmpty()){
            result=QSqlQuery::exec();
        } else{
            QString cmdExecute = this->headerComments.join(";\n");
            cmdExecute += "\n";
            cmdExecute += queryString;
            result=QSqlQuery::exec(cmdExecute);
        }

        _gmErro = this->lastError();

        if (_gmErro.isErro()){
            debug();

//        #ifdef QT_DEBUG
//            qFatal("SQLStrings::db()==invalido");
//        #endif
        }

#ifdef QT_DEBUG
        QString filename = QString("%1/queries.sql").arg(QDir::homePath());
        QFile file(filename);

        if(file.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out(&file);
            out << executedQuery() << "\n\n";
            out << lastError().text() << "\n\n";
        }

        file.close();
#endif

        return result;
    }

    bool DSqlQuery::prepare(const QString &query)
    {
        this->headerComments; // = traceMethod_DSQLQuery(4,"--");

        QString cmdExecute = this->headerComments.join(";\n");
        cmdExecute += "\n";
        cmdExecute += query;

        return QSqlQuery::prepare(cmdExecute);
    }

    bool DSqlQuery::execBatch(QSqlQuery::BatchExecutionMode mode)
    {
        bool result = QSqlQuery::execBatch(mode);
        _gmErro = this->lastError();

        if (_gmErro.isErro())
            debug();

        return result;
    }

    QString DSqlQuery::generateNameTempTable(QString prefix)
    {
        double numeroRandomico = qrand() % ((10000000 + 1) - 1) + 1;
        QString numeroRandomicoString = QString::number(numeroRandomico);
        QString dataMomento = QDateTime::currentDateTime().toString("ddMMyyhhmmsszzz");

        while (prefix.startsWith("#"))
            prefix.remove(0, 1);

         QString nomeTabela = "#" + prefix + numeroRandomicoString + dataMomento;

         _tabelasTemporarias << nomeTabela;

         return nomeTabela;
    }
}
