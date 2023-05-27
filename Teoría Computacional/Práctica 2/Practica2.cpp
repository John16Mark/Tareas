#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "automata.h"
#include <locale.h>

/*
g++ Practica2.cpp -o Practica2.exe automata.cpp
*/

typedef struct celda{
    string pal;
    int linea;
    Estado tipo;
}celda;


using namespace std;

int main() {

    ifstream archivo("archivo.java");
    int contador_linea = 0;

    vector<celda> analizador;

    string linea;
    while (getline(archivo, linea)) {
        contador_linea++;
        istringstream iss(linea);
        string palabra;
        celda celda_aux;
        while (iss >> palabra) {
            celda_aux.pal = palabra;
            celda_aux.linea = contador_linea;
            celda_aux.tipo = verificarPalabra(palabra);
            analizador.push_back(celda_aux);
            //cout << palabra << "\t\t";
            //cout << imprimirEstado(verificarPalabra(palabra)) << endl;
        }
    }

    for(celda cel: analizador){
        cout << cel.pal << "\t\t" << imprimirEstado(cel.tipo) << endl;
    }

    return 0;
}