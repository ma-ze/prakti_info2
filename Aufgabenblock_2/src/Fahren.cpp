#include "Fahren.h"
#include "Floatie.h"

Fahren::Fahren(Weg &weg) : Verhalten(weg) {}

double Fahren::dStrecke(Fahrzeug &aFzg, double dZeitIntervall){
    double geschwindigkeit = std::min(aFzg.getGeschwindigkeit(), p_Weg.getStreckenLimit());
    std::cout << aFzg.getName() << ": Geschwindigkeit: " << geschwindigkeit << std::endl;
    if(approximatelyEqual(p_Weg.getLaenge(), aFzg.getAbschnittStrecke())){
        std::cout << std::endl << "Fahrzeug " << aFzg.getName() <<" hat das Ende des Weges erreicht!" << std::endl << std::endl;
        return 0;
    }
    if(p_Weg.getLaenge() - aFzg.getAbschnittStrecke() < geschwindigkeit * dZeitIntervall){
        return p_Weg.getLaenge() - aFzg.getAbschnittStrecke();
    }
    return aFzg.getGeschwindigkeit() * dZeitIntervall;
}