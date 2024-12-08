#include "../headers/aircraft_carrier.h"

TAircraftCarrier::TAircraftCarrier() : TBattleship(), _planes() {}

TAircraftCarrier::TAircraftCarrier(TWeaponry weaponry, TPlaneGroup planes, const std::string &name, const std::string &captainName, 
        const std::string &captainRank, const size_t experience, double survivability, double speed, size_t crewMembersAmount, double fuelUsage) :
    TBattleship(weaponry, name, captainName, captainRank, experience, speed, survivability, crewMembersAmount, fuelUsage),
    _planes(planes) {}

TAircraftCarrier::TAircraftCarrier(const TAircraftCarrier &aircraftCarrier) :
    TBattleship(aircraftCarrier.getWeaponry(), aircraftCarrier.getName(), aircraftCarrier.getCaptain()._name, aircraftCarrier.getCaptain()._rank,
            aircraftCarrier.getCaptain()._experience, aircraftCarrier.getSpeed(), aircraftCarrier.getSurvivability(), 
            aircraftCarrier.getCrewMembersAmount(), aircraftCarrier.getFuelUsage()),
    _planes(aircraftCarrier._planes) {}

TAircraftCarrier::TAircraftCarrier(TAircraftCarrier &&aircraftCarrier) :
    TBattleship(aircraftCarrier.getWeaponry(), std::move(aircraftCarrier.getName()), std::move(aircraftCarrier.getCaptain()._name), 
            std::move(aircraftCarrier.getCaptain()._rank), std::move(aircraftCarrier.getCaptain()._experience), std::move(aircraftCarrier.getSpeed()), 
            std::move(aircraftCarrier.getSurvivability()), std::move(aircraftCarrier.getCrewMembersAmount()), std::move(aircraftCarrier.getFuelUsage())),
    _planes(std::move(aircraftCarrier._planes)) {}

TPlaneGroup & TAircraftCarrier::getPlaneInfo() {
    return _planes;
}

void TAircraftCarrier::addPlane(TPlane &plane) {
    _planes.addPlane(plane);
}

void TAircraftCarrier::deletePlane(const std::string &planeName) {
    _planes.deletePlane(planeName);
}

double TAircraftCarrier::calcPlaneDamage() const {
    return _planes.getTotalDamage();
}

void TAircraftCarrier::setWeaponry(TWeaponry &weaponry) {
    if (weaponry.getType() != WeaponryType::light) {
        throw std::logic_error("Can't set heavy weaponry on an aircraft carrier");
    }
    TBattleship::setWeaponry(weaponry);
}

void TAircraftCarrier::setPlaneInfo(TPlaneGroup &planes) {
    _planes = planes;
}

void TAircraftCarrier::dump(std::ostream &out) const {
    TBattleship::dump(out);
    _planes.dump(out);
}

void TAircraftCarrier::read(std::istream &in) {
    TBattleship::read(in);
    _planes.read(in);
}

TAircraftCarrier &TAircraftCarrier::operator=(const TAircraftCarrier &aircraftCarrier) {
    if (this != &aircraftCarrier) {
        TBattleship::operator=(aircraftCarrier);
        _planes = aircraftCarrier._planes;
    }
    return *this;
}

TAircraftCarrier &TAircraftCarrier::operator=(TAircraftCarrier &&aircraftCarrier) {
    if (this != &aircraftCarrier) {
        TBattleship::operator=(std::move(aircraftCarrier));
        _planes = std::move(aircraftCarrier._planes);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const TAircraftCarrier &aircraftCarrier) {
    aircraftCarrier.dump(out);
    return out;
}

std::istream &operator>>(std::istream &in, TAircraftCarrier &aircraftCarrier) {
    aircraftCarrier.read(in);
    return in;
}
