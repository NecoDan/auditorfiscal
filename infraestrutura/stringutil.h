#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <QColor>
#include <QObject>
#include <QString>
#include <QStringList>

#define stringify( name ) # name

class StringUtil
{
	public:

		StringUtil();

		~StringUtil();

		/* ########################## Métodos de Ação ########################## */

		static QString adicionarQuebraNaStringPorIntervalo(QString string, int intervalo);

		QString centralizar(QString s, int size);

		QString centralizar(QString s, int size, QString pad);

		bool isEmpty(QString value);

		static bool mesmaRaizCnpj(QString cnpj1, QString cnpj2);

		static QString primeiraLetraMaiuscula(QString nome);

		/**
		 * @author Clézio
		 * @brief StringUtil::primeiraLetraNomeMaiuscula
		 * @param texto função responsável por converter o texto com as primeiras letras de cada nome em maiuscula.
		 * @return retorna o texto passado com a primeira letra de cada nome em maiuscula e o restante em minuscula.
		 */
		static QString primeiraLetraNomeMaiuscula(QString nome);

		/**
		 * @author Ueider Moraes, Rayrone
		 * @brief StringUtil::removerAcentos
		 * @param texto função responsável por remover acentos em um texto
		 * @return retorna o texto passado sem acentos.
		 */
		static QString removerAcentos(QString texto);

		/**
		 * @author Daniel Santos
         * @brief  removerCaracterEspeciais
         * @param  texto função responsável por remover caracteres especiais em um texto
		 * @return retorna o texto passado sem caracteres.
		 */
		static QString removerCaracterEspeciais(QString texto);

		static QString removerEspacosDuplicados(QString string);

		//Rever a função abaixo, está retirando valores além dos zeros
		static QString removerZerosIniciais(QString texto);

        static QString removerCaracteresNaoTextuais(QString string);

        static QString removerSimbolos(QString string);

		static QString replaceAll(QString valor, QString valorAserSubisttituido, QString subistituicao);

		static QString retiraCaracteresNaoNumericos(QString valor);

		/**
		 * @author Rayrone
		 * @date   14/02/2015
		 * @brief  toBool função responsável por converter uma string em bool. A ideia dessa função é tratar todos os possíveis
		 *         valores que podem ser passar por tipo bool, por exemplo: "true", "false", "TRUE", "FALSE", "t", "T", "f", "F", "0" ou "1".
		 * @return o valor true ou false correspondente a string passada. Em caso de string que não corresponda a nenhuma das opções suportadas
		 *         pela função, o valor false é retornado.
		 */
		static bool toBool(QString valor);

		static QStringList toStringList(QList<long long> lista);

		/**
		 * @brief numeroFormatadoComZerosAEsquerda Função que recebe uma string e insere a quantidade de zeros a esquerda da mesma que você passar como parâmetro
		 * @param numero o n
		 * @param quantidadeZerosEsquerda
		 * @return
		 */
        static QString inserirZerosAEsquerda(QString string, int tamanhoMaximoString);

		static QString inserirZerosAEsquerda(int string, int tamanhoMaximoString);

		static QString boolToString(bool trueOrFalse, bool emptyIfFalse = false);

		/**
		 * @author Rayrone
		 * @date   18/09/2015
		 * @brief  caracteres
		 * @param  caractere
		 * @param  qtd
		 * @param  separador
		 * @return
		 */
		static QString caracteres(QChar caractere, int qtd, QChar separador);

		static QString rightPad(QString value,QChar padChar , int size);

		static QString lefttPad(QString value, QChar padChar, int size);

		static QColor stringHexToColor(QString cor);

        /**
         * @author Daniel Santos
         * @date   18/03/2016
         * @brief  extrairConteudoAPartir
         * @param  valor uma string contendo como conteúdo
         * @param  posicao
         * @param  quantidadeAExtrair
         * @return retorna uma string
         */
        static QString extrairConteudoAPartir(QString valor, int posicao, int quantidadeAExtrair);

        /**
         * @author Daniel Santos
         * @date   18/03/2016
         * @brief  extrairValorSemCaracteres
         * @param  valor
         * @param  qtdeCasasDecimais
         * @return string formatada sem caracteres
         */
        static QString extrairValorSemCaracteres(double valor, int qtdeCasasDecimais);

        static QStringList listDoubleToStringList(QList<double> valores);

        static QStringList listStringToStringList(QList<QString> valores);

        /**
         * @author Daniel Santos
         * @date   05/07/2016
         * @brief  equals
         * @param  value1 string contendo como conteúdo a referência do primeiro valor a ser comparado.
         * @param  value2 string contendo como conteúdo o valor para ser comparado com o primeiro.
         * @return TRUE caso excluído com sucesso, caso contrário FALSE.
         */
        static bool equals(QString value1, QString value2);

        static QString extrairConteudoDaString(QString texto, int posicao, int quantidadeAExtrair);

        static QString addQuote(QString valor);

        /**
         * @author Daniel Santos
         * @date   01/04/2017
         * @brief  extrairListStringToStringListPor
         * @param  separador
         * @param  conteudo uma string contendo todo o conteudo
         * @return uma QStringList
         */
        static QStringList extrairListStringToStringListPor(QString separador, QString conteudo);

        /**
          * @author Daniel Santos
          * @date   23/06/2017
          * @brief  adicionaConteudoVazio método responsável por
          * @param  strConteudo
          * @param  tamanho
          * @return uma string contendo um conteudo a partir do tamanhao definido vazio.
          */
       static QString adicionaConteudoVazio(QString strConteudo, int tamanho);

       static QByteArray encodeString(QString texto);

       /**
        *@author  Daniel Santos
        * @date   04/07/2018
        * @brief  cnpjRaizMatriz string que contém um CNPJ válido para extração da raiz do mesmo;
        * @param  cnpj um objeto de QString contendo como conteúdo um CNPJ, de prefência válido
        * @param  removeZeroInicial TRUE caso seja necessário remover o zero inicial, do contrário FALSE.
        * @return um objeto QString contendo somente a raiz do CNPJ pertence à filial.
        */
       static QString cnpjRaiz(QString cnpj, bool removeZerioInicial = false);

};

#endif // STRINGUTIL_H
