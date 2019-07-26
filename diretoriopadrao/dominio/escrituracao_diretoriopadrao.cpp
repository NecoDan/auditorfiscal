#include "escrituracao_diretoriopadrao.h"

namespace gm_escrituracao
{

    DiretorioPadrao::DiretorioPadrao(QObject *parent) : QObject(parent)
    {
        this->inicializar();
    }

    long long DiretorioPadrao::id() const
    {
        return _id;
    }

    void DiretorioPadrao::setId(long long id)
    {
        _id = id;
    }

    QString DiretorioPadrao::caminho() const
    {
        return _caminho;
    }

    void DiretorioPadrao::setCaminho(const QString &caminho)
    {
        _caminho = caminho;
    }

    QDateTime DiretorioPadrao::data() const
    {
        return _data;
    }

    void DiretorioPadrao::setData(const QDateTime &data)
    {
        _data = data;
    }

    void DiretorioPadrao::inicializar(int id)
    {
        _id = id;
    }

} // namespace gm_escrituracao
