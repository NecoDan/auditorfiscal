#ifndef DIMPORTARARQUIVOS_H
#define DIMPORTARARQUIVOS_H

#include <QDialog>

namespace Ui
{
    class DImportarArquivos;
}

namespace gm_escrituracao
{
    class DiretorioPadrao;
}

class DImportarArquivos : public QDialog
{
    Q_OBJECT

public:
    explicit DImportarArquivos(QWidget *parent = 0);
    ~DImportarArquivos();

private:

    Ui::DImportarArquivos *ui;

    gm_escrituracao::DiretorioPadrao* _diretorio;

private slots:

    void configuracoesIniciais();

    void setConnects();

    void clicouEmPbLimpar();

    void carregarDiretorioPadrao();

    void clicouEmPbSelecionarDiretorioPadrao();

    void clicouEmPbSelecionarArquivos();

    void carregarArquivosDiretorioPadrao();

    void clicouEmPbSelecionarTodos(bool clicked);

    void clicouEmPbCarregar();

    QStringList getArquivosSelecionados();
};

#endif // DIMPORTARARQUIVOS_H
