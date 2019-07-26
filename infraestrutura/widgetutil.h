#ifndef WIDGETUTIL_H
#define WIDGETUTIL_H

//#include "infraestrutura/infraestrutura_global.h"

#include <QWidget>
#include <QColor>
#include <QMessageBox>
#include <QTreeWidget>
#include <QTableWidget>
#include <QEasingCurve>
#include <QFont>

class BaseException;

namespace gm
{
    class GMErro;

    class WidgetUtil : public QObject
    {
        Q_OBJECT

        public:

            /* ######################### Outros Gets e Sets ######################### */

            static QColor amarelo();
            static QColor azul();
            static QColor azulBebe();
            static QColor azulEscuro();
            static QColor azulMarinho();
            static QColor azulGMCore();
            static QColor azulForte();
            static QColor branco();
            static QColor cinza();
            static QColor cinzaEscuro();
            static QColor creme();
            static QColor laranja();
            static QColor amareloClaro();

            /**
             * @brief lilas #0903AB
             */
            static QColor lilas();
            static QColor marrom();
            static QColor preto();
            static QColor verdeClaro();
            static QColor rosa();
            static QColor roxoMedio();
            static QColor roxo();

            /**
             * @brief lilas #4A8359
             */
            static QColor verdeEscuro();
            static QColor verdeNeutro();
            static QColor vermelho();
            static QColor vermelhoMuitoClaro();
            static QColor salmao();

            /* ########################## Métodos de Ação ########################## */

            static bool alertarOperacao(QString mensagem);

            static void centralizar(QWidget* widget);

            static bool confirmarAcao(QString titulo, QString mensagem);

            /**
             * @author Rayrone
             * @date   30/12/2014
             * @brief  confirmacao função usada para realizar a confirmação de alguma operação do usuário.
             * @param  mensagem a mensagem de confirmação exibida ao usuário
             * @return TRUE caso o usuário confirme a operação, FALSE caso contrário
             */
            static bool confirmacao(QString mensagem);

            static void mensagem(gm::GMErro* erro);

            static void mensagem(gm::GMErro erro);

            static void mensagem(QString texto);

            static void mensagemErro(gm::GMErro* erro);

            /**
             * @author Flavio Portela
             * @brief mensagemErro
             * @param mensagem
             */
            static void mensagemErro(QString mensagem);

            static void mensagemAlerta(QString mensagem);

            static void mensagemErroTransacao();

//            static void mensagem(BaseException &e);

            static void mensagem(GMErro erro, QWidget *parent);

            static void ajustarTamanhoConformePai(QWidget *widget, QWidget* parent);

            /**
             * @author Carlos Alberto / Rodrigo Matos
             * @date 17/06/2015
             * @brief animacaoWidget
             * @param isVisivel
             * @param rectShow
             * @param rectHide
             * @param ObjAnimado
             * @param tipoAnimacao
             */
            static void animacaoWidget(bool isVisivel, QRect rectShow, QRect rectHide, QWidget* ObjAnimado, QEasingCurve tipoAnimacao = QEasingCurve::InOutBack);

            /**
             * @author Flavio Portela
             * @brief cssForDWidget
             * @return
             */
            static QString cssForWidget();

            /**
             * @author Flavio Portela/Allyx Cristinano
             * @brief cssForDWidgetForm
             * @return
             */
            static QString cssForWidgetForm();

            /**
             * @author Flavio Portela/Allyx Cristinano
             * @brief cssForDWidgetMobile
             * @return
             */
            static QString cssForWidgetMobile();

            /**
             * @author Daniel Santos
             * @date 19/12/2015
             * @brief mensagemAlertaComFonte
             * @param mensagem uma string contendo a descrição a descrição para montar a mensagem
             * @param font
             */
            static void mensagemAlertaComFonte(QString mensagem, QFont font);

            /**
             * @author Carlos Alberto
             * @brief mensagem
             * @param mensagem
             * @param cabecalho
             */
            static void mensagem(QString titulo, QString mensagem);

            // ###################### Getters & Setters ######################## //

            static void mensagemInformacao(QString msg);

            static void mensagemInformacao(QString msg, QWidget* parent);

    private:
            explicit WidgetUtil(QObject* parent = 0);

            // ###################### Métodos Ação ######################## //

            /**
             * @author Arthur Turrini
             * @brief criarWidgetDeEspera
             * @param icone
             * @param mensagem
             */
            static void criarWidgetDeEspera(QMessageBox::Icon icone, const QString &titulo, const QString &mensagem, QFont font = QFont(), QWidget *parent = 0);

    };
}

#endif // WIDGETUTIL_H
