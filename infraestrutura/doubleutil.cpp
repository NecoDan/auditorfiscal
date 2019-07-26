#include "doubleutil.h"

#include "infraestrutura/conversor.h"
#include "infraestrutura/bcmath.h"

#include <cmath>

using namespace std;

namespace gm
{
    DoubleUtil::DoubleUtil(QObject* parent) : QObject(parent)
    {

    }

    double DoubleUtil::arredondar(double valor, int precisao)
    {
        QBCMath qValor(valor);
        qValor.round(precisao);
        return qValor.toDouble();
    }

    double DoubleUtil::arredondarComMultiplo(double quantidadeAArredondar, double multiplo, bool sempreValorMaior)
    {
        if(igualA(multiplo, 0.000, 3))
            return quantidadeAArredondar;

        double quantidade = 0.0;

        quantidadeAArredondar = truncateDouble(quantidadeAArredondar,3);

        if (sempreValorMaior){
            quantidade = ceil(quantidadeAArredondar / multiplo) * multiplo;
        } else{
            quantidade = round(quantidadeAArredondar / multiplo) * multiplo;
        }

        return quantidade;
    }

    bool DoubleUtil::igualA(double primeiroValor, double segundoValor, int precisao)
    {
        Q_UNUSED(precisao)
        QBCMath vlr1(primeiroValor);
        QBCMath vlr2(segundoValor);
        vlr1.round(precisao);
        vlr2.round(precisao);

        return vlr1 == vlr2;
    }

    bool DoubleUtil::igualATruncate(double primeiroValor, double segundoValor, int precisao)
    {
        QBCMath vlr1(truncateDouble(primeiroValor, precisao));
        QBCMath vlr2(truncateDouble(segundoValor, precisao));
        return vlr1 == vlr2;
    }

    bool DoubleUtil::igualAZero(double valor, int precisao)
    {
        return igualA(valor, 0.000, precisao);
    }

    bool DoubleUtil::maiorOuIgual(double valorMaior, double valorMenor, int precisao)
    {
        QBCMath bcValorMaior(valorMaior);
        QBCMath bcValorMenor(valorMenor);

        bcValorMaior.round(precisao);
        bcValorMenor.round(precisao);

        return  bcValorMaior >= bcValorMenor;
    }

    bool DoubleUtil::maiorQue(double valorMaior, double valorMenor, int precisao)
    {
        QBCMath bcValorMaior(valorMaior);
        QBCMath bcValorMenor(valorMenor);

        // qDebug()<<bcValorMenor.toDouble();
        // qDebug()<<bcValorMaior.toDouble();

        bcValorMaior.round(precisao);
        bcValorMenor.round(precisao);

        return bcValorMaior > bcValorMenor;
    }

    bool DoubleUtil::menorOuIgual(double valorMenor, double valorMaior, int precisao)
    {
        QBCMath bcValorMenor(valorMenor);
        QBCMath bcValorMaior(valorMaior);

        bcValorMenor.round(precisao);
        bcValorMaior.round(precisao);

        return bcValorMenor <= bcValorMaior;
    }

    bool DoubleUtil::menorQue(double valorMenor, double valorMaior, int precisao)
    {
        QBCMath bcValorMenor(valorMenor);
        QBCMath bcValorMaior(valorMaior);

        bcValorMaior.round(precisao);
        bcValorMenor.round(precisao);

        return bcValorMenor< bcValorMaior;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int DoubleUtil::somarTudo(QList<int> valores)
    {
        int total = 0;

        foreach (int valor, valores){
            total += valor;
        }

        return total;
    }

    double DoubleUtil::somarTudo(QList<double> valores)
    {
        /*Adaptando o algoritmo de Kahan para efetuar a soma - Francisco*/
        double sum = 0.0;

        foreach(double valor, valores){
            double y = valor - 0;
            double t = sum + y;
            sum = t;
        }

        return sum;
    }

    double DoubleUtil::truncateDouble(double valor, int precisao)
    {
        double valorTruncado = 0;

        valorTruncado = (int) (valor * pow(10, precisao));
        valorTruncado /= pow(10, precisao);

        return valorTruncado;
    }

    double DoubleUtil::porcentagem(double quantidadeTotal, double quantidadePacial, int precisao)
    {
        quantidadeTotal = arredondar(quantidadeTotal, precisao);
        quantidadePacial = arredondar(quantidadePacial, precisao);

        double resultado = (100 * quantidadePacial) / quantidadeTotal;
        return resultado;
    }

    bool DoubleUtil::isFracionado(double valor, int precisao)
    {
        int valorInteiro = valor;
        return !igualA(valor, (double) valorInteiro, precisao);
    }

    bool DoubleUtil::between(double value, double lessValue, double greaterValue)
    {
        return ((value>=lessValue) && (value<=greaterValue));
    }

    double DoubleUtil::fromString(QString texto)
    {
        return texto.replace(".", "").replace(",", ".").toDouble();
    }

    double DoubleUtil::fromStringMoney(QString texto)
    {
        return texto.replace("R$", "").replace(".", "").replace(",", ".").toDouble();
    }

    bool DoubleUtil::diferenteDeZero(double valor)
    {
        if(valor < -0.009 || valor > 0.009)
            return true;

        return false;
    }
}
