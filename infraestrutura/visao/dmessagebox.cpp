#include "dmessagebox.h"
#include "infraestrutura/constantes/constantes_icones.h"
#include "infraestrutura/widgetutil.h"
//#include "infraestrutura/utilitarios/stringutil.h"
//#include "infraestrutura/visao/subclasses_qt/dpushbutton.h"
//#include "infraestrutura/visao/subclasses_qt/ddialogmobile.h"
//#include "infraestrutura/visao/subclasses_qt/dlabel.h"
//#include "infraestrutura/visao/subclasses_qt/dlabeltitle.h"
#include <QTimer>

const int QUANTIDADE_MILESIMOS_SEGUNDO_POR_CARACTERE = 80;

namespace gm
{
	DMessageBox::DMessageBox(QString texto, Tipo tipo, QObject *parent, bool orientacaoBotoesVertical) : QObject(parent)
	{
		_texto = texto;
		_tipo = tipo;
		_orientacaoBotoesVertical = orientacaoBotoesVertical;
		_botaoClicado = 0;
		_dialog = 0;
	}

	DMessageBox::DMessageBox(DMessageBox::Tipo tipo, QObject *parent, bool orientacaoBotoesVertical) : QObject(parent)
	{
		_tipo = tipo;
		_orientacaoBotoesVertical = orientacaoBotoesVertical;
		_botaoClicado = 0;
		_dialog = 0;
	}

	DMessageBox::DMessageBox(QString texto, QObject *parent) : QObject(parent)
	{
		_texto = texto;
		_tipo = PERGUNTA;
		_botaoClicado = 0;
		_dialog = 0;
		_orientacaoBotoesVertical = false;
	}

	bool DMessageBox::question(QString mensagem, QString titulo, QString textoBotaoSim, QString textoBotaoNao, bool comIcone)
	{
		QMessageBox janelaAlerta;
		janelaAlerta.setIcon(QMessageBox::Question);
		janelaAlerta.setWindowTitle(titulo);
		janelaAlerta.setText(mensagem);

        QPushButton* botaoNao = new QPushButton(textoBotaoNao);
		botaoNao->setShortcut(Qt::Key_Escape);
		botaoNao->setAutoDefault(false);
		botaoNao->setFocusPolicy(Qt::NoFocus);

        QPushButton* botaoSim = new QPushButton(textoBotaoSim);
		botaoSim->setShortcut(Qt::Key_Enter | Qt::Key_Return);
		botaoSim->setAutoDefault(false);
		botaoSim->setFocusPolicy(Qt::NoFocus);

        janelaAlerta.addButton(botaoSim, QMessageBox::AcceptRole);
		janelaAlerta.addButton(botaoNao, QMessageBox::RejectRole);

		if (comIcone)
		{
			botaoNao->setIcon(QIcon(icones::sistema::FECHAR));
			botaoSim->setIcon(QIcon(icones::sistema::CHECKED));
		}

		janelaAlerta.exec();

        return janelaAlerta.clickedButton() == botaoSim;
    }

    bool DMessageBox::genericQuestion(QString mensagem, QString titulo, QString textoBotao1, QString textoBotao2)
    {
        QMessageBox janelaAlerta;
        janelaAlerta.setIcon(QMessageBox::Question);
        janelaAlerta.setWindowTitle(titulo);
        janelaAlerta.setText(mensagem);

        QPushButton* botao1 = new QPushButton(textoBotao1);
        botao1->setAutoDefault(false);
        botao1->setFocusPolicy(Qt::NoFocus);

        QPushButton* botao2 = new QPushButton(textoBotao2);
        botao2->setAutoDefault(false);
        botao2->setFocusPolicy(Qt::NoFocus);

        janelaAlerta.exec();

        return janelaAlerta.clickedButton() == botao1;
    }

	void DMessageBox::setOrientacaoBotoes(bool orientacaoBotoesVertical)
	{
		_orientacaoBotoesVertical = orientacaoBotoesVertical;
	}

	// Utilizei duas listas para não sofrer com a ordenação de chaves do mapa
	void DMessageBox::adicionarOpcao(QString opcao, QString icone)
	{
		_opcoes << opcao.toUpper();
		_icones << icone;
	}

//	int DMessageBox::exec()
//	{
//		_dialog = new DDialogMobile();
//		_dialog->setWindowTitle(this->toStringTipo());
//        _dialog->setStyleSheet("QLabel{background-color: yellow;color: black;font: 12pt; font-weight: bold; padding-top: 20px;}");
//		QVBoxLayout* layout = new QVBoxLayout();

//		QFont fonte;
//		fonte.setBold(true);
//		fonte.setPointSize(10);

//        DLabelTitle* titulo = new DLabelTitle(this->toStringTipo());
//		titulo->setWordWrap(true);
//        titulo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//		titulo->setFont(fonte);
//        titulo->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
//        titulo->setMaximumHeight(35);

//		QBoxLayout* layoutTitulo = new QVBoxLayout;
//		layoutTitulo->addWidget(titulo);

//		QBoxLayout* layoutTexto = NULL;
//		if (!_texto.isEmpty())
//		{
//            QLabel* texto = new QLabel(_texto.toUpper());
//			texto->setWordWrap(true);
//			texto->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

//			layoutTexto = new QVBoxLayout;
//			layoutTexto->setContentsMargins(2,2,2,2);
//            layoutTexto->addWidget(texto);
//            layoutTexto->setContentsMargins(2,2,2,2);
//		}

//		QBoxLayout* layoutBotoes = this->layoutBotoes();

//		int i = 0;
//		foreach (QString opcao, _opcoes)
//		{
//			QPushButton* botaoOpcao = new DPushButton(QIcon(_icones.at(i)), StringUtil::adicionarQuebraNaStringPorIntervalo(opcao, 20).toUpper());
//			botaoOpcao->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//			botaoOpcao->setShortcut(QKeySequence(QString::number(i + 1)));
//			botaoOpcao->setAutoDefault(false);

//			connect(botaoOpcao, SIGNAL(clicked(bool)), this, SLOT(setBotaoClicado()));
//			layoutBotoes->addWidget(botaoOpcao);
//			i++;
//		}

//		QPushButton* botaoFechar = new DPushButton(QIcon(icones::sistema::FECHAR), "FECHAR");
//		botaoFechar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//		botaoFechar->setShortcut(Qt::Key_Escape);
//		botaoFechar->setAutoDefault(false);
//		connect(botaoFechar, SIGNAL(clicked(bool)), this, SLOT(setBotaoClicado()));
//		layoutBotoes->addWidget(botaoFechar);

//		layout->addItem(layoutTitulo);

//		if (layoutTexto != NULL)
//		{
//			layout->addItem(layoutTexto);
//		}

//		layout->addItem(layoutBotoes);
//		layout->setContentsMargins(0,0,0,0);
//		_dialog->setLayout(layout);

//		WidgetUtil::ajustarTamanhoConformePai(_dialog, dynamic_cast<QWidget*>(this->parent()));

//		_dialog->exec();

//		return _botaoClicado;
//	}

	QBoxLayout *DMessageBox::layoutBotoes()
	{
		QBoxLayout* layoutBotoes = NULL;

		if (_orientacaoBotoesVertical)
		{
			layoutBotoes = new QVBoxLayout();
		}
		else
		{
			layoutBotoes = new QHBoxLayout();
		}

		layoutBotoes->setSpacing(5);

		return layoutBotoes;
	}

	void DMessageBox::setBotaoClicado()
	{
		QPushButton* botaoClicado = qobject_cast<QPushButton*>(QObject::sender());

		if (botaoClicado != NULL)
		{
			if (botaoClicado->text().toUpper() != "FECHAR")
			{
				for (int indexOpcao = 0; indexOpcao < _opcoes.size(); indexOpcao++)
				{
					QString opcao = _opcoes.at(indexOpcao);
					if (opcao == botaoClicado->text().remove("\n"))
					{
						_botaoClicado = indexOpcao;
						break;
					}
				}
			}
			else
			{
				_botaoClicado = _opcoes.size();
			}
		}

		_dialog->close();
	}

	void DMessageBox::setLayoutBotoesVertical(bool layoutBotoesVertical)
	{
		_orientacaoBotoesVertical = layoutBotoesVertical;
	}

	bool DMessageBox::clicouFechar()
	{
		return _opcoes.size() == _botaoClicado;
	}

	QString DMessageBox::toStringTipo()
	{
		if (_tipo == PERGUNTA)
		{
			return "PERGUNTA";
		}
		else if (_tipo == INFORMACAO)
		{
			return "INFORMAÇÃO";
		}
		else if (_tipo == ALERTA)
		{
			return "ALERTA";
		}
		else if (_tipo == CRITICO)
		{
			return "CRÍTICO";
		}

		return "INDEFINIDO";
	}

	DMessageBox::Tipo DMessageBox::tipoPorGMErro(GMErro lastError)
	{
		if (lastError.tipo() == GMErro::VALIDACAO || lastError.tipo() == GMErro::NEGOCIO || lastError.tipo() == GMErro::ALERTA)
		{
			return Tipo::ALERTA;
		}
		else if (lastError.tipo() == GMErro::BANCO || lastError.tipo() == GMErro::INFRAESTRUTURA)
		{
			return Tipo::INFRAESTRUTURA;
		}

		return Tipo::SEM_ERRO;
	}
}

#include "moc_dmessagebox.cpp" // inclusao do MOC desta classe
