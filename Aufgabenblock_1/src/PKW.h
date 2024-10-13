/*
 * PKW.h
 *
 *  Created on: 13.10.2024
 *      Author: marti
 */

#ifndef PKW_H_
#define PKW_H_

#include "Fahrzeug.h"

class PKW : public Fahrzeug {
public:
    PKW(const std::string& name, double maxSpeed, double verbrauch);
    PKW(const std::string& name, double maxSpeed, double verbrauch, double tankvolumen);
    virtual ~PKW();
    double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
    void vSimulieren() override;
    void vAusgeben() override;

private:
    double p_dVerbrauch = 0; // Verbrauch des PKW (l/100km)
    double p_dTankvolumen = 55; // Tankvolumen des PKW (l)
    double p_dTankinhalt = 55/2; // Tankinhalt des PKW (l)
};

#endif /* PKW_H_ */