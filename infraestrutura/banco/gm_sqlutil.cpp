#include "gm_sqlutil.h"

// Infraestrutura
#include "infraestrutura/conversor.h"

namespace gm
{
    SqlUtil::SqlUtil() { }

    void SqlUtil::appendBetweenValues(QString& queryString, const QString column, QVariant value1, QVariant value2)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " BETWEEN ");
        appendValue(queryString, value1);
        queryString.append(" AND ");
        appendValue(queryString, value2);
    }

    void SqlUtil::appendInValues(QString& queryString, const QString column, QString values)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " IN " + values);
    }

    void SqlUtil::appendIsNull(QString& queryString, const QString column)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " IS NULL ");
    }

    void SqlUtil::appendIsNotNull(QString& queryString, const QString column)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " IS NOT NULL ");
    }

    void SqlUtil::appendNotInValues(QString& queryString, const QString column, QString values)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " NOT IN " + values);
    }

    void SqlUtil::appendValue(QString& queryString, const QVariant& value)
    {
        if(value.isNull())
        {
            return;
        }

        switch((int)value.type())
        {
            case QVariant::Date:
                queryString.append(dateToSqlFormat(value.toDate(), true));
            break;

            case QVariant::DateTime:
                queryString.append(dateToSqlFormat(value.toDateTime(), true));
            break;

            case QVariant::String:
                queryString.append(quoteValue(value.toString()));
            break;
            case QVariant::Char:
                queryString.append(quoteValue(value.toChar()));
            break;

            default:
                queryString.append(value.toString());
            break;
        }
    }

    void SqlUtil::appendValue(QString& queryString, const QString column, QVariant value)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " = ");
        appendValue(queryString, value);
    }

    void SqlUtil::appendValueLike(QString& queryString, const QString column, QVariant value)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " LIKE ");
        appendValue(queryString,value);
    }

    void SqlUtil::appendValueDiferent(QString& queryString, const QString column, QVariant value)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " != ");
        appendValue(queryString, value);
    }

    void SqlUtil::appendValueGreaterOrEqual(QString& queryString, const QString column, QVariant value)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " >= ");
        appendValue(queryString, value);
    }

    void SqlUtil::appendValueGreaterThan(QString& queryString, const QString column, QVariant value)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " > ");
        appendValue(queryString, value);
    }

    void SqlUtil::appendValueLessOrEqual(QString& queryString, const QString column, QVariant value)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " <= ");
        appendValue(queryString, value);
    }

    void SqlUtil::appendValueLessThan(QString& queryString, const QString column, QVariant value)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " < ");
        appendValue(queryString, value);
    }

    void SqlUtil::appendValueNotEqual(QString &queryString, const QString column, QVariant value)
    {
        appendWhereOrAnd(queryString);
        queryString.append(column + " <> ");
        appendValue(queryString, value);
    }

    void SqlUtil::appendInnerJoin(QString &queryString, const QString table, const QString firstValue, const QString secondValue, bool withNolock)
    {
        queryString.append(" INNER JOIN " + table + (withNolock? " WITH (NOLOCK) ON " : " ON ") + "(" + firstValue + " = " + secondValue + ")");
    }

    void SqlUtil::appendInnerJoinMultipleOn(QString &queryString, const QString table, const QMap<QString, QString> onKeyValues, bool withNolock)
    {
        QString innerJoin;
        innerJoin.append(" INNER JOIN " + table + (withNolock? " WITH (NOLOCK) ON " : " ON "));

        QList<QString> keys = onKeyValues.keys();

        for (int i = 0; i < keys.size(); i++)
        {
            innerJoin.append("(" + keys.at(i) + " = " + onKeyValues.value(keys.at(i)) + ")");
            if (i < keys.size() - 1)
            {
                innerJoin.append(" AND ");
            }
        }

        queryString.append(innerJoin);
    }

    void SqlUtil::appendLeftJoin(QString &queryString, const QString table, const QString firstValue, const QString secondValue, bool withNolock)
    {
        queryString.append(" LEFT JOIN " + table + (withNolock? " WITH (NOLOCK) ON " : " ON ") + "(" + firstValue + " = " + secondValue + ")");
    }

    void SqlUtil::appendLeftJoinMultipleOn(QString &queryString, const QString table, const QMap<QString, QString> onKeyValues, bool withNolock)
    {
        QString leftJoin;
        leftJoin.append(" LEFT JOIN " + table + (withNolock? " WITH (NOLOCK) ON " : " ON "));

        QList<QString> keys = onKeyValues.keys();

        for (int i = 0; i < keys.size(); i++)
        {
            leftJoin.append("(" + keys.at(i) + " = " + onKeyValues.value(keys.at(i)) + ")");
            if (i < keys.size() - 1)
            {
                leftJoin.append(" AND ");
            }
        }

        queryString.append(leftJoin);
    }

    void SqlUtil::appendColumn(QString &queryString, QString column)
    {
        if (queryString.contains("FROM"))
        {
            queryString.replace("FROM", " , " + column + " FROM ");
        }
    }

    void SqlUtil::appendDateBetween(QString& queryString, QString campoDate, QDate dataInicio, QDate dataFim)
    {
        appendWhereOrAnd(queryString);
        queryString.append(campoDate + " BETWEEN "+ SqlUtil::quoteValue(SqlUtil::toDateTimeStart(dataInicio)) + " AND " + SqlUtil::quoteValue(SqlUtil::toDateTimeEnd(dataFim)));
    }

    void SqlUtil::appendStringOnWhere(QString &queryString, QString string)
    {
        appendWhereOrAnd(queryString);
        queryString.append(string);
    }

    void SqlUtil::appendGroupBy(QString &queryString, QStringList campos)
    {
        QString group;

        for (int i = 0; i < campos.size() ; i++ )
        {
            if((i + 1) == campos.size())
                group += campos.at(i);
            else
                group += campos.at(i) + ", ";
        }

        group.push_front(" GROUP BY ");
        queryString.append(group);
    }

    void SqlUtil::appendOrderBy(QString &queryString, QStringList campos)
    {
        QString group;

        for (int i = 0; i < campos.size() ; i++ )
        {
            if((i + 1) == campos.size())
                group += campos.at(i);
            else
                group += campos.at(i) + ", ";
        }

        group.push_front(" ORDER BY ");
        queryString.append(group);
    }

    void SqlUtil::appendWhereOrAnd(QString& queryString)
    {
        if(!hasWhere(queryString))
        {
            queryString.append(" WHERE ");
        }
        else
        {
            queryString.append(" AND ");
        }
    }

    QString SqlUtil::dateToSqlFormat(QDate data, bool quote)
    {
       return quote ? quoteValue(data.toString("yyyy-MM-dd")) : data.toString("yyyy-MM-dd");
    }

    QString SqlUtil::dateToSqlFormat(QDateTime data, bool quote)
    {
       return quote ? quoteValue(data.toString("yyyy-MM-dd hh:mm:ss")) : data.toString("yyyy-MM-dd hh:mm:ss");
    }

    bool SqlUtil::endsWithWhere(QString sql)
    {
        QString str = sql.trimmed().toLower();
        return str.endsWith(" where");
    }

    bool SqlUtil::hasWhere(QString sql)
    {
        return sql.toLower().trimmed().contains(" where")
               || sql.toLower().trimmed().startsWith("where ")
               || sql.toLower().trimmed().startsWith("where\n");
    }

    QString SqlUtil::quoteValue(QVariant value)
    {
        return "'"+ value.toString().trimmed() + "'";
    }

    QString SqlUtil::toDateTimeStart(QDate date)
    {
        return (dateToSqlFormat(date) + " 00:00:00:000");
    }

    QString SqlUtil::toDateTimeEnd(QDate date)
    {
        return (dateToSqlFormat(date) + " 23:59:59.990");
    }

    QString SqlUtil::toSqlList(QList<int> list, bool quote)
    {
        QStringList values;

        foreach (int value, list)
        {
            values << QString::number(value);
        }

        return toSqlList(values, quote);
    }

    QString SqlUtil::toSqlList(QList<long long> list, bool quote)
    {
        QStringList values;

        foreach (int value, list)
        {
            values << QString::number(value);
        }

        return toSqlList(values, quote);
    }

    QString SqlUtil::toSqlList(QList<QString> list, bool quote)
    {
        QStringList values;

        foreach (QString value, list)
        {
            values << value;
        }

        return toSqlList(values, quote);
    }

    QString SqlUtil::toSqlList(QList<QVariant> list, bool quote)
    {
        QStringList values;

        foreach (QVariant value, list)
        {
            if(value.type() == QVariant::Double)
            {
                values << QString::number(gm::Conversor::toDouble(value));
            }
            else if(value.type() == QVariant::Int)
            {
                values << QString::number(value.toInt());
            }
            else if(value.type() == QVariant::LongLong)
            {
                values << QString::number(value.toLongLong());
            }
            else if(value.type() == QVariant::Date)
            {
                values << dateToSqlFormat(value.toDate(), true);
            }
            else
            {
                values << quoteValue(value.toString());
            }
        }

        return toSqlList(values, quote);
    }

    QString SqlUtil::toSqlList(QStringList list, bool quote)
    {
        QString sql("");

        if (list.size() == 0)
        {
            return "(null)";
        }

        for (int i = 0; i < list.count() ; i++ )
        {
            QString s = list.value(i);

            if (i == 0)
            {
                sql += "(";
            }

            if (i == list.count() - 1)
            {
                QString pre = quote ? quoteValue(s) : s;
                sql += pre + " )";
            }
            else
            {
                QString pre = quote ? quoteValue(s) : s;
                sql +=  pre + ",";
            }
        }

        return sql;
    }

    void SqlUtil::insertValue(QString &queryString, const QString column, QVariant value, QString separador)
    {
        QString primeiraParte = queryString.mid(0, queryString.lastIndexOf(separador));
        QString segundaParte = queryString.mid(queryString.lastIndexOf(separador));

        appendValue(primeiraParte, column, value);
        queryString = primeiraParte + ' ' + segundaParte;
    }
}
