#include <iostream>
#include <string>

using namespace std;

bool AFDoctal(const string& cadena) ;

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
		DIGITO_OCTAL,
		NO_OCTAL,
		INVALIDO
	};

	Estado estado = Estado::INICIAL;

	for (char c : cadena){
		switch (estado) {
		case Estado::INICIAL:
			if (c == '0') {
				estado = Estado::DIGITO_OCTAL;
			}
			else if (c == '+' || c == '-') {
				estado = Estado::SIGNO;
			}
			else {
				estado = Estado::NO_OCTAL;
				return false;
			}
			break;
		case Estado::SIGNO:
			if (c == '0'){
				estado = Estado::DIGITO_OCTAL;
			} else{
				return false;
			}
			break;
		case Estado::DIGITO_OCTAL:
			if (c >= '0' && c <= '7'){
				estado = Estado::DIGITO_OCTAL;
			} else {
				return false;
			}
			break;
		}
	}
	return estado == Estado::DIGITO_OCTAL;
}