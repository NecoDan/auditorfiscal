#include "dvisualizararquivos.h"
#include "ui_dvisualizararquivos.h"

#include "escrituracao/dominio/escrituracao_escrituracao.h"
#include "escrituracao/negocio/escrituracao_escrituracaonegocio.h"
#include "infraestrutura/visao/dprogressstatus.h"
#include "infraestrutura/gm_itemutil.h"

#include "visao/dresumoauditoria.h"

#include "infraestrutura/widgetutil.h"

#include <QMap>

using namespace gm;
using namespace gm_escrituracao;

const int COLUNA_AGRUPAMENTO    = 0;
const int COLUNA_INSC_ESTADUAL  = 1;
const int COLUNA_DT_MODIF       = 2;
const int COLUNA_NOME_DATABASE  = 3;

DVisualizarArquivos::DVisualizarArquivos(QWidget *parent) : QDialog(parent), ui(new Ui::DVisualizarArquivos)
{
    ui->setupUi(this);
    configuracoesIniciais();
    setConnects();
    pesquisarDados();
}

DVisualizarArquivos::~DVisualizarArquivos()
{
    delete ui;
}

void DVisualizarArquivos::configuracoesIniciais()
{

}

void DVisualizarArquivos::setConnects()
{
    connect(ui->pbVoltar, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(ui->twArquivos, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(duploCliqueArquivo(QTreeWidgetItem*,int)));
}

void DVisualizarArquivos::pesquisarDados()
{
    ui->twArquivos->clear();

    DProgressStatus* status = new DProgressStatus;

    EscrituracaoNegocio escrituracaoNegocio;
    QList<Escrituracao*> listaEscrituracao = escrituracaoNegocio.recuperarEscrituracoes();

    if(escrituracaoNegocio.lastError().isErro())
    {
        status->close();
        WidgetUtil::mensagem(escrituracaoNegocio.lastError());
        return;
    }

    preencherTreeWidget(listaEscrituracao);
    status->close();
}

void DVisualizarArquivos::preencherTreeWidget(QList<Escrituracao *> listaEscrituracao)
{
    QMap<QString, QTreeWidgetItem*> mapItens;

    foreach(Escrituracao* escrituracao, listaEscrituracao)
    {
        QTreeWidgetItem* itemAno;
        QString chaveAno = escrituracao->nomeDatabase().split("_").at(0);

        if(!mapItens.contains(chaveAno))
        {
            itemAno = new QTreeWidgetItem;
            itemAno->setText(COLUNA_AGRUPAMENTO, escrituracao->nomeDatabase().split("_").at(0));
            mapItens.insert(chaveAno, itemAno);
        }
        else
            itemAno = mapItens.value(chaveAno);

        QTreeWidgetItem* itemCnpjRaiz;
        QString chaveCnpjRaiz = chaveAno + "|" + escrituracao->nomeDatabase().split("_").at(1);

        if(!mapItens.contains(chaveCnpjRaiz))
        {
            itemCnpjRaiz = new QTreeWidgetItem;
            itemCnpjRaiz->setText(COLUNA_AGRUPAMENTO, escrituracao->nomeDatabase().split("_").at(1));
            mapItens.insert(chaveCnpjRaiz, itemCnpjRaiz);
            itemAno->addChild(itemCnpjRaiz);
        }
        else
            itemCnpjRaiz = mapItens.value(chaveCnpjRaiz);

        QTreeWidgetItem* itemFilial = new QTreeWidgetItem;
        itemFilial->setText(COLUNA_AGRUPAMENTO, escrituracao->nomeDatabase().split("_").at(2) + " - " + escrituracao->descricaoFilial());

        itemFilial->setText(COLUNA_INSC_ESTADUAL, QString::number(escrituracao->inscricaoEstadual()));
        itemFilial->setTextAlignment(COLUNA_INSC_ESTADUAL, Qt::AlignCenter);

        itemFilial->setText(COLUNA_DT_MODIF, escrituracao->data().toString("dd/MM/yyyy hh:mm:ss"));
        itemFilial->setTextAlignment(COLUNA_DT_MODIF, Qt::AlignCenter);

        itemFilial->setText(COLUNA_NOME_DATABASE, escrituracao->nomeDatabase().trimmed().toUpper());
        itemFilial->setTextAlignment(COLUNA_NOME_DATABASE, Qt::AlignCenter);

        gm::itemutil::setObject<Escrituracao>(itemFilial, COLUNA_AGRUPAMENTO, escrituracao);

        itemCnpjRaiz->addChild(itemFilial);

        ui->twArquivos->addTopLevelItem(itemAno);
    }

    ui->twArquivos->setFocus();
    ui->twArquivos->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->twArquivos->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->twArquivos->header()->setStretchLastSection(false);
}

void DVisualizarArquivos::duploCliqueArquivo(QTreeWidgetItem *item, int coluna)
{
    Q_UNUSED(coluna)

    Escrituracao* escrituracao = gm::itemutil::getObject<Escrituracao>(item, COLUNA_AGRUPAMENTO);

    if(escrituracao != nullptr)
    {
        DResumoAuditoria* resumo = new DResumoAuditoria(escrituracao);

        if(resumo->exec() == QDialog::Rejected)
            this->show();
    }
}
