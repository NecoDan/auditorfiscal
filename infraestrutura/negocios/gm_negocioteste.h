#ifndef GM_NEGOCIOTESTE_H
#define GM_NEGOCIOTESTE_H

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>
#include <QApplication>
#include <QFileDialog>
#include <QThread>

class NegocioTeste : public QObject
{
        Q_OBJECT

    public:

        explicit NegocioTeste(QObject *parent = nullptr);

        /*############################# Métodos de Ação #############################*/

        void testeDoDaniel();

        void testeCriacaoDatabase();

    private:

        /**
          * @author Daniel Santos
          * @date   04/07/2018
          * @brief  outPutDebug método responsável
          * @param  value1 um objeto de QVariant
          * @param  value2 um objeto de QVariant
          */
        void outPutDebug(QVariant value1 = QVariant(), QVariant value2 = QVariant());
};

#endif // GM_NEGOCIOTESTE_H
