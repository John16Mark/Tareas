#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

/*
g++ Practica2.cpp -o Practica2.exe -std=c++11
*/

using namespace std;

int main() {
    ifstream archivo("archivo.java");
    int contador_linea = 0;
    stack<string> pilaIF;
	stack<string> pilaFOR;    

    vector<string> tokens;

    regex enteroDecimal("([+-]?([0-9]+)[,]?)");
    regex enteroOctal("([+-]?([0-7]+)[,]?)");
	regex enteroHex("(([+-]?0x[0-9a-fA-F])[,]?)");
	regex realDecimal("([+-]?([0-9]+).([0-9]+)[,]?)");
	regex realDecimalExp("([+-]?([0-9]+).([0-9]+)[,]?)");
	
	string intDec = "[+-]?([0-9]+)";
	string intOct = "[+-]?([0-7]+)";
	string intHex = "[+-]?0x[0-9a-fA-F]";
	string realDec = "[+-]?([0-9]+).([0-9]+)";
	string realDecExp = "[+-]?([0-9]+).([0-9]+)E[+-]?([0-9]+)";

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string palabra;
        contador_linea++;
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
			bool ant_tipo_dato = false;
			if(ant_tipo_dato){
				if(palabra == "int" || palabra == "short" || palabra == "double" || palabra == "float"){
					cout << "Error: Línea " << contador_linea << endl; 
				}else{
					
				}
			}
			else{
				if()
			}
            
			
        }
    }
/*
    while(pilaIF.empty()){
    	cout << "Error: Línea " << contador_linea << endl;
    	pilaIF.pop();
    }

    // Imprimir los tokens identificados
    for (const string& token : tokens) {
        cout << token << endl;
    }
*/
    return 0;
}

bool check_dato(string p){
	
}

bool check_tipo_dato