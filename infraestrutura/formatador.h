#ifndef FORMATADOR_H
#define FORMATADOR_H

#include <QLocale>
#include <QDate>

class QString;

namespace gm
{
    class Formatador
    {
        public:

            /* ########################## Métodos de Ação ########################## */

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarCEP função usada para colocar um CEP no formato 99999-999
             * @param   cep o CEP que deseja-se formatar
             * @return  uma string no formato 99999-999
             */
            static QString formatarCEP(long long cep);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarCEP função usada para colocar um CEP no formato 99999-999
             * @param   cep o CEP que deseja-se formatar
             * @return  uma string no formato 99999-999
             */
            static QString formatarCEP(const QString& cep);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarChaveNfeCte função usada para colocar uma chave NFe ou CTe no formato
             *          9999 9999 9999 9999 9999 9999 9999 9999 9999 9999 9999
             * @param   chave a chave NFe ou CTe que deseja-se formatar
             * @return  uma string no formato 9999 9999 9999 9999 9999 9999 9999 9999 9999 9999 9999
             */
            static QString formatarChaveNfeCte(const QString& chave);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarCNPJ função usada para colocar um cnpj no formato 99.999.999/9999-99
             * @param   cnpj o cnpj que deseja-se formatar
             * @return  uma string cnpj no formato 99.999.999/9999-99
             */
            static QString formatarCNPJ(long long cnpj);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarCPF função usada para colocar um cpf no formato 999.999.999-99
             * @param   cpf o cpf que deseja-se formatar
             * @return  uma string cpf no formato 999.999.999-99
             */
            static QString formatarCPF(long long cpf);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarFax função usada para colocar um fax no formato (99) 99999999
             * @param   ddd o número do ddd a ser usado para formatar o número do fax
             * @param   numeroFax o número do fax propriamente dito
             * @return  uma string fax no formato (999) 99999999
             */
            static QString formatarFax(QString ddd, QString numeroFax);

            /**
             * @author  Daniel Santos
             * @date    indefinida
             * @brief   formatarInscricaoEstadual função usada para colocar um número de inscrição no formato 999.999.9999
             * @param   ddd o número do ddd a ser usado para formatar o número do fax
             * @param   numeroFax o número do fax propriamente dito
             * @return  uma string inscrição estadual no formato 999.999.999
             */
            static QString formatarInscricaoEstadual(long long inscricaoEstadual);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarMoeda função usada para colocar um numero no formato R$ [###.###.###],[##]
             * @param   numero o número que deseja-se formatar
             * @param   precisao a quantidade de casas decimais usadas na formatação do número
             * @return  um número no formato R$ [###.###.###],[##]
             */
            static QString formatarMoeda(double numero, int precisao = 2);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarMoeda função usada para colocar um numero no formato R$ [###.###.###],[##]
             * @param   numero o número que deseja-se formatar
             * @param   precisao a quantidade de casas decimais usadas na formatação do número
             * @return  um número no formato R$ [###.###.###],[##]
             */
            static QString formatarMoeda(QString numero, int precisao = 2);

            /**
             * @author  Rayrone
             * @date    indefnida
             * @brief   formatarNumero função para colocar um numero no formato [###.###.###],[##]
             * @param   numero o número que deseja-se formatar
             * @param   precisao a quantidade de casas decimais usadas na formatação do número
             * @return  um número no formato [###.###.###],[##]
             */
            static QString formatarNumero(double numero, int precisao = 2);

            /**
             * @brief formatarValorNotacaoContabil
             * @param numero
             * @param precisao
             * @return um número no formato [###.###.###],[##], caso ele seja negativo, retorna-se o número entre parenteses
             * @author Carlos Alberto (variação do método do Rayrone - formatarNumero)
             */
            static QString formatarValorNotacaoContabil(double numero, int precisao = 2);

            /**
             * @author  Rayrone
             * @date    indefnida
             * @brief   formatarNumero função para colocar um numero no formato [###.###.###],[##]
             * @param   numero o número que deseja-se formatar
             * @param   precisao a quantidade de casas decimais usadas na formatação do número
             * @return  um número no formato [###.###.###],[##]
             */
            static QString formatarNumero(QString numero, int precisao = 2);

            /**
             * @author Flavio Portela
             * @brief   formatarPeso função para colocar um numero no formato [###.###.###],[###]
             * @param   numero o número que deseja-se formatar
             * @param   precisao a quantidade de casas decimais usadas na formatação do número
             * @return  um número no formato [###.###.###],[##]
             */
            static QString formatarPeso(double numero, int precisao = 3);

            /**
             * @author Flavio Portela
             * @brief   formatarPeso função para colocar um numero no formato [###.###.###],[###]
             * @param   numero o número que deseja-se formatar
             * @param   precisao a quantidade de casas decimais usadas na formatação do número
             * @return  um número no formato [###.###.###],[##]
             */
            static QString formatarPeso(QString numero, int precisao = 3);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarPorcentagem função para colocar um numero no formato de porcentagem [###.###.###],[##] %
             * @param   numero o número que deseja-se formatar
             * @param   precisao a quantidade de casas decimais usadas na formatação do número
             * @return  um número no formato [###.###.###],[##] %
             */
            static QString formatarPorcentagem(double numero, int precisao = 2);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarPorcentagem função para colocar um numero no formato de porcentagem [###.###.###],[##] %
             * @param   numero o número que deseja-se formatar
             * @param   precisao a quantidade de casas decimais usadas na formatação do número
             * @return  um número no formato [###.###.###],[##] %
             */
            static QString formatarPorcentagem(QString porcentagem, int precisao = 2);

            /**
             * @author  Rayrone
             * @date    indefinida
             * @brief   formatarTelefone função usada para colocar um telefone no formato (99) 99999999
             * @param   ddd o número do ddd a ser usado para formatar o número do telefone
             * @param   numeroTelefone o número do telefone propriamente dito
             * @return  uma string telefone no formato (999) 99999999
             */
            static QString formatarTelefone(QString ddd, QString numeroTelefone);

            /**
             * @author Flavio Portela
             * @date    30.06.2015
             * @brief
             * @param   formata data para formatacao padrao
             */
            static QString formataData(QDate date);

            /**
             * @author Flavio Portela
             * @date    30.06.2015
             * @brief
             * @param   formata data para formatacao padrao
             */
            static QString formataData(QDateTime date);

            /**
             * @author Flavio Portela
             * @date    30.06.2015
             * @brief
             * @param   formata data para formatacao padrao
             */
            static QString formataDataHora(QDateTime date);

            /**
             * @author Flavio Portela
             * @date    07.08.2015
             * @return  formata data com mascara predefinida
             */
            static QString formataData(QString data);

            /**
             * @author  Daniel Santos
             * @date    31/12/2014
             * @brief   formatarDataPorExtensoCompleta função usada para colocar uma data no formato por extenso
             * @param   data o valor da data a ser usado para formatar a data passada como parâmetro
             * @return  uma string data no formato dd de MM(mês por extenso) de AAAA
             */
            static QString formataDataPorExtensoCompleta(QDate data);

            /**
             * @author  Daniel Santos
             * @date    31/12/2014
             * @brief   formatarDataPorExtensoSemDiaSemana função usada para colocar uma data no formato por extenso
             * @param   data o valor da data a ser usado para formatar a data passada como parâmetro
             * @return  uma string data no formato dia-da-semana, dd de MM(mês por extenso) de AAAA
             */
            static QString formataDataPorExtensoSemDiaSemana(QDate data);

            /**
             * @author  Daniel Santos
             * @date    14/04/2015
             * @brief   formataDataComoAnoMes função usada para colocar uma data num formato por extenso
             * @param   anoMes valor inteiro a ser usado para formatar como parâmetro
             * @return  uma string data no formato MMM/yyyy, MMM(mês por extenso) de AAAA
             */
            static QString formataDataComoAnoMes(int anoMes);

            /**
             * @author  Daniel Santos
             * @date    14/04/2015
             * @brief   formataDataComoAnoMesCompleta função usada para colocar uma data num formato por extenso
             * @param   anoMes valor inteiro a ser usado para formatar como parâmetro
             * @return  uma string data no formato MMMM/yyyy, MMMM(mês por extenso) de AAAA
             */
            static QString formataDataComoAnoMesCompleta(int anoMes);

            /**
             * @author Flavio Portela
             * @date    07.08.2015
             * @return  formata hora com mascara predefinida
             */
            static QString formataHora(QTime hora);

            /**
             * @author Flavio Portela
             * @date    07.08.2015
             * @return  formata hora com mascara predefinida
             */
            static QString formataHora(QString hora);

            /**
             * @author Johnnys Lima
             * @date    15.10.2015
             * @return  formata a placa de veiculos
             */
            static QString formatarPlacaVeiculo(QString placaVeiculo);

            /**
             * @brief formatarCargaHoraria
             * @param cargaHoraria
             * @return formata carga horaria
             * @author Carlos Alberto
             */
            static QString formatarCargaHoraria(QString cargaHoraria);


            static long long formatarCodigoBarras(QString codigo);

        private:

            Formatador();

            /* ############################## Atributos ############################ */

            static const QLocale _locale;
    };
}

#endif // FORMATADOR_H
