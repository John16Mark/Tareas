#include <iostream>
#include <string>
#include <stack>

/*
g++ Practica2.cpp -o Practica2.exe automata.cpp
*/

using namespace std;

bool analizador(const string& cadena);

int main(int argc, char* argv[]) {
	
	
	stack<string> pila;
	string x = "C323 = E313+C1";
    analizador(x);
    

    return 0;
}

bool analizador(const string& cadena) {
	
	stack<string> pila;
	pila.push("Z0");
	
	enum class Estado {
		INICIO,
		ID_INICIO
	};
	
	Estado estado = Estado::INICIO;
	
	for(char c : cadena){
		switch(estado) {
		case Estado::INICIO:
			
			break;
		}
	}
	
}
