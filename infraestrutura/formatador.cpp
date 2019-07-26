#include "formatador.h"

#include "infraestrutura/stringutil.h"
#include "infraestrutura/conversor.h"

namespace gm
{
    const QLocale Formatador::_locale  = QLocale(QLocale::Portuguese, QLocale::Brazil);

    Formatador::Formatador()
    {
    }

    QString Formatador::formatarCEP(long long cep)
    {
        return formatarCEP(QString::number(cep));
    }

    QString Formatador::formatarCEP(const QString &cep)
    {
        QString aux = StringUtil::retiraCaracteresNaoNumericos(cep).trimmed();
        return aux.mid(0, 5) + "-" + aux.mid(5, 3);
    }

    QString Formatador::formatarChaveNfeCte(const QString &chave)
    {
        QString chaveFormatada;

        for(int i = 0 ; i < 11 ; i++)
        {
            chaveFormatada.append(chave.mid(i * 4, 4) + " ");
        }

        return chaveFormatada.trimmed();
    }

    QString Formatador::formatarCNPJ(long long cnpj)
    {
        QString cnpjString = QString::number(cnpj).rightJustified(14, '0');

        QString parte1 = cnpjString.mid(0, 2);
        QString parte2 = cnpjString.mid(2, 3);
        QString parte3 = cnpjString.mid(5, 3);
        QString parte4 = cnpjString.mid(8, 4);
        QString parte5 = cnpjString.mid(12, 2);

        QString formato = "%1.%2.%3/%4-%5";

        return formato.arg(parte1, parte2, parte3, parte4, parte5);
    }

    QString Formatador::formatarCPF(long long cpf)
    {
        QString cpfString = QString::number(cpf).rightJustified(11, '0');

        QString parte1 = cpfString.mid(0, 3);
        QString parte2 = cpfString.mid(3, 3);
        QString parte3 = cpfString.mid(6, 3);
        QString parte4 = cpfString.mid(9, 2);

        QString formato = "%1.%2.%3-%4";

        return formato.arg(parte1, parte2, parte3, parte4);
    }

    QString Formatador::formatarFax(QString ddd, QString numeroFax)
    {
        QString dddAjustado = StringUtil::retiraCaracteresNaoNumericos(ddd).rightJustified(3, '0');
        QString numeroFaxAjustado = StringUtil::retiraCaracteresNaoNumericos(numeroFax);

        return "(" + dddAjustado + ") " + numeroFaxAjustado;
    }

    QString Formatador::formatarInscricaoEstadual(long long inscricaoEstadual)
    {
        QString inscricaoString = QString::number(inscricaoEstadual).rightJustified(9, '0');

        QString parte1 = inscricaoString.mid(0, 3);
        QString parte2 = inscricaoString.mid(3, 3);
        QString parte3 = inscricaoString.mid(6, 3);

        QString formato = "%1.%2.%3";

        return formato.arg(parte1, parte2, parte3);
    }

    QString Formatador::formatarMoeda(double numero, int precisao)
    {
        return "R$ " + formatarNumero(numero, precisao);
    }

    QString Formatador::formatarMoeda(QString numero, int precisao)
    {
        return formatarMoeda(gm::Conversor::toDouble(numero), precisao);
    }

    QString Formatador::formatarNumero(double numero, int precisao)
    {
        QString numeroFormatado = _locale.toString(numero, 'f', precisao);

        // Para evitar a situação bizarra do zero negativo, quando arredondamos um número negativo com zeros casas decimais
        if(numeroFormatado == "-0" || numeroFormatado == "-0,00")
        {
            numeroFormatado = numeroFormatado.replace("-", "");
        }

        return numeroFormatado;
    }

    QString Formatador::formatarValorNotacaoContabil(double numero, int precisao)
    {
        QString numeroFormatado;

        if(numero < 0)
            numeroFormatado = "(" + _locale.toString(numero, 'f', precisao).replace("-","") + ")";
        else
            numeroFormatado = _locale.toString(numero, 'f', precisao);

        // Para evitar a situação bizarra do zero negativo, quando arredondamos um número negativo com zeros casas decimais
        if(numeroFormatado == "-0" || numeroFormatado == "-0,00")
        {
            numeroFormatado = numeroFormatado.replace("-", "");
        }

        return numeroFormatado;
    }

    QString Formatador::formatarNumero(QString numero, int precisao)
    {
        return formatarNumero(gm::Conversor::toDouble(numero), precisao);
    }

    QString Formatador::formatarPeso(double numero, int precisao)
    {
        return formatarNumero(numero, precisao);
    }

    QString Formatador::formatarPeso(QString numero, int precisao)
    {
        return formatarNumero(gm::Conversor::toDouble(numero), precisao);
    }

    QString Formatador::formatarPorcentagem(double numero, int precisao)
    {
        return formatarNumero(numero, precisao) + " %";
    }

    QString Formatador::formatarPorcentagem(QString numero, int precisao)
    {
        return formatarPorcentagem(gm::Conversor::toDouble(numero), precisao);
    }

    QString Formatador::formatarTelefone(QString ddd, QString numeroTelefone)
    {
        QString dddAjustado = StringUtil::retiraCaracteresNaoNumericos(ddd).rightJustified(3, '0');
        QString numeroTelefoneAjustado = StringUtil::retiraCaracteresNaoNumericos(numeroTelefone);

        return "(" + dddAjustado + ") " + numeroTelefoneAjustado;
    }

    QString Formatador::formataHora(QTime hora)
    {
        return hora.toString("hh:mm:ss");
    }

    QString Formatador::formataHora(QString hora)
    {
        return formataHora(QTime::fromString(hora));
    }

    QString Formatador::formatarPlacaVeiculo(QString placaVeiculo)
    {
        placaVeiculo.replace("-", "");
        QString letra = placaVeiculo.mid(0,3);
        QString numero = placaVeiculo.mid(3,4);

        return letra + "-" + numero;
    }

    QString Formatador::formatarCargaHoraria(QString cargaHoraria)
    {
        cargaHoraria.replace(":", "");
        QString hora = cargaHoraria.mid(0,2);
        QString minuto = cargaHoraria.mid(2,2);

        return hora + ":" + minuto;
    }

    long long Formatador::formatarCodigoBarras(QString codigo)
    {
        QString codigoFormatado = StringUtil::retiraCaracteresNaoNumericos(codigo);
        return codigoFormatado.toLongLong();
    }

    QString Formatador::formataData(QString data)
    {
        return formataData(QDate::fromString(data));
    }

    QString Formatador::formataData(QDate date)
    {
        return date.toString("dd/MM/yyyy");
    }

    QString Formatador::formataData(QDateTime date)
    {
        return date.toString("dd/MM/yyyy");
    }

    QString Formatador::formataDataHora(QDateTime date)
    {
        return date.toString("dd/MM/yyyy hh:mm:ss");
    }

    QString Formatador::formataDataPorExtensoCompleta(QDate data)
    {
        QString dataFormatadaPorExtenso;

        QLocale locale(QLocale::Portuguese, QLocale::Brazil);
        dataFormatadaPorExtenso = locale.toString(data, QLocale::LongFormat);

        return dataFormatadaPorExtenso;
    }

    QString Formatador::formataDataPorExtensoSemDiaSemana(QDate data)
    {
        QString dataFormatadaPorExtenso;
        QLocale locale(QLocale::Portuguese, QLocale::Brazil);

        QStringList diasDaSemana = QStringList() << "domingo," << "segunda-feira," << "terça-feira," << "quarta-feira," << "quinta-feira," << "sexta-Feira," << "sábado,";
        dataFormatadaPorExtenso = locale.toString(data, QLocale::LongFormat);

        if(!dataFormatadaPorExtenso.isEmpty())
        {
            for (int i = 0; i < diasDaSemana.size(); ++i)
            {
                while(dataFormatadaPorExtenso.contains(diasDaSemana.at(i)))
                {
                    dataFormatadaPorExtenso = dataFormatadaPorExtenso.replace(diasDaSemana.at(i),"");
                }
            }
        }
        return dataFormatadaPorExtenso;
    }

    QString Formatador::formataDataComoAnoMes(int anoMes)
    {
        QString dataAnoMesStr = QString::number(anoMes);
        QDate dataProAnoMes(dataAnoMesStr.mid(0, 4).toInt(), dataAnoMesStr.mid(4, 2).toInt(), 1);
        return dataAnoMesStr = dataProAnoMes.toString("MMM/yyyy").toUpper();
    }

    QString Formatador::formataDataComoAnoMesCompleta(int anoMes)
    {
        QString dataAnoMesStr = QString::number(anoMes);
        QDate dataProAnoMes(dataAnoMesStr.mid(0, 4).toInt(), dataAnoMesStr.mid(4, 2).toInt(), 1);
        return dataAnoMesStr = dataProAnoMes.toString("MMMM/yyyy").toUpper();
    }
}
