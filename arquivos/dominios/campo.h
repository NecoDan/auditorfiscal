#ifndef CAMPO_H
#define CAMPO_H

#include <QDate>
#include <QLocale>
#include <QObject>
#include <QVariant>

namespace gm_arquivo
{
    class Campo : public QObject
    {
        Q_OBJECT

        public:

            enum TipoDadoCampo
            {
                AlfaNumerico, Numerico, Moeda, Data, Hora, Texto, DataVisualMix, MoedaVisualMix, BoolVisualMix, AlfaNumericoCarone, NumericoCarone
            };

            explicit Campo(QVariant valor, QString descricao, int qtdDigitos, bool qtdExataCaracteres = false, int qtdCasasDecimais = 0, TipoDadoCampo tipoDado = AlfaNumerico, QObject* parent = 0);

            explicit Campo(bool isValorDouble, double valorDouble, QString descricao, int qtdDigitos, bool qtdExataCaracteres = false, int qtdCasasDecimais = 0, TipoDadoCampo tipoDado = AlfaNumerico, QObject* parent = 0);

            /* ################################ Gets e Sets ################################ */

            QString descricao();
            void setDescricao(QString descricao);

            // Posicao iniciada em 1
            int posicaoInicial();
            void setPosicaoInicial(int posicaoInicial);

            int qtdCasasDecimais();
            void setQtdCasasDecimais(int qtdCasasDecimais);

            int qtdDigitos();
            void setQtdDigitos(int qtdDigitos);

            bool qtdExataCaracteres() const;
            void setQtdExataCaracteres(bool qtdExataCaracteres);

            TipoDadoCampo tipoDadoCampo();
            void setTipoDadoCampo(Campo::TipoDadoCampo tipoCampo);

            QVariant valor();
            void setValor(QVariant valor);

            /* ############################## Metodos de Acão ############################## */

            void extrairValor(QString& linha);

            inline int tamanho();

            QString toString();

        private:

            /* ################################# Atributos ################################# */

            QString         _descricao;
            int             _posicaoInicial;
            int             _qtdCasasDecimais;
            int             _qtdDigitos;
            bool            _qtdExataCaracteres;
            TipoDadoCampo   _tipoDadoCampo;
            QVariant        _valor;
            double          _valorDouble = 0.00;
            bool            _isValorDouble = false;

    };
}

#endif // CAMPO_H
