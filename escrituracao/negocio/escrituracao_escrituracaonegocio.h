#ifndef ESCRITURACAO_ESCRITURACAONEGOCIO_H
#define ESCRITURACAO_ESCRITURACAONEGOCIO_H

/** @author Daniel Santos @date 04/07/2018 **/

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QVariant>

// Infraestrutura
#include "infraestrutura/gm_erro.h"

namespace gm_escrituracao
{
    class Escrituracao;

    class EscrituracaoNegocio : public QObject
    {
            Q_OBJECT

        public:

            explicit EscrituracaoNegocio(QObject *parent = nullptr);

            explicit EscrituracaoNegocio(QSqlDatabase& db, QObject *parent = nullptr);

            /*################################## Gets ####################################*/

            gm::GMErro lastError();

            /*######################### Métodos de Ação ###################################*/

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  atualizarEscrituracao método responsável.
              * @param  escrituracao uma instância de Escrituracao.
              */
            void atualizarEscrituracao(Escrituracao* escrituracao);

            /**
              * @author Daniel Santos
              * @date   05/07/2018
              * @brief  carregarBancoEscrituracaoPor método responsável.
              * @param  escrituracao uma instância de Escrituracao
              * @return TRUE caso banco carregado com sucesso, do contrário FALSE.
              */
            bool carregarBancoEscrituracaoPor(Escrituracao* escrituracao);

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  extrairObjEscrituracao método responsável.
              * @param  mapPosicoesRegistroArquivoSped
              * @return uma instância de Escrituracao
              */
            Escrituracao* extrairObjEscrituracao(QMap<int, QString> mapPosicoesRegistroArquivoSped);

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  efetuarLeiturasArquivos método responsável
              * @param  pathsCaminhosArquivo um objeto de QStringList
              * @return uma lista de instâncias de Escrituracao
              */
            QList<Escrituracao*> gerarEscrituracoesMaster(QStringList pathsCaminhosArquivo);

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  gerarEscrituracao método responsável.
              * @param  mapPosicoesRegistroArquivoSped
              * @return uma instância de Escrituracao
              */
            Escrituracao* gerarEscrituracao(QMap<int, QString> mapPosicoesRegistroArquivoSped, QString pathArquivo = QString());

            /**
              * @author Daniel Santos
              * @date   11/07/2018
              * @brief  processarArquivoSpedFiscal método responsável.
              * @param  escrituracao uma instância de Escrituracao
              */
            void processarArquivoSpedFiscal(Escrituracao* escrituracao);

            /**
              * @author Daniel Santos
              * @date   10/07/2018
              * @brief  recuperarEscrituracao método responsável por.
              * @param  ano
              * @param  cnpjRaiz
              * @param  cnjp
              * @return uma instância de Escrituracao
              */
            Escrituracao* recuperarEscrituracao(int ano = 0, QString cnpjRaiz = QString(), QString cnjp = QString());

            /**
              * @author Daniel Santos
              * @date   10/07/2018
              * @brief  recuperarPorId método responsável.
              * @param  id
              * @return uma instância de Escrituracao
              */
            Escrituracao* recuperarPorId(long long id);

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  salvarEscrituracaoPai método responsável.
              * @param  linhasRegistro uma lista de objetos QString
              * @return uma instância de Escrituracao
              */
            Escrituracao* salvarEscrituracaoPai(QStringList linhasRegistro, QString pathArquivo = QString());

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  salvarEscrituracaoPai método responsável.
              * @param  linhasRegistro uma lista de objetos QString
              */
            void salvarEscrituracaoPaiPor(QStringList linhasRegistro);

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  salvarEscrituracaoPor método responsável.
              * @param  escrituracao uma instância de Escrituracao
              */
            void salvarEscrituracaoPor(Escrituracao* escrituracao);

            QList<Escrituracao*> recuperarEscrituracoes();

        private:

            /*############################# Atributos #####################################*/

            QSqlDatabase _db;

            gm::GMErro _lastError;

            /*######################### Métodos de Ação ###################################*/

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  extrairConteudoLinhaArquivo método responsável.
              * @param  linhaArquivo um objeto de QString
              * @return um objeto de QString
              */
            QString extrairConteudoLinhaArquivo(QString linhaArquivo);

            /**
              * @author Daniel Santos
              * @date   10/07/2018
              * @brief  obtemMapPosicoesRegistroArquivoSped método responsável.
              * @param  linhasRegistro um objeto de QStringList
              * @return um map
              */
            QMap<int, QString> obtemMapPosicoesRegistroArquivoSped(QStringList linhasRegistro);

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  outPutDebug método responsável
              * @param  value1 um objeto de QVariant
              * @param  value2 um objeto de QVariant
              */
            void outPutDebug(QVariant value1 = QVariant(), QVariant value2 = QVariant());
    };
}


#endif // ESCRITURACAO_ESCRITURACAONEGOCIO_H
