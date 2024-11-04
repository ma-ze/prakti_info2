/*
 * PKW.cpp
 *
 *  Created on: 13.10.2024
 *      Author: marti
 */

#include "PKW.h"
#include "Verhalten.h"
#include "SimuClient.h"

PKW::PKW(const std::string &name, double maxSpeed, double verbrauch)
: Fahrzeug(name, maxSpeed), p_dVerbrauch(verbrauch)
{
}

PKW::PKW(const std::string &name, double maxSpeed, double verbrauch, double tankvolumen)
: Fahrzeug(name, maxSpeed), p_dVerbrauch(verbrauch), p_dTankvolumen(tankvolumen), p_dTankinhalt(tankvolumen/2)
{
}

PKW::~PKW()
{
}

double PKW::dTanken(double dMenge)
{
    if(dMenge < p_dTankvolumen - p_dTankinhalt) //max. Tankinhalt wird nicht überschritten
    {
        p_dTankinhalt += dMenge;
    }
    else //volltanken
    {
        dMenge = p_dTankvolumen - p_dTankinhalt;
        p_dTankinhalt = p_dTankvolumen;
    }
    p_bLiegengeblieben = false;
    return dMenge;
}

void PKW::vSimulieren()
{
    if(p_dZeit != dGlobaleZeit)
    {
        double strecke = p_dGesamtStrecke;
        Fahrzeug::vSimulieren();
        strecke = p_dGesamtStrecke - strecke;  
        p_dTankinhalt -= (p_dVerbrauch * strecke / 100);
        if(p_dTankinhalt < 0){
            p_dTankinhalt = 0;
            p_bLiegengeblieben = true;
        }
    }
}

void PKW::vAusgeben(std::ostream& out) const{
    Fahrzeug::vAusgeben(out);
    double gestamtVerbrauch = p_dGesamtStrecke / 100 * p_dVerbrauch;
    out << std::setw(15) << gestamtVerbrauch << std::setw(15) << p_dTankinhalt;
}

void PKW::vZeichnen(Weg &weg) const{
    bZeichnePKW(p_sName, weg.getName(), p_dAbschnittStrecke / weg.getLaenge(), dGeschwindigkeit(), p_dTankinhalt);
}

double PKW::dGeschwindigkeit() const{
    if(p_dTankinhalt <= 0)
    {
        return 0;
    }
    else return std::min(p_pVerhalten->getWeg().getStreckenLimit(), p_dMaxGeschwindigkeit);
}
