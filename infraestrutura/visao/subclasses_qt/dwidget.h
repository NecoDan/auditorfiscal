#ifndef DWIDGET_H
#define DWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVariant>
//#include "infraestrutura/infraestrutura_global.h"
#include "infraestrutura/gm_erro.h"

/**
 * Classe com Basica para Widgets
 *
*/

class DObject;

using namespace gm;

class DWidget : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DWidget(QWidget *parent = 0);
    Q_INVOKABLE ~DWidget();
    Q_INVOKABLE virtual void doEnabled();
    Q_INVOKABLE virtual void doDisabled();

    /**
     * @brief  setFocus
     * @param
     * @return T*
     * Rotina setFocus, reimplementacao para permitir virtualizacao e tambem focar objetivamente em outros controles
     * rotina adaptapara para ser usada atravez de DWidgetMenu
     */
    Q_INVOKABLE virtual void setFocus();

    /**
     * @brief  isClass
     * @param
     * @return bool
     * Rotina testa se o objeto é do tipo de classe desejado
     */
    template <class T>
    bool isClass()
    {
        return dynamic_cast<T*>(this)!=nullptr;
    }

    /**
     * @brief  isClass
     * @param
     * @return bool
     * Rotina testa se o objeto é do tipo de classe desejado
     */
    template <class T>
    bool isClass(QObject*value)
    {
        return qobject_cast<T*>(value)!=nullptr;
    }

    /**
     * @brief  setLastSucess
     * @param
     * @return bool
     * Rotina insere um erro especifico como sucesso
     */
//    virtual bool setLastSucess(QString message="");

    /**
     * @brief  lastError
     * @param
     * @return T*
     * Rotina recuperar erro das classe
     */
    virtual GMErro lastError();

    /**
     * @brief  lastErrorMessage
     * @param
     * @return T*
     * Rotina recuperar mensagem do erro
     */
    virtual QString lastErrorMessage();

    /**
     * @brief  setLastError
     * @param
     * @return T*
     * Rotina insere um erro especific, possibilitando repassar erros de outras classes
     */
    virtual bool setLastError(GMErro value);

    /**
     * @brief  setLastError
     * @param
     * @return T*
     * Rotina insere um erro especific, possibilitando repassar erros de outras classes
     */
//    virtual bool setLastError(GMErro ifError, QString elseMessage);

    /**
     * @brief  setLastError
     * @param
     * @return T*
     * Rotina insere um erro especific, possibilitando repassar erros de outras classes
     */
    virtual bool setLastError(GMErro ifError, GMErro elseError);

    /**
     * @brief  setLastError
     * @param
     * @return T*
     * Rotina insere um erro especific, possibilitando repassar erros de outras classes
     */
//    virtual bool setLastError(DObject objectError);

    /**
     * @brief  setLastError
     * @param
     * @return T*
     * Rotina insere um erro especific, possibilitando repassar erros de outras classes
     */
//    virtual bool setLastError(QString value, GMErro::TipoErro tipoErro = GMErro::VALIDACAO);

    /**
     * @brief  setLastErrorForce
     * @param
     * @return T*
     * Rotina insere um erro especifico e se value nao conter erro ainda sim sera introduzido um erro generico
     */
//    virtual bool setLastErrorForce(GMErro value);

    /**
     * @brief  setLastErrorForce
     * @param
     * @return T*
     * Rotina insere um erro especifico e se value nao conter erro ainda sim sera introduzido um erro generico
     */
//    virtual bool setLastErrorForce(QString value);

    /**
     * @brief  lastErrorMessage
     * @param
     * @return T*
     * Rotina insere um erro especifico e se value nao conter erro ainda sim sera introduzido um erro generico
     */
//    virtual bool setLastErrorForce();

    /**
     * @brief setUnknownError
     * @return
     *
     * gerar um erro desconhecido
     *
     */
//    virtual bool setUnknownError();

    /**
     * @brief setUnknownErrorNULL
     * @return
     *
     * gerar um erro desconhecido
     *
     */
    template <class T>
//    T* setUnknownErrorNULL()
//    {
//        this->setLastError(QString("Erro desconhecido: classe == ").arg(QObject::metaObject()->className()));
//        return NULL;
//    }

    /**
     * @brief setUnknownErrorLIST
     * @return
     *
     * gerar um erro desconhecido
     *
     */
//    template <class T>
//    QList<T*> setUnknownErrorLIST()
//    {
//        this->setLastError(QString("Erro desconhecido: classe == ").arg(QObject::metaObject()->className()));
//        return QList<T*>();
//    }

    /**
     * @brief  clearError
     * @param
     * @return T*
     * Rotina reseta lastError() para sem error
     */
//    virtual void clearError();

    /**
     * @brief  isSucess
     * @param
     * @return T*
     *
     * Rotina verifica sucesso em lastError().isSucesso() e retornar true or false
     *
     */
//    virtual bool isSuccess();

    /**
     * @brief  isError
     * @param
     * @return T*
     * Rotina verifica error em lastError().isErros() e retornar true or false
     */
//    virtual bool isError();

    /**
     * @brief  tag
     * @param
     * @return
     */
    //QVariant tag() const;

    /**
     * @brief  setTag
     * @param
     * @return
     */
//    void setTag(QVariant value);

    /**
     * @brief emitSlot
     * @param slotExecute
     *
     * metodo utilizado para emit um slot.
     *
     *
     * metodo é utilizado para facilitar o uso com QThread
     *
     *
     */
    void emitSlot(const char *slot);

//    /**
//     * @brief emitSlot
//     * @param slotExecute
//     *
//     * metodo utilizado para executar um metodo de uma thread
//     *
//     */
//    void emitSlot(QObject*parentSlot, const char *slot);

    /**
     * @brief execSlotThread
     * @param slotExecute
     *
     * metodo utilizado para executar um slot ja na QThread
     *
     */
//    QThread *execSlotThread(const char *slot);

    /**
     * @brief execSlotThread
     * @param slotExecute
     *
     * metodo utilizado para executar um slot ja na QThread
     *
     */
//    QThread *execSlotThread(QObject*parentSlot, const char *slot);

public:
    GMErro _lastError;
    bool checked() const;
    void setChecked(bool checked);
    void centralizar();
    bool automaticCSS() const;
    void setAutomaticCSS(bool automaticCSS);
private:
    QVariant _tag;
    bool _checked=false;
    bool _internalSetStyleSheet = false;
    bool _automaticCSS = false;
protected:
    virtual QString css();
    Q_INVOKABLE virtual void keyPressEvent(QKeyEvent *event);
    Q_INVOKABLE virtual void showEvent(QShowEvent *event);
signals:
    void slotEmit();
};

#endif // DWIDGET_H
