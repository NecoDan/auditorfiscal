#include "campo.h"

#include "infraestrutura/conversor.h"
//#include "infraestrutura/utilitarios/doubleutil.h"
//#include "infraestrutura/utilitarios/formatador.h"
#include "infraestrutura/stringutil.h"

namespace gm_arquivo
{
    Campo::Campo(QVariant valor, QString descricao, int qtdDigitos, bool qtdExataCaracteres, int qtdCasasDecimais, Campo::TipoDadoCampo tipoDado, QObject* parent) : QObject(parent)
    {
        _valor              = valor;
        _descricao          = descricao;
        _qtdDigitos         = qtdDigitos;
        _qtdCasasDecimais   = qtdCasasDecimais;
        _tipoDadoCampo      = tipoDado;
        _qtdExataCaracteres = qtdExataCaracteres;
    }

    Campo::Campo(bool isValorDouble, double valorDouble, QString descricao, int qtdDigitos, bool qtdExataCaracteres, int qtdCasasDecimais, Campo::TipoDadoCampo tipoDado, QObject* parent) : QObject(parent)
    {
        _valorDouble        = valorDouble;
        _descricao          = descricao;
        _qtdDigitos         = qtdDigitos;
        _qtdCasasDecimais   = qtdCasasDecimais;
        _tipoDadoCampo      = tipoDado;
        _qtdExataCaracteres = qtdExataCaracteres;
        _isValorDouble      = isValorDouble;
    }


    QString Campo::descricao()
    {
        return _descricao;
    }

    void Campo::setDescricao(QString descricao)
    {
        _descricao = descricao;
    }

    int Campo::posicaoInicial()
    {
        return _posicaoInicial;
    }

    void Campo::setPosicaoInicial(int posicaoInicial)
    {
        _posicaoInicial = posicaoInicial;
    }

    int Campo::qtdCasasDecimais()
    {
        return _qtdCasasDecimais;
    }

    void Campo::setQtdCasasDecimais(int qtdCasasDecimais)
    {
        _qtdCasasDecimais = qtdCasasDecimais;
    }

    int Campo::qtdDigitos()
    {
        return _qtdDigitos;
    }

    void Campo::setQtdDigitos(int qtdDigitos)
    {
        _qtdDigitos = qtdDigitos;
    }

    bool Campo::qtdExataCaracteres() const
    {
        return _qtdExataCaracteres;
    }

    void Campo::setQtdExataCaracteres(bool qtdExataCaracteres)
    {
        _qtdExataCaracteres = qtdExataCaracteres;
    }

    Campo::TipoDadoCampo Campo::tipoDadoCampo()
    {
        return _tipoDadoCampo;
    }

    void Campo::setTipoDadoCampo(Campo::TipoDadoCampo tipoDadoCampo)
    {
        _tipoDadoCampo = tipoDadoCampo;
    }

    QVariant Campo::valor()
    {
        return _valor;
    }

    void Campo::setValor(QVariant valor)
    {
        _valor = valor;
    }

    void Campo::extrairValor(QString& linha)
    {
        if(linha.isNull())
        {
            linha = "";
        }

        int posicaoInicialAux = _posicaoInicial - 1;
        QString valor = linha.mid(posicaoInicialAux, tamanho());

        switch(_tipoDadoCampo)
        {
            case Campo::AlfaNumerico:
                _valor = valor.trimmed();
            break;

            case Campo::Numerico:
                _valor = gm::Conversor::toDouble( valor.mid(0, _qtdDigitos).append(".").append(valor.mid(_qtdDigitos, _qtdCasasDecimais)));
            break;

            case Campo::Data:
                _valor = QDate::fromString(valor, "ddMMyyyy");
            break;

            case Campo::Hora:
                _valor = QTime::fromString(valor, "hhmmss");
            break;

            default:
                _valor = valor.trimmed();
            break;
        }
    }

    inline int Campo::tamanho()
    {
        return _qtdDigitos + _qtdCasasDecimais;
    }

    QString Campo::toString()
    {
        switch(_tipoDadoCampo)
        {
            case Campo::AlfaNumerico:
            {
                QString texto;

                if(_qtdExataCaracteres && !_valor.toString().isEmpty())
                {
                    texto = _valor.toString().rightJustified(tamanho(), QChar('0'), true).mid(0, tamanho());
                }
                else
                {
                    texto = _valor.toString().trimmed();
                }

    //            texto = texto.replace(QChar('|'),"");
    //            for(int c = 0; c < 31; c++) {
    //                texto = texto.replace(QChar(c), "");
    //            }

    //            texto = texto.trimmed();

                return texto.replace(QChar::LineFeed, QChar::Space);
            }
            case Campo::Numerico:
            {
                if(_qtdExataCaracteres)
                {
                    if(_isValorDouble && _valorDouble != 0)
                        return QString::number(_valorDouble, 'f', _qtdCasasDecimais).remove(".").rightJustified(tamanho(), QChar('0'), true).mid(0, tamanho());
                    else
                        return QString::number(gm::Conversor::toDouble(_valor), 'f', _qtdCasasDecimais).remove(".").rightJustified(tamanho(), QChar('0'), true).mid(0, tamanho());

                }
                else
                {
                    return gm::Conversor::toString(_valor.toDouble(), _qtdCasasDecimais).remove(".");
                }
            }
            case Campo::Moeda:
            {
                return gm::Conversor::toString(_valor.toDouble(), _qtdCasasDecimais).remove(".");
            }
            case Campo::Data:
            {
                return _valor.toDate().toString("ddMMyyyy");
            }
            case Campo::Hora:
            {
                return _valor.toTime().toString("hhmmss");
            }

            case Campo::Texto:
            {
                QString texto;

                if(_qtdExataCaracteres)
                {
                    texto = _valor.toString().trimmed().leftJustified(tamanho(), QChar(' '), true);
                }
                else
                {
                    texto = _valor.toString().trimmed();
                }

    //            texto = texto.replace(QChar('|'),"");
    //            for(int c = 0; c < 31; c++) {
    //                texto = texto.replace(QChar(c), "");
    //            }

    //            texto = texto.trimmed();

                return texto.replace(QChar::LineFeed, QChar::Space);
            }

            case DataVisualMix:
            {
                return _valor.toDate().toString("ddMMyyyy").leftJustified(tamanho(), QChar('0'), true);
            }

            case MoedaVisualMix:
            {
                QString strValor = StringUtil::retiraCaracteresNaoNumericos(gm::Conversor::toString(_valor.toDouble(), _qtdCasasDecimais));
                return strValor.rightJustified(tamanho(), QChar('0'), true).mid(0, tamanho());
            }

            case BoolVisualMix:
            {
                QString strValor = _valor.toString();

                if(strValor == "t" || strValor == "1")
                    return "S";

                if(strValor == "f" || strValor == "0")
                    return "N";

                return "N";
            }

            case Campo::AlfaNumericoCarone:
            {
                return "\""+_valor.toString().trimmed()+"\"";
            }

            case Campo::NumericoCarone:
            {
                QStringList partes = _valor.toString().split(".");
                if(partes.size() > 1)
                    return partes.at(1) == "0" ? _valor.toString() : gm::Conversor::toString(_valor.toDouble(), _qtdCasasDecimais);
                else
                    return _valor.toString();
            }

            default:
            {
                return "";
            }
        }

        return "";
    }
}

#include "moc_campo.cpp" // inclusao do MOC desta classe
