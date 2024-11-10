#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "PKW.h"
#include <iostream>
#include <iomanip>

Weg::Weg()
    : Simulationsobjekt(), p_dLaenge(0), 
      p_eTempolimit(Tempolimit::Autobahn) {}

Weg::Weg(const std::string& name, double laenge, Tempolimit tempolimit, bool ueberholverbot, std::shared_ptr<Kreuzung> zielkreuzung, std::shared_ptr<Weg> rueckweg)
    : Simulationsobjekt(name),
      p_dLaenge(laenge),
      p_eTempolimit(tempolimit),
      p_bUeberholverbot(ueberholverbot),
      p_pZielkreuzung(zielkreuzung),
      p_pRueckweg(rueckweg) {}

Weg::~Weg() {}

void Weg::vSimulieren() {
    p_pFahrzeuge.vAktualisieren();
    for (auto& fahrzeugPtr : p_pFahrzeuge) {
        try{
            fahrzeugPtr->vSimulieren();
            fahrzeugPtr->vZeichnen(*this);
        }
        catch(Fahrausnahme& e) {
            e.vBearbeiten();
        }
        catch(std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
    }
    p_pFahrzeuge.vAktualisieren();
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
    if(fahrzeug == nullptr){
        return;
    }
    fahrzeug->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(std::move(fahrzeug));
}
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartZeit){
    if(fahrzeug == nullptr){
        return;
    }
    fahrzeug->vNeueStrecke(*this, dStartZeit);
    p_pFahrzeuge.push_front(std::move(fahrzeug));
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug &fahrzeug){
    for(auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it){
        if(*it == nullptr){
            continue;
        }
        if(**it == fahrzeug){
            std::unique_ptr<Fahrzeug> tempFz = std::move(*it);
            p_pFahrzeuge.erase(it);
            return tempFz;
        }
    }
    return nullptr;
}
bool Weg::getUeberholverbot() const{
    return p_bUeberholverbot;
}

std::vector<std::vector<double>> Weg::getFzPositions() const{
    //vector mit allen Fahrzeugen auf diesem Weg und deren abschnittStrecke
    std::vector<std::vector<double>> fahrzeuge;
    for(auto &f : p_pFahrzeuge){
        if(f == nullptr){
            continue;
        }
        if(f->bLiegengeblieben()){
            continue;
        }
        std::vector<double> temp;
        temp.push_back(f->getID());
        temp.push_back(f->getAbschnittStrecke());
        fahrzeuge.push_back(temp);
    }
    return fahrzeuge;
}
/**
 * This function uses the lock() method to convert the weak pointer p_pZielkreuzung
 * to a shared pointer. The lock() method attempts to create a shared_ptr that 
 * shares ownership of the object managed by the weak_ptr. If the weak_ptr is 
 * expired, the returned shared_ptr will be empty.
 */
std::shared_ptr<Kreuzung> Weg::getZielkreuzung() const{
    return p_pZielkreuzung.lock();
}

std::shared_ptr<Weg> Weg::getRueckweg() const{
    return p_pRueckweg.lock();
}

void Weg::setRueckweg(const std::shared_ptr<Weg> &rueckweg){
    p_pRueckweg = rueckweg;
}
