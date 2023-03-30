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
#include <algorithm>

#define PANTALLA_ANCHO 120
#define PANTALLA_ALTO 30
#define INTENTOS 1000
#define TAB_TITULO 9
#define TAB_SUBTITULO 4

using namespace std;

string definirAlfabeto();
void presentacion();
void leerPalabras(string &w1, string &w2, string alfa);
void pre_su_sub(string w1, string w2);
string generarPalabraAleatoria(string alfabeto, int l);
auto generarLenguaje(string alfabeto, int c_palabras, int l)->vector<string>;
void lenguajes(string alfabeto, vector<string> &l1, vector<string> &l2);
auto diferenciaLenguaje(vector<string> &L1, vector<string> &L2)->vector<string>;
auto regexAVector(string re)->vector<string>;
auto alfabetoPotencia(vector<string> ab)->vector<string>;
void expresionRegular();

void titulo(string s);
void subtitulo(string s);
void pausa();
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
	vector<string> L1 = vector<string>();	// Cadena 1
	vector<string> L2 = vector<string>();	// Cadena 2

	vector<string> chars = vector<string>();	// Vector con todos los caracteres válidos en un alfabeto
	vector<string> pot = vector<string>();	// Vector del alfabeto elevado a una potencia

	presentacion();
	ab = definirAlfabeto();
	regex alfabeto(ab);
	leerPalabras(w1, w2, ab);
	lenguajes(ab,L1,L2);
	diferenciaLenguaje(L1,L2);
	chars = regexAVector(ab);
	pot = alfabetoPotencia(chars);
	expresionRegular();
}



/**************************************************************************
					   *   *
					  **    *
					 * *    *
					   *    *
					   *    *
					 ****  *
**************************************************************************/
/*
string definirAlfabeto()
Efecto:
	Lee entradas para definir un alfabeto regex
Regresa:
	string para definir un alfabeto
*/
string definirAlfabeto()
{
	//Ejemplos leerAlfabeto -> E1=0-9; E2=1,2,3,4,5,6,7,8,9,0;

	string leer = "";		// Entrada
	string ab = "";		// Alfabeto
	titulo("DEFINIR ALFABETO");
	printf("\n  Se puede introducir caracter %cnico. Ej: \033[92mp\033[0m, \033[92mB\033[0m, \033[92m!\033[0m",163);
	printf("\n  Se puede introducir rango de caracteres. Ej: \033[92ma-z\033[0m, \033[92mF-Q\033[0m, \033[92m4-7\033[0m");
	printf("\n  La definci%cn del alfabeto \033[91mTERMINA\033[0m cuando se introduce un caracter \033[91mNO V%cLIDO\033[0m (Por ej. 2312)\n\n",162,181);
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
	cout<<"\n         Afabeto definido: \033[95m\""<<ab<<"\"\033[0m\n";
	pausa();
	
	return ab;
}

/**************************************************************************
					 ****  *
					    *   *
					  **    *
					 *      *
					 *      *
					 ****  *
**************************************************************************/
void leerPalabras(string &w1, string &w2, string alfa)
{
	//Ejemplo leercadena -> C1={100101}; C2={010010001};

	int i, j;
	string leer = "";		// Entrada
	string leer2 = "";		// Entrada
	regex alfabeto(alfa+"*");	// Alfabeto
	presentacion();
	titulo("LEER CADENAS");
	printf("\n  Introduzca dos cadenas v%clidas dentro del alfabeto definido \033[95m\"",160);
	cout<<alfa<<"\"\n\033[0m";
	subtitulo("CADENA w1");
	while(true)
	{
		gotoxy(0,6);

		for(i=0; i<PANTALLA_ANCHO; i++)
		{
			for(j=0; j<2; j++)
			{
				printf(" ");
			}
		}

		gotoxy(3,6);
		cin>>leer;
		gotoxy(14,5);
		for(i=0; i<33; i++)
		{
			printf(" ");
		}
		gotoxy(14,5);
		if(regex_match(leer,alfabeto))
		{
			printf("  <-\033[92mS%c\033[0m es v%clida",214,160);
			w1 = leer;
			break;
		}
		else
		{
			printf("  <-\033[91mNO\033[0m es v%clida, introduzca otra",160);
		}
	}
	gotoxy(0,7);
	subtitulo("CADENA w2");
	while(true)
	{
		gotoxy(0,9);

		for(i=0; i<PANTALLA_ANCHO; i++)
		{
			for(j=0; j<2; j++)
			{
				printf(" ");
			}
		}
		printf("\033[0m");
		gotoxy(3,9);
		cin>>leer2;
		gotoxy(14,8);
		for(i=0; i<33; i++)
		{
			printf(" ");
		}
		gotoxy(14,8);
		if(regex_match(leer2,alfabeto))
		{
			printf("  <-\033[92mS%c\033[0m es v%clida",214,160);
			w2 = leer2;
			break;
		}
		else
		{
			printf("  <-\033[91mNO\033[0m es v%clida, introduzca otra",160);
		}
	}
	gotoxy(0,8);
	cout<<"\n";
	pre_su_sub(w1,w2);
}

/**************************************************************************
					 ****  *
					   **   *
					  **    *
					    *   *
					    *   *
					 ***   *
**************************************************************************/
void pre_su_sub(string w1, string w2)
{
	cout<<"\n\n         \033[96mPREFIJO, SUFIJO O SUBCADENA\033[0m\n";
	regex subcadena(w1);
	if(regex_search(w2, subcadena))
	{
		printf("\n  cadena1 \033[92mS%c\033[0m ES SUBCADENA",214);
		if(w1 != w2)
		{
			printf(" \033[95mPROPIA\033[0m");
		}
		
	}
	else
	{
		printf("\n  cadena1 \033[91mNO\033[0m ES SUBCADENA");
	}
	printf(" de cadena2");
	regex prefijo("^" + w1);	// "^+" Es para validar prefijos
	if(regex_search(w2, prefijo))
	{
		printf("\n  cadena1 \033[92mS%c\033[0m ES PREFIJO",214);
		if(w1 != w2)
		{
			printf(" \033[95mPROPIO\033[0m");
		}	
	}
	else
	{
		printf("\n  cadena1 \033[91mNO\033[0m ES PREFIJO");
	}
	printf(" de cadena2");
	regex postfijo(w1 + "$");	// "+$" Es para validar sufijos
	if(regex_search(w2, postfijo))
	{
		printf("\n  cadena1 \033[92mS%c\033[0m ES SUFIJO",214);
		if(w1 != w2)
		{
			printf(" \033[95mPROPIO\033[0m");
		}	
	}
	else
	{
		printf("\n  cadena1 \033[91mNO\033[0m ES SUFIJO");
	}
	printf(" de cadena2\n");
	pausa();
}

string generarPalabraAleatoria(string alfabeto, int l)
{
	regex r(alfabeto+"*");	// Alfabeto definido
	string palabra = "";
	char c;

	// Mientras sea menor a la longitud definida
	while(palabra.length() < l)
	{
		c = static_cast<char>(rand()%256);	// Caracter aleatorio
		palabra += c;				// Se añade dicho caracter al string
		if(!regex_match(palabra, r))		// Si la palabra no coincide con el alfabeto, se quita del string el último caracter
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
	string palabraAleatoria;
	int intentos = 0;

	// Mientras se hayan generado menos palabras de las requeridas o no se haya sobrepasado el número de intentos
	while(lenguaje.size()<c_palabras && intentos <= INTENTOS)
	{
		intentos++;
		palabraAleatoria = generarPalabraAleatoria(alfabeto, l);	// Genera una palabra con caracteres aleatorios

		// Si la palabra no se encuentra ya en el vector, se añade al vector
		if(find(lenguaje.begin(), lenguaje.end(), palabraAleatoria) == lenguaje.end())	
		{
			lenguaje.push_back(palabraAleatoria);
			intentos = 0;	// Si se añadió satisfactoriamente una palabra, se reinician los intentos
		}
	}
	if(intentos >= INTENTOS)
	{
		cout<<"\033[91mHUBO UN ERROR GENERANDO EL LENGUAJE\033[0m\n";
	}

	// Imprime los elementos del lenguaje
	for (const auto& str : lenguaje)
	{
      	std::cout << str << " ";
	}
	return lenguaje;
}

/**************************************************************************
					    *  *
					   **   *
					  * *   *
					 ****   *
					    *   *
					    *  *
**************************************************************************/
void lenguajes(string alfabeto, vector<string> &L1, vector<string> &L2)
{
	int cl1, ll1, cl2, ll2;
	presentacion();
	titulo("GENERAR LENGUAJES ALEATORIOS");
	subtitulo("LENGUAJE L1");
	printf("\n  Cantidad de palabras: ");
	cin>>cl1;
	printf("  Longitud de las palabras: ");
	cin>>ll1;
	L1 = generarLenguaje(alfabeto, cl1, ll1);
	cout<<"\n";
	subtitulo("LENGUAJE L2");
	printf("\n  Cantidad de palabras: ");
	cin>>cl2;
	printf("  Longitud de las palabras: ");
	cin>>ll2;
	L2 = generarLenguaje(alfabeto, cl2, ll2);
}

/**************************************************************************
					 ****  *
					 *      *
					 ***    *
					    *   *
					    *   *
					 ****  *
**************************************************************************/
auto diferenciaLenguaje(vector<string> &L1, vector<string> &L2)->vector<string>
{
	//Ejemplo -> L1={010,101,111,100}; L2={010,110,111,001,100}; LR={010,111,100};

	int i;
	vector<string> LD;
	cout<<"\n";
	titulo("DIFERENCIA DE LOS DOS LENGUAJES");
	
	// el for añade todos los elementos de L1 que NO están en L2 a un tercer vector LD
	for (auto i : L1) {
		if(find(L2.begin(), L2.end(),i) == L2.end()) {	// Búsqueda si se encuentra en L2, si el elemento buscado pasa del end(), entonces no está en el vector
			LD.push_back(i);
		}
	}

	subtitulo("LENGUAJE LD");
	printf("\n  Cantidad de palabras: %d",LD.size());
	printf("\n  Longitud de las palabras: ");

	// Para imprimir la longitud de las palabras
	if(LD.empty()){
		printf("0");
	}
	else{
		printf("%d",LD[0].length());
	}
	
	// Imprime los elementos de LD
	for(auto i : LD){
		cout <<"\n"<<i;
	}
	cout<<"\n";
	pausa();
	return LD;
}

/**************************************************************************
					 ****  *
					 *      *
					 ****   *
					 *  *   *
					 *  *   *
					 ****  *
**************************************************************************/
auto alfabetoPotencia(vector<string> ab)->vector<string>
{
	//Ejemplo Potencia -> A={0,1}; n=3 R={000,001,010,011,100,101,110,111}

	int potencia;
	vector<string> abconpotencia = {""};

	presentacion();
	titulo("POTENCIA DE UN ALFABETO");
	printf("  Introduzca una potencia (rango de -5 a 5)\n  Valor de la potencia: ");
	while(true){
		gotoxy(24,3);
		for(int i = 23; i < PANTALLA_ANCHO; i++){
			printf(" ");
		}
		gotoxy(24,3);
		cin>>potencia;
		if(potencia <= 5 && potencia >= -5){
			break;
		}
	}
	if(potencia == 0){
		abconpotencia.push_back("\033[95mlambda\033[0m");
	}
	else if(potencia > 0)	// POTENCIA POSITIVA
	{
		for(int i = 0; i < potencia; i++)			// Primer for se hace tantas veces sea la potencia
		{
			vector<string> auxiliar;
			for(string s : abconpotencia){		// Segundo for se hace para cada string dentro del vector con potencia
				for(string c : ab){			// Tercer for se hace para cada string dentro del alfabeto
					auxiliar.push_back(s+c);
				}
			}
			abconpotencia = auxiliar;
		}
	}
	else{				// POTENCIA NEGATIVA
		string aux;

		// Mismo algoritmo para valores mayores a 0
		for(int i = 0; i < potencia*(-1); i++){
			vector<string> auxiliar;
			for(string s : abconpotencia){
				for(string c : ab){
					auxiliar.push_back(s+c);
				}
			}
			abconpotencia = auxiliar;
		}

		// Invierte todas las cadenas dentro del vector
		for(int i = 0; i < abconpotencia.size(); i++){
			reverse(abconpotencia[i].begin(), abconpotencia[i].end());
		}

		// Invierte el orden de los elementos del vector (este cambio es solo estético)
		reverse(abconpotencia.begin(), abconpotencia.end());
	}

	// Imprime los elementos del vector
	for (string s : abconpotencia) {
		cout << s << " ";
	}

	cout<<"\n";
	pausa();

	return abconpotencia;
}

// Pasa todos los caracteres válidos en una expresión regular a un vector
auto regexAVector(string re)->vector<string>
{
	regex r(re+"*");
	vector<string> caracteresValidos;
	string ca;
	for(int i=32; i<256; i++)
	{
		ca = static_cast<char>(i);
		if(regex_match(ca, r))
		{
			caracteresValidos.push_back(ca);
		}
	}
	return caracteresValidos;
}

/**************************************************************************
					 ****  *
					    *   *
					   *    *
					  *     *
					 *      *
					 *     *
**************************************************************************/
void expresionRegular(){
	regex er("(\\d)*(\\d)(\\d)*\\1(\\d)*");
	// (\\d)*	---> Captura cualquier dígito 0 o más veces
	// (\\d) 	---> Captura cualquier dígito
	// (\\d)*	---> Captura cualquier dígito 0 o más veces
	// \\1   	---> Referencia al primer grupo de captura, coincidirá con cualquier dígito que sea igual al primer dígito encontrado en la cadena.
	// (\\d)*	---> Captura cualquier dígito 0 o más veces
	// 1234526789
	string entrada;

	presentacion();
	titulo("VALIDAR EXPRESION REGULAR");
	printf("  B. Todas las cadenas de d%cgitos que tengan por lo menos un d%cgito repetido. Los d%cgitos no tienen que estar en orden.   La cadena debe tener una longitud m%cnima de 5 caracteres (escribe \"lambda\" para salir).",161,161,161,161);
	printf("\n\n  Ingrese una cadena para validar: ");
	
	while(true){
		gotoxy(35,5);
		for(int i = 35; i < PANTALLA_ANCHO; i++)	// Borrar la entrada para el usuario
		{
			printf(" ");
		}
		gotoxy(35,5);
		getline(cin, entrada);
		if(entrada == "lambda") // Si la cadena es igual a lambda se sale del programa
		{
			break;
		}
		else if(entrada.length() < 5) // Si la cadena es de long. menor a 5, no pasa
		{
			gotoxy(0,7);
			for(int i=0; i <= 22; i++){
				printf(" ");
			}
			gotoxy(0,6);
			cout<<"\n \033[91mLA CADENA ES INVALIDA\033[0m"<<endl;
		}
		else	// Si la cadena no es lambda y la longitud es 5 o más
		{
			gotoxy(0,7);
			for(int i=0; i <= 22; i++){
				printf(" ");
			}
			gotoxy(0,6);
			if(regex_match(entrada, er)) 	// Valida si la entrada pertenece a la expresión regular.
			{
				cout<<"\n \033[92mLA CADENA ES VALIDA\033[0m"<<endl;
			}
			else{
				cout<<"\n \033[91mLA CADENA ES INVALIDA\033[0m"<<endl;
			}
		}
	}
}

/**************************************************************************
				  FUNCIONES DE DISEÑO VISUAL
**************************************************************************/
void titulo(string s){
	cout<<"\n";
	for(int i=1; i<= TAB_TITULO; i++){
		cout<<" ";
	}
	cout<<"\033[96m"<<s<<"\033[0m\n";
}

void subtitulo(string s){
	cout<<"\n";
	for(int i=1; i<= TAB_SUBTITULO; i++){
		cout<<" ";
	}
	cout<<"\033[93m"<<s<<"\033[0m";
}

void pausa(){
	printf("\033[92m\n    ");
	system("pause");
	printf("\033[0m");
}

void presentacion()
{
	system ("CLS");
	gotoxy(76,0);
	printf("\033[91mMolina, Juan. \033[35mRobles, Axel. \033[33mCopyright 2023 %c\033[0m",184);
}