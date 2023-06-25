#include <iostream>
#include <string>
#include <stack>
#include <vector>

/*
g++ Practica3.cpp -o Practica3.exe
*/

using namespace std;

enum class Estado {
	INICIO = 0,
	ID_INICIO = 1,
	ESPACIO = 2,
	INICIO_EXPRESION = 3,
	ID = 4,
	NUMERO = 5,
	OPERADOR = 6,
	INVALIDO = 9999
};

bool analizador(const string& cadena);
bool esCaracter(char c);
bool esDigito(char c);
bool esOperador(char c);
string imprimirEstado(Estado e);

void generacion();

// Si queremos que imprima qué es lo que hace paso por paso
bool realizarImpresiones = false;
// Si queremos probar el programa con los ejemplos dados en las especificaciones de la práctica
bool pruebas = true;

string generar = "";

int main(int argc, char* argv[]) {

	if(pruebas) {
		vector<string> expresiones;
		expresiones.push_back("A2 = A1 + 12 + C5;");
		expresiones.push_back("AB = A*B/100-59;");
		expresiones.push_back("ABC = (340 % 2) + (12-C);");
		expresiones.push_back("AC = 10 + 8 * (5+B);");
		expresiones.push_back("Var1 = Var2 = Var3 = 8;");
		expresiones.push_back("VAR = (CatA + (( CatA + CatB ) * CatC ))*(CatD - CatF);");
		expresiones.push_back("3=A2=1+12+C5;");
		expresiones.push_back("AB=A**B/100-59");
		expresiones.push_back("ABC(340 % 2);");

		for (string s : expresiones) {
			generar = "";
			bool paso = analizador(s);
			
			if(paso) {
		    	cout << "\033[92mTRUE\033[0m ";
		    } else {
		    	cout << "\033[91mFALSE\033[0m ";
		    }
		    cout << s << endl << endl;
		    if(paso) {
	    		//imprimir
	    		//validarYMostrarArbol(s);
	    		//cout << generar << endl;;
	    		generacion();
	    		cout << generar << endl;;
	    		cout << s << endl;
	    	}
		}
	} else {
		string s = argv[1];
		bool paso = analizador(s);
		if(paso) {
	    	cout << "\033[92mTRUE\033[0m ";
	    } else {
	    	cout << "\033[91mFALSE\033[0m ";
	    }
	    cout << s << endl << endl;
	    if(paso) {
	    	//imprimir
	    	//validarYMostrarArbol(s);
	    	cout << generar;
	    }
	}

    return 0;
}

bool analizador(const string& cadena) {
	
	stack<char> pila;
	pila.push('Z');
	Estado estado = Estado::INICIO;
	
	if(realizarImpresiones){
		cout << "\033[96mchar\tTope\tEstado\033[0m" <<endl;
	}

	for(char c : cadena){
		if(pila.empty()){
			return false;
		}
		switch(estado) {
		case Estado::INICIO:
			if( esCaracter(c) && pila.top() == 'Z' ) {
				generar += "<Id>";
				estado = Estado::ID_INICIO;
				// La pila se queda igual
			} else if(c == ' ' && pila.top() == 'Z') {
				// Se queda en el mismo estado
				// La pila se queda igual
			} else {
				estado = Estado::INVALIDO;
			}
			break;
		case Estado::ID_INICIO:
			if( (esCaracter(c) || esDigito(c)) && pila.top() == 'Z' ) {
				// Se queda en el mismo estado
				// La pila se queda igual
			} else if( c == ' ' && pila.top() == 'Z') {
				estado = Estado::ESPACIO;
				// La pila se queda igual
			} else if( c == '=' && pila.top() == 'Z') {
				generar += "=";
				estado = Estado::INICIO_EXPRESION;
				// La pila se queda igual
			} else {
				estado = Estado::INVALIDO;
			}
			break;
		case Estado::ESPACIO:
			if(c == ' ' && pila.top() == 'Z') {
				estado = Estado::ESPACIO;
				// La pila se queda igual
			} else if( c == '=' && pila.top() == 'Z') {
				estado = Estado::INICIO_EXPRESION;
				// La pila se queda igual
				generar += "=";
			} else {
				estado = Estado::INVALIDO;
			}
			break;
		case Estado::INICIO_EXPRESION:
			if(c == ' '){
				// Se queda en el mismo estado
				// La pila se queda igual
			} else if(esCaracter(c)) {
				estado = Estado::ID;
				// La pila se queda igual
				generar += "<Id>";
			} else if(esDigito(c)) {
				estado = Estado::NUMERO;
				// La pila se queda igual
				generar += "<Numero>";
			} else if(c == '(') {
				// Se queda en el mismo estado
				generar += "(";
				pila.push(c);
			} else {
				estado = Estado::INVALIDO;
			}
			break;
		case Estado::ID:
			if( (esCaracter(c) || esDigito(c))/* && pila.top() == 'Z'*/ ) {
				// Se queda en el mismo estado
			} else if(c == ' ' && esOperador(pila.top())) {
				// Se queda en el mismo estado
				pila.pop();
			} else if(c == ' ' && !esOperador(pila.top())) {
				// Se queda en el mismo estado
			} else if(esOperador(c) && (pila.top() == 'Z' || pila.top() == '(')) {
				estado = Estado::OPERADOR;
				pila.push('+');
				generar += "<Operador>";
			} else if(esOperador(c) && esOperador(pila.top())) {
				generar += "<Operador>";
				estado = Estado::OPERADOR;
			} else if(c == ')' && pila.top() == '('){
				generar += ")";
				pila.pop();
				estado = Estado::NUMERO;
			} else if(c == ')' && esOperador(pila.top())){
				generar += ")";
				pila.pop();
				pila.pop();
				estado = Estado::NUMERO;
			} else if(c == '=' && pila.top() == 'Z') {
				generar += "=";
				estado = Estado::INICIO_EXPRESION;
			} else if(c == ';' && pila.top() == 'Z'){
				pila.pop();
			} else if(c == ';' && esOperador(pila.top())){
				pila.pop();
				pila.pop();
			} else {
				estado = Estado::INVALIDO;
			}
			break;
		case Estado::NUMERO:
			if(esDigito(c) && esOperador(pila.top())) {
				// Se queda en el mismo estado
			} else if(esDigito(c) && (pila.top() == 'Z' || pila.top() == '(')) {
				// Se queda en el mismo estado
			} else if(c == ' ' && esOperador(pila.top())) {
				// Se queda en el mismo estado
				pila.pop();
			} else if(c == ' ' && (pila.top() == 'Z' || pila.top() == '(')) {
				// Se queda en el mismo estado
			} else if(esOperador(c) && esOperador(pila.top())) {
				generar += "<Operador>";
				estado = Estado::OPERADOR;
			} else if(esOperador(c) && (pila.top() == 'Z' || pila.top() == '(')) {
				generar += "<Operador>";
				estado = Estado::OPERADOR;
				pila.push('+');
			} else if(c == ')' && pila.top() == '('){
				pila.pop();
				generar += ")";
				estado = Estado::NUMERO;
			} else if(c == ')' && esOperador(pila.top())){
				pila.pop();
				generar += ")";
				pila.pop();
				estado = Estado::NUMERO;
			} else if(c == '=' && pila.top() == 'Z') {
				generar += "=";
				estado = Estado::INICIO_EXPRESION;
			} else if(c == ';' && pila.top() == 'Z'){
				pila.pop();
			} else if(c == ';' && esOperador(pila.top())){
				pila.pop();
				pila.pop();
			} 
			else {
				estado = Estado::INVALIDO;
			}
			break;
		case Estado::OPERADOR:
			if(c == ' '){
				// Se queda en el mismo estado
			} else if(esCaracter(c) && esOperador(pila.top())) {
				generar += "<Id>";
				estado = Estado::ID;
			} else if(esDigito(c) && esOperador(pila.top())) {
				generar += "<Numero>";
				estado = Estado::NUMERO;
			} else if(c == '(' && esOperador(pila.top())) {
				pila.pop();
				generar += "(";
				pila.push('(');
				estado = Estado::INICIO_EXPRESION;
			} else {
				estado = Estado::INVALIDO;
			}
			break;
		case Estado::INVALIDO:
			return false;
			break;
		}
		if(realizarImpresiones){
			if(pila.empty()){
				cout << " " << c << "\t\t" << imprimirEstado(estado) << endl;
			} else {
				cout << " " << c << "\t" << pila.top() <<"\t" << imprimirEstado(estado) << endl;
			}
		}
	}
	if(pila.empty())
	{
		return true;
	} else {
		return false;
	}
}

bool esCaracter(char c) {
	if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
		return true;
	}
	return false;
}

bool esDigito(char c) {
	if(c >= '0' && c <= '9'){
		return true;
	}
	return false;
}

bool esOperador(char c) {
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
		return true;
	}
	return false;
}

string imprimirEstado(Estado e) {
	switch(e) {
	case Estado::INICIO:
		return "Inicio";
	case Estado::ID_INICIO:
		return "Identificador antes del igual";
	case Estado::ESPACIO:
		return "Espacio en blanco antes del igual";
	case Estado::INICIO_EXPRESION:
		return "Inicio Expresion";
	case Estado::ID:
		return "Identificador";
	case Estado::NUMERO:
		return "Valor numerico";
	case Estado::OPERADOR:
		return "Operador";
	case Estado::INVALIDO:
		return "\033[31mINVALIDO\033[0m";
	default:
		return "?";
	}
}

void generacion() {

	vector<string> v;
	string aux = generar;
	
	while (true) {
		size_t pos = aux.find("<Id>");
		if(pos == string::npos) {break;}
		aux.replace(pos, 4, "<Termino>");
		v.push_back(aux);
	}

	while (true) {
		size_t pos = aux.find("<Numero>");
		if(pos == string::npos) {break;}
		aux.replace(pos, 8, "<Termino>");
		v.push_back(aux);
	}
	while(true) {

		string aux3 = aux;

		while (true) {
			size_t pos = aux.find("<Termino>");
			if(pos == string::npos) {break;}
			aux.replace(pos, 9, "<Expresion>");
			v.push_back(aux);
		}

		while (true) {
			size_t pos = aux.find("<Expresion><Operador><Expresion>");
			if(pos == string::npos) {break;}
			string aux2 = "<Expresion><Operador><Expresion>";
			aux.replace(pos, aux2.length(), "<Expresion>");
			v.push_back(aux);
		}

		while (true) {
			size_t pos = aux.find("(<Expresion>)");
			if(pos == string::npos) {break;}
			aux.replace(pos, 13, "<Termino>");
			v.push_back(aux);
		}

		if(aux3 == aux) {
			break;
		}

	}
	
	while (true) {
		size_t pos = aux.find("<Expresion>=");
		if(pos == string::npos) {break;}

		aux.replace(pos, 11, "<Id>");
		v.push_back(aux);
	}

	while (true) {

		string aux3 = aux;

		while (true) {
			size_t pos = aux.find("=<Expresion>");
			if(pos == string::npos) {break;}

			aux.replace(pos, 12, "<Igualdad>");
			v.push_back(aux);
		}

		if(aux == "<Id><Igualdad>"){
			aux = "<Inicio>";
			v.push_back(aux);
			break;
		}

		while (true) {
			size_t pos = aux.find("<Id><Igualdad>");
			if(pos == string::npos) {break;}

			aux.replace(pos, 14, "<Igualdad>");
			v.push_back(aux);
		}

		

		while (true) {
			size_t pos = aux.find("<Igualdad>");
			if(pos == string::npos) {break;}

			aux.replace(pos, 10, "<Expresion>");
			v.push_back(aux);
		}

		if(aux3 == aux) {
			break;
		}
	}
	
	for(int i = v.size()-1; i >= 0; i--) {
		cout << v.at(i) << endl;
	}

}