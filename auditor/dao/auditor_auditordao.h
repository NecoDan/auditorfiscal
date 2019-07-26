#ifndef AUDITOR_AUDITORDAO_H
#define AUDITOR_AUDITORDAO_H

#include <QObject>
#include <QSqlDatabase>

// Infraestrutura
#include "infraestrutura/gm_erro.h"

namespace gm_auditor
{
    class AuditorDao : public QObject
    {
            Q_OBJECT

        public:

            explicit AuditorDao(QObject *parent = nullptr);

            explicit AuditorDao(QSqlDatabase& db, QObject *parent = nullptr);

            /*################################ Métodos de Ação ###############################*/

        private:

            /*############################### Atributos #######################################*/

            QSqlDatabase _db;

            gm::GMErro _lastError;
    };
}


#endif // AUDITOR_AUDITORDAO_H
