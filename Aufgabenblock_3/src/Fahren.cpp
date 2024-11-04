#include "Fahren.h"
#include "Floatie.h"
#include "Streckenende.h"

Fahren::Fahren(Weg &weg) : Verhalten(weg) {}

double Fahren::dStrecke(Fahrzeug &aFzg, double dZeitIntervall){
    double geschwindigkeit = aFzg.getGeschwindigkeit();
    //std::cout << aFzg.getName() << ": Geschwindigkeit: " << geschwindigkeit << std::endl;
    if(approximatelyEqual(p_Weg.getLaenge(), aFzg.getAbschnittStrecke())){
        throw Streckenende(aFzg, p_Weg);
        return 0;
    }
    //wenn weg ueberholverbot hat...
    if(p_Weg.getUeberholverbot()){
        std::vector fzPositions = p_Weg.getFzPositions();
        double distToFzgInFront = -1;
        for(auto &fz : fzPositions){
            if(fz[0] == aFzg.getID()){
                continue;
            }
            double abstand = fz[1] - aFzg.getAbschnittStrecke();
            if(abstand > distToFzgInFront) distToFzgInFront = abstand;
        }
          if(distToFzgInFront > 0 && distToFzgInFront < geschwindigkeit * dZeitIntervall){
                return distToFzgInFront - 0.5; //wenn das Fzg in diesem Intervall auf ein anderes Fzg trifft, dann fahre nur bis (0.5km) kurz davor
            }
        
    }

    if(p_Weg.getLaenge() - aFzg.getAbschnittStrecke() < geschwindigkeit * dZeitIntervall){
        return p_Weg.getLaenge() - aFzg.getAbschnittStrecke(); //wenn die verbleibende Strecke kleiner ist als was das Fzg in diesem Intervall fahren wuerde, dann fahre nur die verbleibende Strecke
    }
    return aFzg.getGeschwindigkeit() * dZeitIntervall; //fahre die normal erwartete Strecke
}