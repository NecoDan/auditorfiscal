#include "dprogressstatus.h"
#include "ui_dprogressstatus.h"
#include<QApplication>
#include<QDesktopWidget>
#include<QDebug>

DProgressStatus::DProgressStatus(QWidget *parent) : DWidget(parent), ui(new Ui::DProgressStatus)
{
    ui->setupUi(this);

    connect(ui->buttonCancel, SIGNAL(clicked(bool)), this,SLOT(onCancelClicked()));

    connect(this,SIGNAL(internalOnShow()),this,SLOT(onShow()));
    connect(this,SIGNAL(internalOnHide()),this,SLOT(onHide()));
    connect(this,SIGNAL(internalOnUpdate()),this,SLOT(onUpdate()));
    connect(this, SIGNAL(internalOnClear()), this, SLOT(onClear()));

    this->setVisibleStatus(true);
    this->setVisibleProgress(false);
    this->setVisibleButtonCancel(false);
    this->onClear();
    this->setStyleSheet(QString("#DProgressStatus{border-style: inset;border-width: 1px;border-color: gray;}"));
}

DProgressStatus::~DProgressStatus()
{
    delete ui;
}

bool DProgressStatus::isCanceled()
{
    return this->_canceled;
}

QPushButton *DProgressStatus::buttonCancel()
{
    return ui->buttonCancel;
}

QProgressBar *DProgressStatus::progressBar()
{
    return ui->progressBar;
}

QLabel *DProgressStatus::labelMessage()
{
    return ui->label;
}

void DProgressStatus::closeEvent(QCloseEvent *event)
{
    if (this->_hideLiberado)
        event->accept();
    else
        event->ignore();
}

void DProgressStatus::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)
    this->_firtShow=true;
}

void DProgressStatus::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)

    if(this->_firtShow)
    {
        this->_firtShow=false;
        ui->label->setText(this->_message);
        ui->label->setVisible(true);
        ui->progressBar->setVisible(false);
        ui->frmButton->setVisible(false);
        ui->buttonCancel->setEnabled(true);
    }
}

void DProgressStatus::clear()
{  
    emit internalOnClear();
}

void DProgressStatus::setStatusText(QString text)
{
    this->_message=text;
    emit internalOnUpdate();
}

void DProgressStatus::setProgress(int min, int max, int pos)
{
    this->_max=max;
    this->_min=min;
    this->_pos=pos;
    emit internalOnUpdate();
}

void DProgressStatus::setButtonCancelText(QString text)
{
    ui->buttonCancel->setText(text.trimmed());
}

void DProgressStatus::show()
{
    emit internalOnShow();
}

void DProgressStatus::hide()
{
    emit internalOnHide();
}

void DProgressStatus::close()
{
    emit internalOnHide();
}

void DProgressStatus::setVisible(bool value)
{
    DWidget::setVisible(value);
}

void DProgressStatus::setVisibleStatus(bool value)
{
    this->_visibleStatus=value;
}

void DProgressStatus::setVisibleProgress(bool value)
{
    this->_visibleProgress=value;
}

void DProgressStatus::setVisibleButtonCancel(bool value)
{
    this->_visibleButtonCancel=value;
}

void DProgressStatus::doClearVariables()
{
    this->_canceled=false;
    this->_hideLiberado=false;
    this->_message="";
    this->_max=100;
    this->_min=0;
    this->_pos=0;
}

void DProgressStatus::onClear()
{
    this->doClearVariables();
    emit internalOnUpdate();
}

void DProgressStatus::onSetStatus(QString message)
{
    this->setStatusText(message);
}

void DProgressStatus::onSetProgress(int min, int max, int pos)
{
    this->setProgress(min, max, pos);
}

void DProgressStatus::onShow()
{
    this->_hideLiberado=false;

    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags( Qt::FramelessWindowHint );

    this->onSetVisible();
    emit internalOnUpdate();
    DWidget::show();
}

void DProgressStatus::onHide()
{
    this->doClearVariables();
    this->_hideLiberado=true;
    DWidget::hide();
}

void DProgressStatus::onUpdate()
{
    ui->progressBar->setMaximum(this->_max);
    ui->progressBar->setMinimum(this->_min);
    ui->progressBar->setValue(this->_pos);
    ui->label->setText(this->_message);

    this->onSetVisible();
}

void DProgressStatus::onSetVisible()
{
    if(ui->progressBar->isVisible()!=this->_visibleProgress)
        ui->progressBar->setVisible(this->_visibleProgress);

    if(ui->label->isVisible()!=this->_visibleStatus)
        ui->label->setVisible(this->_visibleStatus);

    if(ui->frmButton->isVisible()!=this->_visibleButtonCancel)
        ui->frmButton->setVisible(this->_visibleButtonCancel);

    int SpacerItem   = ui->frmButton->layout()->spacing();
    int SpacerTop    = 9;
    int SpacerBotton = 9;

    int H=SpacerTop+SpacerBotton;

    if(this->_visibleStatus)
        H+=ui->label->minimumHeight()+SpacerItem;

    if(this->_visibleProgress)
        H+=ui->progressBar->minimumHeight()+SpacerItem;

    if(this->_visibleButtonCancel)
        H+=ui->frmButton->minimumHeight()+SpacerItem;

    H=H<10?20:H;

    if(this->maximumHeight()!=H)
    {
        this->setMaximumHeight(H);
        this->setMinimumHeight(H);

        if(!this->isFullScreen())
            this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    }

}

void DProgressStatus::onCancelClicked()
{
    this->_canceled=true;
    ui->buttonCancel->setText("Cancelando...");
    ui->buttonCancel->setEnabled(false);
    emit onCanceled();
}

#include "moc_dprogressstatus.cpp" // inclusao do MOC desta classe
