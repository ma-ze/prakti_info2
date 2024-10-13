/*
 * Fahrrad.h
 *
 *  Created on: 13.10.2024
 *      Author: marti
 */
#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
public:
    Fahrrad(const std::string& name, double maxSpeed);
    virtual ~Fahrrad();

private:
    double dGeschwindigkeit() override;

};

#endif /* FAHRRAD_H_ */