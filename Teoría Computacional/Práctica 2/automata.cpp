#include <iostream>
#include <string>
#include "automata.h"

using namespace std;

bool comentarioMulti = false;

Estado verificarPalabra(const string& palabra){

	Estado estado = Estado::INICIAL;
	//bool imprimir = true;
	if(comentarioMulti && palabra.at(0) != '*'){
		return Estado::COMENTARIO;
	} else {
		for(char c: palabra){
			switch (estado){
				case Estado::INICIAL:
					if(c == '0') {
						estado = Estado::OCT_HEX;
						//if(imprimir) {printf("  \033[96mOCT_HEX\033[0m");}  //--------------------------------------
					} else if(c == '+' || c == '-') {
						estado = Estado::SIGNO;
					} else if(c == '%') {
						estado = Estado::OPERADOR_BINARIO;
					} else if(c == '/') {
						estado = Estado::COMENTARIOS_DIVISION;
					} else if(c == '*') {
						estado = Estado::COMENTARIOS_MULTIPLICACION;
					} else if(c == '=') {
						estado = Estado::ASIGNADOR;
					} else if(c == '{') {
						estado = Estado::LLAVES_APERTURA;
					} else if(c == '}') {
						estado = Estado::LLAVES_CERRADURA;
					} else if(c == '[') {
						estado = Estado::CORCHETES_APERTURA;
					} else if(c == ']') {
						estado = Estado::CORCHETES_CERRADURA;
					} else if(c == '(') {
						estado = Estado::PARENTESIS_APERTURA;
					} else if(c == ')') {
						estado = Estado::PARENTESIS_CERRADURA;
					} else if(c == '<' || c == '>'){
						estado = Estado::COMPARADOR_1;
					} else if(c >= '1' && c <= '9') {
						estado = Estado::DECIMAL;
					} else if(isalpha(c) || c == '_' || c == '$') {
						estado = Estado::ID_RESERVADA;
					} else {
						estado = Estado::INVALIDO;
					}
					break;
				case Estado::SIGNO:
					if (c == '0'){
						estado = Estado::OCT_HEX;
					} else if(c >= '1' && c <= '9') {
						estado = Estado::DECIMAL;
					} else if(c == '=') {
						estado = Estado::ASIGNADOR;
					} else {
						estado = Estado::INVALIDO;
					}
					break;
				case Estado::OCT_HEX:
					if(c == 'x'){
						estado = Estado::HEX;
					} else if(c >= '0' && c <= '7'){
						estado = Estado::OCTAL;
					} else if(c == '.') {
						estado = Estado::REAL;
					} else {
						estado = Estado::ERROR_NUMERICO;
					}
					break;
				case Estado::OCTAL:
					if(c >= '0' && c <= '7'){
						estado = Estado::OCTAL;
					} else if(c == ',') {
						estado = Estado::OCTAL_COMA;
					} else {
						estado = Estado::ERROR_NUMERICO;
					}
					break;
				case Estado::HEX:
					if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')){
						estado = Estado::HEX_DIGITO;
					} else {
						estado = Estado::ERROR_NUMERICO;
					}
					break;
				case Estado::HEX_DIGITO:
					if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')){
						estado = Estado::HEX_DIGITO;
					} else if (c == ',') {
						estado = Estado::HEX_COMA;
					} else if (c == ';') {
						estado = Estado::HEX_PCOMA;
					} else {
						estado = Estado::ERROR_NUMERICO;
					}
					break;
				case Estado::DECIMAL:
					if (c >= '0' && c <= '9') {
						estado = Estado::DECIMAL;
					} else if (c == '.') {
						estado = Estado::PUNTO;
					} else if (c == ',') {
						estado = Estado::DECIMAL_COMA;
					} else if (c == ';') {
						estado = Estado::DECIMAL_PCOMA;
					} else {
						estado = Estado::ERROR_NUMERICO;
					}
					break;
				case Estado::PUNTO:
					if (c >= '0' && c <= '9') {
						estado = Estado::REAL;
					} else {
						estado = Estado::ERROR_NUMERICO;
					}
					break;
				case Estado::REAL:
					if (c >= '0' && c <= '9') {
						estado = Estado::REAL;
					} else if (c == 'E') {
						estado = Estado::EXP; 
					} else if (c == ',') {
						estado = Estado::DECIMAL_COMA;
					} else if (c == ';') {
						estado = Estado::DECIMAL_PCOMA;
					} else {
						estado = Estado::ERROR_NUMERICO;
					}
					break;
				case Estado::EXP:
					if(c == '+' || c == '-') {
						estado = Estado::EXP_SIGNO;
					} else if (c >= '0' && c <= '9') {
						estado = Estado::EXP_REAL;
					} else {
						estado = Estado::ERROR_NUMERICO;
					}
					break;
				case Estado::EXP_SIGNO:
					if (c >= '0' && c <= '9') {
						estado = Estado::EXP_REAL;
					} else {
						estado = Estado::ERROR_NUMERICO;
						return estado;
					}
					break;
				case Estado::EXP_REAL:
					if (c >= '0' && c <= '9') {
						estado = Estado::EXP_REAL2;
					} else if (c == ',') {
						estado = Estado::DECIMAL_COMA;
					} else if (c == ';') {
						estado = Estado::DECIMAL_PCOMA;
					} else {
						estado = Estado::ERROR_NUMERICO;
						return estado;
					}
					break;
				case Estado::EXP_REAL2:
					if (c == ',') {
						estado = Estado::DECIMAL_COMA;
					} else if (c == ';') {
						estado = Estado::DECIMAL_PCOMA;
					} else {
						estado = Estado::ERROR_NUMERICO;
						return estado;
					}
					break;
				case Estado::OCTAL_COMA:
				case Estado::OCTAL_PCOMA:
				case Estado::DECIMAL_COMA:
				case Estado::DECIMAL_PCOMA:
				case Estado::HEX_COMA:
				case Estado::HEX_PCOMA:
					estado = Estado::INVALIDO;
					break;
				case Estado::ID_RESERVADA:
					if(palabra == "public" || palabra == "private" || palabra == "package" || palabra == "protected" ||
						palabra == "static" || palabra == "final" || palabra == "class") {
						estado = Estado::RESERVADA;
						return estado;
					} else if(palabra == "int" || palabra == "short" || palabra == "void" || palabra == "float" ||
						palabra == "double" || palabra == "String") {
						estado = Estado::TIPO_DATO;
						return estado;
					} else {
						if (c == '_' || isalpha(c) || isdigit(c)){
							estado = Estado::IDENTIFICADOR;
						} else {
							estado = Estado::INVALIDO;
						}
					}
					break;
				case Estado::IDENTIFICADOR:
					if (c == '_' || isalpha(c) || isdigit(c)){
						estado = Estado::IDENTIFICADOR;
					} else if(c == ','){
						estado =Estado::ID_COMA;
					} else if(c == ';'){
						estado =Estado::ID_PCOMA;
					} else {
						estado = Estado::INVALIDO;
					}
					break;
				case Estado::COMENTARIOS_DIVISION:
					if (c == '/') {
						estado = Estado::COMENTARIO_SIMPLE;
					} else if (c == '*') {
						estado = Estado::COMENTARIO_MULTILINEA;
						comentarioMulti = true;
					} else {
						estado = Estado::INVALIDO;
					}
					break;
				case Estado::COMENTARIOS_MULTIPLICACION:
					if (c == '/') {
						estado = Estado::COMENTARIO_MULTILINEA_FIN;
						comentarioMulti = false;
					} else {
						estado = Estado::INVALIDO;
					}
					break;
				case Estado::COMENTARIO_SIMPLE:
				case Estado::COMENTARIO_MULTILINEA:
					
					break;
				case Estado::ASIGNADOR:
					if (c == '=') {
						estado = Estado::COMPARADOR_2;
					} else {
						estado = Estado::INVALIDO;
					}
					break;
				case Estado::COMPARADOR_1:
					if(c == '=') {
						estado = Estado::COMPARADOR_2;
					} else {
						estado = Estado::INVALIDO;
					}
					break;
				case Estado::COMENTARIO:
					if(c == '*'){
						estado = Estado::COMENTARIO_SLASH;
					} else {
						Estado::COMENTARIO;
					}
					break;
				case Estado::COMENTARIO_SLASH:
					if (c == '/') {
						estado = Estado::COMENTARIO_MULTILINEA_FIN;
						comentarioMulti = false;
					} else {
						Estado::COMENTARIO;
					}
					break;
				case Estado::ERROR_NUMERICO:
					break;
				default:
					estado = Estado::INVALIDO;
					break;
			}
		}
	}

	if (estado == Estado::SIGNO || estado == Estado::COMENTARIOS_DIVISION || estado == Estado::COMENTARIOS_MULTIPLICACION){
		estado = Estado::OPERADOR_BINARIO;
	} else if (estado == Estado::ID_RESERVADA){
		estado = Estado::IDENTIFICADOR;
	}
	// palabra == "(int)" || palabra == "(short)" || palabra == "(void)" || palabra == "(float)"
	return estado;
}

string imprimirEstado(Estado e){
	switch(e){
	case Estado::ERROR_NUMERICO:
		return "\033[91mERROR NUMERICO\033[0m";
		break;
	case Estado::INVALIDO:
		return "\033[31mINVALIDO\033[0m";
		break;
	case Estado::OCTAL:
		return "Octal";
		break;
	case Estado::HEX_DIGITO:
		return "Hexadecimal";
		break;
	case Estado::DECIMAL:
		return "Decimal entero";
		break;
	case Estado::OCTAL_COMA:
		return "Octal coma";
		break;
	case Estado::OCTAL_PCOMA:
		return "Octal punto y coma";
		break;
	case Estado::DECIMAL_COMA:
		return "Decimal coma";
		break;
	case Estado::DECIMAL_PCOMA:
		return "Decimal punto y coma";
		break;
	case Estado::HEX_COMA:
		return "Hexadecimal coma";
		break;
	case Estado::HEX_PCOMA:
		return "Hexadecimal punto y coma";
		break;
	case Estado::OPERADOR_BINARIO:
		return "Operador binario";
		break;
	case Estado::ASIGNADOR:
		return "Asignador";
		break;
	case Estado::RESERVADA:
		return "\033[96mPalabra reservada\033[0m";
		break;
	case Estado::TIPO_DATO:
		return "Tipo de dato";
		break;
	case Estado::IDENTIFICADOR:
		return "\033[93mIdentificador\033[0m";
		break;
	case Estado::ID_COMA:
		return "\033[93mIdentificador coma\033[0m";
		break;
	case Estado::ID_PCOMA:
		return "\033[93mIdentificador punto y coma\033[0m";
		break;
	case Estado::CORCHETES_APERTURA:
		return "Corchetes: Abrir";
		break;
	case Estado::CORCHETES_CERRADURA:
		return "Corchetes: Cerrar";
		break;
	case Estado::PARENTESIS_APERTURA:
		return "Parentesis: Abrir";
		break;
	case Estado::PARENTESIS_CERRADURA:
		return "Parentesis: Cerrar";
		break;
	case Estado::LLAVES_APERTURA:
		return "Llaves: Abrir";
		break;
	case Estado::LLAVES_CERRADURA:
		return "Llaves: Cerrar";
		break;
	default:
		return "\033[90m\033[4mPOR IDENTIFICAR\033[0m";
		break;
	}
}

