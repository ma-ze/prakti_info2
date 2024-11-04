/*
 * Fahrzeug.cpp
 *
 *  Created on: 11.10.2024
 *      Author: marti
 */

#include "Fahrzeug.h"
#include "Fahren.h"
#include "Parken.h"
#include "Weg.h"

// Constructor
Fahrzeug::Fahrzeug()
:Simulationsobjekt(){}
Fahrzeug::Fahrzeug(std::string name)
:Simulationsobjekt(name){}
Fahrzeug::Fahrzeug(std::string name, double maxGeschwindigkeit)
:Simulationsobjekt(name), p_dMaxGeschwindigkeit(maxGeschwindigkeit < 0 ? -maxGeschwindigkeit : maxGeschwindigkeit){}
// Destructor
Fahrzeug::~Fahrzeug(){}
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {
    if (this != &other) {
        p_sName = other.p_sName + "_copy";
        p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
        //p_iID = ++p_maxID; do not change the ID because this already has an ID
    }
    return *this;
}
void Fahrzeug::vAusgeben(std::ostream& out) const {
    Simulationsobjekt::vAusgeben(out);
    out << std::setw(20) << p_dMaxGeschwindigkeit << std::setw(15) << p_dGesamtStrecke << std::setw(15) 
    << p_dAbschnittStrecke << std::setw(15) << p_dGesamtZeit << std::setw(15) << p_dZeit;
}
const void Fahrzeug::vKopf() {
    std::cout << std::setw(5)<< std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
    << "ID" << std::setw(20) << "Name" << std::setw(20) << "MaxGeschwindigkeit" << std::setw(15) << "GesamtStrecke" << std::setw(15)
    << "AbschnittStrecke" << std::setw(15) << "GesamtZeit" << std::setw(15) << "Zeit" << std::setw(15) << "GesamtVerbrauch" << std::setw(15) << "Tankinhalt" << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
}
void Fahrzeug::vSimulieren(){
    if(p_dZeit != dGlobaleZeit){
        double elapsedTime = dGlobaleZeit - p_dZeit;
        double deltaStrecke = p_pVerhalten->dStrecke(*this, elapsedTime);
        p_dGesamtStrecke += deltaStrecke;
        p_dAbschnittStrecke += deltaStrecke;
        p_dGesamtZeit += elapsedTime;
        p_dZeit = dGlobaleZeit;
    }
}
double Fahrzeug::dTanken(double dMenge){
    return 0.0;
}

bool Fahrzeug::operator<(const Fahrzeug &other) const{
    return p_dGesamtStrecke < other.p_dGesamtStrecke;
}

double Fahrzeug::dGeschwindigkeit() const{
    return p_dMaxGeschwindigkeit;
}

double Fahrzeug::getGeschwindigkeit() const{
    return dGeschwindigkeit();
}
double Fahrzeug::getGesamtStrecke() const{
    return p_dGesamtStrecke;
}
double Fahrzeug::getAbschnittStrecke() const{
    return p_dAbschnittStrecke;
}

void Fahrzeug::vNeueStrecke(Weg &weg){
    p_pVerhalten = std::make_unique<Fahren>(weg);
    //Frage aus Skript: p_pVerhalten ist ein unique_ptr, daher wird die alte Instanz automatisch gelöscht
    p_dAbschnittStrecke = 0;
}
void Fahrzeug::vNeueStrecke(Weg &weg, double dStartZeit){
    p_pVerhalten = std::make_unique<Parken>(weg, dStartZeit);
    p_dAbschnittStrecke = 0;
}

void Fahrzeug::vZeichnen(Weg &weg) const{}
