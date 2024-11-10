#include "Kreuzung.h"
#include "PKW.h"

Kreuzung::Kreuzung() : Simulationsobjekt() {}
Kreuzung::Kreuzung(const std::string &name, double tankstelleVolumen) : Simulationsobjekt(name), p_dTankstelle(tankstelleVolumen) {}

Kreuzung::Kreuzung(const Kreuzung& other) 
    : Simulationsobjekt(other.p_sName), p_pWege(other.p_pWege), p_dTankstelle(other.p_dTankstelle) {}

Kreuzung& Kreuzung::operator=(const Kreuzung& other) {
    if (this != &other) {
        p_sName = other.p_sName + "_copy";
        p_pWege = other.p_pWege;
        p_dTankstelle = other.p_dTankstelle;
    }
    return *this;
}

void Kreuzung::vVerbinde(const std::string &weg_hin, const std::string &weg_rueck, double laenge,
                         std::shared_ptr<Kreuzung> kreuzung_start, std::shared_ptr<Kreuzung> kreuzung_ende, Tempolimit tempolimit, bool ueberholverbot)
{
    std::shared_ptr<Weg> hin = std::make_shared<Weg>(weg_hin, laenge, tempolimit, ueberholverbot, kreuzung_ende, nullptr);
    std::shared_ptr<Weg> rueck = std::make_shared<Weg>(weg_rueck, laenge, tempolimit, ueberholverbot, kreuzung_start, hin);
    hin->setRueckweg(rueck);
    kreuzung_start->p_pWege.push_back(hin);
    kreuzung_ende->p_pWege.push_back(rueck);
}
void Kreuzung::vTanken(Fahrzeug *fzg){
    if(fzg == nullptr || p_dTankstelle <= 0){
        return;
    }

    // Use dynamic_cast to check if fzg is a PKW
    PKW* pkw = dynamic_cast<PKW*>(fzg);
    if(pkw != nullptr){
        // fzg is a PKW
        double tankmenge = pkw->dTanken();
        p_dTankstelle -= tankmenge;
    }
}
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartZeit){
    if (!p_pWege.empty()) {
        vTanken(fahrzeug.get());
        p_pWege.front()->vAnnahme(std::move(fahrzeug), dStartZeit);
    }
}

void Kreuzung::vSimulieren()
{
    for(auto &weg : p_pWege){
        weg->vSimulieren();
    }
}

std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg &ankommenderWeg){
    std::vector<std::shared_ptr<Weg>> moeglicheWege;
    for (auto &weg : p_pWege) {
        if (weg.get() != ankommenderWeg.getRueckweg().get()) {
            moeglicheWege.push_back(weg);
        } 
    }

    if (moeglicheWege.empty()) {
    return ankommenderWeg.getRueckweg();
    }

    int zufaelligerIndex = rand() % moeglicheWege.size();
    return moeglicheWege[zufaelligerIndex];
}

void Kreuzung::vEinlesen(std::istream &in) {
    in >> p_sName >> p_dTankstelle;
}