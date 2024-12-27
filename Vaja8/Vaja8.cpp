#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <time.h>
#include <chrono>
using namespace std;

struct vozlisce {
	int predhodnik;
	int status;			// 0 - nepregledano vozlišče     1 - vozlišče v stanju pregledovanja      2 - razvito vozlišče
	int dolzina;
	int indeks;
	int ime;
};

std::stack<vozlisce*> stck;
vector <vozlisce*> vrsta;

void menu() {
	cout << "Iskanje v globino in sirino - izbira:" << endl;
	cout << "1) Preberi graf iz datoteke" << endl;
	cout << "2) Iskanje v globino iz vozlisca s do d" << endl;
	cout << "3) Iskanje v sirino iz vozlisca s do d" << endl;
	cout << "4) Izpis seznama vozlisc" << endl;
	cout << "5) Konec" << endl;
	cout << endl;
	cout << "Izbira: ";
}

int stevilo_vozlisc;

int** branje(vector <vozlisce*>& V) {
	int stevilo_povezav;

	ifstream f("graf.txt");
	f >> stevilo_vozlisc;
	f >> stevilo_povezav;

	for (int i = 0; i < stevilo_vozlisc; i++) {			//polje vozlišč V
		vozlisce* v1 = new vozlisce();
		v1->indeks = i;
		v1->ime = i + 1;
		v1->status = 0;
		V.push_back(v1);
	}

	int** E = new int* [stevilo_vozlisc];

	for (int i = 0; i < stevilo_vozlisc; i++) {			//2D polje E
		E[i] = new int[stevilo_vozlisc];
	}

	for (int i = 0; i < stevilo_vozlisc; i++) {			//inicializacija vseh vrednosti v E na 0
		for (int j = 0; j < stevilo_vozlisc; j++) {
			E[i][j] = 0;
		}
	}

	int indeksV1;
	int indeksV2;
	int cena;

	for (string line; getline(f, line);) {
		f >> indeksV1 >> indeksV2 >> cena;
		E[indeksV1 - 1][indeksV2 - 1] = 1;
		E[indeksV2 - 1][indeksV1 - 1] = 1;			//v matriki C označi vozlišči v1 in v2 kot soseda
	}
	cout << endl;

	return E;
}


void izpis_poti(vector <vozlisce*> V, int* E[], vozlisce* s, vozlisce* v) {
	if (s->ime == v->ime)
		cout << "Pot je: " << v->ime << " ";
	else {
		if (v->predhodnik == -1)
			cout << "Med " << s->ime << " in " << v->ime << " ni poti!" << endl;
		else {
			izpis_poti(V, E, s, V[v->predhodnik]);
			cout << v->ime << " ";
		}
	}
}


void iskanje_v_globino(vector <vozlisce*> V, int* E[], int s, int d) {		//s in d sta imeni vozlisc

	bool exist = false;														//prvo preverimo če vozlišče s sploh obstaja ... 
	for (int i = 0; i < V.size(); i++) {
		if (V[i]->ime != s) {
			exist = false;
		}
		else {
			exist = true;
			break;
		}
	}
	if (!exist) {
		cout << "Vozlisce " << s << " ne obstaja!" << endl;
		cout << endl;
		return;
	}

	for (int i = 0; i < V.size(); i++) {
		if (V[i]->ime != d) {
			exist = false;
		}
		else {
			exist = true;
			break;
		}
	}
	if (!exist) {
		cout << "Vozlisce " << d << " ne obstaja!" << endl;
		cout << endl;
		return;
	}

	for (int i = 0; i < V.size(); i++) {					//vsem vozliščem razen tistega z imenom s določimo atribute
		if (V[i]->ime == s)
			continue;
		V[i]->status = 0;
		V[i]->dolzina = INT_MAX;
		V[i]->predhodnik = -1;
	}

	V[s - 1]->status = 1;									// s določimo atribute in ga dodamo na sklad
	V[s - 1]->dolzina = 0;
	V[s - 1]->predhodnik = -1;
	stck.push(V[s - 1]);

	auto start = std::chrono::steady_clock::now();
	while (!stck.empty()) {	
		vozlisce* v = stck.top();
		stck.pop();
		
		if (v->ime == d) {
			auto end = std::chrono::steady_clock::now();
			cout << endl;
			izpis_poti(V, E, V[s - 1], v);
			cout << endl;
			cout << "Cena: " << v->dolzina << endl;
			cout << "Cas iskanja: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs." << endl;
			cout << endl;
			return;				
		}

		for (int i = 0; i < V.size(); i++) {
			if (E[v->indeks][i] == 1) {					//sosednja vozlišča od v
				if (V[i]->status == 0) {				//če je sosednje vozlišče nepregledano ...
					V[i]->status = 1;
					V[i]->dolzina = v->dolzina + 1;
					V[i]->predhodnik = v->indeks;
					stck.push(V[i]);
				}
			}
		}

		v->status = 2;
	}
}

void iskanje_v_sirino(vector <vozlisce*> V, int* E[], int s, int d) {		//s in d sta imeni vozlisc

	bool exist = false;														//prvo preverimo če vozlišče s sploh obstaja ... 
	for (int i = 0; i < V.size(); i++) {
		if (V[i]->ime != s) {
			exist = false;
		}
		else {
			exist = true;
			break;
		}
	}

	if (!exist) {
		cout << "Vozlisce " << s << " ne obstaja!" << endl;
		cout << endl;
		return;
	}

	for (int i = 0; i < V.size(); i++) {
		if (V[i]->ime != d) {
			exist = false;
		}
		else {
			exist = true;
			break;
		}
	}

	if (!exist) {
		cout << "Vozlisce " << d << " ne obstaja!" << endl;
		cout << endl;
		return;
	}


	for (int i = 0; i < V.size(); i++) {
		if (V[i]->ime == s)
			continue;
		V[i]->status = 0;
		V[i]->dolzina = INT_MAX;
		V[i]->predhodnik = -1;
	}

	if (V[s - 1]->indeks == -1) {
		cout << "Vozlisce " << s << " ne obstaja!" << endl;
		cout << endl;
		return;
	}

	V[s - 1]->status = 1;
	V[s - 1]->dolzina = 0;
	V[s - 1]->predhodnik = -1;
	vrsta.push_back(V[s - 1]);

	auto start = std::chrono::steady_clock::now();
	while (vrsta.size() > 0) {	
		vozlisce* v = vrsta.front();
		vrsta.erase(vrsta.begin());

		if (v->ime == d) {
			auto end = std::chrono::steady_clock::now();
			cout << endl;
			izpis_poti(V, E, V[s - 1], v);
			cout << endl;
			cout << "Cena: " << v->dolzina << endl;
			cout << "Cas iskanja: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs." << endl;
			cout << endl;
			return;
		}

		for (int i = 0; i < V.size(); i++) {
			if (E[v->indeks][i] == 1) {					//sosednja vozlišča od v
				if (V[i]->status == 0) {				//če je sosednje vozlišče nepregledano ...
					V[i]->status = 1;
					V[i]->dolzina = v->dolzina + 1;
					V[i]->predhodnik = v->indeks;
					vrsta.push_back(V[i]);
				}
			}
		}

		v->status = 2;
	}
}


void print_vozlisca(vector <vozlisce*> V, int* E[]) {
	cout << "  ";
	for (int i = 0; i < V.size(); i++) {
		cout << V[i]->ime << " ";
	}
	cout << endl;
	for (int i = 0; i < V.size(); i++) {
		cout << V[i]->ime << " ";
		for (int j = 0; j < V.size(); j++) {
			cout << E[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}

int main() {
	int d1;
	int s1;

	vector <vozlisce*> V;
	int** E = new int* [stevilo_vozlisc];

	int selection;
	bool running = true;

	do {
		menu();
		cin >> selection;
		switch (selection) {
		case 1:
			E = branje(V);
			break;
		case 2:
			cout << "Vozlisce s: ";
			cin >> s1;
			cout << "Vozlisce d: ";
			cin >> d1;
			iskanje_v_globino(V, E, s1, d1);
			break;
		case 3:
			cout << "Vozlisce s: ";
			cin >> s1;
			cout << "Vozlisce d: ";
			cin >> d1;
			iskanje_v_sirino(V, E, s1, d1);
			break;
		case 4:
			print_vozlisca(V, E);
			break;
		case 5:
			running = false;
			break;
		default:
			cout << "ERROR";
			break;
		}
	} while (running);

	return 0;
}

