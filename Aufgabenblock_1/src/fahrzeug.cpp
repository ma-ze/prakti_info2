/*
 * Fahrzeug.cpp
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
Fahrzeug::Fahrzeug(std::string name, double maxGeschwindigkeit)
:p_sName(name), p_dMaxGeschwindigkeit(maxGeschwindigkeit < 0 ? -maxGeschwindigkeit : maxGeschwindigkeit), p_iID(++p_maxID){
    std::cout << "created new Fahrzeug with ID: " << p_iID << " and name: " << p_sName << " and maxGeschwindigkeit: " << p_dMaxGeschwindigkeit << std::endl;
}
// Destructor
Fahrzeug::~Fahrzeug(){
    
}
// Methods
void Fahrzeug::vAusgeben(){
    std::cout << std::setw(5) << std::setprecision(2) << std::setiosflags(std::ios::fixed) << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
    << p_iID << std::setw(20) << p_sName << std::setw(20) << p_dMaxGeschwindigkeit << std::setw(15) << p_dGesamtStrecke << std::setw(15) << p_dGesamtZeit << std::setw(15) << p_dZeit;
}
const void Fahrzeug::vKopf(){
    std::cout << std::setw(5)<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
    << "ID" << std::setw(20) << "Name" << std::setw(20) << "MaxGeschwindigkeit" << std::setw(15) << "GesamtStrecke" << std::setw(15) 
    << "GesamtZeit" << std::setw(15) << "Zeit" << std::endl << std::setw(15) << "GesamtVerbrauch" << std::setw(15) << "Tankinhalt" << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------------------------------------------------";
}
void Fahrzeug::vSimulieren(){
    if(p_dZeit != dGlobaleZeit){
        double elapsedTime = dGlobaleZeit - p_dZeit;
        p_dGesamtStrecke += p_dAktuelleGeschwindigkeit * elapsedTime;
        p_dGesamtZeit += elapsedTime;
        p_dZeit = dGlobaleZeit;
    }
}
double Fahrzeug::dTanken(double dMenge)
{
    return 0.0;
}