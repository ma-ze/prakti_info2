#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>

Weg::Weg()
    : Simulationsobjekt(), p_dLaenge(0), p_eTempolimit(Tempolimit::Autobahn) {}

Weg::Weg(const std::string& name, double laenge, Tempolimit tempolimit)
    : Simulationsobjekt(name), p_dLaenge(laenge), p_eTempolimit(tempolimit) {}

Weg::~Weg() {}

void Weg::vSimulieren() {
    for (auto& fahrzeug : p_pFahrzeuge) {
        fahrzeug->vSimulieren();
    }
}

void Weg::vAusgeben(std::ostream& out) const {
    Simulationsobjekt::vAusgeben(out);
    out << std::setw(20) << p_dLaenge <<  std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << " (";
    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
        out << (*it)->getName();
        if (std::next(it) != p_pFahrzeuge.end()) {
            out << ", ";
        }
    }
    out << ")";
}

const void Weg::vKopf()
{
    std::cout << std::setw(5) << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
        << "ID" << std::setw(20) << "Name" << std::setw(20) << "Laenge" <<  std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << " Fahrzeuge" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}