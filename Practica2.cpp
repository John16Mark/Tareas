#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

/*
g++ Practica2.cpp -o Practica2.exe
*/

using namespace std;

int main() {
    ifstream archivo("archivo.java");
    int contador_linea = 0;
    stack<string> pilaIF;
	stack<string> pilaFOR;    

    vector<string> tokens;

    regex enteroDecimal("([0-9]+)");
    regex enteroOctal("(0+[0-7]+)");
	regex enteroHex("(0+x+[0-9a-fA-F]+)");

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string palabra;
        while (iss >> palabra) {
            // Verificar si la palabra es una palabra clave
            /*if (palabra == "if" || palabra == "else" || palabra == "for" || palabra == "while") {
                tokens.push_back(word);
            }*//*
            if (palabra == "if"){
            	pilaIF.push(to_string(contador_linea));
            }
            else if (palabra == "{") {
            	if(!pilaIF.empty()) {
            		pilaIF.pop();
            	}
            	else{
            		cout << "Error: Línea " << contador_linea << endl;
            	}
            }
            else if (palabra == "}") {
            	if(pilaIF.empty()) {
            		cout << "Error: Línea " << contador_linea << endl;
            	}
            }*/
            bool anteriorInt = false;
            if (anteriorInt){
            	if(!palabra =",")
            }
            else{
            	if(palabra == "int"){
	            	anteriorInt = true;
	            }
            }
            

        }
    }

    while(pilaIF.empty()){
    	cout << "Error: Línea " << contador_linea << endl;
    	pilaIF.pop();
    }

    // Imprimir los tokens identificados
    for (const string& token : tokens) {
        cout << token << endl;
    }

    return 0;
}