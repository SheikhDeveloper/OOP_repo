#include "../headers/aircraft_cruiser.h"

#include <iostream>

TAircraftCarryingCruiser::TAircraftCarryingCruiser():  TAircraftCarrier(), TCoveringShip() {} 

TAircraftCarryingCruiser::TAircraftCarryingCruiser(TWeaponry weaponry, TPlaneGroup planes, TBattleship &shipToCover, const std::string &name, 
    const std::string &captainName, const std::string &captainRank, const size_t experience, double survivability, double speed, 
    size_t crewMembersAmount, double fuelUsage) : 
    TAircraftCarrier(weaponry, planes, name, captainName, captainRank, experience, survivability, speed, crewMembersAmount, fuelUsage),
    TCoveringShip(shipToCover, weaponry, name, captainName, captainRank, experience, survivability, speed, crewMembersAmount, fuelUsage) {}

TAircraftCarryingCruiser::TAircraftCarryingCruiser(const TAircraftCarryingCruiser &aircraftCarryingCruiser) : 
     TAircraftCarrier(aircraftCarryingCruiser), TCoveringShip(aircraftCarryingCruiser) {}

TAircraftCarryingCruiser::TAircraftCarryingCruiser(TAircraftCarryingCruiser &&aircraftCarryingCruiser) : 
     TAircraftCarrier(std::move(aircraftCarryingCruiser)), TCoveringShip(std::move(aircraftCarryingCruiser)) {}

void TAircraftCarryingCruiser::dump(std::ostream &out) const {
    TAircraftCarrier::dump(out);
    getShipToCover().dump(out);
}

void TAircraftCarryingCruiser::read(std::istream &in) {
    TAircraftCarrier::read(in);
    TCoveringShip::readShipToCover(in);
}

TAircraftCarryingCruiser &TAircraftCarryingCruiser::operator=(const TAircraftCarryingCruiser &aircraftCarryingCruiser) {
    TAircraftCarrier::operator=(aircraftCarryingCruiser);
    TCoveringShip::operator=(aircraftCarryingCruiser);
    return *this;
}

TAircraftCarryingCruiser &TAircraftCarryingCruiser::operator=(TAircraftCarryingCruiser &&aircraftCarryingCruiser) {
    TAircraftCarrier::operator=(std::move(aircraftCarryingCruiser));
    TCoveringShip::operator=(std::move(aircraftCarryingCruiser));
    return *this;
}

std::ostream &operator<<(std::ostream &out, const TAircraftCarryingCruiser &aircraftCarryingCruiser) {
    aircraftCarryingCruiser.dump(out);
    return out;
}

std::istream &operator>>(std::istream &in, TAircraftCarryingCruiser &aircraftCarryingCruiser) {
    aircraftCarryingCruiser.read(in);
    return in;
}
