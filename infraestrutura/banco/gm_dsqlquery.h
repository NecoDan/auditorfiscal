#ifndef GM_DSQLQUERY_H
#define GM_DSQLQUERY_H

#include "infraestrutura/gm_erro.h"
#include "infraestrutura/banco/gm_dbutil.h"

#include <QDate>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>

namespace gm
{
    class DSqlQuery : public QSqlQuery
    {
    public:


        explicit DSqlQuery();

        explicit DSqlQuery(QSqlDatabase db);

        /* ############################ Gets e Sets ############################ */

        QStringList colunas();

        QDate getDate(const QString &nomeColuna);

        QDateTime getDateTime(const QString &nomeColuna);

        double getDouble(const QString &nomeColuna);

        int getInt(const QString &nomeColuna);

        long long getLongLong(const QString &nomeColuna);

        QString getString(const QString &nomeColuna);

        QTime getTime(const QString &nomeColuna);

        gm::GMErro gmErro();

        QVariant value(int indexColuna);

        QVariant value(const QString &nomeColuna);

        /* ########################## Métodos de Ação ########################## */

        void close();

        QVariant currentIdent(QSqlDatabase& db, QString tabela);

        void debug();

        bool exec();

        bool exec(const QString& queryString);

        bool prepare(const QString& query);

        /**
         * @author Allyx, Rayrone
         * @date   05/10/2015
         * @brief  execBatch
         * @param  mode
         * @return
         */
        bool execBatch(BatchExecutionMode mode = ValuesAsRows);

    public:

        QStringList headerComments;

        QString generateNameTempTable(QString prefix="");

    private:

        /* ############################## Atributos ############################ */

        QStringList         _colunas;
        gm::GMErro          _gmErro;
        QStringList         _tabelasTemporarias;
        QSqlDatabase        _db;
    };
}

#endif // GM_DSQLQUERY_H
