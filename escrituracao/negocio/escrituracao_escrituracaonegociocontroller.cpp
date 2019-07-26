#include "escrituracao_escrituracaonegociocontroller.h"

// Domínios
#include "escrituracao/dominio/escrituracao_escrituracao.h"
#include "escrituracao/dominio/escrituracao_escrituracaosped.h"

// Daos
#include "escrituracao/dao/escrituracao_escrituracaodao.h"
#include "escrituracao/dao/escrituracao_escrituracaospeddao.h"

// Negócios
#include "arquivos/negocio/arquivo_arquivonegocio.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"

using namespace gm;

namespace gm_escrituracao
{
    EscrituracaoNegocioController::EscrituracaoNegocioController(Escrituracao* escrituracao, QObject *parent) : QObject(parent)
    {
        _escrituracao = escrituracao;
        this->inicializarDataBase();
    }

    EscrituracaoNegocioController::EscrituracaoNegocioController(int ano, QString cnpjRaiz, QString cnpjFilial, QObject *parent) : QObject(parent)
    {
        QSqlDatabase db = DBUtil::conexao();
        EscrituracaoDao escrituracaoDao(db);
        _escrituracao = escrituracaoDao.recuperarEscrituracao(ano, cnpjRaiz, cnpjFilial);
        this->inicializarDataBase();
    }

    void EscrituracaoNegocioController::inicializarDataBase()
    {
        if (_escrituracao != nullptr && !_escrituracao->nomeDatabase().isEmpty())
            _dbConexao = DBUtil::conexao(_escrituracao->nomeDatabase());
    }

    void EscrituracaoNegocioController::fecharDatabase()
    {
        _dbConexao.close();
    }

    bool EscrituracaoNegocioController::isParametrosValidosEscrituracao()
    {
        if (!_dbConexao.isValid() || !_dbConexao.isOpen()){
            _lastError = GMErro("Não existe conexão válida.", GMErro::NEGOCIO, metaObject()->className());
            return false;
        }

        if (!this->_dbConexao.transaction()){
            _lastError = GMErro("Não existe conexão válida ou impossível conectar com a base de dados local.", GMErro::NEGOCIO, metaObject()->className());
            return false;
        }

        return true;
    }

    GMErro EscrituracaoNegocioController::lastError()
    {
        return _lastError;
    }

    /*################################################# Métodos de Ação  ##################################################*/

    EscrituracaoSped*EscrituracaoNegocioController::constroiObjEscrituracaoSped(int mes)
    {
        EscrituracaoSped* escrituracaoSped = new EscrituracaoSped();

        escrituracaoSped->setCnpj(_escrituracao->cnpj());
        escrituracaoSped->setDescricaoFilial(_escrituracao->descricaoFilial());
        escrituracaoSped->setData(QDateTime::currentDateTime());
        escrituracaoSped->setCaminhoArquivo(_escrituracao->pathCaminhoArquivo());
        escrituracaoSped->setAno(_escrituracao->ano());
        (mes > 0) ? escrituracaoSped->setMes(mes) : escrituracaoSped->setMes(_escrituracao->mes());

        return escrituracaoSped;
    }

    void EscrituracaoNegocioController::efetuarLancamentoEscrituracaoSped(Escrituracao* escrituracao)
    {                
        if (!isParametrosValidosEscrituracao())
            return;

        _escrituracao = escrituracao;

        EscrituracaoSped* escrituracaoSped = this->constroiObjEscrituracaoSped();
        this->salvarEscrituracaoSped(escrituracaoSped, false);

        if (_lastError.isErro()){
            _lastError = GMErro(_lastError.mensagem(), GMErro::NEGOCIO, metaObject()->className());
            this->_dbConexao.rollback();
            return;
        }

        this->_dbConexao.commit();
        _lastError = GMErro("Lançamento escrituração SPEDFISCAL efetuado c/ sucesso.");
    }

    void EscrituracaoNegocioController::efetuarLancamentoEscrituracaoSpedAuxiliar(Escrituracao* escrituracao)
    {
        if (!isParametrosValidosEscrituracao())
            return;

        int mes = escrituracao->mes();

        QList<EscrituracaoSped*> escrituracoesSped;
        escrituracoesSped << this->constroiObjEscrituracaoSped(mes);
        mes++;
        escrituracoesSped << this->constroiObjEscrituracaoSped(mes);
        mes++;
        escrituracoesSped << this->constroiObjEscrituracaoSped(mes);
        mes++;
        escrituracoesSped << this->constroiObjEscrituracaoSped(mes);
        mes++;
        escrituracoesSped << this->constroiObjEscrituracaoSped(mes);
        mes++;
        escrituracoesSped << this->constroiObjEscrituracaoSped(mes);
        mes++;
        escrituracoesSped << this->constroiObjEscrituracaoSped(mes);

        for (auto& escrituracaoSped : escrituracoesSped){
            this->salvarEscrituracaoSped(escrituracaoSped, false);

            if (_lastError.isErro()){
                _lastError = GMErro(_lastError.mensagem(), GMErro::NEGOCIO, metaObject()->className());
                this->_dbConexao.rollback();
                return;
            }

            this->_dbConexao.commit();
        }

        _lastError = GMErro("Lançamento escrituração SPEDFISCAL efetuado c/ sucesso.");
    }

    void EscrituracaoNegocioController::salvarEscrituracaoSped(EscrituracaoSped* escrituracaoSped, bool validaParams)
    {
        if (validaParams && !isParametrosValidosEscrituracao())
            return;

        if (escrituracaoSped == nullptr){
            _lastError = GMErro("Escrituração SPEDFISCAL inválida e/ou inexistente.", GMErro::NEGOCIO, metaObject()->className());
            return;
        }

        EscrituracaoSpedDao escrituracaoSpedDao(_dbConexao);
        escrituracaoSpedDao.salvarEscrituracaoSped(escrituracaoSped);

        if (escrituracaoSpedDao.lastError().isErro()){
            _lastError = GMErro(escrituracaoSpedDao.lastError().mensagem(), GMErro::NEGOCIO, metaObject()->className());
            return;
        }

        _lastError = GMErro("Escrituração SPEDFISCAL salva c/ sucesso.");
    }

    EscrituracaoSped* EscrituracaoNegocioController::recuperarEscrituracaoSped(Escrituracao* escrituracao)
    {
        if (!isParametrosValidosEscrituracao())
            return nullptr;

        if (escrituracao == nullptr){
            _lastError = GMErro("Escrituração inválida e/ou inexistente.", GMErro::NEGOCIO, metaObject()->className());
            return nullptr;
        }

        EscrituracaoSpedDao escrituracaoSpedDao(_dbConexao);
        EscrituracaoSped* escrituracaoSped = escrituracaoSpedDao.recuperarEscrituracaoSped(escrituracao);

        if (escrituracaoSpedDao.lastError().isErro()){
            _lastError = GMErro(escrituracaoSpedDao.lastError().mensagem(), GMErro::NEGOCIO, metaObject()->className());
            return nullptr;
        }

        return escrituracaoSped;
    }

    QList<EscrituracaoSped*> EscrituracaoNegocioController::recuperarEscrituracoesSped()
    {
        QList<EscrituracaoSped*> escrituracoesSped;

        if (!isParametrosValidosEscrituracao())
            return escrituracoesSped;

        EscrituracaoSpedDao escrituracaoSpedDao(_dbConexao);
        escrituracoesSped = escrituracaoSpedDao.recuperarEscrituracoesSped();

        if (escrituracaoSpedDao.lastError().isErro()){
            _lastError = GMErro(escrituracaoSpedDao.lastError().mensagem(), GMErro::NEGOCIO, metaObject()->className());
            return escrituracoesSped;
        }

        return escrituracoesSped;
    }

    QList<EscrituracaoSped*> EscrituracaoNegocioController::recuperarEscrituracoesSped(Escrituracao* escrituracao)
    {
        QList<EscrituracaoSped*> escrituracoesSped;

        if (!isParametrosValidosEscrituracao())
            return escrituracoesSped;

        if (escrituracao == nullptr){
            _lastError = GMErro("Escrituração inválida e/ou inexistente.", GMErro::NEGOCIO, metaObject()->className());
            return escrituracoesSped;
        }

        EscrituracaoSpedDao escrituracaoSpedDao(_dbConexao);
        escrituracoesSped = escrituracaoSpedDao.recuperarEscrituracoesSped();

        if (escrituracaoSpedDao.lastError().isErro()){
            _lastError = GMErro(escrituracaoSpedDao.lastError().mensagem(), GMErro::NEGOCIO, metaObject()->className());
            return escrituracoesSped;
        }

        return escrituracoesSped;
    }

}
