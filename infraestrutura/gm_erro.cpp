#include "gm_erro.h"
#include <QPointer>
#include <QDebug>

namespace gm
{
	GMErro::GMErro(QString mensagem, GMErro::TipoErro tipo, QString classe)
	{
        _mensagem = mensagem;
		_tipo = tipo;
		_classe = classe;
		_camposInvalidos = QMap<QString, QString>();

        //gm_log::RetornoNegocio::instance()->registrarErro(StackTraceUtil::getTrace(), this);
	}

    GMErro::GMErro(QSqlError erro){
        _mensagem = erro.text();
        _tipo = BANCO;
        _classe = "";
        _camposInvalidos = QMap<QString, QString>();

        //gm_log::RetornoNegocio::instance()->registrarErro(StackTraceUtil::getTrace(), this);
    }

	void GMErro::adicionarCampoInvalido(QString campo, QString detalhe)
	{
		_camposInvalidos.insert(campo, detalhe);
	}

	QMap<QString, QString> GMErro::camposInvalidos()
	{
		return _camposInvalidos;
	}

	void GMErro::setCamposInvalidos(QMap<QString, QString> value)
	{
		_camposInvalidos = value;
	}

	QString GMErro::classe() const
	{
		return _classe;
	}

	void GMErro::clear()
	{
		_tipo = SEM_ERRO;
		_mensagem.clear();
		_camposInvalidos.clear();
	}

	GMErro GMErro::fromPointer(GMErro* gmerro)
	{
		return GMErro(gmerro->mensagem(), gmerro->tipo(), gmerro->classe());
	}

	bool GMErro::isAlerta()
	{
		return _tipo == ALERTA;
	}

	bool GMErro::isErro()
	{
		return _tipo != SEM_ERRO;
	}

	bool GMErro::isSucesso()
	{
		return _tipo == SEM_ERRO;
	}

	QString GMErro::mensagem() const
	{
		if(_tipo == SEM_ERRO || _camposInvalidos.size() == 0)
		{
//#ifdef QT_DEBUG
//            if(_mensagem.contains("Sem erro")){
//                qFatal("Sem erro");
//            }
//#endif
			return "<p>" + _mensagem + "</p>";
		}

		QString mensagemCamposInvalidos;
		QMapIterator<QString, QString> it(_camposInvalidos);

		while(it.hasNext())
		{
			it.next();
			mensagemCamposInvalidos.append("<b>" + it.key() + "</b>: " + it.value() + "<br/>");
		}

		QString mensagemErroValidacao;
		mensagemErroValidacao.append("<p><b>" + _mensagem + "</b><p>");
		mensagemErroValidacao.append(mensagemCamposInvalidos);
//#ifdef QT_DEBUG
//        if(_mensagem.contains("Sem erro")){
//            qFatal("Sem erro");
//        }
//#endif
        return mensagemErroValidacao;
    }

    QString GMErro::text() const
    {
        return this->mensagem();
    }

	GMErro::TipoErro GMErro::tipo() const
	{
		return _tipo;
	}

	GMErro* GMErro::toPointer(GMErro gmerro)
	{
		return new GMErro(gmerro.mensagem(), gmerro.tipo(), gmerro.classe());
	}

	QString GMErro::toString()
	{
		if(_tipo == BANCO)
		{
			return "Erro de banco de dados.";
		}

		if(_tipo == NEGOCIO)
		{
			return "Erro de regra de negócio.";
		}

		if(_tipo == VALIDACAO)
		{
			return "Erro de validação de campos.";
		}

		if(_tipo == ALERTA)
		{
			return "Atenção.";
		}

		if(_tipo == SEM_ERRO)
		{
			return "Sucesso.";
		}

		if(_tipo == INFRAESTRUTURA)
		{
			return "Erro de infraestrutura de serviço.";
		}

		return "";
	}

	void GMErro::setMensagem(QString value)
	{
		_mensagem = value;
	}

	void GMErro::setTipo(GMErro::TipoErro tipo)
	{
		_tipo = tipo;
	}

	bool GMErro::temCamposInvalidos()
	{
        return !_camposInvalidos.isEmpty();
    }

    bool GMErro::isValid()
    {
        return this->isErro();
    }

	void GMErro::operator =(QSqlError error)
	{
		if (error.type() != QSqlError::NoError)
		{
			(*this)._mensagem = error.text();
			(*this)._tipo = GMErro::BANCO;
		}
		else
		{
			(*this)._mensagem = error.text();
			(*this)._tipo = GMErro::SEM_ERRO;
		}
	}

	void GMErro::operator =(GMErro* error)
	{
		// Não mudar para método get, pois senão duplica as mensagens na hora de exibir
		(*this)._mensagem = error->_mensagem;
		(*this)._tipo = error->tipo();
		(*this)._camposInvalidos = error->camposInvalidos();
	}
}
