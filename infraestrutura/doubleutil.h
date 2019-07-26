#ifndef DOUBLEUTIL_H
#define DOUBLEUTIL_H

#include <QObject>

namespace gm
{
        class DoubleUtil : public QObject
	{
		Q_OBJECT

        public:

            static double arredondar(double valor, int precisao = 2);

            /**
             * @autor Rodrigo Matos
             * @param quantidadeAArredondar
             * @param multiplo
             * @param sempreValorMaior
             * @brief arredondarComMultiplo: função que arredonda a quantidadeAArredondar com relação ao multiplo informado,
             * @brief caso sempreValorMaior = false as quantidades geradas sempre vão ser maiores do que a quantidadeAArredondar
             * @brief exemplo: quantidadeAArredondar = 1772, multiplo = 1200  = 1200
             * @brief caso sempreValorMaior = true as quantidades geradas sempre vão ser as mais próximas do que a quantidadeAArredondar
             * @brief exemplo: quantidadeAArredondar = 1772, multiplo = 1200  = 1400
             * @return
             */
            static double arredondarComMultiplo(double quantidadeAArredondar, double multiplo, bool sempreValorMaior = false);

            /**
             * @brief igualA funçao que compara dois numeros
             * @param primeiroValor o primeiro valor
             * @param segundoValor o segundo
             * @param precisao a precisao que deve ser levada em conta, exemplo: 0.00 tem precisao 2 (padrao)
             * @return o resultado da comparaçao
             */
            static bool igualA(double primeiroValor, double segundoValor, int precisao = 2);

            /**
             * @brief igualA funçao que compara dois numeros
             * @param primeiroValor o primeiro valor
             * @param segundoValor o segundo
             * @param precisao a precisao que deve ser levada em conta, exemplo: 0.00 tem precisao 2 (padrao)
             * @return o resultado da comparaçao
             */
            static bool igualATruncate(double primeiroValor, double segundoValor, int precisao = 2);

            static bool igualAZero(double valor, int precisao = 2);

            /**
             * @brief maiorOuIgual funçao que compara dois numeros
             * @param valorMaior maior valor a ser comparado
             * @param valorMenor o menor valor a ser comparado
             * @param precisao a precisao que deve ser levada em conta, exemplo: 0.00 tem precisao 2 (padrao)
             * @return o resultado da comparaçao
             */
            static bool maiorOuIgual(double valorMaior, double valorMenor, int precisao = 2);

            /**
             * @brief maiorQue funçao que compara dois numeros
             * @param valorMaior maior valor a ser comparado
             * @param valorMenor o menor valor a ser comparado
             * @param precisao a precisao que deve ser levada em conta, exemplo: 0.00 tem precisao 2 (padrao)
             * @return o resultado da comparaçao
             */
            static bool maiorQue(double valorMaior, double valorMenor, int precisao = 2);

            /**
             * @brief menorOuIgual funçao que compara dois numeros
             * @param valorMenor o menor valor a ser comparado
             * @param valorMaior maior valor a ser comparado
             * @param precisao a precisao que deve ser levada em conta, exemplo: 0.00 tem precisao 2 (padrao)
             * @return o resultado da comparaçao
             */
            static bool menorOuIgual(double valorMenor, double valorMaior, int precisao = 2);

            /**
             * @brief menorQue funçao que compara dois numeros
             * @param valorMenor o menor valor a ser comparado
             * @param valorMaior maior valor a ser comparado
             * @param precisao a precisao que deve ser levada em conta, exemplo: 0.00 tem precisao 2 (padrao)
             * @return o resultado da comparaçao
             */
            static bool menorQue(double valorMenor, double valorMaior, int precisao = 2);

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            /**
             * @brief somarTudo função que soma os totais de uma lista, muito últil ao usar um multimap para armazenar
             * totais a uma chave
             * @param valores
             * @return o total
             */
            static int somarTudo(QList<int> valores);

            static double somarTudo(QList<double> valores);

            static double truncateDouble(double valor, int precisao = 2);

            static double porcentagem(double quantidadeTotal, double quantidadePacial, int precisao = 2);

            static bool isFracionado(double valor, int precisao = 2);

            static bool between(double value, double lessValue, double greaterValue);

            static double fromString(QString texto);

            static double fromStringMoney(QString texto);

            static bool diferenteDeZero(double valor);

        private:

            explicit DoubleUtil(QObject *parent = 0);

	};

}
#endif // DOUBLEUTIL_H

