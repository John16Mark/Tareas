/*
Pr1.c
V 1.0 Marzo 2022
Autores: Juan Luis Molina Acuña.



	Compilar con el comando:
gcc Pr1.cpp -o Pr1.exe -lstdc++

*/

#include <iostream>
#include <regex>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <random>
#include <cstdlib>
#include <ctime>

#define PANTALLA_ANCHO 120
#define PANTALLA_ALTO 30

using namespace std;

string definirAlfabeto();
void presentacion();
void leerPalabras(string &w1, string &w2, string alfa);
void pre_su_sub(string w1, string w2);
string generarPalabraAleatoria(string alfabeto, int l);
auto generarLenguaje(string alfabeto, int c_palabras, int l)->vector<string>;
void lenguajes(string alfabeto, vector<string> &l1, vector<string> &l2);
/*-------------------------------------*/
typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(0, 7);
rng_type rng;
/*--------------------------------*/

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 } 

int main()
{
	srand(time(nullptr));
	string w1, w2;	// Cadenas
	string ab;		// Alfabeto
	vector<string> l1 = vector<string>();
	vector<string> l2 = vector<string>();

	presentacion();
	//string alfabeto;
	//alfabeto = definirAlfabeto();
	ab = "[a-zA-Z]";
	regex alfabeto(ab);
	//leerPalabras(w1, w2, ab);
	w1 = "Hola";
	w2 = "Holamundo";
	//cout<<"\n"<<generarPalabraAleatoria(ab, 6);
	//generarLenguaje(ab,5,8);
	lenguajes(ab,l1,l2);
	//cout<<w1<<"   "<<w2;
}

void presentacion()
{
	system ("CLS");
	gotoxy(76,0);
	printf("\033[95mMolina, Juan. Rosas, Axel. Copyright 2023 %c\033[0m",184);
}

/*
string definirAlfabeto()
	Efecto:
Lee entradas para definir un alfabeto regex
	Regresa:
string para definir un alfabeto
*/
string definirAlfabeto()
{
	string leer = "";	// Entrada
	string ab = "";		// Alfabeto
	cout<<"\n         \033[96mDEFINIR ALFABETO\033[0m\n";
	printf("\n  Se puede introducir caracter %cnico. Ej: \033[92mp\033[0m, \033[92mB\033[0m, \033[92m!\033[0m",163);
	printf("\n  Se puede introducir rango de caracteres. Ej: \033[92ma-z\033[0m, \033[92mF-Q\033[0m, \033[92m4-7\033[0m");
	printf("\n  La definci%cn del alfabeto \033[91mTERMINA\033[0m cuando se introduce un caracter \033[91mNO V%cLIDO\033[0m\n\n",162,181);
	while(true)
	{
		printf("   ");
		cin>>leer;
		if(leer.length() == 1)
		{
			if(leer == "[" || leer == "]" || leer == "\\")
			{
				leer = "\\" + leer;
			}
			//cout<<"       "<<leer;
			ab += leer;
		}
		else if(leer.length() == 3 && leer[1] == '-')
		{
			ab += leer;
		}
		else
		{
			break;
		}
	}
	ab = "["+ab+"]";
	cout<<"\n         \033[95m"<<ab<<"\033[0m\n";
	cin.get();
	//printf("\n         \033[96m%s\033[0m\n",ab);
	
	return ab;
}

void leerPalabras(string &w1, string &w2, string alfa)
{
	int i, j;
	string leer = "";		// Entrada
	string leer2 = "";		// Entrada
	regex alfabeto(alfa+"*");	// Alfabeto
	cout<<"\n         \033[96mLEER CADENAS\033[0m\n";
	printf("\n  Introduzca dos cadenas v%clidas dentro del alfabeto definido \033[95m",160);
	cout<<alfa;
	printf("\033[0m\n\n    PRIMER CADENA:\n");
	while(true)
	{
		gotoxy(0,7);
		//printf("\033[106m");
		for(i=0; i<PANTALLA_ANCHO; i++)
		{
			for(j=0; j<2; j++)
			{
				printf(" ");
			}
		}
		//printf("\033[0m");
		gotoxy(3,7);
		cin>>leer;
		gotoxy(8,9);
		for(i=0; i<30; i++)
		{
			printf(" ");
		}
		gotoxy(8,9);
		if(regex_match(leer,alfabeto))
		{
			printf("\033[92mS%c\033[0m es v%clida",214,160);
			w1 = leer;
			break;
		}
		else
		{
			printf("\033[91mNO\033[0m es v%clida, introduzca otra",160);
		}
	}
	//gotoxy(8,11);
	printf("\033[0m\n\n    SEGUNDA CADENA:\n");
	while(true)
	{
		gotoxy(0,13);
		//printf("\033[106m");
		for(i=0; i<PANTALLA_ANCHO; i++)
		{
			for(j=0; j<2; j++)
			{
				printf(" ");
			}
		}
		printf("\033[0m");
		gotoxy(3,13);
		cin>>leer2;
		gotoxy(8,15);
		for(i=0; i<30; i++)
		{
			printf(" ");
		}
		gotoxy(8,15);
		if(regex_match(leer2,alfabeto))
		{
			printf("\033[92mS%c\033[0m es v%clida",214,160);
			w2 = leer2;
			break;
		}
		else
		{
			printf("\033[91mNO\033[0m es v%clida, introduzca otra",160);
		}
	}
	
	pre_su_sub(w1,w2);
}

void pre_su_sub(string w1, string w2)
{
	cout<<"\n\n         \033[96mPREFIJO, SUFIJO O SUBCADENA\033[0m\n";
	regex subcadena(w1);
	if(regex_search(w2, subcadena))
	{
		printf("\n  cadena1 \033[92mS%c\033[0m ES SUBCADENA",214);
		if(w1 != w2)
		{
			printf(" PROPIA");
		}
		
	}
	else
	{
		printf("\n  cadena1 \033[91mNO\033[0m ES SUBCADENA");
	}
	printf(" de cadena2");
	regex prefijo("^" + w1);
	if(regex_search(w2, prefijo))
	{
		printf("\n  cadena1 \033[92mS%c\033[0m ES PREFIJO",214);
		if(w1 != w2)
		{
			printf(" PROPIO");
		}	
	}
	else
	{
		printf("\n  cadena1 \033[91mNO\033[0m ES PREFIJO");
	}
	printf(" de cadena2");
	regex postfijo(w1 + "$");
	if(regex_search(w2, postfijo))
	{
		printf("\n  cadena1 \033[92mS%c\033[0m ES SUFIJO",214);
		if(w1 != w2)
		{
			printf(" PROPIO");
		}	
	}
	else
	{
		printf("\n  cadena1 \033[91mNO\033[0m ES SUFIJO");
	}
	printf(" de cadena2");
	printf("\n\n    ");
	system("pause");
}

string generarPalabraAleatoria(string alfabeto, int l)
{
	regex r(alfabeto+"*");
	string palabra = "";
	char c;
	
	while(palabra.length() < l)
	{
		c = static_cast<char>(rand()%256);
		palabra += c;
		if(!regex_match(palabra, r))
		{
			palabra.pop_back();
		}
	}
	return palabra;
}

auto generarLenguaje(string alfabeto, int c_palabras, int l)->vector<string>
{
	int i;
	vector<string> lenguaje = vector<string>();

	for(i=1; i<= c_palabras; i++)
	{
		lenguaje.push_back(generarPalabraAleatoria(alfabeto, l));
	}
	for (const auto& str : lenguaje)
	{
        std::cout << str << " ";
    }
	return lenguaje;
}

void lenguajes(string alfabeto, vector<string> &l1, vector<string> &l2)
{
	int cl1, ll1, cl2, ll2;
	cout<<"\n         \033[96mGENERAR LENGUAJES ALEATORIOS\033[0m\n";
	printf("\n  Cantidad de palabras del lenguaje 1: ");
	cin>>cl1;
	printf("\n  Longitud de palabras del lenguaje 1: ");
	cin>>ll1;
	l1 = generarLenguaje(alfabeto, cl1, ll1);
	printf("\n  Cantidad de palabras del lenguaje 2: ");
	cin>>cl2;
	printf("\n  Longitud de palabras del lenguaje 2: ");
	cin>>ll2;
	l2 = generarLenguaje(alfabeto, cl2, ll2);
}