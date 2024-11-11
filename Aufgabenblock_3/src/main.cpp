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
#include <fstream>

#include "Fahrzeug.h"
#include "Weg.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimuClient.h"
#include "vertagt_liste.h"
#include "vertagt_aktion.h"
#include "Simulation.h"


double dGlobaleZeit = 0.0;

void vAufgabe_1(){
	Fahrzeug f1;
	Fahrzeug f2("BMW");
	Fahrzeug *f3 = new Fahrzeug("Audi");
	//delete f3;
	std::unique_ptr<Fahrzeug> f4 = std::make_unique<Fahrzeug>();
	std::unique_ptr<Fahrzeug> f5 = std::make_unique<Fahrzeug>();
	//std::unique_ptr<Fahrzeug> stupid = f4;

	std::shared_ptr<Fahrzeug> f6 = std::make_shared<Fahrzeug>();
	std::shared_ptr<Fahrzeug> f7 = std::make_shared<Fahrzeug>();

	std::cout << "use count: " <<	f7.use_count() << std::endl;
	std::shared_ptr<Fahrzeug> sharedf7 = f7;
	std::cout << "use count: " <<	f7.use_count() << std::endl;

	std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge; //a vector of unique pointers
	fahrzeuge.push_back(std::unique_ptr<Fahrzeug>(f3)); //implicitly creates a unique ptr from the raw pointer (not so good)
	fahrzeuge.push_back(std::move(f4)); //moves f4 from original pointer to the new pointer in the vector of ptrs
	fahrzeuge.push_back(std::move(f5));
	fahrzeuge.push_back(std::make_unique<Fahrzeug>("Mini"));
	fahrzeuge.clear(); //deletes all elements in the vector

	std::vector<std::shared_ptr<Fahrzeug>> sharedFahrzeuge;
	sharedFahrzeuge.push_back(std::move(f6));
	sharedFahrzeuge.push_back(f7); //if we use move on this, it would delete the original pointer
	
	std::cout << "use count: " <<	f7.use_count() << std::endl;
	sharedFahrzeuge.push_back(sharedf7);
	std::cout << "use count: " <<	f7.use_count() << std::endl; //with use_count we can see that we are still using the shared ptr here
	
	
	Fahrzeug::vKopf();
	std::cout << std::endl;
	f1.vAusgeben(std::cout);
	std::cout << std::endl;
	f2.vAusgeben(std::cout);
	std::cout << std::endl;
}
void vAufgabe_1a(){
	std::cout << "Aufgabe 1a" << std::endl << "============" << std::endl;
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;
	for(int i = 0; i < 3; i++){
		std::cout << "Fahrzeug " << i+1 << "." << "enter Name: " << std::endl;
		std::string name;
		std::cin >> name;
		std::cout << "enter max speed: " << std::endl;
		double maxSpeed;
		std::cin >> maxSpeed;
		fahrzeuge.push_back(std::make_unique<Fahrzeug>(name, maxSpeed));
	}
	Fahrzeug::vKopf();
	std::cout << std::endl;
	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.2;
		for(auto &f : fahrzeuge){
			f->vSimulieren();
			f->vAusgeben(std::cout);
			std::cout << std::endl;
		}
	}
}
void vAufgabe_2() {
    int anzahlPKW, anzahlFahrrad;
    std::cout << "PKW Anzahl? ";
    std::cin >> anzahlPKW;
    std::cout << "Fahrrad Anzahl? ";
    std::cin >> anzahlFahrrad;

    std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

    for (int i = 0; i < anzahlPKW; ++i) {
        std::string name = "PKW_" + std::to_string(i + 1);
        double maxSpeed = 200 + i * 10; // Beispielwerte
        fahrzeuge.push_back(std::make_unique<PKW>(name, maxSpeed, 8.0));
    }

    for (int i = 0; i < anzahlFahrrad; ++i) {
        std::string name = "Fahrrad_" + std::to_string(i + 1);
        double maxSpeed = 20 + i * 2; // Beispielwerte
        fahrzeuge.push_back(std::make_unique<Fahrrad>(name, maxSpeed));
    }

	Fahrzeug::vKopf();
	std::cout << std::endl;

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
			std::cout << *f << std::endl;
		}
	}

}
void vAufgabe_3() {
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;
	fahrzeuge.push_back(std::make_unique<PKW>("Mini", 180, 5.5, 40));
	fahrzeuge.push_back(std::make_unique<PKW>("BMW", 220, 7.5, 60));
	fahrzeuge.push_back(std::make_unique<Fahrrad>("Bike", 25));
	Fahrzeug f3("base_fz");
	
	Fahrzeug::vKopf();
	std::cout << std::endl;
	for(auto &f : fahrzeuge){
		std::cout << *f << std::endl;
	}
	f3.vAusgeben(std::cout);std::cout << std::endl;
	PKW f4("Audi", 200, 6.5, 50);
	f3 = f4; //copying f4 to f3 from PKW to Fahrzeug (implicit conversion) NOTE! properties of PKW are lost
	f4.vAusgeben(std::cout);std::cout << std::endl;
	f3.vAusgeben(std::cout);std::cout << std::endl;
	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.5;
		for(auto &f : fahrzeuge){
			f->vSimulieren();
			std::cout << *f << std::endl;
		}
	}
	std::cout << "Gesamtstrecke vom Bike kleiner als vom BMW?  " << (*fahrzeuge[2] < *fahrzeuge[1]) << std::endl;


}
void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    std::vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<std::unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(std::make_unique <PKW>("Audi", 231, 11.4));
    vecFahrzeuge.push_back(std::make_unique <Fahrrad>("BMX", 19.8));
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
                std::cout << *vecFahrzeuge[i] << std::endl;
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
	std::cout << w1 << std::endl;
}
void vAufgabe_5(){
	Weg w1("Weg1", 100, Tempolimit::Innerorts);
	std::unique_ptr<Fahrzeug> f1 = std::make_unique<PKW>("Mini", 180, 5.5, 40);
	std::unique_ptr<Fahrzeug> f2 = std::make_unique<PKW>("BMW", 220, 7.5, 60);
	std::unique_ptr<Fahrzeug> f3 = std::make_unique<Fahrrad>("Bike", 25);
	w1.vAnnahme(std::move(f1));
	w1.vAnnahme(std::move(f2), 3.0);
	w1.vAnnahme(std::move(f3), 6);
	Weg::vKopf();
	std::cout << w1 << std::endl;
	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.3;
		w1.vSimulieren();
		std::cout << "---" << std::endl;
	}
}
void vAufgabe_6(){
	Weg w1("Weg1", 500, Tempolimit::Autobahn);
	Weg w2("Weg2", 500, Tempolimit::Autobahn);
	std::unique_ptr<Fahrzeug> f1 = std::make_unique<PKW>("Mini", 180, 5.5, 250);
	std::unique_ptr<Fahrzeug> f2 = std::make_unique<PKW>("BMW", 220, 7.5, 60);
	std::unique_ptr<Fahrzeug> f3 = std::make_unique<Fahrrad>("Bike", 25);
	w1.vAnnahme(std::move(f1));
	w1.vAnnahme(std::move(f2), 3.0);
	w1.vAnnahme(std::move(f3), 0.5);
	Weg::vKopf();
	std::cout << w1 << std::endl;

	bInitialisiereGrafik(800, 500);
	vSleep(0);
	bZeichneStrasse("Weg1", "Weg2", 500, 2, new int[4]{700, 250, 100, 250});


	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.1;
		w1.vSimulieren();
		std::cout << "---" << std::endl;
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
	std::cout << "Liste: " << std::endl;
	for(auto &i : liste){
		std::cout << i << " ";
	}
	std::cout << std::endl;
	for(auto it = liste.begin(); it != liste.end(); ++it){
		if(*it > 5){
			liste.erase(it);
		}
	}
	std::cout << "Liste nachdem erase geplant: " << std::endl;
	for(auto &i : liste){
		std::cout << i << " ";
	}
	std::cout << std::endl;
	liste.vAktualisieren();
	std::cout << "Liste nachdem aktualisiert: " << std::endl;
	for(auto &i : liste){
		std::cout << i << " ";
	}
	std::cout << std::endl;
	liste.push_front(100);
	liste.push_back(200);
	liste.vAktualisieren();
	std::cout << "Liste nachdem push_front und push_back: " << std::endl;
	for(auto &i : liste){
		std::cout << i << " ";
	}
	std::cout << std::endl;
	
}
void testat(){
/* 	std::unique_ptr<Fahrzeug> pPKW = std::make_unique<PKW>("BMW",150, 6, 500);
	Weg aStr("Strasse",500);
	aStr.vAnnahme(std::move(pPKW));



	while(dGlobaleZeit < 10){
		dGlobaleZeit += 1;
		aStr.vSimulieren();
		std::cout << "---" << std::endl;
	}
 */

	std::list<int> listT(3, 2);
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
		std::cout << i << " ";
	}
}
void vAufgabe_6_block3(){
	Weg w1("Weg1", 500, Tempolimit::Autobahn);
	std::unique_ptr<Fahrzeug> f1 = std::make_unique<PKW>("Mini", 80, 5.5, 250);
	std::unique_ptr<Fahrzeug> f3 = std::make_unique<PKW>("Dummerchen", 200, 5.5, 10);
	std::unique_ptr<Fahrzeug> f2 = std::make_unique<PKW>("BMW", 220, 7.5, 60);
	w1.vAnnahme(std::move(f1));
	w1.vAnnahme(std::move(f3));
	w1.vAnnahme(std::move(f2), 2);
	Weg::vKopf();
	std::cout << w1 << std::endl;

	bInitialisiereGrafik(800, 500);
	vSleep(0);
	bZeichneStrasse("Weg1", "Weg2", 500, 2, new int[4]{700, 250, 100, 250});


	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.1;
		w1.vSimulieren();
		//std::cout << "---" << std::endl;
		vSetzeZeit(dGlobaleZeit);
		vSleep(20);
	}
	vBeendeGrafik();
}
void vAufgabe7(){
	//Erstelle Kreuzungen
	std::shared_ptr<Kreuzung> kr_1 = std::make_shared<Kreuzung>("Kreuzung1", 0);
	std::shared_ptr<Kreuzung> kr_2 = std::make_shared<Kreuzung>("Kreuzung2", 1000);
	std::shared_ptr<Kreuzung> kr_3 = std::make_shared<Kreuzung>("Kreuzung3", 0);
	std::shared_ptr<Kreuzung> kr_4 = std::make_shared<Kreuzung>("Kreuzung4", 0);
/* 	std::shared_ptr<Weg> str_1 = 	std::make_shared<Weg>("W12", 40, Tempolimit::Innerorts, true);
	std::shared_ptr<Weg> str_1r = 	std::make_shared<Weg>("W21", 40, Tempolimit::Innerorts, true);
	std::shared_ptr<Weg> str_2 = 	std::make_shared<Weg>("W23a", 115, Tempolimit::Autobahn, false);
	std::shared_ptr<Weg> str_2r = 	std::make_shared<Weg>("W32a", 115, Tempolimit::Autobahn, false);
	std::shared_ptr<Weg> str_3 = 	std::make_shared<Weg>("W23b", 40, Tempolimit::Innerorts, true);
	std::shared_ptr<Weg> str_3r = 	std::make_shared<Weg>("W32b", 40, Tempolimit::Innerorts, true);
	std::shared_ptr<Weg> str_4 = 	std::make_shared<Weg>("W24", 55, Tempolimit::Innerorts, true);
	std::shared_ptr<Weg> str_4r = 	std::make_shared<Weg>("W42", 55, Tempolimit::Innerorts, true);
	std::shared_ptr<Weg> str_5 = 	std::make_shared<Weg>("W43", 85, Tempolimit::Autobahn, true);
	std::shared_ptr<Weg> str_5r = 	std::make_shared<Weg>("W34", 85, Tempolimit::Autobahn, true);
	std::shared_ptr<Weg> str_6 = 	std::make_shared<Weg>("W44a", 130, Tempolimit::Landstrasse, true);
	std::shared_ptr<Weg> str_6r = 	std::make_shared<Weg>("W44b", 130, Tempolimit::Landstrasse, true); */

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
	std::unique_ptr<Fahrzeug> f1 = std::make_unique<PKW>("Mini", 80, 5.5, 250);
	std::unique_ptr<Fahrzeug> f2 = std::make_unique<PKW>("BMW", 220, 7.5, 60);
	std::unique_ptr<Fahrzeug> f3 = std::make_unique<PKW>("Dummerchen", 200, 5.5, 10);
	std::unique_ptr<Fahrzeug> f4 = std::make_unique<PKW>("Audi", 150, 6, 500);
	std::unique_ptr<Fahrzeug> f5 = std::make_unique<PKW>("VW", 180, 5.5, 250);
	std::unique_ptr<Fahrzeug> f6 = std::make_unique<PKW>("Mercedes", 220, 7.5, 60);
	std::unique_ptr<Fahrzeug> f7 = std::make_unique<PKW>("Opel", 200, 5.5, 100);
	std::unique_ptr<Fahrzeug> f8 = std::make_unique<PKW>("Ford", 150, 6, 500);
	std::unique_ptr<Fahrzeug> f9 = std::make_unique<PKW>("Toyota", 180, 5.5, 250);
	std::unique_ptr<Fahrzeug> f10 = std::make_unique<Fahrrad>("Bike", 25);
	std::unique_ptr<Fahrzeug> f11 = std::make_unique<Fahrrad>("Bike2", 28);
	std::unique_ptr<Fahrzeug> f12 = std::make_unique<Fahrrad>("Bike3", 30);
	std::unique_ptr<Fahrzeug> f13 = std::make_unique<Fahrrad>("Bike4", 20);
	
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
void vAufgabe8(){
	try {
		std::ifstream inputFile("/Users/marti/eclipse-workspace/prakti_info2/Aufgabenblock_3/VO.dat");
		if (!inputFile) {
			throw std::runtime_error("File not found");
			return;
		}
		std::unique_ptr<Fahrrad> fahrrad = std::make_unique<Fahrrad>();
		std::unique_ptr<PKW> pkw = std::make_unique<PKW>();
		std::shared_ptr<Kreuzung> kreuzung = std::make_shared<Kreuzung>();
		inputFile >> *pkw >> *fahrrad >> *kreuzung;
		std::cout << *pkw << std::endl << *fahrrad << std::endl << *kreuzung << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "FEHLER: " << e.what() << std::endl;
		return;
	}
}
void vAufgabe9(){
	std::ifstream inputFile("/Users/marti/eclipse-workspace/prakti_info2/Aufgabenblock_3/Simu.dat");
	if (!inputFile) {
		throw std::runtime_error("File not found");
		return;
	}
	Simulation sim;
	sim.vEinlesen(inputFile);
}
void vAufgabe10(){
	std::ifstream inputFile("/Users/marti/eclipse-workspace/prakti_info2/Aufgabenblock_3/SimuDisplay.dat");
	if (!inputFile) {
		throw std::runtime_error("File not found");
		return;
	}
	Simulation sim;
	sim.vEinlesen(inputFile, true);
	while(dGlobaleZeit < 10){
		dGlobaleZeit += 0.1;
		sim.vSimulieren();
		vSetzeZeit(dGlobaleZeit);
		//vSleep(20);
    }    
	
	vBeendeGrafik();
}
int main() {
	//vAufgabe_6_block3();
    //vAufgabe7();
	//vAufgabe8();
	//vAufgabe9();
	vAufgabe10();
	return 0;
}