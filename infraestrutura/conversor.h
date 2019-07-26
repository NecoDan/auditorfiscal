#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <QLocale>
#include <QVariant>

namespace gm
{
    class Conversor
    {
        public:

            /* ############################ Gets e Sets ############################ */

            static QLocale locale();

            /* ########################## Métodos de Ação ########################## */

            /**
             * @brief ehNumero
             * @param valor
             * @return true se o valor for numero e false caso não seja
             */
            static bool ehNumero(QString valor);

            static bool ehNumero(QVariant valor);

            static double toDouble(QVariant numero);

            /**
             * @brief toString
             * @param valor
             * @param precisao
             * @return
             */
            static QString toString(double valor, int precisao = 2);

        private:

            explicit Conversor();

            /* ############################## Atributos ############################ */

            static const QLocale _locale;

            /* ########################## Métodos de Ação ########################## */

            static QString retiraCaracteres(QString valor);

    };
}

#endif // CONVERSOR_H
