#include "escrituracao_escrituracaonegocio.h"

// Domínios
#include "escrituracao/dominio/escrituracao_escrituracao.h"

// Daos
#include "escrituracao/dao/escrituracao_escrituracaodao.h"

// Negocios
#include "arquivos/negocio/arquivo_arquivonegocio.h"
#include "escrituracao/negocio/escrituracao_escrituracaonegociocontroller.h"

// Infraestrutura
#include "infraestrutura/banco/gm_dbutil.h"
#include "infraestrutura/banco/dbmanager.h"
#include "infraestrutura/stringutil.h"

// Constantes
const QString DELIMITADOR = "|";

using namespace gm;
using namespace gm_arquivo;

namespace gm_escrituracao
{
    EscrituracaoNegocio::EscrituracaoNegocio(QObject *parent) : QObject(parent)
    {
        _db = DBUtil::conexao();
        _lastError = GMErro();
    }

    EscrituracaoNegocio::EscrituracaoNegocio(QSqlDatabase& db, QObject *parent) : QObject(parent)
    {
        _db = db;
        _lastError = GMErro();
    }

    GMErro EscrituracaoNegocio::lastError()
    {
        return _lastError;
    }

    QList<Escrituracao*> EscrituracaoNegocio::gerarEscrituracoesMaster(QStringList pathsCaminhosArquivo)
    {
        QList<Escrituracao*> escrituracoes;

        if (pathsCaminhosArquivo.isEmpty()){
            _lastError = GMErro("Não foram encontrados ou localizado(s) as pasta(s) para leitura dos arquivo(s)");
            return escrituracoes;
        }

        ArquivoNegocio arquivoNegocio;
        bool gerado = false;

        for (auto pathCaminhoArquivo : pathsCaminhosArquivo) {
            QStringList linhas = arquivoNegocio.gerarLinhasRegistrosEscrituracao(pathCaminhoArquivo);
            escrituracoes << this->salvarEscrituracaoPai(linhas, pathCaminhoArquivo);

            if (!_lastError.isErro())
                gerado = true;
        }

        if (gerado)
            _lastError = GMErro("Escrituracoes e arquivos carregados e salvos com sucesso.");

        return escrituracoes;
    }

    Escrituracao* EscrituracaoNegocio::salvarEscrituracaoPai(QStringList linhasRegistro, QString pathArquivo)
    {
        Escrituracao* escrituracao = nullptr;

        if (linhasRegistro.isEmpty()){
            _lastError = GMErro("Não existem registros e/ou arquivos carregados.", GMErro::VALIDACAO, metaObject()->className());
            return escrituracao;
        }

        escrituracao = this->gerarEscrituracao((this->obtemMapPosicoesRegistroArquivoSped(linhasRegistro)), pathArquivo);
        return escrituracao;
    }

    void EscrituracaoNegocio::salvarEscrituracaoPaiPor(QStringList linhasRegistro)
    {
        if (linhasRegistro.isEmpty()){
            _lastError = GMErro("Não existem registros e/ou arquivos carregados.", GMErro::VALIDACAO, metaObject()->className());
            return;
        }

        Escrituracao* escrituracao = this->gerarEscrituracao((this->obtemMapPosicoesRegistroArquivoSped(linhasRegistro)));

        if (escrituracao == nullptr){
            _lastError = GMErro("Não foi possível salvar a escrituração. Erro no processamento e geração.", GMErro::NEGOCIO, metaObject()->className());
            return;
        }

        _lastError = GMErro("Escrituracao gerada e salva com sucesso.", gm::GMErro::SEM_ERRO);
    }

    void EscrituracaoNegocio::salvarEscrituracaoPor(Escrituracao* escrituracao)
    {
        EscrituracaoDao escrituracaoDAO(_db);
        escrituracaoDAO.salvarEscrituracao(escrituracao);

        if (escrituracaoDAO.lastError().isErro()){
            _lastError = GMErro(escrituracaoDAO.lastError().mensagem(), GMErro::BANCO, metaObject()->className());
            return;
        }

        _lastError = GMErro("Escrituração salva com sucesso.");
    }

    Escrituracao* EscrituracaoNegocio::gerarEscrituracao(QMap<int, QString> mapPosicoesRegistroArquivoSped, QString pathArquivo)
    {
        Escrituracao* escrituracao = nullptr;
        escrituracao = this->extrairObjEscrituracao(mapPosicoesRegistroArquivoSped);
        escrituracao->setPathCaminhoArquivo(pathArquivo);

        EscrituracaoDao escrituracaoDao(_db);
        Escrituracao* escrituracaoExistente = escrituracaoDao.recuperarEscrituracao(escrituracao->ano(), escrituracao->cnpjRaizEmpresa(), escrituracao->cnpj());

        if (escrituracaoExistente != nullptr){
            if (escrituracaoExistente->nomeDatabase().isEmpty()){
                if (!carregarBancoEscrituracaoPor(escrituracao)){
                    _lastError = GMErro(this->_lastError.mensagem(), GMErro::NEGOCIO, metaObject()->className());
                    return nullptr;
                }
            }

            this->processarArquivoSpedFiscal(escrituracaoExistente);
            return escrituracaoExistente;
        }

        this->salvarEscrituracaoPor(escrituracao);

        if (this->_lastError.isErro()){
            _lastError = GMErro(_lastError.mensagem(), GMErro::NEGOCIO, metaObject()->className());
            return nullptr;
        }

        if (!carregarBancoEscrituracaoPor(escrituracao)){
            _lastError = GMErro(this->_lastError.mensagem(), GMErro::NEGOCIO, metaObject()->className());
            return nullptr;
        }

        this->processarArquivoSpedFiscal(escrituracao);
        return escrituracao;
    }

    void EscrituracaoNegocio::processarArquivoSpedFiscal(Escrituracao* escrituracao)
    {
        EscrituracaoNegocioController escrituracaoNegocioController(escrituracao);

        /*Roda na PRODUÇÃO VALENDO!!!!*/
        // escrituracaoNegocioController.efetuarLancamentoEscrituracaoSped(escrituracao);

        /*Roda de modo teste!!!!*/
        escrituracaoNegocioController.efetuarLancamentoEscrituracaoSpedAuxiliar(escrituracao);

        if (escrituracaoNegocioController.lastError().isErro()){
            _lastError = GMErro(escrituracaoNegocioController.lastError().mensagem(), GMErro::NEGOCIO, metaObject()->className());
            return;
        }

        _lastError = GMErro(_lastError.mensagem());
    }

    void EscrituracaoNegocio::atualizarEscrituracao(Escrituracao* escrituracao)
    {
        if (escrituracao == nullptr){
            _lastError = GMErro("Escrituração inválida e/ou inexistente.", GMErro::NEGOCIO, metaObject()->className());
            return;
        }

        EscrituracaoDao escrituracaoDAO(_db);
        escrituracaoDAO.atualizarEscrituracao(escrituracao);

        if (escrituracaoDAO.lastError().isErro()){
            _lastError = GMErro(escrituracaoDAO.lastError().mensagem(), GMErro::BANCO, metaObject()->className());
            return;
        }

        _lastError = GMErro("Escrituração atualizada com sucesso.");
    }

    Escrituracao* EscrituracaoNegocio::extrairObjEscrituracao(QMap<int, QString> mapPosicoesRegistroArquivoSped)
    {
        Escrituracao* escrituracao = EscrituracaoBuilder::umNovaEscrituracao(mapPosicoesRegistroArquivoSped)->constroi();
        return escrituracao;
    }

    bool EscrituracaoNegocio::carregarBancoEscrituracaoPor(Escrituracao* escrituracao)
    {
        bool carregadoOuCriado = false;

        if (escrituracao == nullptr){
            _lastError = GMErro("Escrituração inválida e/ou inexistente.", GMErro::VALIDACAO, metaObject()->className());
            return carregadoOuCriado;
        }

        if (!escrituracao->nomeDatabase().isEmpty())
            return carregadoOuCriado = true;

        QString nomeDatabase = escrituracao->toStringNomeArquivoEscrituracao();

        if (escrituracao->nomeDatabase().isEmpty()){
            QSqlDatabase db = DBUtil::criarDatabase(DBUtil::getDiretorioPadraoDataBase(), DBUtil::DIRETORIO_DATABASE_ABERTOS, nomeDatabase);

            DbManager dbManager(db);
            dbManager.criarAmbienteApuracaoEscrituracao();
            carregadoOuCriado = true;
        }

        if (carregadoOuCriado){
            escrituracao->setNomeDatabase(nomeDatabase);
            escrituracao->setData(QDateTime::currentDateTime());
            this->atualizarEscrituracao(escrituracao);

            if (_lastError.isErro())
                _lastError = GMErro(_lastError.mensagem(), GMErro::NEGOCIO, metaObject()->className());
        }

        return carregadoOuCriado;
    }

    Escrituracao* EscrituracaoNegocio::recuperarEscrituracao(int ano, QString cnpjRaiz, QString cnjp)
    {
        EscrituracaoDao escrituracaoDAO(_db);
        Escrituracao* escrituracao = escrituracaoDAO.recuperarEscrituracao(ano, cnpjRaiz, cnjp);

        if (escrituracaoDAO.lastError().isErro())
            _lastError = GMErro(escrituracaoDAO.lastError().mensagem(), GMErro::NEGOCIO, metaObject()->className());

        return escrituracao;
    }

    Escrituracao* EscrituracaoNegocio::recuperarPorId(long long id)
    {
        EscrituracaoDao escrituracaoDAO(_db);
        Escrituracao* escrituracao = escrituracaoDAO.recuperarPorId(id);

        if (escrituracaoDAO.lastError().isErro())
            _lastError = GMErro(escrituracaoDAO.lastError().mensagem(), GMErro::NEGOCIO, metaObject()->className());

        return escrituracao;
    }

    QList<Escrituracao *> EscrituracaoNegocio::recuperarEscrituracoes()
    {
        EscrituracaoDao escrituracaoDAO(_db);
        QList<Escrituracao*> listaEscrituracoes = escrituracaoDAO.recuperarEscrituracoes();

        if(escrituracaoDAO.lastError().isErro())
            _lastError = GMErro(escrituracaoDAO.lastError().mensagem(), GMErro::NEGOCIO);

        return listaEscrituracoes;
    }

    QMap<int, QString> EscrituracaoNegocio::obtemMapPosicoesRegistroArquivoSped(QStringList linhasRegistro)
    {
        QMap<int, QString> mapPosicoesRegistroArquivoSped;

        for (auto conteudoLinha : linhasRegistro){
            QStringList conteudosObject = StringUtil::extrairListStringToStringListPor(DELIMITADOR, conteudoLinha);

            if (!conteudosObject.isEmpty()){
                int pos = 1;
//                QMap<int, QString> mapPosicoesRegistroArquivoSped;
                for (auto conteudo : conteudosObject){
                    mapPosicoesRegistroArquivoSped.insert(pos, conteudo);
                    pos++;
                }
            }
        }

        return mapPosicoesRegistroArquivoSped;
    }

    QString EscrituracaoNegocio::extrairConteudoLinhaArquivo(QString linhaArquivo)
    {
        QString value;

        if (linhaArquivo.contains("\r") || linhaArquivo.contains("\n")){
            value = linhaArquivo;
        } else{
           value = linhaArquivo.append("\r\n");
        }

        return value;
    }

    void EscrituracaoNegocio::outPutDebug(QVariant value1, QVariant value2)
    {
        qDebug() << value1.toString() << value2.toString();
    }

}
