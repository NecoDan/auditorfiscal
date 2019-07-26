#ifndef REGISTRO_H
#define REGISTRO_H

#include <QMap>
#include <QObject>

namespace gm_arquivo
{
    class Campo;

    class  RegistroArquivo : public QObject
    {
            Q_OBJECT

        public:

            explicit RegistroArquivo(QObject* parent = 0);

            ~RegistroArquivo();

            /*############################## Metodos de Acao ##############################*/

            void addCampo(int sequencia, Campo* campo);
            Campo* campo(int sequencia);

            void addCampo(Campo* campo);
            QList<Campo *> campos();

            QString toString();

            QString toStringSemSeparadores();

        protected:

            /*################################# Atributos #################################*/

            QMap<int, Campo*> _mapCampos;

    };
}

#endif // REGISTRO_H
