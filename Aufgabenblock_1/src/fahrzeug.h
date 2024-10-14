/*
 * Fahrzeug.h
 *
 *  Created on: 11.10.2024
 *      Author: marti
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <iostream>
#include <string>
#include <iomanip>

extern double dGlobaleZeit;

class Fahrzeug
{
public:
	Fahrzeug();
	Fahrzeug(std::string name);
	Fahrzeug(std::string name, double maxGeschwindigkeit);
	virtual ~Fahrzeug();
	Fahrzeug(const Fahrzeug&) = delete; // Verbietet den Copy-Konstruktor
	Fahrzeug& operator=(const Fahrzeug& other); // Zuweisungsoperator
	virtual void vAusgeben(std::ostream& out);
	static const void vKopf();
	virtual void vSimulieren();
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
	bool operator<(const Fahrzeug& other) const;

protected:
	static inline int p_maxID = 0;
	std::string p_sName = "";
	int p_iID = 0;
	double p_dMaxGeschwindigkeit = 0; // Maximalgeschwindigkeit des Fahrzeugs (assuming km/h)
	double p_dGesamtStrecke = 0; //die bisher zur¨uckgelegte Gesamtstrecke
	double p_dGesamtZeit = 0; //gesamte Fahrzeit des Objektes
	double p_dZeit = 0; //Zeit, zu der das Fahrzeug zuletzt simuliert wurde
	virtual double dGeschwindigkeit();
};
#endif /* FAHRZEUG_H_ */
