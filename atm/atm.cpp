#include "reg.h"
#include "globals.h"
#include "log.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std; 
#define KEY_UP 72 	//A felfelé nyíl ASCII kódja
#define KEY_DOWN 80 //A lefelé nyíl ASCII kódja
#define ESC 27 		//Az ESC bill. ASCII kódja
#define ENT 13 		//Az ENTER bill. ASCII kódja

int main() {
	system("cls"); //Parancssori ablak tartalmának törlése
	cout << ">> Felhasznalo regisztralasa <<";
	cout << endl;
	cout << "Meglevo felhasznaloval valo belepes";
	while (1) //"Végtelen" ciklus
	{
		switch ((c = _getch())) { //Egy karakter beolvasása, billenyű nyomásának érzékelése
		case ESC: //ESC esetén:
			exit(1); //Kilépés a programból
		case KEY_UP: //Felfelé nyíl esetén:
			cr = 1; //Esetszám
			system("cls");
			cout << ">> Felhasznalo regisztralasa <<";
			cout << endl;
			cout << "Meglevo felhasznaloval valo belepes";
			break;
		case KEY_DOWN: //Lefelé nyíl esetén:
			system("cls");
			cr = 2;
			cout << "Felhasznalo regisztralasa";
			cout << endl;
			cout << ">> Meglevo felhasznaloval valo belepes <<";
			break;
		case ENT: //Enter esetén:
			if (cr == 1) {
				reg(); //reg.cpp hívása
			}
			else if (cr == 2) {
				log(); //log.cpp hívása
			}
			break;
		}
		
	}
}