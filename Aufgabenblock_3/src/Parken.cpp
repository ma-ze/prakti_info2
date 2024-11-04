#include "Parken.h"
#include "Losfahren.h"
#include "Floatie.h"

Parken::Parken(Weg &weg, double parkEndZeit) : Verhalten(weg), p_dParkEndZeit(parkEndZeit) {}

double Parken::dStrecke(Fahrzeug & aFzg, double dZeitIntervall){
    if(approximatelyEqual(dGlobaleZeit, p_dParkEndZeit) /* dGlobaleZeit >= p_dParkEndZeit */){
        //std::cout << aFzg.getName() << " sollte losfahren!" << std::endl;
        throw Losfahren(aFzg, p_Weg);
    }
    return 0.0;
}
