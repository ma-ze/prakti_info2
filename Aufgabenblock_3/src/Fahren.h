#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"

class Fahren : public Verhalten {
public:
    Fahren(Weg& weg);
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif /* FAHREN_H_ */