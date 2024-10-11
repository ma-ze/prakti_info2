/*
 * fahrzeug.cpp
 *
 *  Created on: 11.10.2024
 *      Author: marti
 */

#include "Fahrzeug.h"
// Constructor
Fahrzeug::Fahrzeug()
:p_iID(++p_maxID){
    std::cout << "created new Fahrzeug with ID: " << p_iID << std::endl;
}
Fahrzeug::Fahrzeug(std::string name)
:p_sName(name), p_iID(++p_maxID){
    std::cout << "created new Fahrzeug with ID: " << p_iID << " and name: " << p_sName << std::endl;
}

// Destructor
Fahrzeug::~Fahrzeug(){
    std::cout << "deleted Fahrzeug with ID: " << p_iID << std::endl;
}
