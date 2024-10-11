//============================================================================
// Name        : main.cpp
// Author      : Martin Zeuner
// Version     :
// Copyright   : Your copyright notice
// Description : Inf2-Praktikum Aufgabenblock 1, C++, WS2425
//============================================================================

#include <iostream>
using namespace std;
#include <string>
#include <vector>

#include "Fahrzeug.h"

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

}
int main() {
	vAufgabe_1();

	cout << "!!!Hello World!!!" << endl;
	return 0;
}
