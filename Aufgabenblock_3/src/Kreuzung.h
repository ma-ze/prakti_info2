#ifndef KREUZUNG_H
#define KREUZUNG_H

#include <vector>
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "PKW.h"

class Kreuzung : public Simulationsobjekt {
public:
    Kreuzung();
    Kreuzung(const std::string& name, double tankstelleVolumen);
    Kreuzung(const Kreuzung& other); // Copy constructor
    Kreuzung& operator=(const Kreuzung& other); // Copy assignment operator

    static void vVerbinde(
        const std::string&  weg_hin, 
        const std::string&  weg_rueck, 
        double              laenge, 
        std::shared_ptr<Kreuzung> kreuzung_start, 
        std::shared_ptr<Kreuzung> kreuzung_ende, 
        Tempolimit          tempolimit = Tempolimit::Autobahn, 
        bool                ueberholverbot = true
    );
    void vTanken(Fahrzeug* fzg);
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartZeit);
    void vEinlesen(std::istream& in) override;
    void vSimulieren() override;
    std::shared_ptr<Weg> pZufaelligerWeg(Weg& ankommenderWeg);

private:
    std::vector<std::shared_ptr<Weg>> p_pWege;
    double p_dTankstelle;
};

#endif // KREUZUNG_H