#include "widgetutil.h"

#include "infraestrutura/gm_erro.h"
#include "infraestrutura/exception_baseexception.h"
//#include "infraestrutura/utilitarios/gm_itemutil.h"


#include <QApplication>
#include <QColor>
#include <QComboBox>
#include <QIcon>
#include <QStyle>
#include <QLabel>
#include <QPixmap>
#include <QScreen>
#include <QTextEdit>
#include <QSpacerItem>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QAbstractScrollArea>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QFont>

#include "infraestrutura/visao/dmessagebox.h"

namespace gm
{

	WidgetUtil::WidgetUtil(QObject* parent) : QObject(parent)
	{
	}

	// Por favor, nao mudar sem antes perguntar, se possivel.
	void WidgetUtil::criarWidgetDeEspera(QMessageBox::Icon icone, const QString &titulo, const QString &mensagem, QFont font, QWidget *parent)
	{
		QStyle *style = QApplication::style();
		QWidget *widget = new QWidget(parent);
		widget->setWindowModality(Qt::ApplicationModal);
		widget->setAttribute(Qt::WA_DeleteOnClose, true);
		widget->setWindowFlags(Qt::Window);
		widget->setWindowTitle(titulo);
		widget->setStyleSheet(qApp->styleSheet());
        widget->resize(400,110);
        widget->setFixedSize(widget->size());

		QDesktopWidget desktop;
        //widget->setMaximumWidth(desktop.screenGeometry().width() * 0.5);
//		int size = mensagem.length();
//		double fator = 0;
//		if(size > 1000)
//			fator = size / 1000 / 100;
//		if(desktop.screenGeometry().width() <= 640)
//			widget->resize(QSize(220 + 220 * fator, 64 + 64 * fator));
//		else
//			widget->resize(QSize(500 + 500 * fator, 140 + 140 * fator));

		QIcon tmpIcon;
		switch (icone) {
		case QMessageBox::Information:
			tmpIcon = style->standardIcon(QStyle::SP_MessageBoxInformation, 0);
			break;
		case QMessageBox::Warning:
			tmpIcon = style->standardIcon(QStyle::SP_MessageBoxWarning, 0);
			break;
		case QMessageBox::Critical:
			tmpIcon = style->standardIcon(QStyle::SP_MessageBoxCritical, 0);
			break;
		case QMessageBox::Question:
			tmpIcon = style->standardIcon(QStyle::SP_MessageBoxQuestion, 0);
		default:
			break;
		}

		QLabel *iconLabel = new QLabel(widget);
		if(desktop.screenGeometry().width() <= 640)
			iconLabel->setPixmap(tmpIcon.pixmap(24, 24));
		else
			iconLabel->setPixmap(tmpIcon.pixmap(48, 48));

		QTextEdit *label = new QTextEdit(widget);
		label->setText(mensagem);
		label->setMaximumWidth(widget->maximumWidth() * 0.8);
		label->setFrameShape(QFrame::NoFrame);
		label->setReadOnly(true);
		label->setAttribute(Qt::WA_DontShowOnScreen);
		label->setFocusPolicy(Qt::NoFocus);
		label->setFont(font);
		label->show();

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        QHBoxLayout *hbox = new QHBoxLayout();
        hbox->addItem(spacer);

		QPushButton *botao = new QPushButton("Ok", widget);
		botao->setMaximumWidth(120);
		hbox->addWidget(botao);

		QGridLayout *grid = new QGridLayout(widget);
		grid->addWidget(iconLabel, 0, 0, 1, 1);
		grid->addWidget(label, 0, 1, 1, 1);
		grid->addLayout(hbox, 1, 0, 1, 2);
		widget->setLayout(grid);

		connect(botao, SIGNAL(clicked(bool)), widget, SLOT(close()));

		iconLabel->show();
		label->show();
		botao->show();
		widget->show();

//		int vSize = 0;
//		if(desktop.screenGeometry().height() <= 480) {
//			//vSize = 140 - (botao->height() + grid->verticalSpacing() + 11);
//			widget->resize(desktop.screenGeometry().width() * 0.80, 110);
//		}
//		else {
//			vSize = label->document()->size().height();
//			label->setMinimumSize(label->width(), vSize);
//		}

		gm::WidgetUtil::centralizar(widget);
		botao->setDefault(true);
		botao->setFocus();
	}

	bool WidgetUtil::alertarOperacao(QString mensagem)
	{
		return gm::DMessageBox::question(mensagem + "\n Deseja continuar mesmo assim?");
	}

	void WidgetUtil::centralizar(QWidget* widget)
	{
		if(widget->isFullScreen())
			return;

		//Posiciona formulario ao centro da tela.
		QRect position = widget->frameGeometry();
		position.moveCenter(QDesktopWidget().availableGeometry().center());
        widget->move(position.topLeft());
	}

	bool WidgetUtil::confirmarAcao(QString titulo, QString mensagem)
	{
		return gm::DMessageBox::question(mensagem,titulo);
	}

	bool WidgetUtil::confirmacao(QString mensagem)
	{
        return  gm::DMessageBox::question(mensagem);

	}

	void WidgetUtil::mensagem(GMErro* erro)
	{
		switch(erro->tipo())
		{
		case GMErro::ALERTA:
			criarWidgetDeEspera(QMessageBox::Warning, tr(erro->toString().toStdString().c_str()), erro->mensagem());
			break;

		case GMErro::SEM_ERRO:
			criarWidgetDeEspera(QMessageBox::Information, tr(erro->toString().toStdString().c_str()), erro->mensagem());
			break;

		default:
			criarWidgetDeEspera(QMessageBox::Critical, tr(erro->toString().toStdString().c_str()), erro->mensagem());
			break;
		}
	}

	void WidgetUtil::mensagemAlerta(QString mensagem)
	{
		criarWidgetDeEspera(QMessageBox::Warning, "Alerta", mensagem);
	}

	void WidgetUtil::mensagemErroTransacao()
	{
		return mensagem((GMErro("Ocorreu um erro ao abrir uma transação com o banco de dados.", GMErro::BANCO)));
	}

//	void WidgetUtil::mensagem(BaseException &e)
//	{
//		QMessageBox::warning(0, "Alerta", e.toString());
//	}

	void WidgetUtil::mensagem(gm::GMErro erro)
	{
		switch(erro.tipo())
		{
		case GMErro::ALERTA:
			criarWidgetDeEspera(QMessageBox::Warning, tr(erro.toString().toStdString().c_str()), erro.mensagem());
			break;

		case GMErro::SEM_ERRO:
			criarWidgetDeEspera(QMessageBox::Information, tr(erro.toString().toStdString().c_str()), erro.mensagem());
			break;

		default:
			criarWidgetDeEspera(QMessageBox::Critical, tr(erro.toString().toStdString().c_str()), erro.mensagem());
			break;
		}
	}
	void WidgetUtil::mensagemInformacao(QString msg){
        QString titulo = "Informação";
		criarWidgetDeEspera(QMessageBox::Information, tr(titulo.toStdString().c_str()), msg, QFont());
	}

    void WidgetUtil::mensagemInformacao(QString msg, QWidget* parent) {
        QString titulo = "Informação";
        criarWidgetDeEspera(QMessageBox::Information, tr(titulo.toStdString().c_str()), msg, QFont(), parent);
    }

	void WidgetUtil::mensagem(GMErro erro, QWidget *parent)
	{
		switch(erro.tipo())
		{
		case GMErro::ALERTA:
			criarWidgetDeEspera(QMessageBox::Warning, tr(erro.toString().toStdString().c_str()), erro.mensagem(), QFont(), parent);
			break;
		case GMErro::SEM_ERRO:
			criarWidgetDeEspera(QMessageBox::Information, tr(erro.toString().toStdString().c_str()), erro.mensagem(), QFont(), parent);
			break;
		default:
			criarWidgetDeEspera(QMessageBox::Critical, tr(erro.toString().toStdString().c_str()), erro.mensagem(), QFont(), parent);
			break;
		}
	}

	void WidgetUtil::ajustarTamanhoConformePai(QWidget *widget, QWidget *parent)
	{
		if (widget != NULL && parent != NULL)
		{
			widget->setGeometry(QRect(0, 0, parent->geometry().width(), parent->geometry().height()));
			WidgetUtil::centralizar(widget);
		}
		else
		{
			widget->setGeometry(QRect(0, 0, 200, 100));
			WidgetUtil::centralizar(widget);
		}
	}

	void WidgetUtil::animacaoWidget(bool isVisivel, QRect rectShow, QRect rectHide, QWidget *ObjAnimado, QEasingCurve tipoAnimacao)
	{
		QPropertyAnimation *animation;
		animation = new QPropertyAnimation(ObjAnimado, "geometry");
		animation->setEasingCurve(tipoAnimacao);
		animation->setDuration(700);

		if(isVisivel)
		{
			animation->setStartValue(rectHide);
			animation->setEndValue(rectShow);
		}
		else
		{
			animation->setStartValue(rectShow);
			animation->setEndValue(rectHide);
		}

		animation->start();
	}

	QString WidgetUtil::cssForWidget()
	{
		return QString(
					   " QTableWidget                           "
					   " {                                      "
					   "     font:8pt;                          "
					   "     font-weight:none;                  "
					   " }                                      "
					   "                                        "
					   " QTreeWidget                            "
					   " {                                      "
					   "     font:8pt;                          "
					   "     font-weight:none;                  "
					   " }                                      "
					   "                                        "
					   " QTreeWidget::item                      "
					   " {                                      "
					   "   border-bottom: 1px solid #aaa;       "
					   "   border-right: 1px solid #aaa;        "
					   " }                                      "
					   "                                        "
					   " QTreeView::item:hover                  "
					   " {                                      "
					   "   background: #e7effd;                 "
					   " }                                      "
					   "                                        "
					   " QTreeView::item:selected:active{       "
					   "   background: #6ea1f1;                 "
					   " }                                      "
					   "                                        "
					   " QTreeView::item:selected:!active {     "
					   "   background: #6b9be8;                 "
					   " }                                      "
					);
	}

	QString WidgetUtil::cssForWidgetForm()
	{
		return WidgetUtil::cssForWidget();
	}

	QString WidgetUtil::cssForWidgetMobile()
	{
		return QString(
					   "QWidget                         "
					   "{                               "
					   "     background-color: white;   "
					   "}                               "
					   "QDialog                         "
					   "{                               "
					   "     background-color: white;   "
					   "}                               "
					   "DPushButtonItem                 "
					   "{                               "
					   "    border-radius: 0px;         "
					   "    border: none;               "
					   "}                               "
					   "QLineEdit                       "
					   " {                              "
					   "     border-radius: 0px;        "
					   "     background-color: white;   "
					   "     border: 1px solid;         "
					   "     color : #000;              "
					   "     border-color: gray;        "
					   " }                              "
					   "                                "
					   " QLineEdit:focus                "
					   " {                              "
					   "     border-radius: 0px;        "
					   "     color: #000;               "
					   "     background-color: yellow;  "//#FFFEDC
					   "     border: 1px solid;         "
					   "     border-color: gray;        "
					   " }                              "
					   "                                "
					   " QLineEdit:edit-focus           "
					   " {                              "
					   "     border-radius: 0px;        "
					   "     background-color: #3D3C3C; "
					   "     color : #FFF;              "
					   "     border: 1px solid #3D3C3C; "//#FFF
					   "     border-color: gray;        "
					   " }                              "
					   "                                "
					   " QLineEdit:disabled             "
					   " {                              "
					   "     border-radius: 0px;        "
					   "     background-color: white;   "
					   "     color : black;             "
					   "     border: 1px solid ;        "
					   "     border-color: gray;        "
					   " }                              "
					   "                                "
					   " QLabel                         "
					   " {                              "
					   "     font  : bold;              "
					   "     color : black;             "
					   " }                              "
					   "                                "
					   " DLabel                         "
					   " {                              "
					   "     color : black;             "
					   " }                              "
					   "                                "
					   " DLabelTitle                    "
					   " {                              "
					   "     font  : bold;              "
					   "     color : white;             "
					   "     background-color: #0B3880; "
					   " }                              "
					   "                                "
					   " QPushButton                    "
					   " {                              "
					   "     border-radius: 0px;        "
					   "     font  : bold;              "
					   "     border: 1px solid ;        "
					   "     border-color: lightGray;   "
					   " }                              "
					   "                                "
					   " QHeaderView::section           "
					   " {                              "
					   "     background-color: #0058A8; "
					   "     color: #FFFFFF;            "
					   "     font:9pt;                  "
					   " }                              "
					   "                                "
					   " QTableView                                 "
					   " {                                          "
					   "     background-color: white;               "
					   "     selection-background-color: yellow;    "
					   "     selection-color: black;                "
					   " }                                          "
					   "                                            "
					   " QTableWidget                               "
					   " {                                          "
					   "     font:8pt;                              "
					   "     font-weight:none;                      "
					   " }                                          "
					   "                                            "
					   " QTreeWidget                                "
					   " {                                          "
					   "     font:8pt;                              "
					   "     font-weight:none;                      "
					   " }                                          "
					   " QTreeView::item:selected:active{           "
					   "   color: black;                            "
					   "   background: yellow;                      "
					   " }                                          "
					   " QTreeWidget::item                          "
					   " {                                          "
					   "   border-bottom: 1px solid #aaa;           "
					   "   border-right: 1px solid #aaa;            "
					   " }                                          "
					   "                                            "
					   );

	}

	void WidgetUtil::mensagemAlertaComFonte(QString mensagem, QFont font)
	{
		criarWidgetDeEspera(QMessageBox::Warning, "Aviso", mensagem, font);
	}

	void WidgetUtil::mensagem(QString titulo, QString mensagem)
	{
		criarWidgetDeEspera(QMessageBox::NoIcon, titulo , mensagem);
	}

	void WidgetUtil::mensagem(QString texto)
	{
		QMessageBox::information(0, "Sucesso", texto);
	}

	void WidgetUtil::mensagemErro(GMErro* erro)
	{
		if(!erro->isErro())
		{
			return;
		}

		QMessageBox::critical(0, tr(erro->toString().toStdString().c_str()), erro->mensagem());
	}

	void WidgetUtil::mensagemErro(QString mensagem)
	{
		criarWidgetDeEspera(QMessageBox::Critical, "Erro", mensagem);
	}

	QColor WidgetUtil::amarelo()
	{
		return QColor(255, 140, 0, 255);
	}

	QColor WidgetUtil::azul()
	{
		return QColor(0, 0, 213, 255);
	}

	QColor WidgetUtil::azulBebe()
	{
		return QColor(166, 202, 240, 255);
	}

	QColor WidgetUtil::azulGMCore()
	{
		return QColor(66, 142, 255, 50);
	}

	QColor WidgetUtil::azulForte()
	{
		return QColor(65,172,225);
	}

	QColor WidgetUtil::azulEscuro()
	{
        return QColor(16,36,62,255);
    }

    QColor WidgetUtil::azulMarinho()
    {
        return QColor(0, 78, 190);
    }

	QColor WidgetUtil::branco()
	{
		return QColor(255, 255, 255, 255);
	}

	QColor WidgetUtil::cinza()
	{
		return QColor(232, 232, 220, 255);
	}

	QColor WidgetUtil::cinzaEscuro()
	{
		return QColor(0, 0, 0, 110);
	}

	QColor WidgetUtil::creme()
	{
		return QColor(255, 255, 204, 255);
	}

	QColor WidgetUtil::laranja()
	{
        return QColor(210, 105, 30, 255);
    }

    QColor WidgetUtil::amareloClaro()
    {
        return QColor(245, 245, 0);
    }

	QColor WidgetUtil::lilas()
	{
		return QColor(4, 1, 67, 255);
	}

	QColor WidgetUtil::marrom()
	{
		return QColor(67, 0, 0, 255);
	}

	QColor WidgetUtil::preto()
	{
		return QColor(0, 0, 0, 255);
	}

	QColor WidgetUtil::verdeClaro()
	{
		return QColor(0, 95, 0, 255);
	}

	QColor WidgetUtil::rosa()
	{
		return QColor(255, 0, 255);
	}

	QColor WidgetUtil::roxoMedio()
	{
		return QColor(142, 17, 142);
	}

	QColor WidgetUtil::roxo()
	{
		return QColor(51, 0, 51);
	}

	QColor WidgetUtil::verdeEscuro()
	{
		return QColor(74, 131, 89, 255);
	}

	QColor WidgetUtil::verdeNeutro()
	{
		return QColor(50, 205, 50, 200);
	}

	QColor WidgetUtil::vermelho()
	{
		return QColor(220, 0, 0, 255);
	}

    QColor WidgetUtil::vermelhoMuitoClaro()
    {
        return QColor(255, 224, 224, 255);
    }

    QColor WidgetUtil::salmao()
    {
        return QColor(250,128,114, 255);
    }
}

#include "moc_widgetutil.cpp" // inclusao do MOC desta classe
