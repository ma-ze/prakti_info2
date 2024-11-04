#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
    Losfahren(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg) {}
    void vBearbeiten() override {
        std::cout << std::endl << "🛻 Fahrausnahme: Losfahren auf " << p_weg.getName() << " mit Fahrzeug: "<< std::endl;
        Fahrzeug::vKopf();
        std::cout << p_fahrzeug << std::endl << std::endl;
        p_weg.vAnnahme(p_weg.pAbgabe(p_fahrzeug));
    }
};

#endif /* LOSFAHREN_H_ */