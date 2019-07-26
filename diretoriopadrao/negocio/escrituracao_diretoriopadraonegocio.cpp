#include "escrituracao_diretoriopadraonegocio.h"

#include "infraestrutura/banco/gm_dbutil.h"

#include "diretoriopadrao/dominio/escrituracao_diretoriopadrao.h"
#include "diretoriopadrao/dao/escrituracao_diretoriopadraodao.h"

using namespace gm;

namespace gm_escrituracao
{
    DiretorioPadraoNegocio::DiretorioPadraoNegocio(QObject *parent) : QObject(parent)
    {
        _db = DBUtil::conexao();
        _lastError = gm::GMErro();
    }

    DiretorioPadraoNegocio::DiretorioPadraoNegocio(QSqlDatabase &db, QObject *parent) : QObject(parent)
    {
        _db = db;
        _lastError = gm::GMErro();
    }

    gm::GMErro DiretorioPadraoNegocio::lastError()
    {
        return _lastError;
    }

    bool DiretorioPadraoNegocio::salvarDiretorioPadrao(DiretorioPadrao *diretorio)
    {
        if(diretorio == nullptr)
        {
            _lastError = gm::GMErro("Diretório padrão inválido.", gm::GMErro::VALIDACAO);
            return false;
        }

        DiretorioPadraoDAO diretorioPadraoDAO(_db);
        diretorioPadraoDAO.salvarDiretorioPadrao(diretorio);

        if(diretorioPadraoDAO.lastError().isErro())
        {
            _lastError = diretorioPadraoDAO.lastError();
            return false;
        }

        return diretorio;
    }

    DiretorioPadrao *DiretorioPadraoNegocio::recuperar()
    {
        DiretorioPadraoDAO diretorioPadraoDAO(_db);
        DiretorioPadrao* diretorio = diretorioPadraoDAO.recuperar();

        if(diretorioPadraoDAO.lastError().isErro())
        {
            _lastError = diretorioPadraoDAO.lastError();
            return diretorio;
        }

        return diretorio;
    }

} // namespace gm_escrituracao
