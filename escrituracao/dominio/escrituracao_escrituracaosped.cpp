#include "escrituracao_escrituracaosped.h"

namespace gm_escrituracao
{
    const QString EscrituracaoSped::NOME_TABELA = "ESCRITURACAO_SPED";

    EscrituracaoSped::EscrituracaoSped(QObject *parent) : QObject(parent)
    {
        this->inicializar();
    }

    EscrituracaoSped::EscrituracaoSped(int id, QObject *parent) : QObject(parent)
    {
        this->inicializar(id);
    }

    int EscrituracaoSped::id() const
    {
        return _id;
    }

    void EscrituracaoSped::setId(int id)
    {
        _id = id;
    }

    QString EscrituracaoSped::cnpj() const
    {
        return _cnpj;
    }

    void EscrituracaoSped::setCnpj(const QString& cnpj)
    {
        _cnpj = cnpj;
    }

    QString EscrituracaoSped::descricaoFilial() const
    {
        return _descricaoFilial;
    }

    void EscrituracaoSped::setDescricaoFilial(const QString& descricaoFilial)
    {
        _descricaoFilial = descricaoFilial;
    }

    int EscrituracaoSped::ano() const
    {
        return _ano;
    }

    void EscrituracaoSped::setAno(int ano)
    {
        _ano = ano;
    }

    int EscrituracaoSped::mes() const
    {
        return _mes;
    }

    void EscrituracaoSped::setMes(int mes)
    {
        _mes = mes;
    }

    QDate EscrituracaoSped::dataInicioApuracao() const
    {
        return _dataInicioApuracao;
    }

    void EscrituracaoSped::setDataInicioApuracao(const QDate& dataInicioApuracao)
    {
        _dataInicioApuracao = dataInicioApuracao;
    }

    QDate EscrituracaoSped::dataFimApuracao() const
    {
        return _dataFimApuracao;
    }

    void EscrituracaoSped::setDataFimApuracao(const QDate& dataFimApuracao)
    {
        _dataFimApuracao = dataFimApuracao;
    }

    QDateTime EscrituracaoSped::data() const
    {
        return _data;
    }

    void EscrituracaoSped::setData(const QDateTime& data)
    {
        _data = data;
    }

    QString EscrituracaoSped::caminhoArquivo() const
    {
        return _caminhoArquivo;
    }

    void EscrituracaoSped::setCaminhoArquivo(const QString& caminhoArquivo)
    {
        _caminhoArquivo = caminhoArquivo;
    }
    
    bool EscrituracaoSped::fiscal() const
    {
        return _fiscal;
    }
    
    void EscrituracaoSped::setFiscal(bool fiscal)
    {
        _fiscal = fiscal;
    }
    
    bool EscrituracaoSped::naoFiscalSaldo() const
    {
        return _naoFiscalSaldo;
    }
    
    void EscrituracaoSped::setNaoFiscalSaldo(bool naoFiscalSaldo)
    {
        _naoFiscalSaldo = naoFiscalSaldo;
    }
    
    bool EscrituracaoSped::naoFiscalMovimentacao() const
    {
        return _naoFiscalMovimentacao;
    }
    
    void EscrituracaoSped::setNaoFiscalMovimentacao(bool naoFiscalMovimentacao)
    {
        _naoFiscalMovimentacao = naoFiscalMovimentacao;
    }
    
    /*########################### Métodos de Ação ##########################*/
    
    void EscrituracaoSped::inicializar(int id)
    {
        _id = id;
        _ano = 0;
        _mes = 0;
        _naoFiscalMovimentacao = false;
        _naoFiscalSaldo = false;
        _fiscal = false;
    }
    
}
