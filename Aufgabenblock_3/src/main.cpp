//============================================================================
// Name        : main.cpp
// Author      : Martin Zeuner
// Version     :
// Copyright   : Your copyright notice
// Description : Inf2-Praktikum Aufgabenblock 1, C++, WS2425
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>

#include "Fahrzeug.h"
#include "Weg.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimuClient.h"
#include "vertagt_liste.h"
#include "vertagt_aktion.h"

using namespace std;



double dGlobaleZeit = 0.0;

void vAufgabe_1(){
	Fahrzeug f1;
	Fahrzeug f2("BMW");
	Fahrzeug *f3 = new Fahrzeug("Audi");
	//delete f3;
	unique_ptr<Fahrzeug> f4 = make_unique<Fahrzeug>();
	unique_ptr<Fahrzeug> f5 = make_unique<Fahrzeug>();
	//unique_ptr<Fahrzeug> stupid = f4;

	shared_ptr<Fahrzeug> f6 = make_shared<Fahrzeug>();
	shared_ptr<Fahrzeug> f7 = make_shared<Fahrzeug>();

	cout << "use count: " <<	f7.use_count() << endl;
	shared_ptr<Fahrzeug> sharedf7 = f7;
	cout << "use count: " <<	f7.use_count() << endl;

	vector<unique_ptr<Fahrzeug>> fahrzeuge; //a vector of unique pointers
	fahrzeuge.push_back(unique_ptr<Fahrzeug>(f3)); //implicitly creates a unique ptr from the raw pointer (not so good)
	fahrzeuge.push_back(std::move(f4)); //moves f4 from original pointer to the new pointer in the vector of ptrs
	fahrzeuge.push_back(std::move(f5));
	fahrzeuge.push_back(make_unique<Fahrzeug>("Mini"));
	fahrzeuge.clear(); //deletes all elements in the vector

	vector<shared_ptr<Fahrzeug>> sharedFahrzeuge;
	sharedFahrzeuge.push_back(std::move(f6));
	sharedFahrzeuge.push_back(f7); //if we use move on this, it would delete the original pointer
	
	cout << "use count: " <<	f7.use_count() << endl;
	sharedFahrzeuge.push_back(sharedf7);
	cout << "use count: " <<	f7.use_count() << endl; //with use_count we can see that we are still using the shared ptr here
	
	
	Fahrzeug::vKopf();
	cout << endl;
	f1.vAusgeben(cout);
	cout << endl;
	f2.vAusgeben(cout);
	cout << endl;
}
void vAufgabe_1a(){
	cout << "Aufgabe 1a" << endl << "============" << endl;
	vector<unique_ptr<Fahrzeug>> fahrzeuge;
	for(int i = 0; i < 3; i++){
		cout << "Fahrzeug " << i+1 << "." << "enter Name: " << endl;
		string name;
		cin >> name;
		cout << "enter max speed: " << endl;
		double maxSpeed;
		cin >> maxSpeed;
		fahrzeuge.push_back(make_unique<Fahrzeug>(name, maxSpeed));
	}
	Fahrzeug::vKopf();
	cout << endl;
	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.2;
		for(auto &f : fahrzeuge){
			f->vSimulieren();
			f->vAusgeben(cout);
			cout << endl;
		}
	}
}
void vAufgabe_2() {
    int anzahlPKW, anzahlFahrrad;
    cout << "PKW Anzahl? ";
    cin >> anzahlPKW;
    cout << "Fahrrad Anzahl? ";
    cin >> anzahlFahrrad;

    vector<unique_ptr<Fahrzeug>> fahrzeuge;

    for (int i = 0; i < anzahlPKW; ++i) {
        string name = "PKW_" + to_string(i + 1);
        double maxSpeed = 200 + i * 10; // Beispielwerte
        fahrzeuge.push_back(make_unique<PKW>(name, maxSpeed, 8.0));
    }

    for (int i = 0; i < anzahlFahrrad; ++i) {
        string name = "Fahrrad_" + to_string(i + 1);
        double maxSpeed = 20 + i * 2; // Beispielwerte
        fahrzeuge.push_back(make_unique<Fahrrad>(name, maxSpeed));
    }

	Fahrzeug::vKopf();
	cout << endl;

	while(dGlobaleZeit < 10){
		if(dGlobaleZeit >= 2.99 && dGlobaleZeit <= 3.01){//tanken after 3 hours
			for(auto &f : fahrzeuge){
				PKW *pkw = dynamic_cast<PKW*>(f.get());//dynamic cast to check if the pointer returned by f.get() is a PKW
				if(pkw != nullptr){
					pkw->dTanken();
				}
			}
		}
		dGlobaleZeit += 0.5;
		for(auto &f : fahrzeuge){
			f->vSimulieren();
			cout << *f << endl;
		}
	}

}
void vAufgabe_3() {
	vector<unique_ptr<Fahrzeug>> fahrzeuge;
	fahrzeuge.push_back(make_unique<PKW>("Mini", 180, 5.5, 40));
	fahrzeuge.push_back(make_unique<PKW>("BMW", 220, 7.5, 60));
	fahrzeuge.push_back(make_unique<Fahrrad>("Bike", 25));
	Fahrzeug f3("base_fz");
	
	Fahrzeug::vKopf();
	cout << endl;
	for(auto &f : fahrzeuge){
		cout << *f << endl;
	}
	f3.vAusgeben(cout);cout << endl;
	PKW f4("Audi", 200, 6.5, 50);
	f3 = f4; //copying f4 to f3 from PKW to Fahrzeug (implicit conversion) NOTE! properties of PKW are lost
	f4.vAusgeben(cout);cout << endl;
	f3.vAusgeben(cout);cout << endl;
	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.5;
		for(auto &f : fahrzeuge){
			f->vSimulieren();
			cout << *f << endl;
		}
	}
	cout << "Gesamtstrecke vom Bike kleiner als vom BMW?  " << (*fahrzeuge[2] < *fahrzeuge[1]) << endl;


}
void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 231, 11.4));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 19.8));
    for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;
}
void vAufgabe_4(){
	Weg w1("Weg1", 100, Tempolimit::Innerorts);
	Weg::vKopf();
	cout << w1 << endl;
}
void vAufgabe_5(){
	Weg w1("Weg1", 100, Tempolimit::Innerorts);
	unique_ptr<Fahrzeug> f1 = make_unique<PKW>("Mini", 180, 5.5, 40);
	unique_ptr<Fahrzeug> f2 = make_unique<PKW>("BMW", 220, 7.5, 60);
	unique_ptr<Fahrzeug> f3 = make_unique<Fahrrad>("Bike", 25);
	w1.vAnnahme(std::move(f1));
	w1.vAnnahme(std::move(f2), 3.0);
	w1.vAnnahme(std::move(f3), 6);
	Weg::vKopf();
	cout << w1 << endl;
	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.3;
		w1.vSimulieren();
		cout << "---" << endl;
	}
}
void vAufgabe_6(){
	Weg w1("Weg1", 500, Tempolimit::Autobahn);
	Weg w2("Weg2", 500, Tempolimit::Autobahn);
	unique_ptr<Fahrzeug> f1 = make_unique<PKW>("Mini", 180, 5.5, 250);
	unique_ptr<Fahrzeug> f2 = make_unique<PKW>("BMW", 220, 7.5, 60);
	unique_ptr<Fahrzeug> f3 = make_unique<Fahrrad>("Bike", 25);
	w1.vAnnahme(std::move(f1));
	w1.vAnnahme(std::move(f2), 3.0);
	w1.vAnnahme(std::move(f3), 0.5);
	Weg::vKopf();
	cout << w1 << endl;

	bInitialisiereGrafik(800, 500);
	vSleep(0);
	bZeichneStrasse("Weg1", "Weg2", 500, 2, new int[4]{700, 250, 100, 250});


	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.1;
		w1.vSimulieren();
		cout << "---" << endl;
		vSetzeZeit(dGlobaleZeit);
		vSleep(20);
	}
	vBeendeGrafik();
}
void vAufgabe_6a(){
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);
	
	vertagt::VListe<int> liste;
	for(int i = 0; i < 20; i++){//arbitrary length of 20 here, was sollen wir nehmen?
		int zuf = dist(device);
		liste.push_back(zuf);
	}
	liste.vAktualisieren();
	cout << "Liste: " << endl;
	for(auto &i : liste){
		cout << i << " ";
	}
	cout << endl;
	for(auto it = liste.begin(); it != liste.end(); ++it){
		if(*it > 5){
			liste.erase(it);
		}
	}
	cout << "Liste nachdem erase geplant: " << endl;
	for(auto &i : liste){
		cout << i << " ";
	}
	cout << endl;
	liste.vAktualisieren();
	cout << "Liste nachdem aktualisiert: " << endl;
	for(auto &i : liste){
		cout << i << " ";
	}
	cout << endl;
	liste.push_front(100);
	liste.push_back(200);
	liste.vAktualisieren();
	cout << "Liste nachdem push_front und push_back: " << endl;
	for(auto &i : liste){
		cout << i << " ";
	}
	cout << endl;
	
}
void testat(){
/* 	unique_ptr<Fahrzeug> pPKW = make_unique<PKW>("BMW",150, 6, 500);
	Weg aStr("Strasse",500);
	aStr.vAnnahme(std::move(pPKW));



	while(dGlobaleZeit < 10){
		dGlobaleZeit += 1;
		aStr.vSimulieren();
		cout << "---" << endl;
	}
 */

	list<int> listT(3, 2);
    listT.remove(1);
    listT.erase(listT.begin());
    for (int i = 0; i < 3; i++)
    {
        listT.push_back(i);
    }
    listT.pop_back();
    listT.remove(1);
    listT.erase(listT.begin());
	for(auto &i : listT){
		cout << i << " ";
	}
}
void vAufgabe_6_block3(){
	Weg w1("Weg1", 500, Tempolimit::Autobahn);
	unique_ptr<Fahrzeug> f1 = make_unique<PKW>("Mini", 80, 5.5, 250);
	unique_ptr<Fahrzeug> f3 = make_unique<PKW>("Dummerchen", 200, 5.5, 10);
	unique_ptr<Fahrzeug> f2 = make_unique<PKW>("BMW", 220, 7.5, 60);
	w1.vAnnahme(std::move(f1));
	w1.vAnnahme(std::move(f3));
	w1.vAnnahme(std::move(f2), 2);
	Weg::vKopf();
	cout << w1 << endl;

	bInitialisiereGrafik(800, 500);
	vSleep(0);
	bZeichneStrasse("Weg1", "Weg2", 500, 2, new int[4]{700, 250, 100, 250});


	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.1;
		w1.vSimulieren();
		//cout << "---" << endl;
		vSetzeZeit(dGlobaleZeit);
		vSleep(20);
	}
	vBeendeGrafik();
}
void vAufgabe7(){
	//Erstelle Kreuzungen
	shared_ptr<Kreuzung> kr_1 = make_shared<Kreuzung>("Kreuzung1", 0);
	shared_ptr<Kreuzung> kr_2 = make_shared<Kreuzung>("Kreuzung2", 1000);
	shared_ptr<Kreuzung> kr_3 = make_shared<Kreuzung>("Kreuzung3", 0);
	shared_ptr<Kreuzung> kr_4 = make_shared<Kreuzung>("Kreuzung4", 0);
/* 	shared_ptr<Weg> str_1 = 	make_shared<Weg>("W12", 40, Tempolimit::Innerorts, true);
	shared_ptr<Weg> str_1r = 	make_shared<Weg>("W21", 40, Tempolimit::Innerorts, true);
	shared_ptr<Weg> str_2 = 	make_shared<Weg>("W23a", 115, Tempolimit::Autobahn, false);
	shared_ptr<Weg> str_2r = 	make_shared<Weg>("W32a", 115, Tempolimit::Autobahn, false);
	shared_ptr<Weg> str_3 = 	make_shared<Weg>("W23b", 40, Tempolimit::Innerorts, true);
	shared_ptr<Weg> str_3r = 	make_shared<Weg>("W32b", 40, Tempolimit::Innerorts, true);
	shared_ptr<Weg> str_4 = 	make_shared<Weg>("W24", 55, Tempolimit::Innerorts, true);
	shared_ptr<Weg> str_4r = 	make_shared<Weg>("W42", 55, Tempolimit::Innerorts, true);
	shared_ptr<Weg> str_5 = 	make_shared<Weg>("W43", 85, Tempolimit::Autobahn, true);
	shared_ptr<Weg> str_5r = 	make_shared<Weg>("W34", 85, Tempolimit::Autobahn, true);
	shared_ptr<Weg> str_6 = 	make_shared<Weg>("W44a", 130, Tempolimit::Landstrasse, true);
	shared_ptr<Weg> str_6r = 	make_shared<Weg>("W44b", 130, Tempolimit::Landstrasse, true); */

	//Verbinde Kreuzungen (dabei werden Wege erstellt)
	Kreuzung::vVerbinde("W12", "W21", 40, kr_1, kr_2, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W23a", "W32a", 115, kr_2, kr_3, Tempolimit::Autobahn, false);
	Kreuzung::vVerbinde("W23b", "W32b", 40, kr_2, kr_3, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W24", "W42", 55, kr_2, kr_4, Tempolimit::Innerorts, true);
	Kreuzung::vVerbinde("W34", "W43", 85, kr_3, kr_4, Tempolimit::Autobahn, true);
	Kreuzung::vVerbinde("W44a", "W44b", 130, kr_4, kr_4, Tempolimit::Landstrasse, true);

	//Grafik
	bInitialisiereGrafik(1000, 600);
	vSleep(0);
	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);
	bZeichneStrasse("W12", "W21", 40, 2, new int[4]{680, 40, 680, 300});
	bZeichneStrasse("W23a", "W32a", 115, 6, new int[12]{680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570}); //autobahn rechts auf der karte
	bZeichneStrasse("W23b", "W32b", 40, 2, new int[4]{680, 300, 680, 570});
	bZeichneStrasse("W24", "W42", 55, 2, new int[4]{680, 300, 320, 300});
	bZeichneStrasse("W34", "W43", 85, 5, new int[10]{680, 570, 500, 570, 350, 510, 320, 420, 320, 300});
	bZeichneStrasse("W44a", "W44b", 130, 7, new int[14]{320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300}); //loop oben links
	
	//ein paar Fahrzeuge
	unique_ptr<Fahrzeug> f1 = make_unique<PKW>("Mini", 80, 5.5, 250);
	unique_ptr<Fahrzeug> f2 = make_unique<PKW>("BMW", 220, 7.5, 60);
	unique_ptr<Fahrzeug> f3 = make_unique<PKW>("Dummerchen", 200, 5.5, 10);
	unique_ptr<Fahrzeug> f4 = make_unique<PKW>("Audi", 150, 6, 500);
	unique_ptr<Fahrzeug> f5 = make_unique<PKW>("VW", 180, 5.5, 250);
	unique_ptr<Fahrzeug> f6 = make_unique<PKW>("Mercedes", 220, 7.5, 60);
	unique_ptr<Fahrzeug> f7 = make_unique<PKW>("Opel", 200, 5.5, 100);
	unique_ptr<Fahrzeug> f8 = make_unique<PKW>("Ford", 150, 6, 500);
	unique_ptr<Fahrzeug> f9 = make_unique<PKW>("Toyota", 180, 5.5, 250);
	unique_ptr<Fahrzeug> f10 = make_unique<Fahrrad>("Bike", 25);
	unique_ptr<Fahrzeug> f11 = make_unique<Fahrrad>("Bike2", 28);
	unique_ptr<Fahrzeug> f12 = make_unique<Fahrrad>("Bike3", 30);
	unique_ptr<Fahrzeug> f13 = make_unique<Fahrrad>("Bike4", 20);
	
	//Fahrzeuge auf Kreuzung 1 stellen
	kr_1->vAnnahme(std::move(f1), 0.1);
 	kr_1->vAnnahme(std::move(f2), 1);
	kr_1->vAnnahme(std::move(f3), 2);
	kr_1->vAnnahme(std::move(f4), 3);
	kr_1->vAnnahme(std::move(f5), 3.5);
	kr_1->vAnnahme(std::move(f6), 4);
	kr_1->vAnnahme(std::move(f7), 4.5);
	kr_1->vAnnahme(std::move(f8), 5);
	kr_1->vAnnahme(std::move(f9), 6);
	kr_1->vAnnahme(std::move(f10), 7);
	kr_1->vAnnahme(std::move(f11), 2);
	kr_1->vAnnahme(std::move(f12), 3);
	kr_1->vAnnahme(std::move(f13), 6); 
	
	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.1;
		kr_1->vSimulieren();
		kr_2->vSimulieren();
		kr_3->vSimulieren();
		kr_4->vSimulieren();
		vSetzeZeit(dGlobaleZeit);
		//vSleep(20);
	}
	vBeendeGrafik();
}
int main() {
	//vAufgabe_6_block3();
    vAufgabe7();
	return 0;
}