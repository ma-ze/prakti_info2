#ifndef WEG_H_
#define WEG_H_

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include <list>
#include <memory>
class Fahrzeug;

class Weg : public Simulationsobjekt {
public:
    Weg();
    Weg(const std::string& name, double laenge, Tempolimit tempolimit = Tempolimit::Autobahn);
    virtual ~Weg();

    void vSimulieren() override;
    void vAusgeben(std::ostream& out) const override;
    static const void vKopf();

    double getLaenge() const;
    double getStreckenLimit() const;
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);
    void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStartZeit);

private:
    double p_dLaenge;
    std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
    Tempolimit p_eTempolimit;
};

#endif /* WEG_H_ */