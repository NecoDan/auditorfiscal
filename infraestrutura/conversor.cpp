#include "conversor.h"

#include <cmath>
#include <QDebug>
#include <QRegExp>

const QLocale gm::Conversor::_locale = QLocale(QLocale::Portuguese, QLocale::Brazil);

gm::Conversor::Conversor()
{
}

bool gm::Conversor::ehNumero(QString valor)
{
    bool ehNumero = false;
    _locale.toDouble(valor,&ehNumero);
    return ehNumero;
}

bool gm::Conversor::ehNumero(QVariant valor)
{
    bool ehNumero = false;
    _locale.toDouble(valor.toString(),&ehNumero);
    return ehNumero;
}

QLocale gm::Conversor::locale()
{
    return _locale;
}

QString gm::Conversor::retiraCaracteres(QString valor)
{
    return valor.remove(QRegExp("\\D")).trimmed();
}

double gm::Conversor::toDouble(QVariant numero)
{
    double result = 0;
    bool ok;

    result = _locale.toDouble(numero.toString(), &ok);

    if(!ok){
        result = numero.toDouble();
    }

    return result;
}

QString gm::Conversor::toString(double valor, int precisao)
{
    return _locale.toString(valor, 'f', precisao);
}
