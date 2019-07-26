#ifndef DRESUMOAUDITORIA_H
#define DRESUMOAUDITORIA_H

#include <QDialog>

#include "escrituracao/dominio/escrituracao_escrituracao.h"
#include "escrituracao/dominio/escrituracao_escrituracaosped.h"

namespace Ui
{
    class DResumoAuditoria;
}

class DResumoAuditoria : public QDialog
{
    Q_OBJECT

public:
    explicit DResumoAuditoria(gm_escrituracao::Escrituracao* escrituracao, QWidget *parent = 0);
    ~DResumoAuditoria();

private:

    Ui::DResumoAuditoria *ui;

private slots:

    void configuracoesIniciais();

    void setConnects();

    void pesquisarDados(gm_escrituracao::Escrituracao* escrituracao);

    void montarResumo(QList<gm_escrituracao::EscrituracaoSped*> listaEscrituracaoSped);
};

#endif // DRESUMOAUDITORIA_H
