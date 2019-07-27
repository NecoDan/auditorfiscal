#include "visao/dimportararquivos.h"
#include "ui_dimportararquivos.h"

#include <QDir>
#include <QFileDialog>

// Arquivos
#include "arquivos/negocio/arquivo_arquivonegocio.h"

// Diretório
#include "diretoriopadrao/dominio/escrituracao_diretoriopadrao.h"
#include "diretoriopadrao/negocio/escrituracao_diretoriopadraonegocio.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"
#include "infraestrutura/widgetutil.h"
#include "infraestrutura/visao/dprogressstatus.h"

// Visão
#include "visao/dvisualizararquivos.h"

using namespace gm;
using namespace gm_arquivo;
using namespace gm_escrituracao;

DImportarArquivos::DImportarArquivos(QWidget *parent) : QDialog(parent), ui(new Ui::DImportarArquivos)
{
    ui->setupUi(this);
    configuracoesIniciais();
    setConnects();
}

DImportarArquivos::~DImportarArquivos()
{
    delete ui;
}

void DImportarArquivos::configuracoesIniciais()
{
    carregarDiretorioPadrao();
}

void DImportarArquivos::setConnects()
{
    connect(ui->pbSelecionarDiretorioPadrao, SIGNAL(clicked(bool)), this, SLOT(clicouEmPbSelecionarDiretorioPadrao()));
    connect(ui->pbSelecionarArquivos, SIGNAL(clicked(bool)), this, SLOT(clicouEmPbSelecionarArquivos()));
    connect(ui->pbLimpar, SIGNAL(clicked(bool)), this, SLOT(clicouEmPbLimpar()));
    connect(ui->pbVoltar, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(ui->chkSelecionarTodos, SIGNAL(clicked(bool)), this, SLOT(clicouEmPbSelecionarTodos(bool)));
    connect(ui->pbCarregar, SIGNAL(clicked(bool)), this, SLOT(clicouEmPbCarregar()));
}

void DImportarArquivos::clicouEmPbLimpar()
{
    ui->leDiretorioPadrao->clear();
}

void DImportarArquivos::carregarDiretorioPadrao()
{
    QSqlDatabase db = gm::DBUtil::conexao();
    DiretorioPadraoNegocio diretorioNegocio(db);
    _diretorio = diretorioNegocio.recuperar();

    if(diretorioNegocio.lastError().isErro())
        qDebug() << "diretorionegocio" << diretorioNegocio.lastError().mensagem();

    if(_diretorio != nullptr){
        ui->leDiretorioPadrao->setText(_diretorio->caminho().trimmed());
        carregarArquivosDiretorioPadrao();
    }

    //ui->pbSelecionarArquivos->setDisabled(_diretorio != nullptr);
}

void DImportarArquivos::clicouEmPbSelecionarDiretorioPadrao()
{
    QString fileName = QFileDialog::getExistingDirectory(this, "<b>Selecione o diretório padrão</b>", QDir::currentPath());

    if(fileName.isEmpty())
        return;

    if(_diretorio == nullptr)
        _diretorio = new DiretorioPadrao;

    _diretorio->setCaminho(fileName);
    _diretorio->setData(QDateTime::currentDateTime());

    DiretorioPadraoNegocio diretorioNegocio;
    diretorioNegocio.salvarDiretorioPadrao(_diretorio);

    ui->leDiretorioPadrao->setText(fileName);
    carregarArquivosDiretorioPadrao();
}

void DImportarArquivos::clicouEmPbSelecionarArquivos()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Selecione os arquivos de SPED", QDir::currentPath());

    if(fileNames.isEmpty())
        return;

    ui->tbwArquivos->setRowCount(0);

    QFont font;
    font.setPointSize(9);
    font.setBold(true);

    int linha = 0;

    for(auto fileName : fileNames){
        ui->tbwArquivos->insertRow(linha);
        QTableWidgetItem* item = new QTableWidgetItem;

        Qt::ItemFlags eFlags = item->flags();
        eFlags &= ~Qt::ItemIsEditable;

        item->setCheckState(Qt::Checked);
        item->setFlags(eFlags);
        ui->tbwArquivos->setItem(linha, 0, item);

        item = new QTableWidgetItem;
        item->setText(fileName);
        item->setFont(font);
        item->setFlags(eFlags);
        ui->tbwArquivos->setItem(linha, 1, item);

        item = new QTableWidgetItem;
        item->setText(fileName);
        item->setFont(font);
        item->setFlags(eFlags);
        ui->tbwArquivos->setItem(linha, 2, item);

        linha++;
    }

    ui->tbwArquivos->hideColumn(2);
    ui->tbwArquivos->resizeColumnsToContents();
}

void DImportarArquivos::carregarArquivosDiretorioPadrao()
{
    if(_diretorio != nullptr && !_diretorio->caminho().isEmpty()){
        QDir diretorio(_diretorio->caminho());
        QFileInfoList list = diretorio.entryInfoList();

        ui->tbwArquivos->setRowCount(0);

        QFont font;
        font.setPointSize(9);
        font.setBold(true);

        int linha = 0;

        for(auto fileInfo : list){
            ui->tbwArquivos->insertRow(linha);
            QTableWidgetItem* item = new QTableWidgetItem;

            Qt::ItemFlags eFlags = item->flags();
            eFlags &= ~Qt::ItemIsEditable;

            item->setCheckState(Qt::Checked);
            item->setFlags(eFlags);
            ui->tbwArquivos->setItem(linha, 0, item);

            item = new QTableWidgetItem;
            item->setText(fileInfo.filePath().remove(_diretorio->caminho() + "/"));
            item->setFont(font);
            item->setFlags(eFlags);
            ui->tbwArquivos->setItem(linha, 1, item);

            item = new QTableWidgetItem;
            item->setText(fileInfo.filePath());
            item->setFont(font);
            item->setFlags(eFlags);
            ui->tbwArquivos->setItem(linha, 2, item);

            linha++;
        }

        ui->tbwArquivos->resizeColumnsToContents();
    }

    ui->tbwArquivos->hideColumn(2);
}

void DImportarArquivos::clicouEmPbSelecionarTodos(bool clicked)
{
    for(int i = 0; i < ui->tbwArquivos->rowCount(); i++)
        (clicked) ? ui->tbwArquivos->item(i,0)->setCheckState(Qt::Checked) : ui->tbwArquivos->item(i,0)->setCheckState(Qt::Unchecked);
}

void DImportarArquivos::clicouEmPbCarregar()
{
    QStringList arquivosSelecionados = this->getArquivosSelecionados();

    if(arquivosSelecionados.isEmpty()){
        WidgetUtil::mensagemAlerta("Selecione ao menos um arquivo para continuar.");
        return;
    }

    if (!WidgetUtil::confirmacao("<p>Você selecionou <b>" + QString::number(arquivosSelecionados.size()) + "</b> arquivos para importar.</p>"
                                 "<p>Deseja continuar?</p>")){
        return;
    }

    DProgressStatus* progress = new DProgressStatus;

    ArquivoNegocio arquivoNegocio;
    arquivoNegocio.gerarEscrituracoesMaster(arquivosSelecionados);

    if(arquivoNegocio.lastError().isErro()){
        progress->close();
        WidgetUtil::mensagem(arquivoNegocio.lastError());
        return;
    }

    progress->close();
    //    WidgetUtil::mensagemInformacao("Arquivos importados com sucesso.");

    if(QMessageBox::information(0, "Aviso", "Arquivos importados com sucesso.")){
        DVisualizarArquivos* visualizar = new DVisualizarArquivos;
        // this->hide();

        if(visualizar->exec() == QDialog::Rejected)
            this->show();
        //        else this->hide();
    }
}

QStringList DImportarArquivos::getArquivosSelecionados()
{
    QStringList arquivosSelecionados;

    for(int i = 0; i < ui->tbwArquivos->rowCount(); i++){
        if(ui->tbwArquivos->item(i,0)->checkState() == Qt::Checked)
            arquivosSelecionados << ui->tbwArquivos->item(i, 2)->text();
    }

    return arquivosSelecionados;
}
