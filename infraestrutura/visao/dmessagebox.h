#ifndef DMESSAGEBOX_H
#define DMESSAGEBOX_H

//#include "infraestrutura/infraestrutura_global.h"
#include "infraestrutura/gm_erro.h"

#include <QObject>
#include <QMessageBox>
#include <QPushButton>
#include <QMap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QLabel>
#include <QDebug>

namespace gm
{
    class DMessageBox : public QObject
    {
        Q_OBJECT

    public:

        enum Tipo{PERGUNTA = 0, INFORMACAO = 1, ALERTA = 2, CRITICO = 3, SEM_ERRO = 4, INFRAESTRUTURA = 5, BANCO = 6};

        explicit DMessageBox(QString texto, Tipo tipo = PERGUNTA, QObject *parent = 0, bool orientacaoBotoesVertical = true);

        explicit DMessageBox(Tipo tipo = PERGUNTA, QObject *parent = 0, bool orientacaoBotoesVertical = true);

        explicit DMessageBox(QString texto, QObject *parent);

        void adicionarOpcao(QString opcao, QString icone = "");

//        int exec();

        void setLayoutBotoesVertical(bool layoutBotoesVertical);

        bool clicouFechar();

        static bool question(QString mensagem, QString titulo = "Confirmação", QString textoBotaoSim = "Sim", QString textoBotaoNao = "Não", bool comIcone = true);
        static bool genericQuestion(QString mensagem, QString titulo = "", QString textoBotao1 = "", QString textoBotao2 = "");

        void setOrientacaoBotoes(bool orientacaoBotoesVertical);

    private:

        QList<QString> _opcoes;

        QList<QString> _icones;

        bool _orientacaoBotoesVertical;

        QBoxLayout *layoutTexto();

        QBoxLayout *layoutBotoes();

        QString _titulo;

        QString _texto;

        int _botaoClicado;

        Tipo _tipo;

        QDialog* _dialog;

        QString toStringTipo();

        Tipo tipoPorGMErro(gm::GMErro lastError);

    private slots:

        void setBotaoClicado();
    };
}

#endif // DMESSAGEBOX_H
