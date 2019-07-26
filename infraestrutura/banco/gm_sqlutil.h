#ifndef SQLUTIL_H
#define SQLUTIL_H

#include <QDebug>
#include <QList>
#include <QStringList>
#include <QDate>
#include <QDateTime>
#include <QtSql>
#include <QObject>
#include <QVariant>

namespace gm
{
    class SqlUtil
    {
        private:

            SqlUtil();

            static void appendWhereOrAnd(QString& queryString);

            static void appendValue(QString& queryString, const QVariant& value);

        public:

            static void appendBetweenValues(QString& queryString, const QString column, QVariant value1, QVariant value2);

            static void appendInValues(QString& queryString, const QString column, QString values);

            static void appendIsNull(QString& queryString, const QString column);

            static void appendIsNotNull(QString& queryString, const QString column);

            static void appendNotInValues(QString& queryString, const QString column, QString values);

            static void appendValue(QString& queryString, const QString column, QVariant value);

            static void appendValueLike(QString& queryString, const QString column, QVariant value);

            static void appendValueDiferent(QString& queryString, const QString column, QVariant value);

            static void appendValueGreaterOrEqual(QString& queryString, const QString column, QVariant value);

            static void appendValueGreaterThan(QString& queryString, const QString column, QVariant value);

            static void appendValueLessOrEqual(QString& queryString, const QString column, QVariant value);

            static void appendValueLessThan(QString& queryString, const QString column, QVariant value);

            static void appendValueNotEqual(QString& queryString, const QString column, QVariant value);

            static void appendInnerJoin(QString& queryString, const QString table, const QString firstValue, const QString secondValue, bool withNolock = true);

            static void appendInnerJoinMultipleOn(QString& queryString, const QString table, const QMap<QString, QString> onKeyValues, bool withNolock = true);

            static void appendLeftJoin(QString& queryString, const QString table, const QString firstValue, const QString secondValue, bool withNolock = true);

            static void appendLeftJoinMultipleOn(QString& queryString, const QString table, const QMap<QString, QString> onKeyValues, bool withNolock = true);

            static void appendColumn(QString& queryString, QString column);

            static void appendDateBetween(QString& queryString, QString campoDate, QDate dataInicio, QDate dataFim);

            static void appendStringOnWhere(QString& queryString, QString string);

            static void appendGroupBy(QString& queryString, QStringList campos);

            static void appendOrderBy(QString& queryString, QStringList campos);

            static QString dateToSqlFormat(QDate data, bool quote = false);

            static QString dateToSqlFormat(QDateTime data, bool quote = false);

            static bool endsWithWhere(QString sql);

            static bool hasWhere(QString sql);

            static QString quoteValue(QVariant value);

            static QString toDateTimeEnd(QDate date);

            static QString toDateTimeStart(QDate date);

            static QString toSqlList(QList<int> list, bool quote = false);

            static QString toSqlList(QList<QVariant> list, bool quote = false);

            static QString toSqlList(QList<long long> list, bool quote = false);

            static QString toSqlList(QList<QString> list, bool quote = false);

            static QString toSqlList(QStringList list, bool quote = false);

            static void insertValue(QString& queryString, const QString column, QVariant value, QString separador);

            template <class T>
            static inline QString toSqlListFromObjectList(QList<T*> list)
            {
                QStringList ids;
                QString chavePrimaria = T::primaryKey();

                foreach(T* obj, list)
                {
                    if(obj != nullptr)
                        ids << QString::number(obj->property(chavePrimaria.toStdString().c_str()).toLongLong());
                }

                if (ids.isEmpty())
                {
                    return "(null)";
                }

                return "(" + ids.join(",") + ")";
            }

    };
}

#endif // SQLUTIL_H
