#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <QMultiMap>
#include <QString>
#include <exception>
#include "infraestrutura/gm_erro.h"

using namespace std;

class BaseException : public exception
{

public:

    BaseException() throw();

    BaseException(gm::GMErro::TipoErro tipo, QString mensagem) throw();

    ~BaseException() throw();

    void adicionarErro(gm::GMErro::TipoErro tipo, QString mensagem);

    QString toString();

    bool temCamposInvalidos();

private:

    QMultiMap<gm::GMErro::TipoErro, QString> _camposInvalidos;

    QString toString(gm::GMErro::TipoErro tipo);
};

#endif // BASEEXCEPTION_H
