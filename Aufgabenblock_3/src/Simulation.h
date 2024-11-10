#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <vector>
#include <map>
#include "Kreuzung.h"

class Simulation {
public:
    void vEinlesen(std::istream& input, bool mitGrafik = false);
    void vSimulieren();

private:
    std::map<std::string, std::shared_ptr<Kreuzung>> kreuzung_map;
    std::vector<std::shared_ptr<Kreuzung>> kreuzungen;
    std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;
};

#endif // SIMULATION_H