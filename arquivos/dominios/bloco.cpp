#include "bloco.h"

#include <QStringList>

// Dominios
#include "arquivos/dominios/registro.h"

namespace gm_arquivo
{
    Bloco::Bloco(QObject* parent) : QObject(parent)
    {

    }

    void Bloco::addRegistro(RegistroArquivo* registro)
    {
        if(registro!=nullptr)
            _registros << registro;
    }

    void Bloco::addRegistros(QList<RegistroArquivo*> registros)
    {
        for(auto& item: registros){
            this->addRegistro(item);
        }
    }

    QList<RegistroArquivo*> Bloco::registros() const
    {
        return _registros;
    }

    void Bloco::setRegistros(const QList<RegistroArquivo*>& registros)
    {
        _registros = registros;
    }

    QString Bloco::toString()
    {
        QStringList blocoString;

        for(auto& registro : _registros){
            if (registro == nullptr)
                continue;

            blocoString << registro->toString();
        }

        return blocoString.join("\n");
    }

    QString Bloco::toStringSemSeparadores()
    {
        QStringList blocoString;

        for (auto& registro : _registros){
            blocoString << registro->toStringSemSeparadores();
        }

        return blocoString.join("\n");
    }
}

#include "moc_bloco.cpp" // inclusao do MOC desta classe
