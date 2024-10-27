#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
    Losfahren(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg) {}
    void vBearbeiten() override {
        std::cout << "Fahrausnahme: Losfahren auf " << p_weg.getName() << " mit Fahrzeug " << p_fahrzeug.getName() << std::endl;
    }
};

#endif /* LOSFAHREN_H_ */