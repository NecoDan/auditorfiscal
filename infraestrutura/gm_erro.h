#ifndef GMERRO_H
#define GMERRO_H

#include <QString>
#include <QMap>
#include <QSqlError>

namespace gm
{
    class GMErro
	{
		public:

            enum TipoErro {SEM_ERRO = 0, VALIDACAO = 1, NEGOCIO = 2, BANCO = 3, ALERTA = 4, INFRAESTRUTURA = 5};

			explicit GMErro(QString mensagem = "Sem erro", TipoErro tipo = SEM_ERRO, QString classe="");
            explicit GMErro(QSqlError erro);

			/* ############################ Gets e Sets ############################ */

			QMap<QString, QString> camposInvalidos();
			void setCamposInvalidos(QMap<QString, QString> value);

			QString classe() const;

            QString mensagem() const;

            QString message(){
                return this->mensagem();
            }

            QString mensagemSimples(){
                return this->message();
            }

            QString text() const;

			TipoErro tipo() const;

            TipoErro type() {
                return this->tipo();
            }

			/* ########################## Métodos de Ação ########################## */

			void adicionarCampoInvalido(QString campo, QString detalhe);

			void clear();

			static GMErro fromPointer(GMErro* gmerro);

			bool isAlerta();

			bool isErro();

			bool isSucesso();

			static GMErro* toPointer(GMErro gmerro);

			QString toString();

			void setMensagem(QString value);

			void setTipo(TipoErro tipo);

			bool temCamposInvalidos();

            bool isValid();

			/* ############################## Operadores ############################ */

			void operator =( QSqlError error);

			void operator =( GMErro* error);

		private:

			QMap<QString, QString> _camposInvalidos;

			QString _classe;

			QString _mensagem;

			TipoErro _tipo;
	};
}

#endif // GMERRO_H
