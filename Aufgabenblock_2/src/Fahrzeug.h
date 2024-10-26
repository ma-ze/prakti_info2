/*
 * Fahrzeug.h
 *
 *  Created on: 11.10.2024
 *      Author: marti
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"

class Fahrzeug : public Simulationsobjekt {
public:
    Fahrzeug();
    Fahrzeug(const std::string name);
    Fahrzeug(const std::string name, double maxGeschwindigkeit);
    virtual ~Fahrzeug();

    Fahrzeug& operator=(const Fahrzeug& other); // Zuweisungsoperator
    static const void vKopf();
    virtual void vAusgeben(std::ostream& out) const override;
    virtual void vSimulieren() override;
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());

    bool operator<(const Fahrzeug& other) const;

protected:
    double p_dMaxGeschwindigkeit = 0; // Maximalgeschwindigkeit des Fahrzeugs (assuming km/h)
	double p_dGesamtStrecke = 0; //die bisher zurückgelegte Gesamtstrecke
	double p_dGesamtZeit = 0; //gesamte Fahrzeit des Objektes

    virtual double dGeschwindigkeit() const;
};

#endif /* FAHRZEUG_H_ */