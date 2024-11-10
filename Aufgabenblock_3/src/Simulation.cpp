#include "Simulation.h"
#include <sstream>
#include <string>
#include <iostream>
#include <memory>
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimuClient.h"

void Simulation::vEinlesen(std::istream& input, bool mitGrafik) {
    if(mitGrafik){
        bInitialisiereGrafik(2000, 2000);
    }
    std::string line;
    int line_number = 0;
    while (std::getline(input, line)) {
        line_number++;
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        try{
            if (command == "KREUZUNG") {
                std::string name;
                double tankstelleVolumen;
                iss >> name >> tankstelleVolumen;
                kreuzungen.push_back(std::make_shared<Kreuzung>(name, tankstelleVolumen));
                if (kreuzung_map.find(name) != kreuzung_map.end()) {
                    throw std::runtime_error("Kreuzung with name " + name + " already exists. Error at line: " + std::to_string(line_number));
                }
                kreuzung_map[name] = kreuzungen.back();
                if(mitGrafik){
                    int xcoord, ycoord;
                    iss >> xcoord >> ycoord;
                    bZeichneKreuzung(xcoord, ycoord);
                }
            } 
            else if (command == "STRASSE") {
                std::string kreuzungStart, kreuzungEnde;
                std::string name_w1, name_w2;
                double laenge;
                Tempolimit tempolimit;
                bool ueberholverbot;
                iss >> kreuzungStart >> kreuzungEnde >> name_w1 >> name_w2;
                std::string laengeStr, tempolimitStr, ueberholverbotStr;
                iss >> laengeStr >> tempolimitStr >> ueberholverbotStr;
                laenge = std::stod(laengeStr);
                tempolimit = static_cast<Tempolimit>(std::stoi(tempolimitStr));
                ueberholverbot = std::stoi(ueberholverbotStr);
                std::shared_ptr<Kreuzung> kr_start = nullptr;
                std::shared_ptr<Kreuzung> kr_ende = nullptr;
                if (kreuzung_map.find(kreuzungStart) != kreuzung_map.end()) {
                    kr_start = kreuzung_map[kreuzungStart];
                }
                else {
                    throw std::runtime_error("Kreuzung with name " + kreuzungStart + " not found. Error at line: " + std::to_string(line_number));
                }
                if (kreuzung_map.find(kreuzungEnde) != kreuzung_map.end()) {
                    kr_ende = kreuzung_map[kreuzungEnde];
                }
                else {
                    throw std::runtime_error("Kreuzung with name " + kreuzungEnde + " not found. Error at line: " + std::to_string(line_number));
                }
                if (kr_start != nullptr && kr_ende != nullptr) {
                    kr_start->vVerbinde(name_w1, name_w2, laenge, kr_start, kr_ende, tempolimit, ueberholverbot);
                }
                if(mitGrafik){
                    int anzahlcoords;
                    iss >> anzahlcoords;
                    int* coords = new int[anzahlcoords*2];
                    for(int i = 0; i < anzahlcoords*2; i++){
                        iss >> coords[i];
                    }
                    bZeichneStrasse(name_w1, name_w2, laenge, anzahlcoords, coords);
                }
            }
            else if (command == "PKW") {
                std::string name;
                double maxSpeed;
                double verbrauch;
                double tankvolumen;
                std::string start_kr, startzeitStr;
                double startzeit;
                iss >> name >> maxSpeed >> verbrauch >> tankvolumen >> start_kr >> startzeitStr;
                startzeit = std::stod(startzeitStr);
                fahrzeuge.push_back(std::make_unique<PKW>(name, maxSpeed, verbrauch, tankvolumen));
                if (kreuzung_map.find(start_kr) != kreuzung_map.end()) {
                    kreuzung_map[start_kr]->vAnnahme(std::move(fahrzeuge.back()), startzeit);
                }
                else {
                    throw std::runtime_error("Kreuzung with name " + start_kr + " not found. Error at line: " + std::to_string(line_number));
                }
            }
            else if (command == "FAHRRAD") {
                std::string name;
                double maxSpeed;
                std::string start_kr, startzeitStr;
                double startzeit;
                iss >> name >> maxSpeed >> start_kr >> startzeitStr;
                startzeit = std::stod(startzeitStr);
                fahrzeuge.push_back(std::make_unique<Fahrrad>(name, maxSpeed));
                if (kreuzung_map.find(start_kr) != kreuzung_map.end()) {
                    kreuzung_map[start_kr]->vAnnahme(std::move(fahrzeuge.back()), startzeit);
                }
                else {
                    throw std::runtime_error("Kreuzung with name " + start_kr + " not found. Error at line: " + std::to_string(line_number));
                }
            }
            else{
                throw std::runtime_error("Unknown command: " + command + " at line: " + std::to_string(line_number));
            }
        }
        catch(std::exception &e){
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
void Simulation::vSimulieren() {
    for(auto &kr : kreuzungen){
        kr->vSimulieren();
    }
}