#include "menuprincipal.h"
#include "ui_menuprincipal.h"

#include <QTime>
#include <QTimer>
#include <QDesktopWidget>

#include "dimportararquivos.h"
#include "visao/dvisualizararquivos.h"

MenuPrincipal::MenuPrincipal(QWidget *parent) : QMainWindow(parent), ui(new Ui::MenuPrincipal)
{
    ui->setupUi(this);
    this->configuracoesIniciais();
    this->setConnects();
}

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

void MenuPrincipal::exibirSaudacao()
{
    ui->lSaudacao->setText(getSaudacao());
}

void MenuPrincipal::exibirDataHoraSistema()
{
    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
}

QString MenuPrincipal::getSaudacao()
{
    QTime time = QTime::currentTime();

    if(time.hour() >= 0 && time.hour() <= 12)
        return "Bom dia! ";
    else if(time.hour() >= 13 && time.hour() <= 18)
        return "Boa tarde! ";
    else if(time.hour() >= 19 && time.hour() <= 23)
        return "Boa noite! ";
}

void MenuPrincipal::configuracoesIniciais()
{
    if(!this->isFullScreen())
        this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    this->setFixedSize(this->size());
    exibirDataHoraSistema();
}

void MenuPrincipal::setConnects()
{
    connect(ui->pbFechar, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->pbImportarArquivos, SIGNAL(clicked(bool)), this, SLOT(clicouEmPbImportarArquivos()));
    connect(ui->pbCarregarAuditoria, SIGNAL(clicked(bool)), this, SLOT(clicouEmPbCarregarAuditoria()));
}

void MenuPrincipal::showTime()
{
    QDate date = QDate::currentDate();
    exibirSaudacao();
    ui->lDataHora->setText(date.toString("dddd, dd MMMM yyyy") + ", " + QTime::currentTime().toString("hh:mm:ss"));
}

void MenuPrincipal::clicouEmPbImportarArquivos()
{
    this->hide();

    DImportarArquivos* importar = new DImportarArquivos;

    if(importar->exec() == QDialog::Rejected)
        this->show();
}

void MenuPrincipal::clicouEmPbCarregarAuditoria()
{
    this->hide();

    DVisualizarArquivos* visualizarArquivos = new DVisualizarArquivos;

    if(visualizarArquivos->exec() == QDialog::Rejected)
        this->show();
}
