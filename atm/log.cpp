#include "reg.h"
#include "globals.h"
#include "atm.h"
#include "log.h"
#include "ffel.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <tchar.h>
#include <limits>
#include <stdio.h>
//#include <dirent.h>
#include <conio.h>

using namespace std;
int nol = 0, ins = 0;
string bnksz = {}, pr = {}, tmp = {};
char in, cf;
int ln = 0, sr = 0, bc = 7, iki = 1;
ifstream be; //Beolvasáshoz objektum
string rndln(int lin) { //Tetszőleges sor beolvasása
	tmp = {}; //Alapértelmezés nagyon fontos!!!
	in = {};
	ln = 0;
	sr = 0;
	be.open(fn, std::ifstream::in);
	if (be) { //Ha a fájl létezik és a program meg tudja nyitni
		while (!be.eof()) { //A fájl végéig történik az olvasáss
		nx: //Visszaugráshoz címke
			in = be.get(); //Egy karakter beolvasása a fájlból
			if (in == '\n' && ln < lin) {
				ln++; //Sorszám növelése
				continue;
			}
			else if (ln + 1 == lin) {
				if (in == '\n' || in == -1) {
					break; //Ha elértük a kiírandó sor végét
				}
				else {
					tmp.insert(sr, 1, in); //A tmp tömbbe pakoljuk annak a sornak a karaktereit melyet ki akarunk olvasni
					sr++;
					goto nx; //Visszaugrás
				}
			}

		}
		be.close(); //Fájl bezárása
		return tmp; //tmp visszaadása
	}
	else {
		cout << "Nincs ilyen ugyfel az adatbazisban!";
		_getch();
		log(); //Ha a felhasználó nem létezik, akkor a hibaüzenet után újra hívja magát a függvény
	}
}


void autchk()
{
	bc = 7;
	bsze = 1;
	csz = 0;
	while (rndln(bc) != "") { //Ügyfél bankszámláinak megszámlálása
		bsze++;
		bc += 3; //Minden 3. sor tartalmazhat bankszámlaszámot
	}

	if (rndln(1).compare(pwd) == 0 && rndln(2).compare(nm) == 0) { //Ha a beírt és tárolt jelszó, név összehasonlításakor "0 helyen térnek el egymástól" akkor sikeres a belépés
		if (bsze == 1) { //Ha 1 db bankszámlája van az ügyfélnek
			ffel(); //Felhasználói felületre való továbbléptetés
		}
	gtSzszer1: //Hibaüzenet címke
		system("cls");
		cout << "A fiokhoz " << bsze << " szamla tartozik." << endl;
		bc = 4;
		cout << "Szamlaszamok: " << endl;
		while (rndln(bc) != "") { //Ügyfél bankszámláinak megszámlálása
			cout << "(" << iki << ") " << rndln(bc) << endl; //Bankszámlák kiíratása
			bc += 3;
			iki++;
		}
		cout << "Melyiket szeretne valasztani?: ";
		string be = {};
		cin >> be;
		cin.ignore(); //FONTOS!
		csz = atoi(be.c_str()); //String -> Intbe való konverzáció
		if (csz == 0) { //Választani kívánt bankszámla sorszámának beírása, 0 nem lehet
			cout << "Hibas bemenet!" << endl;
			_getch();
			csz = 0;
			cin.clear();
			iki = 1;
			goto gtSzszer1; //Hibaüzenet
		}
		else {
			if (csz >= 1 && csz <= bsze) { //Nem lehet lehet n+1 számlaszámot választani ha n-ünk van
				ffel(); //Felhasználói felületre való továbbléptetés
			}
			else {
				cout << "Hibas bemenet!" << endl;
				csz = 0;
				cin.clear();
				iki = 1;
				_getch();
				goto gtSzszer1;
			}
		}
	}
	else {
		cout << "Nincs ilyen ugyfel az adatbazisban!"; //Ha eltérést talál a beírt és a tárolt jelszó, név között akkor az a ügyfél nem létezik
		_getch();
		log(); //log.cpp újrahívása
	}

}

int log(){
	iki = 1;
	nol = 0, ins = 0, ln = 0, sr = 0, bc = 7; //FONTOS, az újrahívás végett!
	bnksz = {}, pr = {}, tmp = {};
	in = {};
	cf = {};
	nm = {}, pwd = {};
	system("cls");
	cout << "Kilepeshez irjon be ""q"" betut a nevhez!" << endl;
	cout << "UGYFEL BELEPESE" << endl << "Felhasznalo nev: "; 
	getline(cin, nm); 
	cin.clear();
	if (nm == "q") {
		nm = {};
		//return 0;
		main();
	}
	cout << nm << " jelszava: "; getline(cin, pwd); cin.clear();
	pwdaz = pwd;
	transform(pwdaz.begin(), pwdaz.end(), pwdaz.begin(), (int(*)(int))tolower); //Azonosító elkészítése
	replace(pwdaz.begin(), pwdaz.end(), ' ', '_'); //Szóközök helyett "_" karakter
	traz(); //reg.cpp traz() függvényének hívása, mely az ügyfél elérési útjának összeállításában segít
	az = az + ".txt"; // .txt hozzáfüzése az elérési úthoz
	autchk(); //Beléptetés ellenörzése
	return 0;
}
