#ifndef ESCRITURACAO_DIRETORIOPADRAONEGOCIO_H
#define ESCRITURACAO_DIRETORIOPADRAONEGOCIO_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QVariant>

// Infraestrutura
#include "infraestrutura/gm_erro.h"

namespace gm_escrituracao
{
    class DiretorioPadrao;

    class DiretorioPadraoNegocio : public QObject
    {
        Q_OBJECT

    public:

        explicit DiretorioPadraoNegocio(QObject *parent = nullptr);

        explicit DiretorioPadraoNegocio(QSqlDatabase& db, QObject *parent = nullptr);

        /*################################## Gets ####################################*/

        gm::GMErro lastError();

        /*######################### Métodos de Ação ###################################*/

        bool salvarDiretorioPadrao(DiretorioPadrao* diretorio);

        DiretorioPadrao* recuperar();

    private:

        /*############################# Atributos #####################################*/

        QSqlDatabase _db;

        gm::GMErro _lastError;

    };

} // namespace gm_escrituracao

#endif // ESCRITURACAO_DIRETORIOPADRAONEGOCIO_H
