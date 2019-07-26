#ifndef DVISUALIZARARQUIVOS_H
#define DVISUALIZARARQUIVOS_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui
{
    class DVisualizarArquivos;
}

namespace gm_escrituracao
{
    class Escrituracao;
}

class DVisualizarArquivos : public QDialog
{
    Q_OBJECT

public:

    explicit DVisualizarArquivos(QWidget *parent = 0);
    ~DVisualizarArquivos();

private:

    Ui::DVisualizarArquivos *ui;

private slots:

    void configuracoesIniciais();

    void setConnects();

    void pesquisarDados();

    void preencherTreeWidget(QList<gm_escrituracao::Escrituracao*> listaEscrituracao);

    void duploCliqueArquivo(QTreeWidgetItem* item, int coluna);
};

#endif // DVISUALIZARARQUIVOS_H
