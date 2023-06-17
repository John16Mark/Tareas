#include <iostream>
#include <string>
#include "automata.h"

using namespace std;

bool comentarioMulti = false;
bool comentarioMono = false;
int linea_comentada = 0;
bool esCadena = false;

Estado verificarPalabra(const string& palabra, int linea){

	Estado estado = Estado::INICIAL;
	//bool imprimir = true;
	if(comentarioMulti && palabra.at(0) != '*'){
		return Estado::COMENTARIO_MULTILINEA;
	} else if (comentarioMono && linea == linea_comentada) {
		return Estado::COMENTARIO_SIMPLE;
	} else if(esCadena && palabra != "\""){
		return Estado::COMILLAS;
	} else {
		linea_comentada = 0;
		comentarioMono = false;
		for(char c: palabra) {
			switch (estado) {
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
					} else if(c == '!') {
						estado = Estado::EXCLAMACION;
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
					} else if(c == '"') {
						estado = Estado::COMILLAS;
						if(esCadena){
							esCadena = false;
						} else {
							esCadena = true;
						}
						break;
					} else if(c >= '1' && c <= '9') {
						estado = Estado::DECIMAL;
					} else if(isalpha(c) || c == '_' || c == '$') {
						estado = Estado::ID_RESERVADA;
					} else if(c == ',') {
						estado = Estado::COMA;
					} else if(c == ';') {
						estado = Estado::PUNTO_COMA;
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
					} else {
						estado = Estado::ERROR_NUMERICO;
					}
					break;
				case Estado::DECIMAL:
					if (c >= '0' && c <= '9') {
						estado = Estado::DECIMAL;
					} else if (c == '.') {
						estado = Estado::PUNTO;
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
					} else {
						estado = Estado::ERROR_NUMERICO;
						return estado;
					}
					break;
				case Estado::EXP_REAL2:
					estado = Estado::ERROR_NUMERICO;
					return estado;
					break;
				case Estado::ID_RESERVADA:
					if(palabra == "public" || palabra == "private" || palabra == "package" || palabra == "protected" ||
						palabra == "static" || palabra == "final" || palabra == "class" || palabra == "main" ||
						palabra == "if" || palabra == "for" || palabra == "while") {
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
					} else {
						estado = Estado::INVALIDO;
					}
					break;
				case Estado::COMENTARIOS_DIVISION:
					if (c == '/') {
						estado = Estado::COMENTARIO_SIMPLE;
						comentarioMono = true;
						linea_comentada = linea;
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
					} else if(c == '*') {
						estado = Estado::COMENTARIOS_MULTIPLICACION;
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
				case Estado::EXCLAMACION:
					if(c == '=') {
						estado = Estado::COMPARADOR_2;
					} else {
						estado = Estado::INVALIDO;
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

	// Si terminó en alguno de estos estados, cambiarlos por otros.
	if (estado == Estado::SIGNO || estado == Estado::COMENTARIOS_DIVISION || estado == Estado::COMENTARIOS_MULTIPLICACION){
		estado = Estado::OPERADOR_BINARIO;
	} else if (estado == Estado::ID_RESERVADA){
		estado = Estado::IDENTIFICADOR;
	} else if (estado == Estado::HEX || estado == Estado::PUNTO || estado == Estado::EXP || estado == Estado::EXP_SIGNO) {
		estado = Estado::ERROR_NUMERICO;
	}
	
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
		return "\033[92mOctal\033[0m";
		break;
	case Estado::HEX_DIGITO:
		return "\033[92mHexadecimal\033[0m";
		break;
	case Estado::DECIMAL:
		return "\033[92mDecimal entero\033[0m";
		break;
	case Estado::REAL:
		return "\033[92mDecimal real\033[0m";
		break;
	case Estado::EXP_REAL:
	case Estado::EXP_REAL2:
		return "\033[92mDecimal real con exponente\033[0m";
		break;
	case Estado::SIGNO:
	case Estado::COMENTARIOS_MULTIPLICACION:
	case Estado::COMENTARIOS_DIVISION:
	case Estado::OPERADOR_BINARIO:
		return "\033[32mOperador binario\033[0m";
		break;
	case Estado::ASIGNADOR:
		return "Asignador";
		break;
	case Estado::RESERVADA:
		return "\033[96mPalabra reservada\033[0m";
		break;
	case Estado::TIPO_DATO:
		return "\033[36mTipo de dato\033[0m";
		break;
	case Estado::ID_RESERVADA:
	case Estado::IDENTIFICADOR:
		return "\033[93mIdentificador\033[0m";
		break;
	case Estado::CORCHETES_APERTURA:
		return "\033[97mCorchetes: Abrir\033[0m";
		break;
	case Estado::CORCHETES_CERRADURA:
		return "\033[97mCorchetes: Cerrar\033[0m";
		break;
	case Estado::PARENTESIS_APERTURA:
		return "\033[97mParentesis: Abrir\033[0m";
		break;
	case Estado::PARENTESIS_CERRADURA:
		return "\033[97mParentesis: Cerrar\033[0m";
		break;
	case Estado::LLAVES_APERTURA:
		return "\033[97mLlaves: Abrir\033[0m";
		break;
	case Estado::LLAVES_CERRADURA:
		return "\033[97mLlaves: Cerrar\033[0m";
		break;
	case Estado::COMA:
		return "\033[97mComa\033[0m";
		break;
	case Estado::PUNTO_COMA:
		return "\033[97mPunto y coma\033[0m";
		break;
	case Estado::COMILLAS:
		return "\033[34mCadena\033[0m";
		break;
	case Estado::COMPARADOR_1:
	case Estado::COMPARADOR_2:
		return "\033[95mComparador\033[0m";
		break;
	case Estado::COMENTARIO_SIMPLE:
		return "\033[90m\033[4mComentario monolinea\033[0m";
		break;
	case Estado::COMENTARIO_MULTILINEA:
	case Estado::COMENTARIO_MULTILINEA_FIN:
		return "\033[90m\033[4mComentario multilinea\033[0m";
		break;
	default:
		return "\033[90m\033[4mPOR IDENTIFICAR\033[0m";
		break;
	}
}

