#ifndef BLOCO_H
#define BLOCO_H

#include <QList>
#include <QObject>

namespace gm_arquivo
{
    class RegistroArquivo;

    class Bloco : public QObject
    {
        Q_OBJECT

        public:

            explicit Bloco(QObject* parent = 0);

            /* ################################ Gets e Sets ################################ */

            QList<RegistroArquivo*> registros() const;
            void setRegistros(const QList<RegistroArquivo*>& registros);

            /* ############################## Metodos de Acao ############################## */

            void addRegistro(RegistroArquivo* registro);

            void addRegistros(QList<RegistroArquivo*> registros);

            QString toString();

            QString toStringSemSeparadores();

        private:

            /* ################################# Atributos ################################# */

            QList<RegistroArquivo*> _registros;

    };
}

#endif // BLOCO_H
