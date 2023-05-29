#include <iostream>
#include <string>

using namespace std;

enum class Estado {
		INVALIDO = 0,
		INICIAL = 1,
		SIGNO = 2,
		OCT_HEX = 3,
		OCTAL = 4,
		HEX = 5,
		HEX_DIGITO = 6,
		DECIMAL = 7,
		PUNTO = 8,
		REAL = 9,
		EXP = 10,
		EXP_SIGNO = 11,
		EXP_REAL = 12,
		EXP_REAL2 = 13,
		OPERADOR_BINARIO = 14,
		ID_RESERVADA = 15,
		RESERVADA = 16,
		TIPO_DATO = 17,
		IDENTIFICADOR = 18,
		CORCHETES_APERTURA = 19,
		CORCHETES_CERRADURA = 20,
		ASIGNADOR = 21,
		COMENTARIOS_DIVISION = 22,
		COMENTARIOS_MULTIPLICACION = 23,
		COMENTARIO_SIMPLE = 24,
		COMENTARIO_MULTILINEA = 25,
		COMENTARIO_MULTILINEA_FIN = 26,
		PARENTESIS_APERTURA = 27,
		PARENTESIS_CERRADURA = 28,
		LLAVES_APERTURA = 29,
		LLAVES_CERRADURA = 30,
		COMPARADOR_1 = 31,
		COMPARADOR_2 = 32,
		COMENTARIO = 33,
		COMENTARIO_SLASH = 34,
		ERROR_NUMERICO = 35,
		EXCLAMACION = 36,
		PUNTO_COMA = 37,
		COMA = 38,
		COMILLAS = 39
	};

Estado verificarPalabra(const string& palabra, int linea);
string imprimirEstado(Estado e);
  
