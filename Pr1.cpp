#include <iostream>
#include <regex>
#include <string>
#include <stdlib.h>
#include <windows.h>

#define PANTALLA_ANCHO 120
#define PANTALLA_ALTO 30

using namespace std;

string definirAlfabeto();
void presentacion();
void leerPalabras(string &w1, string &w2, string alfa);

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
	string w1, w2;	// Cadenas
	string ab;		// Alfabeto
	
	presentacion();
	//string alfabeto;
	//alfabeto = definirAlfabeto();
	ab = "[a-zA-Z]";
	regex alfabeto(ab);
	leerPalabras(w1, w2, ab);
	cout<<w1<<"   "<<w2;
}

void presentacion()
{
	system ("CLS");
	gotoxy(76,0);
	printf("\033[95mMolina, Juan. Rosas, Axel. Copyright 2023 %c\033[0m",184);
}

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
}
