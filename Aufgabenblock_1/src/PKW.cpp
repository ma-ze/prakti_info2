/*
 * PKW.cpp
 *
 *  Created on: 13.10.2024
 *      Author: marti
 */

#include "PKW.h"
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
    return dMenge;
}

void PKW::vSimulieren()
{
    if(p_dZeit != dGlobaleZeit)
    {
        if(p_dTankinhalt <= 0)
        {
            p_dAktuelleGeschwindigkeit = 0;
            return;
        }
        Fahrzeug::vSimulieren();
        double elapsedTime = dGlobaleZeit - p_dZeit;
        p_dTankinhalt -= p_dVerbrauch * p_dAktuelleGeschwindigkeit * elapsedTime / 100;
    }
}

void PKW::vAusgeben()
{
    Fahrzeug::vAusgeben();
    double gestamtVerbrauch = p_dGesamtStrecke / 100 * p_dVerbrauch;
    std::cout << std::setw(15) << gestamtVerbrauch << std::setw(15) << p_dTankinhalt;
}
