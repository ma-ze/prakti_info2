#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>
#include <string>
#include "Fahrzeug.h"
#include "Weg.h"

class Fahrausnahme : public std::exception {
public:
    Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg) : p_fahrzeug(fahrzeug), p_weg(weg) {}
    virtual void vBearbeiten() = 0;

protected:
    Fahrzeug& p_fahrzeug;
    Weg& p_weg;


};

#endif /* FAHRAUSNAHME_H_ */