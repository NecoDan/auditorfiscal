#ifndef DPROGRESSSTATUS_H
#define DPROGRESSSTATUS_H

#include <QKeyEvent>
#include <QCloseEvent>
#include <QWidget>
#include <QThread>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include "infraestrutura/visao/subclasses_qt/dwidget.h"

namespace Ui
{
    class DProgressStatus;
}

//class DProgressStatusThread;

class DProgressStatus : public DWidget
{
    Q_OBJECT

    friend class DWidgetForm;
    friend class DDialogForm;
public:
    explicit DProgressStatus(QWidget *parent = 0);
    ~DProgressStatus();
    /**
     * reseta para condicao inicial os widget na Ui
     *
     */
    void clear();

    /**
     * através de um sinal é lancado um texto para o widget responsavel pelo texto na na ui
     *
     */
    void setStatusText(QString text);

    /**
     *
     * atravez de um sinal é lancado um texto para o widget resposavel pelo progressBar() na na ui
     *
     */
    void setProgress(int min, int max, int pos=0);

    /**
     *
     * atravez de um sinal é lancado um texto para o widget resposavel pelo button cancel na na ui
     *
     */
    void setButtonCancelText(QString text);

    /**
     *
     * metodo otimizado para operacoes com QThread
     *
     * metodo utiliza sinal para sua emissão
     *
     * tem a mesma funcionalidade do metodo QWidget::show()
     *
     */
    virtual void show();

    /**
     *
     * metodo otimizado para operacoes com QThread
     *
     * metodo utiliza sinal para sua emissão
     *
     * tem a mesma funcionalidade do metodo QWidget::hide()
     *
     */
    virtual void hide();

    /**
     *
     * metodo otimizado para operacoes com QThread
     *
     * metodo utiliza sinal para sua emissão
     *
     * tem a mesma funcionalidade do metodo QWidget::close()
     *
     */
    virtual void close();

    /**
     *
     * metodo otimizado para operacoes com QThread
     *
     * metodo utiliza sinal para sua emissão
     *
     * tem a mesma funcionalidade do metodo QWidget::setVisible()
     *
     */
    void setVisible(bool value);

public:
    /**
     *
     * metodo otimizado para operacoes com QThread
     *
     * metodo alimenta variavel que será utilizada para construir a visao e definir os controles
     *
     */
    void setVisibleStatus(bool value);

    /**
     *
     * metodo alimenta variavel que será utilizada para construir a visao e definir os controles
     *
     */
    void setVisibleProgress(bool value);

    /**
     *
     * metodo alimenta variavel que será utilizada para construir a visao e definir os controles
     *
     */
    void setVisibleButtonCancel(bool value);

    /**
     *
     * metodo permite verificar externamente no controle do mesmo teve cancelamento solicitado
     *
     */
    bool isCanceled();

    QPushButton* buttonCancel();

public slots:
    /**
     *
     * metodo otimizado para uso com o QThread
     *
     * evento permite limpeza do controle
     *
     */
    void onClear();

    /**
     *
     * metodo otimizado para uso com o QThread
     *
     * evento permite lancar texto
     *
     */
    void onSetStatus(QString message);

    /**
     *
     * metodo otimizado para uso com o QThread
     *
     * evento permite lancar progresso
     *
     */
    void onSetProgress(int min, int max, int pos);

    /**
     *
     * metodo otimizado para uso com o QThread
     *
     * evento permite lancar o show do controle
     *
     */
    void onShow();

    /**
     *
     * metodo otimizado para uso com o QThread
     *
     * evento permite lancar hide do controle
     *
     */
    void onHide();

    /**
     *
     * metodo responsalve atualizar e montar os controles na Ui
     *
     */
    void onUpdate();


    /**
     * @brief onSetVisible
     *
     * evento aplica status de visible no controles
     *
     */
    void onSetVisible();

    void onCancelClicked();
private:
    bool _canceled=false;
    QString _message="";
    int _min=0;
    int _max=100;
    int _pos=0;
    Ui::DProgressStatus *ui;
    bool _visibleStatus=true;
    bool _visibleProgress=false;
    bool _visibleButtonCancel=false;
    bool _hideLiberado=false;
    bool _firtShow=true;
protected:
    /**
     *
     * permite acesso externo ao componente
     *
     * @return
     */
    QProgressBar* progressBar();

    /**
     * @brief labelMessage
     * @return
     * permite acesso externo ao componente
     *
     */
    QLabel* labelMessage();

    virtual void closeEvent(QCloseEvent * event);

    virtual void hideEvent(QHideEvent * event);

    virtual void showEvent(QShowEvent *event);

    /**
     * @brief doClearVariabled
     *
     * limitado a limpar apenas as variaveis nada de slots
     *
     */
    void doClearVariables();
signals:
    /**
     * @brief internalOnShow
     * sinal de uso interno do controle
     *
     * objeto é otimizado quando utilizando de dentro de um QThread
     *
     */
    void internalOnShow();

    /**
     * @brief internalOnHide
     * sinal de uso interno do controle
     *
     * objeto é otimizado quando utilizando de dentro de um QThread
     *
     */
    void internalOnHide();

    /**
     * @brief internalOnUpdate
     *
     * sinal de uso interno do controle
     *
     * objeto é otimizado quando utilizando de dentro de um QThread
     *
     */
    void internalOnUpdate();

    /**
     * @brief internalOnClear
     *
     * sinal de uso interno do controle
     *
     * objeto é otimizado quando utilizando de dentro de um QThread
     *
     */
    void internalOnClear();

    /**
     * @brief onCanceled
     *
     * será emitido este sinal quando o botao cancelar for pressionado
     *
     * objeto é informar outros objetos que o cancelamento foi solicitado
     */
    void onCanceled();
};

#endif // DPROGRESSSTATUS_H
