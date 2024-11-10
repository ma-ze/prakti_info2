/*
 * Fahrzeug.h
 *
 *  Created on: 11.10.2024
 *      Author: marti
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"

class Verhalten;
class Weg;

std::ostream& operator<<(std::ostream& out, Simulationsobjekt& so);
std::istream& operator>>(std::istream& in, Simulationsobjekt& obj);


class Fahrzeug : public Simulationsobjekt {
public:
    Fahrzeug();
    Fahrzeug(const std::string name);
    Fahrzeug(const std::string name, double maxGeschwindigkeit);
    virtual ~Fahrzeug();

    Fahrzeug& operator=(const Fahrzeug& other); // Zuweisungsoperator
    static const void vKopf();
    virtual void vAusgeben(std::ostream& out) const override;
    virtual void vEinlesen(std::istream& in) override;
    virtual void vSimulieren() override;
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

    bool operator<(const Fahrzeug& other) const;

    double getGeschwindigkeit() const;
    double getGesamtStrecke() const;
    double getAbschnittStrecke() const;
    void vNeueStrecke(Weg& weg);
    void vNeueStrecke(Weg& weg, double dStartZeit);
    virtual void vZeichnen(Weg& weg) const;
    bool bLiegengeblieben() const;

protected:
    double p_dMaxGeschwindigkeit = 0; // Maximalgeschwindigkeit des Fahrzeugs (assuming km/h)
	double p_dGesamtStrecke = 0; //die bisher zurückgelegte Gesamtstrecke
	double p_dGesamtZeit = 0; //gesamte Fahrzeit des Objektes
    double p_dAbschnittStrecke = 0; //die Strecke, die das Fahrzeug auf dem aktuellen Weg zurückgelegt hat
    virtual double dGeschwindigkeit() const;
    std::unique_ptr<Verhalten> p_pVerhalten;
    bool p_bLiegengeblieben = false;
};

#endif /* FAHRZEUG_H_ */