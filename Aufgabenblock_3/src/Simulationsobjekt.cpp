#include "Simulationsobjekt.h"

Simulationsobjekt::Simulationsobjekt()
    : p_sName(""), p_iID(++p_maxID), p_dZeit(0.0) {
    std::cout << "created new Simulationsobjekt with ID: " << p_iID << std::endl;
}

Simulationsobjekt::Simulationsobjekt(const std::string& name)
    : p_sName(name), p_iID(++p_maxID), p_dZeit(0.0) {
    std::cout << "created new Simulationsobjekt with ID: " << p_iID << " and name: " << p_sName << std::endl;
}

Simulationsobjekt::~Simulationsobjekt() {
    std::cout << "deleted Simulationsobjekt with ID: " << p_iID << std::endl;
}

void Simulationsobjekt::vAusgeben(std::ostream &out) const
{
    out << std::setw(5) << std::setprecision(2) << std::setiosflags(std::ios::fixed) << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
        << p_iID << std::setw(20) << p_sName;
}

bool Simulationsobjekt::operator==(const Simulationsobjekt &other) const{
    return p_iID == other.p_iID;
}

std::ostream& operator<<(std::ostream& out, const Simulationsobjekt& obj) {
    obj.vAusgeben(out);
    return out;
}
std::string Simulationsobjekt::getName() const {
    return p_sName;
}

int Simulationsobjekt::getID() const {
    return p_iID;
}