#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken : public Verhalten {
public:
    Parken(Weg& weg, double parkEndZeit);
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
private:
    double p_dParkEndZeit;
};

#endif /* PARKEN_H_ */