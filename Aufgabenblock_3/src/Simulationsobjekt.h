#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <iostream>
#include <string>
#include <iomanip>

extern double dGlobaleZeit;


class Simulationsobjekt {
public:
    Simulationsobjekt();
    Simulationsobjekt(const std::string& name);
    virtual ~Simulationsobjekt();
    Simulationsobjekt(const Simulationsobjekt&) = delete; // Verbietet den Copy-Konstruktor
    Simulationsobjekt& operator=(const Simulationsobjekt&) = delete; // verbietet Zuweisungsoperator
    virtual void vAusgeben(std::ostream& out) const;
    virtual void vEinlesen(std::istream& in);
    virtual void vSimulieren() = 0; // Rein virtuelle Methode

    bool operator==(const Simulationsobjekt& other) const;

    std::string getName() const;
    int getID() const;

protected:
    static inline int p_maxID = 0;
    std::string p_sName;
    const int p_iID;
    double p_dZeit;
};

#endif /* SIMULATIONSOBJEKT_H_ */