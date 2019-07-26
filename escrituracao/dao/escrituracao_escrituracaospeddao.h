#ifndef ESCRITURACAO_ESCRITURACAOSPEDDAO_H
#define ESCRITURACAO_ESCRITURACAOSPEDDAO_H

#include <QObject>
#include <QSqlDatabase>

// Infraestrutura
#include "infraestrutura/gm_erro.h"
#include "infraestrutura/banco/dbmanager.h"

namespace gm
{
    class DSqlQuery;
}

namespace gm_escrituracao
{
    class Escrituracao;
    class EscrituracaoSped;

    class EscrituracaoSpedDao : public QObject
    {
            Q_OBJECT

        public:

            explicit EscrituracaoSpedDao(QSqlDatabase& db, QObject *parent = nullptr);

            /*################################# Gets #######################################*/

            gm::GMErro lastError();

            /*######################### Métodos de Ação ####################################*/

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  salvarEscrituracaoSped método responsável.
              * @param  escrituracaoSped uma instância de EscrituracaoSped
              */
            void atualizarEscrituracaoSped(EscrituracaoSped* escrituracaoSped);

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  salvarEscrituracaoSped método responsável.
              * @param  escrituracaoSped uma instância de EscrituracaoSped
              */
            void salvarEscrituracaoSped(EscrituracaoSped* escrituracaoSped);

            /**
              * @author Daniel Santos
              * @date   12/07/2018
              * @brief  recuperarEscrituracaoSped método responsável.
              * @param  escrituracao uma instância de Escrituracao
              * @return escrituracaoSped uma instância de EscrituracaoSped
              */
            EscrituracaoSped* recuperarEscrituracaoSped(Escrituracao* escrituracao);

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  recuperarEscrituracoesSped método responsável.
              * @return uma lista de instância de EscrituracaoSped.
              */
            QList<EscrituracaoSped*> recuperarEscrituracoesSped();

        private:

            /*############################# Atributos ######################################*/

            QSqlDatabase _db;

            gm::GMErro _lastError;

            /*######################### Métodos de Ação ####################################*/

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  montarCamposEscrituracaoSped método responsável por.
              * @param  escrituracaoSped uma instância de EscrituracaoSped
              * @return uma lista de enums InformacoesCampos
              */
            QList<DbManager::InformacoesCampos> montarCamposEscrituracaoSped(EscrituracaoSped* escrituracaoSped);

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  montarObjEscrituracaoSped método responsável por.
              * @param  query um objeto DSqlQuery
              * @return um instância (Objeto) de EscrituracaoSped
              */
            EscrituracaoSped* montarObjEscrituracaoSped(gm::DSqlQuery& query);

    };
}

#endif // ESCRITURACAO_ESCRITURACAOSPEDDAO_H
