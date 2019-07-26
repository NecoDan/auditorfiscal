#ifndef ESCRITURACAO_DIRETORIOPADRAODAO_H
#define ESCRITURACAO_DIRETORIOPADRAODAO_H

#include <QObject>
#include <QSqlDatabase>

// Infraestrutura
#include "infraestrutura/gm_erro.h"
#include "infraestrutura/banco/dbmanager.h"

namespace gm_escrituracao
{
    class DiretorioPadrao;

    class DiretorioPadraoDAO : public QObject
    {
        Q_OBJECT

    public:

        explicit DiretorioPadraoDAO(QObject *parent = nullptr);

        explicit DiretorioPadraoDAO(QSqlDatabase& db, QObject *parent = nullptr);

        /*################################## Gets ####################################*/

        gm::GMErro lastError();

        /*######################### Métodos de Ação ###################################*/

        void salvarDiretorioPadrao(DiretorioPadrao* diretorio);

        DiretorioPadrao* recuperar();

    private:

        /*############################# Atributos #####################################*/

        QSqlDatabase _db;

        gm::GMErro _lastError;

        QList<DbManager::InformacoesCampos> montarCamposDiretorioPadrao(DiretorioPadrao *diretorio);

    };

} // namespace gm_escrituracao

#endif // ESCRITURACAO_DIRETORIOPADRAODAO_H
