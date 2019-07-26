#ifndef ARQUIVO_CONFIGURACAOARQUIVONEGOCIO_H
#define ARQUIVO_CONFIGURACAOARQUIVONEGOCIO_H

/** @author Daniel Santos @date 03/07/2018 **/

#include <QObject>
#include <QSet>
#include <QFile>
#include <QStringList>
#include <QByteArray>

namespace gm_arquivo
{
    class RegistroArquivo;

    class ConfiguracaoArquivoNegocio : public QObject
    {
            Q_OBJECT

        public:

            explicit ConfiguracaoArquivoNegocio(QObject *parent = nullptr);

            explicit ConfiguracaoArquivoNegocio(bool comDelimitador = true, QObject *parent = 0);

            explicit ConfiguracaoArquivoNegocio(QString titulo, QObject *parent = 0);

            explicit ConfiguracaoArquivoNegocio(QFile*& arquivo, QObject *parent = 0);

            /*################################# Constantes & Enums ###############################*/

            enum TipoEscrita { UTF_8 = 1, LATIN_1 = 2 };

            /*#################################### Gets & Sets ###################################*/

            QFile *arquivo() const;
            void setArquivo(QFile *arquivo);

            QByteArray conteudoArquivo() const;
            void setConteudoArquivo(const QByteArray &conteudoArquivo);

            QStringList linhasConteudoArquivo();
            void addLinhaConteudoArquivo(QString linha);
            void addLinhasConteudosArquivos(QStringList linhas);
            void removeLinhasConteudoArquivo();

            bool existeArquivoSecundarioCarregado() const;
            void setExisteArquivoSecundarioCarregado(bool existeArquivoSecundarioCarregado);

            TipoEscrita tipoEscrita();
            void setTipoEscrita(TipoEscrita tipoEscrita);

            /*################################# Métodos De Ação ####################################*/

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  comDelimitador método responsável
              * @return TRUE, do contrário FALSE
              */
            bool comDelimitador();

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  defineBlocoPaiEFilhos método responsável
              * @param  blocoPaiEFilhos uma instância de QString
              */
            void defineBlocoPaiEFilhos(QString blocoPaiEFilhos);

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  extrairLinhasConteudoArquivo método responsável
              * @param  registros uma lista de instâncias de RegistroArquivo.
              * @return uma lista de instâncias de QStringList
              */
            QStringList extrairLinhasConteudoArquivo(QList<RegistroArquivo *> registros);

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  extrairLinhasConteudoArquivo método responsável
              * @param  registro uma instância de RegistroArquivo.
              * @return uma lista de instância de QStringList
              */
            QStringList extrairLinhasConteudoArquivo(RegistroArquivo* registro);

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  fechaArquivoNovoGerado método responsável
              */
            void fechaArquivoNovoGerado();

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  flush método responsável
              * @param  linhasRegistros
              * @param  bloco
              * @param  ignoraValidacaoBloco
              * @return TRUE, do contrário FALSE
              */
            bool flush(QStringList linhasRegistros, QString bloco = QString(""), bool ignoraValidacaoBloco = false);

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  flush método responsável por
              * @param  registros uma lista de instâncias de RegistroArquivo
              * @param  flushArquivoAuxiliarNovo
              * @return TRUE, do contrário FALSE
              */
            bool flush(QList<RegistroArquivo*> registros, bool flushArquivoAuxiliarNovo = false);

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  flush método responsável por
              * @param  registro uma instância de Registro
              * @return TRUE caso houve escrita, leitura e liberado da memória, do contário FALSE
              */
            bool flush(RegistroArquivo* registro);

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  flush método responsável por
              * @return TRUE caso houve escrita, leitura e liberado da memória, do contário FALSE
              */
            bool flush(QFile* arquivo);

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  isArqConstruidoOuFinalizado método responsável
              * @return TRUE, do contrário FALSE.
              */
            bool isArqConstruidoOuFinalizado();

            /**
              * @author Daniel Santos
              * @date   03/07/2018
              * @brief  isContemBloco método responsável
              * @param  linha um objeto de QString
              * @param  bloco um objeto de QString
              * @return TRUE caso contenha o bloco do registro, do contrário FALSE.
              */
            bool isContemBloco(QString linha, QString bloco);

        private:

           /*############################# Atributos #########################*/

           QFile* _arquivo;

           QFile* _arquivoNovoAGerar;

           bool _comDelimitador;

           QByteArray _conteudoArquivo;

           TipoEscrita _tipoEscrita;

           QStringList  _linhasConteudoArquivo;

           bool _existeArquivoSecundarioCarregado;

           QString _blocoPaiEFilhos;

           /*######################### Métodos De Ação #########################*/

           /**
             * @author Daniel Santos
             * @date   03/07/2018
             * @brief  extrairConteudoArquivo método responsável
             * @return um objeto de QByteArray
             */
           QByteArray extrairConteudoArquivo();

           /**
             * @author Daniel Santos
             * @date   03/07/2018
             * @brief  flush método responsável
             * @param  um objeto de QByteArray
             * @return TRUE caso houve escrita, leitura e liberado da memória, do contário FALSE
             */
           bool flush(QByteArray arquivoString);

           /**
             * @author Daniel Santos
             * @date   03/07/2018
             * @brief  flushArquivoNovo método responsável
             * @param  um objeto de QByteArray
             * @return TRUE caso houve escrita, leitura e liberado da memória, do contário FALSE
             */
           bool flushArquivoNovo(QByteArray arquivoString);

           void inicializar(bool comDelimitador = true);
    };
}


#endif // ARQUIVO_CONFIGURACAOARQUIVONEGOCIO_H
