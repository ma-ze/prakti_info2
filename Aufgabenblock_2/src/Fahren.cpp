#include "Fahren.h"
#include "Floatie.h"
#include "Streckenende.h"

Fahren::Fahren(Weg &weg) : Verhalten(weg) {}

double Fahren::dStrecke(Fahrzeug &aFzg, double dZeitIntervall){
    double geschwindigkeit = aFzg.getGeschwindigkeit();
    std::cout << aFzg.getName() << ": Geschwindigkeit: " << geschwindigkeit << std::endl;
    if(approximatelyEqual(p_Weg.getLaenge(), aFzg.getAbschnittStrecke())){
        //std::cout << std::endl << "Fahrzeug " << aFzg.getName() <<" hat das Ende des Weges erreicht!" << std::endl << std::endl;
        throw Streckenende(aFzg, p_Weg);
        return 0;
    }
    if(p_Weg.getLaenge() - aFzg.getAbschnittStrecke() < geschwindigkeit * dZeitIntervall){
        return p_Weg.getLaenge() - aFzg.getAbschnittStrecke();
    }
    return aFzg.getGeschwindigkeit() * dZeitIntervall;
}