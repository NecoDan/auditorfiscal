#ifndef ITEMUTIL_H
#define ITEMUTIL_H

#include <QObject>
#include <QVariant>
#include <QComboBox>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QDebug>

namespace gm
{
    namespace itemutil
    {
        // QTableWidgetItem

        template <class T> inline T* getObject(QTableWidgetItem* item)
        {
            QVariant value = item->data(QTableWidgetItem::UserType);
            if (!value.isNull())
                return qobject_cast<T*>(qvariant_cast<QObject*>(value));
            return NULL;
        }

        template <class T> inline void setObject(QTableWidgetItem* item, T* obj)
        {
            item->setData(QTableWidgetItem::UserType, QVariant(QMetaType::QObjectStar, &obj));
        }

        QVariant inline getVariant(QTableWidgetItem* item)
        {
            return item->data(QTableWidgetItem::UserType);
        }

        inline void setVariant(QTableWidgetItem* item, QVariant value)
        {
            item->setData(QTableWidgetItem::UserType, value);
        }

        // QTreeWidgetItem

        template <class T> inline T* getObject(QTreeWidgetItem* item, int column)
        {
            QVariant value = item->data(column, QTreeWidgetItem::UserType);
            QObject* object = qvariant_cast<QObject*>(value);
            return qobject_cast<T*>(object);
        }

        inline QObject* getObjectGeneric(QTreeWidgetItem* item, int column)
        {
            QVariant value = item->data(column, QTreeWidgetItem::UserType);
            QObject* object = qvariant_cast<QObject*>(value);
            return object;
        }

        template <class T> inline void setObject(QTreeWidgetItem* item, int column, T* value)
        {
            item->setData(column, QTreeWidgetItem::UserType, QVariant(QMetaType::QObjectStar, &value));
        }

        QVariant inline getVariant(QTreeWidgetItem* item, int column)
        {
            return item->data(column, QTreeWidgetItem::UserType);
        }

        inline void setVariant(QTreeWidgetItem* item, int column, QVariant value)
        {
            item->setData(column, QTreeWidgetItem::UserType, value);
        }

        // QListWidgetItem

        template <class T> inline T* getObject(QListWidgetItem* item)
        {
            QVariant value = item->data(QTreeWidgetItem::UserType);
            QObject* object = qvariant_cast<QObject*>(value);
            return qobject_cast<T*>(object);
        }

        template <class T> inline void setObject(QListWidgetItem* item, T* value)
        {
            item->setData(QTreeWidgetItem::UserType, QVariant(QMetaType::QObjectStar, &value));
        }

        QVariant inline getVariant(QListWidgetItem* item)
        {
            return item->data(QTreeWidgetItem::UserType);
        }

        inline void setVariant(QListWidgetItem* item, QVariant value)
        {
            item->setData(QTreeWidgetItem::UserType, value);
        }

        // QComboBox

        template <class T> inline void addItem(QComboBox* combo, const QString& texto, T* obj)
        {
            combo->addItem(texto, QVariant(QMetaType::QObjectStar, &obj));
        }

        inline void addItem(QComboBox* combo, const QString& texto, QVariant value)
        {
            combo->addItem(texto, QVariant(QMetaType::QVariant, &value));
        }

        template <class T> inline T* getObject(QComboBox* combo)
        {
            int index = combo->currentIndex();
            return qobject_cast<T*>(qvariant_cast<QObject*>(combo->itemData(index)));
        }

        inline QVariant getVariant(QComboBox* combo)
        {
            int index = combo->currentIndex();
            return qvariant_cast<QVariant>(combo->itemData(index));
        }

        /**
         * @author Carlos Alberto
         * seta o item na combo de acordo com o objeto passado
         */
        template <class T> inline void setCurrentIndex(QComboBox* combo, T* obj)
        {
            int i = 0;
            while(i <= combo->count())
            {
                 combo->setCurrentIndex(i);
                 if(getObject<T>(combo) != NULL)
                     if(getObject<T>(combo)->property(obj->primaryKey().toUtf8()).toLongLong() == obj->property(obj->primaryKey().toUtf8()).toLongLong()){
                         break;
                     }

                i++;
            }
        }

        /**
         * @author Carlos Alberto
         * seta o item na combo de acordo com o QVariant passado
         */
        inline void setCurrentIndex(QComboBox* combo, QVariant value)
        {
            int i = 0;
            while(i <= combo->count())
            {
                 combo->setCurrentIndex(i);
                 if(getVariant(combo).toLongLong() == value.toLongLong()){

                     break;
                 }

                i++;
            }
        }

        inline QString currentTextCombo(QComboBox* combo, QVariant value)
        {
            int i = 0;
            QString text = "";
            while(i <= combo->count())
            {

                 combo->setCurrentIndex(i);
                 if(getVariant(combo).toLongLong() == value.toLongLong()){
                     text = combo->itemText(i);
                     break;
                 }

                i++;
            }

            return text;
        }

        inline void removeItem(QComboBox* combo, QVariant value)
        {
            int i = 0;
            while(i <= combo->count())
            {
                 combo->setCurrentIndex(i);
                 if(getVariant(combo).toLongLong() == value.toLongLong()){
                     combo->removeItem(i);
                     break;
                 }

                i++;
            }
        }

        inline int getItemLevel(QTreeWidgetItem* item)
        {
            int level = 0;

            while (item->parent() != NULL)
            {
                item = item->parent();
                level ++;
            }

            return level;
        }

        inline bool isTopLevelItem(QTreeWidgetItem* item)
        {
            return (getItemLevel(item) == 0);
        }


        /**
         * @brief getRow
         * @param widget
         * @return Numero da linha onde o Widget se encontra.
         * @author Carlos Alberto
         */
        inline int getRow(QWidget* widget)
        {
           return widget->property("row").toInt();
        }

        /**
         * @brief setRow
         * @param widget
         * @return Seta o Numero da linha onde o Widget vai ficar.
         * @author Carlos Alberto
         */

        inline void setRow(QWidget* widget, int row)
        {
           widget->setProperty("row",row);
        }

        /**
         * @brief getColumn
         * @param widget
         * @return Numero da coluna onde o Widget se encontra.
         * @author Carlos Alberto
         */
        inline int getColumn(QWidget* widget)
        {
           return widget->property("column").toInt();
        }

        /**
         * @brief setColumn
         * @param widget
         * @param column
         * @return Seta o Numero da coluna onde o Widget vai ficar.
         * @author Carlos Alberto
         */
        inline void setColumn(QWidget* widget, int column)
        {
           widget->setProperty("column",column);
        }

        template <class T> inline QList<T*> invertList(QList<T*> list)
        {
            QList<T*> listaInvertida;

            for(int i = list.size() - 1; i >= 0; i--)
            {
                listaInvertida << list.at(i);
            }

            return listaInvertida;
        }
    }
}
#endif // ITEMUTIL_H
