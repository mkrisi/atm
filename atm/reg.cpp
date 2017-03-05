#include "reg.h"
#include "atm.h"
#include "globals.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;

void traz() { //Ügyfél azonosítójának elkészítése
	for (int i = 0; i < nm.length(); i++) {
		if (nm[i] == ' ') {
			if (i+1 == nm.length()) { //Csak teljes nevet fogad el
				cout << "Csak teljes nev!";
				_getch();
				reg(); //reg.cpp újrahívása
			}
			//Az azonosító több részből tevődik össze. A teljes vezetéknév, a keresztnév első betűje és szóközzel elválasztva a jelszó.
			az = nm.substr(0, i + 2);
			az.erase(std::remove(az.begin(), az.end(), ' '), az.end()); //Szóközök eltávolítása
			az.insert(i + 1, "-"); //Szóköz helyére "-" karakter
			transform(az.begin(), az.end(), az.begin(), (int(*)(int))tolower); //A teljes azonosító kisbetűvé alakítása
			break;
		}
	}
	az = az + pwdaz;
	fn = "../" + az + ".txt"; //Elérési út összeállítása
}

int reg()
{
	char ch;
	system("cls");
	cout << "Kilepeshez irjon be ""q"" betut a nevhez!" << endl;
	cout << "UJ UGYFEL REGISZTRALASA" << endl << "Uj ugyfel neve: "; getline(cin, nm); cin.clear();
	if (nm == "q") {
		main();
	}
pwderr: //Hibaüzenet címke
	pwd = {};
	pwdu = {};
	cout << nm << " jelszava: "; getline(cin, pwd); cin.clear();
	cout << nm << " jelszava ujra: "; getline(cin, pwdu); cin.clear();
	if (pwd != pwdu) {
		cout << endl << "A ket bevitt jelszo nem egyezik meg! Adja meg ujra: " << endl;
		goto pwderr;
	}

	pwdaz = pwd;
	transform(pwdaz.begin(), pwdaz.end(), pwdaz.begin(), (int(*)(int))tolower); //Az azonosítóhoz a jelszó is hozzátartozik, ugyan azok a formázások végződnek el rajtuk mint fent a névnél.
	replace(pwdaz.begin(), pwdaz.end(), ' ', '_');

	bszerr:
	cout << nm << " azonosito szama(bankszamla szam): "; getline(cin, bsz); cin.clear();
	if (bsz == "") {
		cout << "Ures szamlaszamot adott meg! Kerjuk adja meg ujra!" << endl;
		goto bszerr;
	}
	cout << nm << " nyito egyenlege(Ft): "; getline(cin, nye); cin.clear();

	traz(); //A teljes azonosító elkészítése

	ofstream test(fn); //Kiíratásos objektum
	test << pwd << endl << nm << endl << "-" << endl << bsz << endl << nye; //Felhasználó adatainak fájlba írása
	test.close();

nw:
	cout << "Szeretne hozzadni ujabb szamlaszamot y/n?: " << endl;
	switch ((ch = _getch())) {
	case 121: //Y (yes) bill. megnyomása
		cout << nm << " azonosito szama(bankszamla szam): "; getline(cin, bsz); cin.clear();
		cout << nm << " nyito egyenlege(Ft): "; getline(cin, nye); cin.clear();
		test.open(fn, std::ios::app); //"app" (append) megnyitás, nem írjuk felül az egész fájlt, csak hozzáteszünk
		test << endl << "-" << endl << bsz << endl << nye;
		test.close();
		goto nw;
		break;
	case 110: //N (no) karakter megnyomása
		main(); //Visszatérés az atm.cpp main() függvényéhez
		return 0;
		break;
	default:
		main();
		return 0;
		break;
	}
	return 0;
}