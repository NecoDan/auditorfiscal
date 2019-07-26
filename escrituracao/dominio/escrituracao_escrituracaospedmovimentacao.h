#ifndef ESCRITURACAO_ESCRITURACAOSPEDMOVIMENTACAO_H
#define ESCRITURACAO_ESCRITURACAOSPEDMOVIMENTACAO_H

#include <QObject>

namespace gm_escrituracao
{
    class EscrituracaoSpedMovimentacao : public QObject
    {
            Q_OBJECT

        public:

            explicit EscrituracaoSpedMovimentacao(QObject *parent = nullptr);

            explicit EscrituracaoSpedMovimentacao(long long id = 0, QObject *parent = nullptr);

            /*################################## Constantes #############################*/

            static const QString NOME_TABELA;

            /*############################### Getters & Setters #########################*/

            long long id() const;
            void setId(long long id);

            long long codigoProduto() const;
            void setCodigoProduto(long long codigoProduto);

            QString descricaoProduto() const;
            void setDescricaoProduto(const QString& descricaoProduto);

            QString unidadeMedida() const;
            void setUnidadeMedida(const QString& unidadeMedida);

            double qtde() const;
            void setQtde(double qtde);

            double valorTotal() const;
            void setValorTotal(double valorTotal);

        private:

            /*################################### Atributos #############################*/

            long long _id;
            long long _codigoProduto;
            QString   _descricaoProduto;
            QString   _unidadeMedida;
            double    _qtde;
            double    _valorTotal;

            /*############################# Métodos de Ação ############################*/

            void inicializar(long long id = 0);
    };
}

#endif // ESCRITURACAO_ESCRITURACAOSPEDMOVIMENTACAO_H
