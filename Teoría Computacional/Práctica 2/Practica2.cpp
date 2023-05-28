#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include "automata.h"
#include <windows.h>  

/*
g++ Practica2.cpp -o Practica2.exe automata.cpp
*/

//bool comentarioMulti = false;

void gotoxy(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

typedef struct celda{
    string pal;
    int linea;
    Estado tipo;
}celda;

vector<int> errores;

using namespace std;

void tabla(vector<celda> *a);
vector<string> dividir(const string& s, char delimitador);

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
            
            deque<string> cola_despues;

            cout << "\n    SE RECIBIO LA PALABRA: " <<palabra << endl;
            vector<string> partes = dividir(palabra, '(');
            vector<string> partes2;

            for (const string& parte : partes) {
                vector<string> aux = dividir(parte, '{');
                for(int i = 0; i < aux.size(); i++) {
                    partes2.push_back(aux.at(i));
                }
            }
            partes.clear();

            for (const string& parte : partes2) {
                vector<string> aux = dividir(parte, ')');
                for(int i = 0; i < aux.size(); i++) {
                    partes.push_back(aux.at(i));
                }
            }
            partes2.clear();

            for (const string& parte : partes) {
                vector<string> aux = dividir(parte, '[');
                for(int i = 0; i < aux.size(); i++) {
                    partes2.push_back(aux.at(i));
                }
            }
            partes.clear();

            for (const string& parte : partes2) {
                vector<string> aux = dividir(parte, ']');
                for(int i = 0; i < aux.size(); i++) {
                    partes.push_back(aux.at(i));
                }
            }

            //
            for (const string& parte : partes) {
                celda_aux.pal = parte;
                celda_aux.linea = contador_linea;
                celda_aux.tipo = verificarPalabra(parte);
                analizador.push_back(celda_aux);
            }

            
            
        }
    }
    tabla(&analizador);
    

    return 0;
}

vector<string> dividir(const string& s, char delimitador){
    vector<string> partes;
    string parte;

    for(char c: s) {
        if ( c == delimitador) {
            if(!parte.empty()) {
                partes.push_back(parte);
                parte.clear();
            }
            partes.push_back(string(1, delimitador));
        } else {
            parte += c;
        }
    }

    if (!parte.empty()) {
        partes.push_back(parte);
    }

    return partes;
}

void tabla(vector<celda> *a){
    int i;
    system("CLS");
    gotoxy(4,2);
    printf("%c",201);
    for(i = 0; i < 85; i++){
        printf("%c",205);
    }
    printf("%c",187);
    gotoxy(4,3);
    printf("%c",186);
    gotoxy(90,3);
    printf("%c",186);
    gotoxy(38,3);
    printf("TABLA DE PALABRAS");
    gotoxy(4,4);
    printf("%c",204);
    for(i = 0; i < 47; i++){
        printf("%c",205);
    }
    printf("%c",203);
    for(i = 0; i < 9; i++){
        printf("%c",205);
    }
    printf("%c",203);
    for(i = 0; i < 27; i++){
        printf("%c",205);
    }
    printf("%c",185);
    gotoxy(4,5);
    printf("%c Palabra",186);
    gotoxy(52,5);
    printf("%c Rengl%cn",186,162);
    gotoxy(62,5);
    printf("%c Tipo",186);
    gotoxy(90,5);
    printf("%c",186);

    gotoxy(4,6);
    printf("%c",200);
    for(i = 0; i < 47; i++){
        printf("%c",205);
    }
    printf("%c",202);
    for(i = 0; i < 9; i++){
        printf("%c",205);
    }
    printf("%c",202);
    for(i = 0; i < 27; i++){
        printf("%c",205);
    }
    printf("%c",188);

    int count = 0;
    for(celda cel: *a){
        gotoxy(4,7+count);
        cout << (char)179 << " " <<cel.pal;
        gotoxy(52,7+count);
        cout << (char)179 << " " << cel.linea;
        gotoxy(62,7+count);
        cout << (char)179 << " " << imprimirEstado(cel.tipo);
        gotoxy(90,7+count);
        cout << (char)179;
        count++;
    }
    gotoxy(4,7+count);
    printf("%c",192);
    for(i = 0; i < 47; i++){
        printf("%c",196);
    }
    printf("%c",193);
    for(i = 0; i < 9; i++){
        printf("%c",196);
    }
    printf("%c",193);
    for(i = 0; i < 27; i++){
        printf("%c",196);
    }
    printf("%c",217);
}