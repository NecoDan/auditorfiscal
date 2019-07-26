#ifndef ESCRITURACAO_DIRETORIOPADRAO_H
#define ESCRITURACAO_DIRETORIOPADRAO_H

#include <QObject>
#include <QDateTime>

namespace gm_escrituracao
{
    class DiretorioPadrao : public QObject
    {
        Q_OBJECT

    public:

        explicit DiretorioPadrao(QObject *parent = nullptr);

        /*############################### Getters & Setters #########################*/

        long long id() const;
        void setId(long long id);

        QString caminho() const;
        void setCaminho(const QString &caminho);

        QDateTime data() const;
        void setData(const QDateTime &data);

    private:

        /*############################### Atributos ###########################*/

        long long   _id;

        QString     _caminho;

        QDateTime   _data;

        /*########################### Métodos de Ação ##########################*/

        void inicializar(int id = 0);
    };

} // namespace gm_escrituracao

#endif // ESCRITURACAO_DIRETORIOPADRAO_H
