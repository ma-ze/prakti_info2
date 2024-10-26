/*
 * Fahrrad.cpp
 *
 *  Created on: 13.10.2024
 *      Author: marti
 */
#include "Fahrrad.h"

Fahrrad::Fahrrad(const std::string& name, double maxSpeed) : Fahrzeug(name, maxSpeed)
{}

Fahrrad::~Fahrrad()
{}

double Fahrrad::dGeschwindigkeit() const{
    double geschwindigkeit = p_dMaxGeschwindigkeit;
    double gefahreneStrecke = p_dGesamtStrecke;
    // Berechne den prozentualen Geschwindigkeitsverlust
    double verlustProKm = 0.1 / 20.0; // 10% pro 20km
    double gesamtVerlust = verlustProKm * gefahreneStrecke;
    geschwindigkeit *= (1.0 - gesamtVerlust);

    if (geschwindigkeit < 12.0) {
        geschwindigkeit = 12.0; // Minimalgeschwindigkeit
    }

    return geschwindigkeit;
}