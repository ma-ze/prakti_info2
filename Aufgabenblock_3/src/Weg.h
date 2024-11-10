#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "Kreuzung.h"
#include <list>
#include <memory>
#include "vertagt_liste.h"
#include "vertagt_aktion.h"

class Fahrzeug;
class Kreuzung;

class Weg : public Simulationsobjekt {
public:
    Weg();
    Weg(const std::string& name, 
        double laenge, 
        Tempolimit tempolimit = Tempolimit::Autobahn, 
        bool ueberholverbot = true, 
        std::shared_ptr<Kreuzung> zielkreuzung = nullptr, 
        std::shared_ptr<Weg> rueckweg = nullptr);
    virtual ~Weg();

    void vSimulieren() override;
    void vAusgeben(std::ostream& out) const override;
    static const void vKopf();

    double getLaenge() const;
    double getStreckenLimit() const;
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartZeit);
    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);
    bool getUeberholverbot() const;
    std::vector<std::vector<double>> getFzPositions() const;

    std::shared_ptr<Kreuzung> getZielkreuzung() const;
    std::shared_ptr<Weg> getRueckweg() const;
    void setRueckweg(const std::shared_ptr<Weg>& rueckweg);

private:
    double p_dLaenge;
    vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
    Tempolimit p_eTempolimit;
    bool p_bUeberholverbot;
    const std::weak_ptr<Kreuzung> p_pZielkreuzung;
    std::weak_ptr<Weg> p_pRueckweg;
};

#endif /* WEG_H_ */