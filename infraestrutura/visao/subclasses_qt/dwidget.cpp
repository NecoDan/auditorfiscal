#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include "dwidget.h"
//#include "dwidgetform.h"
//#include "infraestrutura/dominio/dobject.h"
#include "infraestrutura/widgetutil.h"
//#include "infraestrutura/dominio/dthread.h"
#include <QKeyEvent>

class DWidgetEmit:public QObject
{
	Q_OBJECT
public:
	explicit DWidgetEmit(QObject*parent=0):QObject(parent){}
	void doEmit()
	{
		emit slotEmit();
	}
signals:
	void slotEmit();
};

DWidget::DWidget(QWidget *parent) : QWidget(parent)
{
}

DWidget::~DWidget()
{
}

void DWidget::doEnabled()
{
	this->setEnabled(true);
}

void DWidget::doDisabled()
{
	this->setEnabled(false);
}

void DWidget::setFocus()
{
	QWidget::setFocus();
}

//bool DWidget::setLastSucess(QString message)
//{
//	return this->setLastError(message.trimmed().isEmpty()?"Processo concluido":message, GMErro::SEM_ERRO);
//}

GMErro DWidget::lastError()
{
	return this->_lastError;
}

QString DWidget::lastErrorMessage()
{
	return this->_lastError.mensagem();
}

bool DWidget::setLastError(GMErro value)
{
    if(value.tipo()==GMErro::SEM_ERRO){
        QString m = value.mensagem().toLower();
        if(m=="")
            value.clear();
        else if(m.contains("sem erro"))
            value.clear();
        else if(m.contains("<p></p>"))
            value.clear();
    }

	this->_lastError=value;
#ifdef QT_DEBUG
	if(!value.isSucesso())
		qDebug()<<"class=="<<this->metaObject()->className()<<", error=="<<this->lastErrorMessage();
#endif
	return this->_lastError.isSucesso();
}

//bool DWidget::setLastError(GMErro ifError, QString elseMessage)
//{
//	if(ifError.isSucesso())
//		this->setLastError(elseMessage);
//	else
//		this->setLastError(ifError);
//	return this->_lastError.isSucesso();
//}

bool DWidget::setLastError(GMErro ifError, GMErro elseError)
{
	this->setLastError(ifError.isSucesso()?ifError:elseError);
	return this->_lastError.isSucesso();
}

//bool DWidget::setLastError(DObject objectError)
//{
//	this->setLastError(objectError.lastError());
//	return this->_lastError.isSucesso();
//}

//bool DWidget::setLastError(QString value, GMErro::TipoErro tipoErro)
//{
//	if (!value.isEmpty())
//		this->_lastError=GMErro(value,tipoErro);
//	else
//		this->_lastError.clear();

//	DObject*dparent=dynamic_cast<DObject*>(this->parent());
//	if(dparent)
//		dparent->setLastError(value, tipoErro);

//	DWidgetForm*wparent=dynamic_cast<DWidgetForm*>(this->parent());
//	if(wparent)
//		wparent->setLastError(value, tipoErro);

//	return this->_lastError.isSucesso();
//}


//bool DWidget::setLastErrorForce(GMErro value)
//{
//	if(value.isSucesso())
//		this->setLastError("Erro desconhecido");
//	else
//		this->setLastError(value);
//	return this->_lastError.isSucesso();
//}

//bool DWidget::setLastErrorForce(QString value)
//{
//	if(this->isSuccess())
//	{
//		if(value.trimmed().isEmpty())
//			this->setLastError("Erro desconhecido");
//		else
//			this->setLastError(value);
//	}
//	return this->_lastError.isSucesso();
//}

//bool DWidget::setLastErrorForce()
//{
//	return this->setLastErrorForce(this->lastError());
//}

//bool DWidget::setUnknownError()
//{
//	return this->setLastError("Erro desconhecido");
//}

//void DWidget::clearError()
//{
//	this->_lastError.clear();
//}

//bool DWidget::isSuccess()
//{
//	return this->lastError().isSucesso();
//}

//bool DWidget::isError()
//{
//	return !this->isSuccess();
//}

//QVariant DWidget::tag() const
//{
//	return _tag;
//}

//void DWidget::setTag(QVariant value)
//{
//	this->_tag=value;
//}

//void DWidget::emitSlot(const char *slot)
//{
//	this->emitSlot(this, slot);
//}

//void DWidget::emitSlot(QObject*parentSlot, const char *slot)
//{
//	disconnect(this, SIGNAL(slotEmit()));
//	connect(this, SIGNAL(slotEmit()), parentSlot, slot);
//	emit slotEmit();
//	disconnect(this, SIGNAL(slotEmit()), parentSlot, slot);
////    while(qApp->hasPendingEvents())
////        QThread::msleep(100);
//	QThread::msleep(100);
//}

//QThread*DWidget::execSlotThread(const char *slot)
//{
//	return DThreadManager::newThread(this, slot);
//}

//QThread *DWidget::execSlotThread(QObject *parentSlot, const char *slot)
//{
//	return DThreadManager::newThread(parentSlot, slot);
//}

bool DWidget::checked() const
{
	return this->_checked;
}

void DWidget::setChecked(bool checked)
{
	this->_checked = checked;
}

void DWidget::centralizar()
{
	if(!this->isFullScreen())
	{
		this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
	}
}

bool DWidget::automaticCSS() const
{
	return _automaticCSS;
}

void DWidget::setAutomaticCSS(bool automaticCSS)
{
	_automaticCSS = automaticCSS;
}

QString DWidget::css()
{
	return WidgetUtil::cssForWidget();
}

void DWidget::keyPressEvent(QKeyEvent *event)
{
	QWidget::keyPressEvent(event);
	event->accept();
}

void DWidget::showEvent(QShowEvent *event)
{
	Q_UNUSED(event);
	if(this->automaticCSS())
		if(!this->css().isEmpty())
			if(!_internalSetStyleSheet)
			{
				this->setStyleSheet(this->css());
				_internalSetStyleSheet=true;
			}
	QWidget::showEvent(event);
}

#include "moc_dwidget.cpp" // inclusao do MOC desta classe
