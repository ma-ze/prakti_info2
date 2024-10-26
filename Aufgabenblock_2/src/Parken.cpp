#include "Parken.h"


Parken::Parken(Weg &weg, double parkEndZeit) : Verhalten(weg), p_dParkEndZeit(parkEndZeit) {}

double Parken::dStrecke(Fahrzeug & aFzg, double dZeitIntervall){
    if(dGlobaleZeit >= p_dParkEndZeit){
        std::cout << aFzg.getName() << " sollte losfahren!" << std::endl;
    }
    return 0.0;
}
