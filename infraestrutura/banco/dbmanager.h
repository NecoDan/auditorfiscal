#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMap>
#include <QVariant>

// Infraestrutura
#include "infraestrutura/gm_erro.h"

class DbManager
{
    public:

        enum TiposCampos { NUMERICO, TEXTO, DATA, BIGINT, DATA_HORA, INT, BOOLEAN };

        struct InformacoesCampos{
            QString     nomeCampo;
            TiposCampos tipoCampo;
            long long   tamanhoCampo = 0;
            QVariant    valor;
            bool        chaveUnica = false;
            bool        notNull = false;
        };

        explicit DbManager();

        explicit DbManager(QSqlDatabase &db);

        explicit DbManager(QSqlDatabase &db, bool carregaAmbientePadrao);

        /*######################################## Gets & Sets ###############################################*/

        InformacoesCampos getInformacoesCampos(QString nomeCampo, TiposCampos tipoCampo, long long tamanhoCampo = 0,  bool notNull = false, bool chaveUnica = false);

        QString getTipoCampo(TiposCampos tipo, long long tamanho);

        gm::GMErro lastError();

        void setDatabase(QSqlDatabase &db);

        void closeDatabase();

        /*################################### Métodos de Ação ################################################*/

        /**
          * @author Daniel Santos
          * @date   05/07/2018
          * @brief  criarAmbienteApuracaoEscrituracao método responsável.
          */
        void criarAmbienteApuracaoEscrituracao();

        bool criarTabela(QString nomeTabela, QList<InformacoesCampos> listaInformacoesCampos);

        bool isTabelaExiste(QString nomeTabela);

        long long addRegistro(QString nomeTabela, QList<InformacoesCampos> listaCampos/*, QSqlQuery query*/);

        // long long addRegistro(QString nomeTabela, QList<InformacoesCampos> listaCampos);

        bool updateRegistro(QString nomeTabela, QList<InformacoesCampos> listaCampos, long long id);

        /**
          * @author Daniel Santos
          * @date   09/07/2018
          * @brief  removeRegistro método responsável.
          * @param  nomeTabela um objeto de QString contendo como conteúdo o nome da tabela a ser criada
          * @param  id
          * @return TRUE caso revomido com sucesso, do contrário FALSE.
          */
        bool removeRegistro(QString nomeTabela = QString(), long long id = 0);

    private:

        /*############################## Atributos ##################################*/

        QSqlDatabase _db;

        gm::GMErro _lastError;

        /*############################ Métodos de Ação ##############################*/

        /**
          * @author Daniel Santos
          * @date   05/07/2018
          * @brief  criarAmbienteDatabasePadrao método responsável.
          */
        void criarAmbienteDatabasePadrao();

        /**
          * @author Daniel Santos
          * @date   05/07/2018
          * @brief  criarTabelaEscrituracaoMaster método responsável.
          * @param  nomeTabela um objeto de QString contendo como conteúdo o nome da tabela a ser criada
          */
        void criarTabelaEscrituracaoMaster(QString nomeTabela);

        /**
          * @author Daniel Santos
          * @date   05/07/2018
          * @brief  criarTabelaDiretorioPadraoMaster método responsável.
          * @param  nomeTabela um objeto de QString contendo como conteúdo o nome da tabela a ser criada
          */
        void criarTabelaDiretorioPadraoMaster(QString nomeTabela);

        /**
          * @author Daniel Santos
          * @date   09/07/2018
          * @brief  toStringValueSqlQuery método responsável por.
          * @param  campo
          * @return um objeto de QString
          */
        QString toStringValueSqlQuery(InformacoesCampos campo);

        /**
          * @author Daniel Santos
          * @date   09/07/2018
          * @brief  toStringAppendLimitadorSqlQuery método responsável por
          * @param  valorColunaTabela
          * @param  tamanho
          * @return um objeto de QString
          */
        QString toStringAppendLimitadorSqlQuery(int valorColunaTabela = 0, int tamanho = 0);

        void outPutDebug(QVariant value = QVariant());

};

#endif // DBMANAGER_H
