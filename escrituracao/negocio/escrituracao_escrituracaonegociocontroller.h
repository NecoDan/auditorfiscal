#ifndef ESCRITURACAO_ESCRITURACAONEGOCIOCONTROLLER_H
#define ESCRITURACAO_ESCRITURACAONEGOCIOCONTROLLER_H

/** @author Daniel Santos @date 11/07/2018 **/

#include <QObject>
#include <QSqlDatabase>

// Infraestrutura
#include "infraestrutura/gm_erro.h"

namespace gm_escrituracao
{
    class Escrituracao;
    class EscrituracaoSped;

    class EscrituracaoNegocioController : public QObject
    {
            Q_OBJECT

        public:

            explicit EscrituracaoNegocioController(Escrituracao* escrituracao = nullptr, QObject *parent = nullptr);

            explicit EscrituracaoNegocioController(int ano = 0, QString cnpjRaiz = QString(), QString cnpjFilial = QString(), QObject *parent = nullptr);

            /*#################################### Gets ########################################*/

            void fecharDatabase();

            gm::GMErro lastError();

            /*############################### Métodos de Ação  ###################################*/

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  efetuarLancamentoEscrituracaoSped método responsável.
              * @param  escrituracao uma instancia de Escrituracao
              */
            void efetuarLancamentoEscrituracaoSped(Escrituracao* escrituracao);

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  efetuarLancamentoEscrituracaoSped método responsável.
              * @param  escrituracao uma instancia de Escrituracao
              */
            void efetuarLancamentoEscrituracaoSpedAuxiliar(Escrituracao* escrituracao);


            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  salvarEscrituracaoSped método responsável.
              * @param  escrituracaoSped uma instância de EscrituracaoSped
              * @param  validaParams
              */
            void salvarEscrituracaoSped(EscrituracaoSped* escrituracaoSped, bool validaParams = true);

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  recuperarEscrituracaoSped método responsável.
              * @return escrituracaoSped uma instância de EscrituracaoSped
              */
            EscrituracaoSped* recuperarEscrituracaoSped(Escrituracao* escrituracao);

            /**
              * @author Daniel Santos
              * @date   12/07/2018
              * @brief  recuperarEscrituracoesSped método responsável.
              * @return uma lista de instância de EscrituracaoSped.
              */
            QList<EscrituracaoSped*> recuperarEscrituracoesSped();

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  recuperarEscrituracoesSped método responsável.
              * @param  escrituracao uma instância de Escrituracao
              * @return uma lista de instância de EscrituracaoSped.
              */
            QList<EscrituracaoSped*> recuperarEscrituracoesSped(Escrituracao* escrituracao = nullptr);

        private:

            /*###################################### Atributos ###################################*/

            QSqlDatabase _dbConexao;

            gm::GMErro _lastError;

            Escrituracao* _escrituracao;

            /*############################### Métodos de Ação  ###################################*/

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  parametrosValidosEscrituracao método responsável.
              * @return TRUE caso todos os parâmetros estejam válidos, do contrário FALSE.
              */
            bool isParametrosValidosEscrituracao();

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  inicializarDataBase método responsável.
              * @param  escrituracao uma instância de Escrituracao.
              */
            void inicializarDataBase();

            EscrituracaoSped* constroiObjEscrituracaoSped(int mes = 0);

    };
}

#endif // ESCRITURACAO_ESCRITURACAONEGOCIOCONTROLLER_H
