#include <QApplication>
#include <csignal>
#include <QCoreApplication>
#include <QDirIterator>
#include <QFontDatabase>
#include <QMessageBox>
#include <QStringList>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QThread>
#include <QObject>

// Visão
#include "visao/menuprincipal.h"

// Infraestrutura
#include "infraestrutura/negocios/gm_negocioteste.h"
#include "infraestrutura/banco/dbmanager.h"
#include "infraestrutura/banco/gm_dbutil.h"

void funcaoTestes()
{
    NegocioTeste negocioTeste;
    negocioTeste.testeDoDaniel();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Auditor Fiscal 2019");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#if QT_VERSION < 0x050000
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

    // Carregar fontes TTF e estilos QSS do QRC
    QString stylesheet;
    QStringList styles;
    QDirIterator qrc(":", QDirIterator::Subdirectories);

    while (qrc.hasNext()) {
        QString file = qrc.next();

        if(file.endsWith(".ttf", Qt::CaseInsensitive))
            QFontDatabase::addApplicationFont(file);
        else if(file.endsWith(".qss", Qt::CaseInsensitive)) {
            styles << file;
        }
    }

    styles.sort();
    for(int i = 0; i < styles.count(); i++) {
        QFile f_style(styles.at(i));
        if(f_style.open(QIODevice::ReadOnly)) {
            stylesheet += f_style.readAll();
            f_style.close();
        }
    }
    styles.clear();

    a.setStyleSheet(stylesheet);
#if QT_VERSION < 0x050000
    a.setStyle("cleanlooks");
#else
    a.setStyle("fusion");
#endif

#ifdef Q_OS_WIN32
    QString env = getenv("SYSTEMROOT");
    QCoreApplication::addLibraryPath(env+"\\system32");
#endif

    QLocale::setDefault(QLocale(QLocale::Portuguese, QLocale::Brazil));
    QStringList argumentos = a.arguments();

    /*Inicialização conexão PADRÃO*/
    QSqlDatabase db = gm::DBUtil::conexao();

    DbManager dbManager(db, true);
    Q_UNUSED(dbManager);

    bool temArgumentos = false;
    QString strConteudoTestes = "testesmain";

    for (int i = 0; i < argumentos.count(); i++){
        if(argumentos.at(i) == strConteudoTestes){
            temArgumentos = true;
            funcaoTestes();
            break;
        }
    }

    if (!temArgumentos && !argumentos.contains(strConteudoTestes)){
        MenuPrincipal menu;
        menu.show();
        return a.exec();
    }

    return a.exec();
}
