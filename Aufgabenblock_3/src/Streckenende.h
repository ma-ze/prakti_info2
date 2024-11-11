#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme {
public:
    Streckenende(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg) {}
    void vBearbeiten() override {
        
        std::cout << std::endl << "🔄 Fahrausnahme: Streckenende auf " << p_weg.getName() << " mit Fahrzeug: " << std::endl;
        std::unique_ptr<Fahrzeug> fz = p_weg.pAbgabe(p_fahrzeug);
        std::shared_ptr<Weg> zielweg = p_weg.getZielkreuzung()->pZufaelligerWeg(p_weg);
        p_weg.getZielkreuzung()->vTanken(fz.get());
        zielweg->vAnnahme(std::move(fz));
        std::cout << "ZEIT: " << dGlobaleZeit << std::endl;
        std::cout << "KREUZUNG: " << p_weg.getZielkreuzung()->getName() << std::endl;
        std::cout << "WECHSEL: " << p_weg.getName() << " -> " << zielweg->getName() << std::endl;
        std::cout << "FAHRZEUG: " << std::endl;
        Fahrzeug::vKopf();
        std::cout << p_fahrzeug << std::endl << std::endl;
    }
};

#endif /* STRECKENENDE_H_ */