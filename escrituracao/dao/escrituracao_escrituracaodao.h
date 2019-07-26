#ifndef ESCRITURACAO_ESCRITURACAODAO_H
#define ESCRITURACAO_ESCRITURACAODAO_H

/** @author Daniel Santos @date 04/07/2018 **/

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

    class EscrituracaoDao : public QObject
    {
            Q_OBJECT

        public:

            explicit EscrituracaoDao(QObject *parent = nullptr);

            explicit EscrituracaoDao(QSqlDatabase& db, QObject *parent = nullptr);

            /*################################## Gets ####################################*/

            gm::GMErro lastError();

            /*######################### Métodos de Ação ###################################*/

            /**
              * @author Daniel Santos
              * @date   05/07/2018
              * @brief  atualizarEscrituracao método responsável.
              * @param  escrituracao uma instância de Escrituracao
              */
            void atualizarEscrituracao(Escrituracao* escrituracao);

            /**
              * @author Daniel Santos
              * @date   05/07/2018
              * @brief  salvarEscrituracao método responsável.
              * @param  escrituracao uma instância de Escrituracao
              */
            void salvarEscrituracao(Escrituracao* escrituracao);

            void salvarEscrituracaoSped(EscrituracaoSped* escrituracaoSped);

            /**
              * @author Daniel Santos
              * @date   09/07/2018
              * @brief  recuperarEscrituracao método responsável.
              * @param  escrituracao uma instância de Escrituracao
              * @param  ano
              * @param  cnpjRaizEmpresa
              * @param  cnpj
              * @return uma instância de Escrituracao
              */
            Escrituracao* recuperarEscrituracao(int ano = 0, QString cnpjRaizEmpresa = QString(), QString cnpj = QString());

            /**
              * @author Daniel Santos
              * @date   09/07/2018
              * @brief  recuperarEscrituracaoPor método responsável.
              * @param  ano
              * @param  cnpjRaizEmpresa
              * @param  cnpj
              * @param  inscricaoEstadual
              * @return uma instância de Escrituracao
              */
            Escrituracao* recuperarEscrituracaoPor(int ano = 0, QString cnpjRaizEmpresa = QString(), QString cnpj = QString(), long long inscricaoEstadual = 0);

            /**
              * @author Daniel Santos
              * @date   09/07/2018
              * @brief  recuperarPorId método responsável.
              * @param  id
              * @return uma instância de Escrituracao
              */
            Escrituracao* recuperarPorId(long long id);

            /**
              * @author Daniel Santos
              * @date   09/07/2018
              * @brief  recuperarPorId método responsável.
              * @param  id
              * @return uma instância de Escrituracao
              */
            Escrituracao* recuperarPorId(int id);

            /**
              * @author Daniel Santos
              * @date   09/07/2018
              * @brief  recuperarEscrituracoes método responsável.
              * @return uma lista de instâncias de Escrituracao
              */
            QList<Escrituracao*> recuperarEscrituracoes();

        private:

            /*############################# Atributos #####################################*/

            QSqlDatabase _db;

            gm::GMErro _lastError;

            /*######################### Métodos de Ação ###################################*/

            /**
              * @author Daniel Santos
              * @date   09/07/2018
              * @brief  montarCamposEscrituracao método responsável por.
              * @param  escrituracao uma instância de Escrituracao
              * @return
              */
            QList<DbManager::InformacoesCampos> montarCamposEscrituracao(Escrituracao* escrituracao);

            /**
              * @author Daniel Santos
              * @date   09/07/2018
              * @brief  montarObjEscrituracao método responsável por.
              * @param  query um objeto DSqlQuery
              * @return um instância (Objeto) de Escrituracao
              */
            Escrituracao* montarObjEscrituracao(gm::DSqlQuery& query);
    };
}


#endif // ESCRITURACAO_ESCRITURACAODAO_H
