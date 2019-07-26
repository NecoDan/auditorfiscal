#ifndef ESCRITURACAO_ESCRITURACAO_H
#define ESCRITURACAO_ESCRITURACAO_H

/** @author Daniel Santos @date 04/07/2018 **/

#include <QObject>
#include <QMap>
#include <QDate>
#include <QDateTime>

namespace gm_escrituracao
{
    class Escrituracao : public QObject
    {
            Q_OBJECT

        public:

            explicit Escrituracao(QObject *parent = nullptr);

            /*################################## Constantes #############################*/

            static const QString NOME_TABELA;

            /*############################### Getters & Setters #########################*/

            int id() const;
            void setId(int id);

            QString descricaoFilial() const;
            void setDescricaoFilial(const QString& descricaoFilial);

            QString cnpjRaizEmpresa() const;
            void setCnpjRaizEmpresa(const QString& cnpjRaizEmpresa);

            QString cnpj() const;
            void setCnpj(const QString& cnpj);

            int ano() const;
            void setAno(int ano);

            QString nomeDatabase() const;
            void setNomeDatabase(const QString& nomeDatabase);

            long long inscricaoEstadual() const;
            void setInscricaoEstadual(long long inscricaoEstadual);

            QDateTime data() const;
            void setData(const QDateTime& data);

            bool fechado() const;
            void setFechado(bool fechado);

            /*###################### Outros Getters & Setters ######################*/

            QString pathCaminhoArquivo() const;
            void setPathCaminhoArquivo(const QString& pathCaminhoArquivo);

            bool contemArquivoLidoImportado() const;
            void setContemArquivoLidoImportado(bool contemArquivoLidoImportado);

            int mes() const;
            void setMes(int mes);

            QDate dataInicio() const;
            void setDataInicio(const QDate& dataInicio);

            QDate dataFim() const;
            void setDataFim(const QDate& dataFim);

            /*########################### Métodos de Ação ##########################*/

            /**
              * @author Daniel Santos
              * @date   05/07/2018
              * @brief  toStringNomeArquivoEscrituracao método responsável.
              * @return um objeto QString
              */
            QString toStringNomeArquivoEscrituracao();

            /**
              * @author Daniel Santos
              * @date   09/07/2018
              * @brief  toStringNomeArquivoEscrituracaoCompleto método responsável.
              * @return um objeto QString
              */
            QString toStringNomeArquivoEscrituracaoCompleto();

        private:

            /*############################### Atributos ###########################*/

            int       _ano;
            QString   _cnpj;
            QString   _cnpjRaizEmpresa;
            QDateTime _data;
            QString   _descricaoFilial;
            int       _id;
            long long _inscricaoEstadual;
            QString   _nomeDatabase;
            bool      _fechado;

            /*##################### Atributos Não-Persistidos #######################*/

            bool    _contemArquivoLidoImportado;
            QString _pathCaminhoArquivo;
            int     _mes;
            QDate   _dataInicio;
            QDate   _dataFim;

            /*########################### Métodos de Ação ##########################*/

            void inicializar(int id = 0);
    };

    /** @author Daniel Santos @date 04/07/2018 **/
    class EscrituracaoBuilder : public QObject
    {
            Q_OBJECT

        private:

            EscrituracaoBuilder(QObject *parent = 0);

            EscrituracaoBuilder(Escrituracao* escrituracao, QObject *parent = 0);

            /*############################## Atributos ###########################*/

            Escrituracao* _escrituracao;

        public:

            /*########################## Métodos de Ação ########################*/

            static EscrituracaoBuilder* umNovaEscrituracao();

            static EscrituracaoBuilder* umNovaEscrituracao(QMap<int, QString> mapPosicoesRegistroArquivoSped);

            Escrituracao* constroi();

            /*########################## Métodos de Ação #########################*/

            EscrituracaoBuilder* comARaizCnjpEmpresa(QString cnpjRaizEmpresa);

            EscrituracaoBuilder* inicializandoPeloAno(int ano);

            EscrituracaoBuilder* inicializadoPeloMes(int mes);

            EscrituracaoBuilder* comOSeguinteCnpj(QString cnpj);

            EscrituracaoBuilder* iniciaPelaData(QDate dataInicio);

            EscrituracaoBuilder* finalizaPelaData(QDate dataFim);

            EscrituracaoBuilder* fechada(bool fechado);

            EscrituracaoBuilder* deAcordoComADataLancamento(QDateTime data);

            EscrituracaoBuilder* comAInscricaoEstadual(long long inscricaoEstadual);

            EscrituracaoBuilder* carregadaComADescricaoFilial(QString descricaoFilial);

            EscrituracaoBuilder* definidaComNomeDatabase(QString nomeDatabase);
    };
}

#endif // ESCRITURACAO_ESCRITURACAO_H
