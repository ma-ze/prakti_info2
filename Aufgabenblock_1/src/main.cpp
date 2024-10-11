//============================================================================
// Name        : main.cpp
// Author      : Martin Zeuner
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include <string>

#include "Fahrzeug.h"

void vAufgabe_1(){
	Fahrzeug f1;
	Fahrzeug f2("BMW");
	Fahrzeug *f3 = new Fahrzeug("Audi");
	delete f3;
	cout << "meeeeep" << endl;
}
int main() {
	vAufgabe_1();

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}


