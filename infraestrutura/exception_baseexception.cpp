#include "exception_baseexception.h"

using namespace gm;

BaseException::BaseException() throw()
{
}

BaseException::~BaseException() throw()
{
}

BaseException::BaseException(GMErro::TipoErro tipo, QString mensagem) throw()
{
    adicionarErro(tipo, mensagem);
}

void BaseException::adicionarErro(gm::GMErro::TipoErro tipo, QString mensagem)
{
    _camposInvalidos.insert(tipo, mensagem);
}

QString BaseException::toString()
{
    QString mensagem;

    foreach (gm::GMErro::TipoErro tipo, _camposInvalidos.uniqueKeys())
    {
        mensagem.append("<b>" + toString(tipo) + "</b><br>");

        foreach (QString erro, _camposInvalidos.values(tipo))
        {
            mensagem.append("<br>" + erro);
        }

        mensagem.append("<br>");
    }

    return mensagem;
}

bool BaseException::temCamposInvalidos()
{
    return !_camposInvalidos.isEmpty();
}

QString BaseException::toString(gm::GMErro::TipoErro tipo)
{
    int quantidadeErros = _camposInvalidos.values(tipo).size();
    QString tipoErroSingularOuPlural = (quantidadeErros == 1? "Erro" : "Erros");
    QString encontradoSingularOuPlural = (quantidadeErros == 1? "encontrado:" : "encontrados:");

    if (tipo == GMErro::BANCO)
    {
        return  tipoErroSingularOuPlural + " de banco de dados " + encontradoSingularOuPlural;
    }
    else if (tipo == GMErro::VALIDACAO)
    {
        return  tipoErroSingularOuPlural + " de validação " + encontradoSingularOuPlural;
    }

    return "Erro indefinido";
}
