#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include <iostream>
#include <iomanip>

Weg::Weg()
    : Simulationsobjekt(), p_dLaenge(0), p_eTempolimit(Tempolimit::Autobahn) {}

Weg::Weg(const std::string& name, double laenge, Tempolimit tempolimit)
    : Simulationsobjekt(name), p_dLaenge(laenge), p_eTempolimit(tempolimit) {}

Weg::~Weg() {}

void Weg::vSimulieren() {
    for (auto& fahrzeug : p_pFahrzeuge) {
        try{
            fahrzeug->vSimulieren();
        }
        catch(Fahrausnahme& e) {
            e.vBearbeiten();
        }
        catch(std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
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

double Weg::getLaenge() const {
    return p_dLaenge;
}

double Weg::getStreckenLimit() const
{
    return getTempolimit(p_eTempolimit);
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug){
    fahrzeug->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(std::move(fahrzeug));
}
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartZeit){
    fahrzeug->vNeueStrecke(*this, dStartZeit);
    p_pFahrzeuge.push_front(std::move(fahrzeug));
}
