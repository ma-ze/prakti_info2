#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#include "Weg.h"
#include "Fahrzeug.h"

class Verhalten {
public:
    // Konstruktor, der eine Referenz auf einen W eg als Parameter bekommt
    Verhalten(Weg& weg): p_Weg(weg) {}
    virtual ~Verhalten() {}
    // Funktion ermittelt, wie weit ein Fahrzeug innerhalb des ubergebenen Zeitintervalls fahren kann, ohne das Wegende zu uberschreiten.
    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

protected:
    Weg& p_Weg;
};

#endif /* VERHALTEN_H_ */