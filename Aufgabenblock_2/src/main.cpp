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

#include "Fahrzeug.h"
#include "Weg.h"
#include "PKW.h"
#include "Fahrrad.h"

using namespace std;

ostream& operator<<(ostream& out, Simulationsobjekt& so){
    so.vAusgeben(out);
    return out;
}

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
void vAufgabe5(){
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
//vAufgabe6() siehe vAufgabe5()
int main() {
	//vAufgabe_4();
	vAufgabe5();
    return 0;
}