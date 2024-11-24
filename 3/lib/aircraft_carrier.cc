#include "aircraft_carrier.h"


TAircraftCarrier::TAircraftCarrier(TWeaponry weaponry, TPlaneGroup planes, const std::string &name, const std::string &captainName, 
        const std::string &captainRank, const size_t experience, double survivability, size_t crewMembersAmount) :
    TBattleship(weaponry, name, captainName, captainRank, experience, 0., survivability, crewMembersAmount),
    _planes(planes) {}

TAircraftCarrier::TAircraftCarrier(const TAircraftCarrier &aircraftCarrier) :
    TBattleship(aircraftCarrier.getWeaponry(), aircraftCarrier.getName(), aircraftCarrier.getCaptain()._name, aircraftCarrier.getCaptain()._rank,
            aircraftCarrier.getCaptain()._experience, 0., aircraftCarrier.getSurvivability(), aircraftCarrier.getCrewMembersAmount()),
    _planes(aircraftCarrier._planes) {}

TAircraftCarrier::TAircraftCarrier(TAircraftCarrier &&aircraftCarrier) :
    TBattleship(std::move(aircraftCarrier.getWeaponry()), std::move(aircraftCarrier.getName()), std::move(aircraftCarrier.getCaptain()._name), 
            std::move(aircraftCarrier.getCaptain()._rank), std::move(aircraftCarrier.getCaptain()._experience), 0., 
            std::move(aircraftCarrier.getSurvivability()), std::move(aircraftCarrier.getCrewMembersAmount())),
    _planes(std::move(aircraftCarrier._planes)) {}

std::pair<size_t, TPlaneGroup> TAircraftCarrier::getPlaneInfo() const {
    return {_planes.size(), _planes};
}

double TAircraftCarrier::calcPlaneDamage() const {
    return _planes.getTotalDamage();
}

void TAircraftCarrier::setPlaneInfo(TPlaneGroup planes) {
    _planes = planes;
}

void TAircraftCarrier::setPlaneType(TPlane &plane) {
    _planes.addPlane(plane);
}

void TAircraftCarrier::dump(std::ostream &out) const {
    TBattleship::dump(out);
    _planes.dump(out);
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
