#include "reg.h"
#include "globals.h"
#include "log.h"
#include "ffel.h"
#include "atm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>

using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define ESC 27
#define ENT 13
vector<string> elol, hatul;
int lines = 1;
int felosz = 0, befosz = 0, chpoz = 1, egyen = 0, cf = 0;
string bejup = {};

void kerekellen() {
	if (befosz < 0) {
		cout << "Az osszeg nem lehet negativ!";
		_getch();
		ffel();
	}
	if (befosz % 1000 != 0 || befosz < 1000) {
		cout << "A beirt osszeg nem kerek! Cimletek: 1.000 Ft, 2.000 Ft, 5.000 Ft, 10.000 Ft, 20.000 Ft" << endl;
		_getch();
		ffel();
	}
}

void penzkitb() {
	if (felosz < 0) {
		cout << "Az osszeg negativ nem lehet!";
		_getch();
		ffel();
	}
	if (felosz > egyen) {
		cout << "Nincs eleg osszeg a szamlan!";
		_getch();
		ffel();
	}
	if (felosz % 1000 != 0 || felosz < 1000) {
		cout << "A beirt osszeg nem kerek! Cimletek: 1.000 Ft, 2.000 Ft, 5.000 Ft, 10.000 Ft, 20.000 Ft" << endl;
		_getch();
		ffel();
	}
	else {
		ofstream ki(fn);
		int ujosz = egyen - felosz;
		for (int i = 0; i < elol.size(); i++) {
			ki << elol[i];
			ki << endl;
		}
		if (hatul.empty()) {
			ki << ujosz;
		}
		else {
			ki << ujosz;
			ki << endl;
			for (int i = 0; i < hatul.size(); i++) {
				ki << hatul[i];
				ki << endl;
			}
		}
		cout << "Sikeres a penzfelvetel! Aktualis egyenleg: " << ujosz << " Ft";
		_getch();
		ki.close();
		ffel();
	}
}

void penzki() {
	if (felosz < 0) {
		cout << "Negativ osszeg nem lehet!";
		_getch();
		ffel();
	}
	if (felosz > egyen) { //Ha nincs elég pénz a számlán a kívánt összeg felvételéhez akkor hibaüzenetet kap
		cout << "Nincs eleg osszeg a szamlan!";
		_getch();
		ffel();
	}
	if (felosz % 1000 != 0 || felosz < 1000) {
		cout << "A beirt osszeg nem kerek! Cimletek: 1.000 Ft, 2.000 Ft, 5.000 Ft, 10.000 Ft, 20.000 Ft" << endl;
		_getch();
		ffel();
	}
	else {
		ofstream ki(fn);
		int ujosz = egyen - felosz; //Új összeg kiszámítása
		ki << pwd << endl << nm << endl << "-" << endl << bejup << endl << ujosz; //A ügyfél egyenlegének frissítése a fájlban
		cout << "Sikeres a penzfelvetel! Aktualis egyenleg: " << ujosz << " Ft";
		_getch();
		ki.close();
		ffel();
	}
}

void tszi() {
	elol.clear();
	hatul.clear();
	for (int i = 1; i <= (4 + (csz - 1) * 3); i++) {
		elol.push_back(rndln(i));
	}
	for (int i = (4 + (csz - 1) * 3) + 2; i <= lines; i++) {
		hatul.push_back(rndln(i));
	}
}

void ffel() {
	chpoz = 1;
	//int felosz = 0, befosz = 0, chpoz = 1, egyen = 0, cf = 0;
	char in = {};
	lines = 1;
	bejup = {};
	if (bsze == 1) { //Ha egy bankszámlaszám van
		bejup = rndln(4); //Számlaszám
		egyen = stoi(rndln(5)); //Egyenleg
	}
	else { //Több számlaszám esetén
		bejup = rndln(4 + (csz - 1) * 3); 
		egyen = stoi(rndln(4 + (csz - 1) * 3 + 1));
	}

	ifstream be;
	be.open(fn, std::ifstream::in);
	while (!be.eof()) {
		in = be.get();
		if (in == '\n') { //Sorok számlálása
			lines++;
			continue;
		}
	}
	be.close();

	system("cls");
	cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
	cout << "1. >> Penz felvetele <<" << endl;
	cout << "2. Penz befizetese" << endl;
	cout << "3. Egyenleg lekerdezese" << endl;
	cout << "4. Kijelentkezes" << endl;
	while (1) //"Végtelen" ciklus
	{
		switch ((c = _getch())) { //Billenyű nyomás figyelése
		case ESC: //ESC esetén:
			log(); //Felhasználói felületből való kilépés, vissza a loginra
			break;
		case KEY_UP:
			if (chpoz == 1) { //Esetszám, nyilakkal tudunk mozogni a menüben
				system("cls");
				cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
				cout << "1. >> Penz felvetele <<" << endl;
				cout << "2. Penz befizetese" << endl;
				cout << "3. Egyenleg lekerdezese" << endl;
				cout << "4. Kijelentkezes" << endl;
			}
			else if (chpoz == 2) {
				system("cls");
				cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
				cout << "1. >> Penz felvetele <<" << endl;
				cout << "2. Penz befizetese" << endl;
				cout << "3. Egyenleg lekerdezese" << endl;
				cout << "4. Kijelentkezes" << endl;
				chpoz--;
			}
			else if (chpoz == 3) {
				system("cls");
				cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
				cout << "1. Penz felvetele" << endl;
				cout << "2. >> Penz befizetese <<" << endl;
				cout << "3. Egyenleg lekerdezese" << endl;
				cout << "4. Kijelentkezes" << endl;
				chpoz--;
			}
			else if (chpoz == 4) {
				system("cls");
				cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
				cout << "1. Penz felvetele" << endl;
				cout << "2. Penz befizetese" << endl;
				cout << "3. >> Egyenleg lekerdezese <<" << endl;
				cout << "4. Kijelentkezes" << endl;
				chpoz--;
			}
			break;
		case KEY_DOWN:
			if (chpoz == 1) {
				system("cls");
				cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
				cout << "1. Penz felvetele" << endl;
				cout << "2. >> Penz befizetese <<" << endl;
				cout << "3. Egyenleg lekerdezese" << endl;
				cout << "4. Kijelentkezes" << endl;
				chpoz++;
			}
			else if (chpoz == 2) {
				system("cls");
				cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
				cout << "1. Penz felvetele" << endl;
				cout << "2. Penz befizetese" << endl;
				cout << "3. >> Egyenleg lekerdezese <<" << endl;
				cout << "4. Kijelentkezes" << endl;
				chpoz++;
			}
			else if (chpoz == 3) {
				system("cls");
				cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
				cout << "1. Penz felvetele" << endl;
				cout << "2. Penz befizetese" << endl;
				cout << "3. Egyenleg lekerdezese" << endl;
				cout << "4. >> Kijelentkezes <<" << endl;
				chpoz++;
			}
			break;
		case ENT:
			if (chpoz == 3) { //Egyenleg
				system("cls");
				if (bsze == 1) {
					cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
					cout << "A szamlan talalhato egyenleg: " << rndln(5) << " Ft"; //Egy számlaszám esetén az egyenleg mindig a fájl 5. sora lesz
					_getch();
					ffel();
				}
				else {
					cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
					cout << "A szamlan talalhato egyenleg: " << rndln(4 + (csz - 1) * 3 + 1) << " Ft"; //Több számlaszám esetén egy képlet eredménye mutat a kiválasztot számlaszámhoz tartozó egyenlegre (csz = kiválasztott számlaszám sorszáma)
					_getch();
					ffel();
				}
			}

			else if (chpoz == 1) { //Pénz felvét
				system("cls");
				nye = rndln(5); //Eredeti egyenleg
				if (bsze == 1) { //Egy számlaszám esetén
					bsz = rndln(4); //Számlaszám
					cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
					cout << "(1) 5.000" << endl;
					cout << "(2) 10.000" << endl;
					cout << "(3) 25.000" << endl;
					cout << "(4) 50.000" << endl;
					cout << "(5) 100.000" << endl;
					cout << "(6) Mas osszeg" << endl;
					cout << "(7) Vissza" << endl;
					switch ((cf = _getch())) { //Összegek közötti választás a megfeleő szám bill. megnyomásával
					case 49: //1.
						felosz = 5000;
						penzki();
					case 50: //2.
						felosz = 10000;
						penzki();
					case 51: //3.
						felosz = 25000;
						penzki();
					case 52: //4.
						felosz = 50000;
						penzki();
					case 53: //5.
						felosz = 100000;
						penzki();
					case 54: //6. tetszőleges összeg bevitele
						cout << "Mekkora osszeget szeretne felvenni?: ";
						cin >> felosz; //Összeg bevitele
						//kerekellen();
						/*if (felosz % 1000 >= 500) { //1000-re történő kerekítés
							felosz = (felosz / 1000 * 1000) + 1000;
						}
						else if (felosz % 1000 < 500) {
							felosz = (felosz / 1000 * 1000);
						}
						else if (felosz < 1000) {
							felosz = 1000;
						}*/
						cin.ignore();
						penzki();
					case 55: //7. kilépés a pénzfelvétből
						ffel();
					default:
						continue;
					}
				}
				else { //Ha nem egy bankszámla van
					tszi(); //Ez a függvény a fájlban található összes bankszámlaszámot és enyenleget összegyűjti egy vector-ba
					system("cls");
					cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
					cout << "(1) 5.000" << endl;
					cout << "(2) 10.000" << endl;
					cout << "(3) 25.000" << endl;
					cout << "(4) 50.000" << endl;
					cout << "(5) 100.000" << endl;
					cout << "(6) Mas osszeg" << endl;
					cout << "(7) Vissza" << endl;
					nye = rndln(4 + (csz - 1) * 3 + 1); //Kiválasztott számlaszámhoz tartozó egyenleg
					switch ((cf = _getch())) {
					case 49:
						felosz = 5000;
						penzkitb();
					case 50:
						felosz = 1000;
						penzkitb();
					case 51:
						felosz = 25000;
						penzkitb();
					case 52:
						felosz = 50000;
						penzkitb();
					case 53:
						felosz = 100000;
						penzkitb();
					case 54:
						cout << "Mekkora osszeget szeretne felvenni? (min. 1000 Ft): ";
						cin >> felosz;
						//kerekellen();
						/*if (felosz % 1000 >= 500) { //1000-re történő kerekítés
							felosz = (felosz / 1000 * 1000) + 1000;
						}
						else if (felosz % 1000 < 500) {
							felosz = (felosz / 1000 * 1000);
						}
						else if (felosz < 1000) {
							felosz = 1000;
						}*/
						cin.ignore();
						penzkitb();
					case 55:
						ffel(); //Pénzfelvétből kilépés
					default:
						continue;
					}
				}
			}

			else if (chpoz == 2) { //Pénz befizetés, dupla jóváhagyással
				char ch = '\0';
				system("cls");
				if (bsze == 1) {		
					cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
					cout << "Mekkora osszeget szeretne befizetni?: ";
					cin >> befosz;
					cin.ignore();
					cout << "Biztos be szeretne fizetni az osszeget? (y/n): " << endl;
				bck:
					switch ((ch = _getch())) {
					case 121: //Y (yes) bill. megnyomása
						goto jmp;
						break;
					case 110: //N (no) karakter megnyomása
						ffel();
						break;
					default:
						goto bck;
						break;
					}
				jmp:
					kerekellen(); //Kerekítés ellenörzése
					int ujosz = egyen + befosz; //Új összeg kiszámítása
					ofstream ki(fn);
					ki << pwd << endl << nm << endl << "-" << endl << bejup << endl << ujosz; //Új összeg fájlba írása
					cout << "Sikeres penz befizetes! Aktualis egyenleg: " << ujosz << " Ft";
					_getch();
					ki.close();
					ffel();
				}
				else {
					tszi();
					cout << "Bejelentkezett ugyfel: " << nm << " Szamlaszam: " << bejup << endl;
					cout << "Mekkora osszeget szeretne befizetni?: ";
					cin >> befosz;
					cin.ignore();
					cout << "Biztos be szeretne fizetni az osszeget? (y/n): " << endl;
				bcktb:
					switch ((ch = _getch())) {
					case 121: //Y (yes) bill. megnyomása
						goto jmptb;
						break;
					case 110: //N (no) karakter megnyomása
						ffel();
						break;
					default:
						goto bcktb;
						break;
					}
				jmptb:
					kerekellen(); //Kerekítés ellenörzése
					int ujosz = egyen + befosz;
					ofstream ki(fn);
					for (int i = 0; i < elol.size(); i++) {
						ki << elol[i];
						ki << endl;
					}
					if (hatul.empty()) {
						ki << ujosz;
					}
					else {
						ki << ujosz;
						ki << endl;
						for (int i = 0; i < hatul.size(); i++) {
							ki << hatul[i];
							ki << endl;
						}
					}
					cout << "Sikeres penz befizetes! Aktualis egyenleg: " << ujosz << " Ft";
					_getch();
					ki.close();
					ffel();
				}

			}

			else if (chpoz == 4) { //Kijelentkezés
				log();
			}
		}
	}
}