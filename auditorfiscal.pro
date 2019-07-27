#-------------------------------------------------
#
# Project created by QtCreator 2018-07-03T09:42:21 by Ueider Moraes & Daniel Santos
#
#-------------------------------------------------

# Modulos do Qt
QT += core gui widgets network printsupport sql xml concurrent webenginewidgets quick quickwidgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

lessThan(QT_MAJOR_VERSION, 4): QT +=webkit webkitwidgets
lessThan(QT_MINOR_VERSION, 7): QT +=webkit webkitwidgets

CONFIG += c++11 silent warn_off
QMAKE_CXXFLAGS += -std=c++11

# Incluir a revisao da compilacao no programa
GITREV = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe)
QMAKE_CXXFLAGS += -DGITREV=\\\"$$GITREV\\\"

TARGET = auditorfiscal
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    auditor/dao/auditor_auditordao.cpp \
    arquivos/negocio/arquivo_arquivonegocio.cpp \
    arquivos/dominios/bloco.cpp \
    arquivos/dominios/campo.cpp \
    arquivos/dominios/registro.cpp \
    arquivos/negocio/arquivo_configuracaoarquivonegocio.cpp \
    diretoriopadrao/dominio/escrituracao_diretoriopadrao.cpp \
    diretoriopadrao/dao/escrituracao_diretoriopadraodao.cpp \
    diretoriopadrao/negocio/escrituracao_diretoriopadraonegocio.cpp \
    escrituracao/dao/escrituracao_escrituracaodao.cpp \
    escrituracao/dao/escrituracao_escrituracaospeddao.cpp \
    escrituracao/dominio/escrituracao_escrituracao.cpp \
    escrituracao/dominio/escrituracao_escrituracaospedmovimentacao.cpp \
    escrituracao/dominio/escrituracao_escrituracaosped.cpp \
    escrituracao/negocio/escrituracao_escrituracaonegocio.cpp \
    escrituracao/negocio/escrituracao_escrituracaonegociocontroller.cpp \
    infraestrutura/gm_erro.cpp \
    infraestrutura/banco/dbmanager.cpp \
    infraestrutura/stringutil.cpp \
    infraestrutura/bcmath.cpp \
    infraestrutura/conversor.cpp \
    infraestrutura/doubleutil.cpp \
    infraestrutura/formatador.cpp \
    infraestrutura/banco/gm_dbutil.cpp \
    infraestrutura/banco/gm_dsqlquery.cpp \
    infraestrutura/negocios/gm_negocioteste.cpp \
    infraestrutura/banco/gm_sqlutil.cpp \
    infraestrutura/visao/dprogressstatus.cpp \
    infraestrutura/widgetutil.cpp \
    infraestrutura/visao/subclasses_qt/dwidget.cpp \
    infraestrutura/visao/dmessagebox.cpp \
    infraestrutura/constantes/ub_constantes.cpp \
    infraestrutura/banco/gm_dbconnection.cpp \
    visao/dvisualizararquivos.cpp \
    visao/menuprincipal.cpp \
    visao/dimportararquivos.cpp \
    visao/dresumoauditoria.cpp

HEADERS += \
    arquivos/negocio/arquivo_arquivonegocio.h \
    arquivos/negocio/arquivo_configuracaoarquivonegocio.h \
    arquivos/dominios/bloco.h \
    arquivos/dominios/campo.h \
    arquivos/dominios/registro.h \
    auditor/dao/auditor_auditordao.h \
    diretoriopadrao/dominio/escrituracao_diretoriopadrao.h \
    diretoriopadrao/dao/escrituracao_diretoriopadraodao.h \
    diretoriopadrao/negocio/escrituracao_diretoriopadraonegocio.h \
    escrituracao/dao/escrituracao_escrituracaodao.h \
    escrituracao/dao/escrituracao_escrituracaospeddao.h \
    escrituracao/dominio/escrituracao_escrituracao.h \
    escrituracao/dominio/escrituracao_escrituracaosped.h \
    escrituracao/dominio/escrituracao_escrituracaospedmovimentacao.h \
    escrituracao/negocio/escrituracao_escrituracaonegocio.h \
    escrituracao/negocio/escrituracao_escrituracaonegociocontroller.h \
    infraestrutura/gm_erro.h \
    infraestrutura/stringutil.h \
    infraestrutura/bcmath.h \
    infraestrutura/banco/dbmanager.h \
    infraestrutura/conversor.h \
    infraestrutura/doubleutil.h \
    infraestrutura/formatador.h \
    infraestrutura/banco/gm_dbutil.h \
    infraestrutura/banco/gm_dsqlquery.h \
    infraestrutura/negocios/gm_negocioteste.h \
    infraestrutura/banco/gm_sqlutil.h \
    infraestrutura/visao/dprogressstatus.h \
    infraestrutura/widgetutil.h \
    infraestrutura/visao/subclasses_qt/dwidget.h \
    infraestrutura/visao/dmessagebox.h \
    infraestrutura/constantes/constantes_icones.h \
    infraestrutura/banco/gm_dbconnection.h \
    infraestrutura/gm_itemutil.h \
    visao/dvisualizararquivos.h \
    visao/menuprincipal.h \
    visao/dimportararquivos.h \
    visao/dresumoauditoria.h

FORMS += \
    visao/menuprincipal.ui \
    visao/dimportararquivos.ui \
    visao/dvisualizararquivos.ui \
    visao/dresumoauditoria.ui \
    infraestrutura/visao/dprogressstatus.ui

RESOURCES += \
    auditoriafiscal.qrc
