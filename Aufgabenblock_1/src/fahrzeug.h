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
	~Fahrzeug();
	void vAusgeben();
	static void vKopf();
	void vSimulieren();

private:
	static inline int p_maxID = 0;
	std::string p_sName = "";
	const int p_iID = 0;
	double p_dMaxGeschwindigkeit = 0; // Maximalgeschwindigkeit des Fahrzeugs (assuming km/h)
	double p_dGesamtStrecke = 0; //die bisher zur¨uckgelegte Gesamtstrecke
	double p_dGesamtZeit = 0; //gesamte Fahrzeit des Objektes
	double p_dZeit = 0; //Zeit, zu der das Fahrzeug zuletzt simuliert wurde
};
#endif /* FAHRZEUG_H_ */
