#ifndef ARQUIVO_ARQUIVONEGOCIO_H
#define ARQUIVO_ARQUIVONEGOCIO_H

/** @author Daniel Santos @date 04/07/2018 **/

#include <QObject>
#include <QSqlDatabase>
#include <QFile>
#include <QVariant>
#include <QTextStream>

// Infraestrutura
#include "infraestrutura/gm_erro.h"

namespace gm_arquivo
{
    class ArquivoNegocio : public QObject
    {
            Q_OBJECT

        public:

            explicit ArquivoNegocio(QObject *parent = nullptr);

            explicit ArquivoNegocio(QSqlDatabase& db, QObject *parent = nullptr);

            /*################################## Gets ###############################*/

            gm::GMErro lastError();

            /*############################ Métodos de Ação ###########################*/

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  efetuarLeiturasArquivos método responsável
              * @param  pathsCaminhosArquivo um objeto de QString.
              */
            void gerarEscrituracoesMaster(QStringList pathsCaminhosArquivo);

            QStringList gerarLinhasRegistrosEscrituracao(QString pathCaminhoArquivo);

            /**
              * @author Daniel Santos
              * @date   04/07/2018
              * @brief  efetuarLeituraArquivo método responsável
              * @param  pathCaminhoArquivo um objeto de QString.
              * @param  chaveBuscaRegistro um objeto de QString.
              */
            QStringList efetuarLeituraArquivo(QString pathCaminhoArquivo, QString chaveBuscaRegistro = QString(), bool lerTodoArquivo = true);

        private:

             /*############################### Atributos #############################*/

            QSqlDatabase _db;

            gm::GMErro _lastError;

            /*############################ Métodos de Ação ###########################*/

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


#endif // ARQUIVO_ARQUIVONEGOCIO_H
