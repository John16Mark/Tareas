#include <iostream>
#include <string>

using namespace std;

bool AFDoctal(const string& cadena);
bool AFDdecimal(const string& cadena);

int main() {
    string numero = "0754";

    if (AFDoctal(numero)) {
        cout << "'" << numero << "' es un número octal válido." << endl;
    } else {
        cout << "'" << numero << "' NO es un número octal válido." << endl;
    }

    return 0;
}

bool AFDoctal(const string& cadena) {
	enum class Estado {
		INICIAL,
		SIGNO,
		CERO,
		DIGITO,
		INVALIDO
	};

	Estado estado = Estado::INICIAL;

	for (char c : cadena){
		switch (estado) {
		case Estado::INICIAL:
			if (c == '0') {
				estado = Estado::DIGITO;
			}
			else if (c == '+' || c == '-') {
				estado = Estado::SIGNO;
			}
			else {
				estado = Estado::INVALIDO;
				return false;
			}
			break;
		case Estado::SIGNO:
			if (c == '0'){
				estado = Estado::DIGITO;
			} else{
				estado = Estado::INVALIDO;
				return false;
			}
			break;
		case Estado::DIGITO:
			if (c >= '0' && c <= '7'){
				estado = Estado::DIGITO;
			} else {
				estado = Estado::INVALIDO;
				return false;
			}
			break;
		}
	}
	return estado == Estado::DIGITO;
}

bool AFDdecimal(const string& cadena){
	enum class Estado {
		INICIAL,
		SIGNO,
		DIGITO,
		PUNTO,
		DIGITO_PUNTO,
		EXPONENTE,
		SIGNO_EXPONENTE,
		DIGITO_EXPONENTE
	};

	Estado estado = Estado::INICIAL;

	return ((estado == Estado::DIGITO) || (estado == Estado::DIGITO_PUNTO) || (estado == Estado::DIGITO_EXPONENTE));
}