#include "dresumoauditoria.h"
#include "ui_dresumoauditoria.h"

#include "escrituracao/dominio/escrituracao_escrituracao.h"
#include "escrituracao/dominio/escrituracao_escrituracaosped.h"
#include "escrituracao/negocio/escrituracao_escrituracaonegociocontroller.h"

#include "infraestrutura/widgetutil.h"

const QString ICONE_VALIDADO     = ":/imagens/infraestrutura/recursos/imagens/selecionar.png";
const QString ICONE_NAO_VALIDADO = ":/imagens/infraestrutura/recursos/imagens/cancelar_32.png";

const int COLUNA_PERIODO        = 0;
const int COLUNA_SPED           = 1;
const int COLUNA_NAO_FISCAL     = 2;
const int COLUNA_STATUS         = 3;
const int COLUNA_STATUS_PERIODO = 4;

using namespace gm_escrituracao;

DResumoAuditoria::DResumoAuditoria(gm_escrituracao::Escrituracao *escrituracao, QWidget *parent) : QDialog(parent), ui(new Ui::DResumoAuditoria)
{
    ui->setupUi(this);
    configuracoesIniciais();
    setConnects();
    pesquisarDados(escrituracao);
}

DResumoAuditoria::~DResumoAuditoria()
{
    delete ui;
}

void DResumoAuditoria::configuracoesIniciais()
{
}

void DResumoAuditoria::setConnects()
{
    connect(ui->pbVoltar, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void DResumoAuditoria::pesquisarDados(gm_escrituracao::Escrituracao *escrituracao)
{
    EscrituracaoNegocioController escrituracaoController(escrituracao);
    QList<EscrituracaoSped*> listaEscrituracaoSped = escrituracaoController.recuperarEscrituracoesSped(escrituracao);

    if(escrituracaoController.lastError().isErro())
    {
        gm::WidgetUtil::mensagem(escrituracaoController.lastError());
        return;
    }

    this->montarResumo(listaEscrituracaoSped);
}

void DResumoAuditoria::montarResumo(QList<EscrituracaoSped *> listaEscrituracaoSped)
{
    int linha = -1;
    QTableWidgetItem* item = nullptr;


    foreach(EscrituracaoSped* sped, listaEscrituracaoSped)
    {
        ui->tbwResumo->insertRow(++linha);
        item = new QTableWidgetItem;

        Qt::ItemFlags eFlags = item->flags();
        eFlags &= ~Qt::ItemIsEditable;

        item->setFlags(eFlags);
        item->setText(QString::number(sped->mes()) + "/" + QString::number(sped->ano()));
        ui->tbwResumo->setItem(linha, COLUNA_PERIODO, item);

        item = new QTableWidgetItem;
        item->setFlags(eFlags);
        sped->fiscal() ? item->setIcon(QIcon(ICONE_VALIDADO)) : item->setIcon(QIcon(ICONE_NAO_VALIDADO));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tbwResumo->setItem(linha, COLUNA_SPED, item);

        item = new QTableWidgetItem;
        item->setFlags(eFlags);
        sped->naoFiscalSaldo() ? item->setIcon(QIcon(ICONE_VALIDADO)) : item->setIcon(QIcon(ICONE_NAO_VALIDADO));
        ui->tbwResumo->setItem(linha, COLUNA_NAO_FISCAL, item);

        item = new QTableWidgetItem;
        item->setFlags(eFlags);
        sped->fiscal() ? item->setIcon(QIcon(ICONE_VALIDADO)) : item->setIcon(QIcon(ICONE_NAO_VALIDADO));
        ui->tbwResumo->setItem(linha, COLUNA_STATUS, item);

        item = new QTableWidgetItem;
        item->setFlags(eFlags);
        sped->naoFiscalSaldo() ? item->setIcon(QIcon(ICONE_VALIDADO)) : item->setIcon(QIcon(ICONE_NAO_VALIDADO));
        ui->tbwResumo->setItem(linha, COLUNA_STATUS_PERIODO, item);
    }

    //ui->tbwResumo->resizeRowsToContents();
    //ui->tbwResumo->resizeColumnsToContents();
}
