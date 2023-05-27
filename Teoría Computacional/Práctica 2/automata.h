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
		OCTAL_COMA = 15,
		OCTAL_PCOMA = 16,
		DECIMAL_COMA = 17,
		DECIMAL_PCOMA = 18,
		HEX_COMA = 19,
		HEX_PCOMA = 20,
		ID_RESERVADA = 21,
		RESERVADA = 22,
		TIPO_DATO = 23,
		IDENTIFICADOR = 24,
		CORCHETES_APERTURA = 25,
		CORCHETES_CERRADURA = 26,
		ID_COMA = 27,
		ID_PCOMA = 28,
		ASIGNADOR = 29,
		COMENTARIOS_DIVISION = 30,
		COMENTARIOS_MULTIPLICACION = 31,
		COMENTARIO_SIMPLE = 32,
		COMENTARIO_MULTILINEA = 33,
		COMENTARIO_MULTILINEA_FIN = 34
	};

Estado verificarPalabra(const string& palabra);
string imprimirEstado(Estado e);