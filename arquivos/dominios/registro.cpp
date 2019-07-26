#include "registro.h"

// Domínios
#include "arquivos/dominios/campo.h"

namespace gm_arquivo
{
    RegistroArquivo::RegistroArquivo(QObject* parent) : QObject(parent)
    {
    }

    RegistroArquivo::~RegistroArquivo()
    {
        if(_mapCampos.count() > 0) {
            qDeleteAll(_mapCampos.begin(), _mapCampos.end());
            _mapCampos.clear();
        }
    }

    void RegistroArquivo::addCampo(Campo* campo)
    {
        int index = 0;

        campo->setParent(this);
        if(!_mapCampos.isEmpty())
        {
            index = _mapCampos.keys().last();
        }

        this->addCampo(++index, campo);
    }

    QList<Campo *> RegistroArquivo::campos()
    {
        return _mapCampos.values();
    }

    void RegistroArquivo::addCampo(int sequencia, Campo* campo)
    {
        _mapCampos.insert(sequencia, campo);
    }

    Campo* RegistroArquivo::campo(int sequencia)
    {
        return _mapCampos.value(sequencia);
    }

    QString RegistroArquivo::toString()
    {
        QString linha =  "|";

        if (!_mapCampos.values().isEmpty())
        {
            foreach (Campo* campo, _mapCampos.values())
            {
                if (campo != nullptr)
                    linha += campo->toString()+ "|";
            }
        }

        return linha;
    }

    QString RegistroArquivo::toStringSemSeparadores()
    {
        QString linha = "";

        for (auto& campo : _mapCampos.values())
        {
            linha += campo->toString();
        }

        return linha;
    }
}

#include "moc_registro.cpp" // inclusao do MOC desta classe
