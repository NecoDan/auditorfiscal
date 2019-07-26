#include "auditor_auditordao.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"

using namespace gm;

namespace gm_auditor
{
    AuditorDao::AuditorDao(QObject *parent) : QObject(parent)
    {
        _db = DBUtil::conexao();
        _lastError = GMErro();
    }

    AuditorDao::AuditorDao(QSqlDatabase& db, QObject *parent) : QObject(parent)
    {
        _db = db;
        _lastError = GMErro();
    }
}

