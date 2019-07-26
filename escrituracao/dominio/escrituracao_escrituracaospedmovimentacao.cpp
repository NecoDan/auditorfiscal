#include "escrituracao_escrituracaospedmovimentacao.h"

namespace gm_escrituracao
{
    EscrituracaoSpedMovimentacao::EscrituracaoSpedMovimentacao(QObject *parent) : QObject(parent)
    {
        this->inicializar();
    }

    EscrituracaoSpedMovimentacao::EscrituracaoSpedMovimentacao(long long id, QObject *parent) : QObject(parent)
    {
        this->inicializar(id);
    }

    long long EscrituracaoSpedMovimentacao::id() const
    {
        return _id;
    }

    void EscrituracaoSpedMovimentacao::setId(long long id)
    {
        _id = id;
    }

    long long EscrituracaoSpedMovimentacao::codigoProduto() const
    {
        return _codigoProduto;
    }

    void EscrituracaoSpedMovimentacao::setCodigoProduto(long long codigoProduto)
    {
        _codigoProduto = codigoProduto;
    }

    QString EscrituracaoSpedMovimentacao::descricaoProduto() const
    {
        return _descricaoProduto;
    }

    void EscrituracaoSpedMovimentacao::setDescricaoProduto(const QString& descricaoProduto)
    {
        _descricaoProduto = descricaoProduto;
    }

    QString EscrituracaoSpedMovimentacao::unidadeMedida() const
    {
        return _unidadeMedida;
    }

    void EscrituracaoSpedMovimentacao::setUnidadeMedida(const QString& unidadeMedida)
    {
        _unidadeMedida = unidadeMedida;
    }

    double EscrituracaoSpedMovimentacao::qtde() const
    {
        return _qtde;
    }

    void EscrituracaoSpedMovimentacao::setQtde(double qtde)
    {
        _qtde = qtde;
    }

    double EscrituracaoSpedMovimentacao::valorTotal() const
    {
        return _valorTotal;
    }

    void EscrituracaoSpedMovimentacao::setValorTotal(double valorTotal)
    {
        _valorTotal = valorTotal;
    }

    /*##################################### Métodos de Ação #######################################*/

    void EscrituracaoSpedMovimentacao::inicializar(long long id)
    {
        _id = id;
        _codigoProduto = 0;
        _valorTotal = 0.0;
        _qtde = 0.0;
    }

}
