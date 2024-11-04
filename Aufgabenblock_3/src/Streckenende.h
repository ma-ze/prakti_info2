#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme {
public:
    Streckenende(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg) {}
    void vBearbeiten() override {
        std::cout << "Fahrausnahme: Streckenende auf " << p_weg.getName() << " mit Fahrzeug " << p_fahrzeug.getName() << std::endl;
        p_weg.pAbgabe(p_fahrzeug);
    }
};

#endif /* STRECKENENDE_H_ */