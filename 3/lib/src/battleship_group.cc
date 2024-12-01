#include "../headers/battleship_group.h"

#include <iostream>

std::istream &operator>>(std::istream &in, ShipType &shipType) {
    std::string type;
    in >> type;
    if (type == "aircraft carrier") {
        shipType = ShipType::AIRCRAFT_CARRIER;
    } else if (type == "covering ship") {
        shipType = ShipType::COVERING_SHIP;
    } else if (type == "aircraft carrying cruiser") {
        shipType = ShipType::AIRCRAFT_CARRYING_CRUISER;
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const ShipType &shipType) {
    switch (shipType) {
        case ShipType::AIRCRAFT_CARRIER:
            out << "Aircraft carrier";
            break;
        case ShipType::COVERING_SHIP:
            out << "Covering ship";
            break;
        case ShipType::AIRCRAFT_CARRYING_CRUISER:
            out << "Aircraft carrying cruiser";
            break;
    }
    return out;
}

TBattleshipGroup::TBattleshipGroup() { 
    _admiral = TCaptainInfo();
    _startingPoint = "";
    _destination = "";
    _distance = 0;
}

TBattleshipGroup::TBattleshipGroup(std::string admiralName, std::string admiralRank, size_t admiralExperience, 
                                   const std::string &startingPoint, const std::string &destination, double distance) {
    _admiral = TCaptainInfo(admiralName, admiralRank, admiralExperience);
    _startingPoint = startingPoint;
    _destination = destination;
    _distance = distance;
}

TBattleshipGroup::TBattleshipGroup(std::string admiralName, std::string admiralRank, size_t admiralExperience, 
                                   const std::string &startingPoint, const std::string &destination, double distance,
                                   std::vector<TBattleship> &battleships) {
    _admiral = TCaptainInfo(admiralName, admiralRank, admiralExperience);
    _startingPoint = startingPoint;
    _destination = destination;
    _distance = distance;
    for (auto &battleship : battleships) {
        _battleshipGroup.insert(battleship.getName(), battleship);
    }
}

TBattleshipGroup::TBattleshipGroup(TCaptainInfo &admiral, const std::string &startingPoint, 
                                   const std::string &destination, double distance) {
    _admiral = TCaptainInfo(admiral);
    _startingPoint = startingPoint;
    _destination = destination;
    _distance = distance;
    _battleshipGroup = THashTable<std::string, TBattleship>();
}

TBattleshipGroup::TBattleshipGroup(TCaptainInfo &admiral, const std::string &startingPoint, 
                                   const std::string &destination, double distance, std::vector<TBattleship> &battleships) {
    _admiral = TCaptainInfo(admiral);
    _startingPoint = startingPoint;
    _destination = destination;
    _distance = distance;
    for (auto &battleship : battleships) {
        _battleshipGroup.insert(battleship.getName(), battleship);
    }
}

TBattleshipGroup::TBattleshipGroup(const TBattleshipGroup &battleshipGroup) {
    _admiral = TCaptainInfo(battleshipGroup._admiral);
    _startingPoint = battleshipGroup._startingPoint;
    _destination = battleshipGroup._destination;
    _distance = battleshipGroup._distance;
    _battleshipGroup = THashTable<std::string, TBattleship>(battleshipGroup._battleshipGroup);
}

TBattleshipGroup::TBattleshipGroup(TBattleshipGroup &&battleshipGroup) {
    _admiral = TCaptainInfo(battleshipGroup._admiral);
    _startingPoint = std::move(battleshipGroup._startingPoint);
    _destination = std::move(battleshipGroup._destination);
    _distance = std::move(battleshipGroup._distance);
    _battleshipGroup = std::move(battleshipGroup._battleshipGroup);
}

TPlane &TBattleshipGroup::getPlane(std::string &name, TPlaneType planeType, const std::string &carrierName) {
    TAircraftCarrier *carrier = (TAircraftCarrier *) &getBattleship(carrierName);
    switch (planeType) {
        case TPlaneType::fighter:
            TFighterPlane *plane = (TFighterPlane *) &(carrier->getPlaneInfo().getPlane(name, planeType));
            return *plane;
        case TPlaneType::bomber:
            TBomberPlane *plane = (TBomberPlane *) &(carrier->getPlaneInfo().getPlane(name, planeType));
            return *plane;
    }
}

void TBattleshipGroup::setAdmiral(TCaptainInfo &admiral) {
    setAdmiral(admiral);
}

void TBattleshipGroup::setStartingPoint(const std::string &startingPoint) {
    setStartingPoint(startingPoint);
}

void TBattleshipGroup::setDestination(const std::string &destination) {
    setDestination(destination);
}

void TBattleshipGroup::setDistance(double distance) {
    setDistance(distance);
}

void TBattleshipGroup::relocatePlane(const std::string planeName, const std::string carrierName1, const std::string carrierName2) {
    TBattleship &carrier1 = getBattleship(carrierName1);
    TBattleship &carrier2 = getBattleship(carrierName2);
    relocatePlane(planeName, carrierName1, carrierName2);
}

void TBattleshipGroup::relocatePlane(const std::string planeName, TAircraftCarrier &carrier1, TAircraftCarrier &carrier2) {
    TPlane plane = getPlane(planeName, carrier1.getName());
    TPlaneGroup carrier2_planes = carrier2.getPlaneInfo();
    carrier2_planes.addPlane(plane);
    carrier2.setPlaneInfo(carrier2_planes);
    TPlaneGroup carrier1_planes = carrier1.getPlaneInfo();
    carrier1_planes.deletePlane(plane.getName());
    carrier1.setPlaneInfo(carrier1_planes);
}

void TBattleshipGroup::dump(std::ostream &out) const {
    out << "Admiral: " << _admiral << std::endl;
    out << "Starting point: " << _startingPoint << std::endl;
    out << "Destination: " << _destination << std::endl;
    out << "Distance: " << _distance << std::endl;
    for (auto &i : _battleshipGroup) {
        out << i.value_ << std::endl;
    }
}

void TBattleshipGroup::read(std::istream &in) {
    in >> _admiral >> _startingPoint >> _destination >> _distance;
    size_t amount;
    in >> amount;
    _battleshipGroup = THashTable<std::string, TBattleship>(amount);
    for (size_t i = 0; i < amount; ++i) {
        ShipType shipType;
        in >> shipType;
        TBattleship battleship;
        switch (shipType) {
            case ShipType::AIRCRAFT_CARRIER: {
                TAircraftCarrier aircraftCarrier;
                in >> aircraftCarrier;
                battleship = std::move(aircraftCarrier);
                break;
            }
            case ShipType::COVERING_SHIP: {
                TCoveringShip coveringShip;
                in >> coveringShip;
                battleship = std::move(coveringShip);
                break;
            }
            case ShipType::AIRCRAFT_CARRYING_CRUISER: {
                TAircraftCarryingCruiser aircraftCarryingCruiser;
                TAircraftCarrier aircraftCarrier = std::move(aircraftCarryingCruiser);
                battleship = std::move(aircraftCarrier);
                in >> battleship;
                break;
            }
        }
        _battleshipGroup.insert(battleship.getName(), battleship);
    }
}
