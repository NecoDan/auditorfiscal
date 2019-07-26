#ifndef ESCRITURACAO_ESCRITURACAOSPED_H
#define ESCRITURACAO_ESCRITURACAOSPED_H

/** @author Daniel Santos @date 11/07/2018 **/

#include <QObject>
#include <QDate>
#include <QDateTime>

namespace gm_escrituracao
{
    class EscrituracaoSped : public QObject
    {
            Q_OBJECT

        public:

            explicit EscrituracaoSped(QObject *parent = nullptr);

            explicit EscrituracaoSped(int id, QObject *parent = nullptr);

            /*################################## Constantes #############################*/

            static const QString NOME_TABELA;

            /*############################### Getters & Setters #########################*/

            int id() const;
            void setId(int id);

            QString cnpj() const;
            void setCnpj(const QString& cnpj);

            QString descricaoFilial() const;
            void setDescricaoFilial(const QString& descricaoFilial);

            int ano() const;
            void setAno(int ano);

            int mes() const;
            void setMes(int mes);

            QDate dataInicioApuracao() const;
            void setDataInicioApuracao(const QDate& dataInicioApuracao);

            QDate dataFimApuracao() const;
            void setDataFimApuracao(const QDate& dataFimApuracao);

            QDateTime data() const;
            void setData(const QDateTime& data);

            QString caminhoArquivo() const;
            void setCaminhoArquivo(const QString& caminhoArquivo);

            bool fiscal() const;
            void setFiscal(bool fiscal);

            bool naoFiscalSaldo() const;
            void setNaoFiscalSaldo(bool naoFiscalSaldo);

            bool naoFiscalMovimentacao() const;
            void setNaoFiscalMovimentacao(bool naoFiscalMovimentacao);

        private:

            /*################################### Atributos #############################*/

            int       _id;
            QString   _cnpj;
            QString   _descricaoFilial;
            int       _ano;
            int       _mes;
            QDate     _dataInicioApuracao;
            QDate     _dataFimApuracao;
            QString   _caminhoArquivo;
            QDateTime _data;
            bool      _fiscal;
            bool      _naoFiscalSaldo;
            bool      _naoFiscalMovimentacao;

            /*############################# Métodos de Ação ############################*/

            void inicializar(int id = 0);
    };
}

#endif // ESCRITURACAO_ESCRITURACAOSPED_H
