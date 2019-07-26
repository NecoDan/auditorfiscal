#include "stringutil.h"
#include <QRegExp>

// Infraestrutura
#include "infraestrutura/conversor.h"
#include "infraestrutura/doubleutil.h"
#include "infraestrutura/formatador.h"

StringUtil::StringUtil()
{

}

StringUtil::~StringUtil()
{

}

QString StringUtil::adicionarQuebraNaStringPorIntervalo(QString string, int intervalo)
{
	int tamanho = 1;

    if (string.trimmed().isEmpty())
		return  string;

    if (string.size() < intervalo)
		return string;

	/* Abaixo eu removo as quebras e espaços que ficarão duplicados, para então aplicar a quebra de linha da maneira passada */
	string = string.replace("\n", " ");

	while (string.contains("  "))
		string = string.replace("  ", " ");

	int incrementoIntervalo = intervalo * tamanho;

	while(string.size() > incrementoIntervalo){
		string.insert(incrementoIntervalo, "\n");
		tamanho++;
		incrementoIntervalo = intervalo * tamanho;
	}

	return string;
}

QString StringUtil::centralizar(QString s, int size)
{
	return centralizar(s, size, " ");
}

QString StringUtil::centralizar(QString s, int size, QString pad)
{
	if(s.trimmed().isEmpty()){
		return  QString().fill(QChar(' '),size);
	}

	if (s.isNull() || size <= s.length()){
		return s;
	}

	QString sb;

	for(int i = 0 ; i < (size - s.length()) / 2 ; i++){
		sb.append(pad);
	}

	sb.append(s);

	while(sb.length() < size){
		sb.append(pad);
	}

	return sb;
}

bool StringUtil::isEmpty(QString value)
{
	return (value.isNull() || value.trimmed().isEmpty());
}

bool StringUtil::mesmaRaizCnpj(QString cnpj1, QString cnpj2)
{
    if (cnpj1.length() <8 || cnpj2.length() <8 )
        return false;

    QString raiz1="";
    QString raiz2="";
    QRegExp regRaiz("[1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]");

    if (regRaiz.indexIn(cnpj1)!=-1)
        raiz1 = regRaiz.cap();

    if (regRaiz.indexIn(cnpj2) != -1)
        raiz2 = regRaiz.cap();

    return (raiz1 == raiz2);
}

QString StringUtil::primeiraLetraMaiuscula(QString nome)
{
	QString letra = nome.mid(0, 1);
	letra = letra.toUpper();
	nome.replace(0, 1, letra);
	return nome;
}

QString StringUtil::primeiraLetraNomeMaiuscula(QString nome)
{
	QString novoNome;

	nome = nome.toLower().trimmed();

	QStringList listaNomes = nome.split(" ");

	foreach (QString texto, listaNomes) {
		novoNome += primeiraLetraMaiuscula(texto) + " ";
	}

	return novoNome.trimmed();
}

QString StringUtil::removerAcentos(QString texto)
{
	texto.replace(QRegExp("á|à|â|ã|ä"), "a");
	texto.replace(QRegExp("Á|À|Â|Ã|Ä"), "A");

	texto.replace(QRegExp("é|è|ê|ẽ|ë"), "e");
	texto.replace(QRegExp("É|È|Ê|Ẽ|Ë"), "E");

	texto.replace(QRegExp("í|ì|î|ĩ|ï"), "i");
	texto.replace(QRegExp("Í|Ì|Î|Ĩ|Ï"), "I");

	texto.replace(QRegExp("ó|ò|ô|õ|ö"), "o");
	texto.replace(QRegExp("Ó|Ò|Ô|Õ|Ö"), "O");

	texto.replace(QRegExp("ú|ù|û|ũ|ü"), "u");
	texto.replace(QRegExp("Ú|Ù|Û|Ũ|Ü"), "U");

	texto.replace(QRegExp("ç"), "c");
	texto.replace(QRegExp("Ç"), "C");

	return texto;
}

QString StringUtil::removerCaracterEspeciais(QString texto)
{
    char c='\u0000';

	texto.replace(QRegExp(",|&|º|°"), " ");
	texto.replace(QRegExp("-|_"), " ");
	texto.replace(QRegExp("/"), " ");
    texto.replace(QRegExp("§"), " ");
    texto.replace(QRegExp("³"), " ");
    texto.replace(QRegExp("^"), " ");
    texto.replace(QRegExp("[!#$%'()*+-./:;?@[\\\]_`{}~=><¨¬§]"), " ");

    texto.replace(c, " ");


	return texto;
}

QString StringUtil::removerEspacosDuplicados(QString string)
{
	string = string.replace("\n", " ");

	while (string.contains("  ")){
		string = string.replace("  ", " ");
	}

	return string;
}

QString StringUtil::removerZerosIniciais(QString texto)
{
    return texto.replace(QRegExp("^0*"),"");
}

QString StringUtil::removerCaracteresNaoTextuais(QString string)
{
    return string.replace(QRegExp("[!#$%&'()*+,-./:;?@[\\\]_`{|}~=><¨¬§'º°³0-9]"), "").replace("^", "");
}

QString StringUtil::removerSimbolos(QString string)
{
    return string.replace(QRegExp("[!#$%&'()*+,-./:;?@[\\\]_`{|}~=><¨¬§'º°³]"), "").replace("^", "");
}

QString StringUtil::replaceAll(QString valor, QString valorAserSubisttituido, QString subistituicao)
{
	QString arg = valor;

	while (arg.contains(valorAserSubisttituido)){
		arg = arg.replace(valorAserSubisttituido,subistituicao);
	}

	return arg;
}

QString StringUtil::retiraCaracteresNaoNumericos(QString valor)
{
    if (valor == nullptr || valor.isEmpty())
        return nullptr;

	return valor.replace(QRegExp("\\D+"), "");
}

bool StringUtil::toBool(QString valor)
{
	valor = valor.trimmed().toLower();

	if(valor == "true" || valor == "t" || valor == "1"){
		return true;
	}

	if(valor == "false" || valor == "f" || valor == "0"){
		return false;
	}

	return false;
}

QStringList StringUtil::toStringList(QList<long long> lista)
{
	QStringList listaString;

    foreach (long long item, lista){
		listaString << QString::number(item);
	}

	return listaString;
}

QString StringUtil::inserirZerosAEsquerda(QString string, int tamanhoMaximoString)
{
    return string.rightJustified(tamanhoMaximoString, '0');
}

QString StringUtil::inserirZerosAEsquerda(int string, int tamanhoMaximoString)
{
    return QString::number(string).rightJustified(tamanhoMaximoString, '0');
}

QString StringUtil::boolToString(bool trueOrFalse, bool emptyIfFalse)
{
	return trueOrFalse ? "true" : emptyIfFalse ? "" : "false";
}

QString StringUtil::caracteres(QChar caractere, int qtd, QChar separador)
{
	QString _caracteres;

	for(int i = 1 ; i <= qtd ; i++){
		_caracteres.append(caractere);

		if(i < qtd){
			_caracteres.append(separador);
		}
	}

	return _caracteres;
}

QString StringUtil::rightPad(QString value, QChar padChar, int size)
{
	QString result = value;

    if (value.length()>= size)
		return value;

    int length = size - value.length();
	QString pad;

    for(int i=0; i < length; i++){
		pad+= padChar;
	}

	return  result + pad;

}
QString StringUtil::lefttPad(QString value, QChar padChar, int size)
{
	QString result = value;

    if (value.length()>= size)
		return value;

    int length = size - value.length();
	QString pad;

    for(int i=0; i < length; i++){
		pad+= padChar;
	}

    return pad + result;
}

QColor StringUtil::stringHexToColor(QString cor)
{
	cor.remove("#");

	if(cor.length() != 6)
		return QColor();

    return QColor(QString("0x" + cor.mid(0, 2)).toInt(0, 16), QString("0x" + cor.mid(2, 2)).toInt(0, 16), QString("0x" + cor.mid(4, 2)).toInt(0, 16));
}

QString StringUtil::extrairConteudoAPartir(QString valor, int posicao, int quantidadeAExtrair)
{
    return valor.mid(posicao, quantidadeAExtrair);
}

QString StringUtil::extrairValorSemCaracteres(double valor, int qtdeCasasDecimais)
{
    QString strValor = StringUtil::retiraCaracteresNaoNumericos(gm::Conversor::toString(gm::DoubleUtil::truncateDouble(valor, 2), qtdeCasasDecimais));
    return strValor;
}

QStringList StringUtil::listDoubleToStringList(QList<double> valores)
{
    QStringList valoresString;

    for(double valor : valores){
        valoresString.append(QString::number(valor, 'f', 2));
    }

    return valoresString;
}

QStringList StringUtil::listStringToStringList(QList<QString> valores)
{
    QStringList valoresString;

    for(QString valor : valores){
        valoresString.append(valor);
    }

    return valoresString;
}

bool StringUtil::equals(QString value1, QString value2)
{
    if(value1.isEmpty() || value2.isEmpty())
        return false;

    if(QString::compare(value1, value2) == 0)
        return true;

    return false;
}

QString StringUtil::extrairConteudoDaString(QString texto, int posicao, int quantidadeAExtrair)
{
    return texto.mid(posicao, quantidadeAExtrair);
}

QString StringUtil::addQuote(QString valor)
{
    return "'"+ valor.trimmed() + "'";
}

QStringList StringUtil::extrairListStringToStringListPor(QString separador, QString conteudo)
{
    QStringList valoresString = conteudo.split(separador, QString::SkipEmptyParts);
    return valoresString;
}

QByteArray StringUtil::encodeString(QString texto)
{
//    QString stringEncode = texto;
//    QTextCodec *codec = QTextCodec::codecForName("ISO_8859-15");
//    return codec->fromUnicode(stringEncode);
}

QString StringUtil::cnpjRaiz(QString cnpj, bool removeZerioInicial)
{
    QString raizCnpjEmitente;

    if (removeZerioInicial && cnpj.startsWith("0"))
        cnpj = StringUtil::removerZerosIniciais(cnpj);

    if (cnpj.size() <= 14){
        raizCnpjEmitente = StringUtil::extrairConteudoAPartir(cnpj, 0, 8);
    } else{
        raizCnpjEmitente = StringUtil::extrairConteudoAPartir(cnpj, 0, 7);
    }

    return raizCnpjEmitente;
}

QString StringUtil::adicionaConteudoVazio(QString strConteudo, int tamanho)
{
    return strConteudo.leftJustified(tamanho, QChar(' '), true).mid(0, tamanho);
}
