#include "../headers/battleship_group.h"

#include <iostream>
#include <thread>

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
    try {
        TAircraftCarrier &carrier = dynamic_cast<TAircraftCarrier &>(getBattleship(carrierName));
        return carrier.getPlaneInfo().getPlane(name, planeType);
    }
    catch (std::bad_cast &e) {
        throw std::invalid_argument("Wrong carrier name");
    }
    catch (std::exception &e) {
        throw e;
    }
}

TBattleship &TBattleshipGroup::getBattleship(const std::string &name) {
    return _battleshipGroup[name];
}

size_t TBattleshipGroup::getShipAmount(ShipType shipType) const {
    size_t amount = 0;
    for (auto &battleship : _battleshipGroup) {
        switch (shipType) {
            case ShipType::AIRCRAFT_CARRIER:
                try {
                    TAircraftCarrier &carrier = dynamic_cast<TAircraftCarrier &>(battleship.value_);
                    amount++;
                    carrier.getPlaneInfo();
                }
                catch (std::exception &e) {
                    break;
                }
                break;
            case ShipType::COVERING_SHIP:
                try {
                    TCoveringShip &ship = dynamic_cast<TCoveringShip &>(battleship.value_);
                    amount++;
                    ship.getShipToCover();
                }
                catch (std::exception &e) {
                    break;
                }
                break;
            case ShipType::AIRCRAFT_CARRYING_CRUISER:
                try {
                    TAircraftCarryingCruiser &cruiser = dynamic_cast<TAircraftCarryingCruiser &>(battleship.value_);
                    amount++;
                    cruiser.getPlaneInfo();
                    cruiser.getShipToCover();
                }
                catch (std::exception &e) {
                    break;
                }
                break;
        }
    }
    return amount;
}

TCaptainInfo &TBattleshipGroup::getAdmiralInfo() {
    return _admiral;
}

std::string TBattleshipGroup::getStartingPoint() const {
    return _startingPoint;
}

std::string TBattleshipGroup::getDestination() const {
    return _destination;
}

double TBattleshipGroup::getDistance() const {
    return _distance;
}

void TBattleshipGroup::addPlane(TPlane &plane, const std::string &carrierName) {
    try {
        TAircraftCarrier &carrier = dynamic_cast<TAircraftCarrier &>(getBattleship(carrierName));
        carrier.addPlane(plane);
    }
    catch (std::bad_cast &e) {
        throw std::invalid_argument("Wrong carrier name");
    }
    catch (std::exception &e) {
        throw e;
    }
}

void TBattleshipGroup::addBattleship(TBattleship &battleship) {
    _battleshipGroup.insert(battleship.getName(), battleship);
}

void TBattleshipGroup::removePlane(const std::string &planeName, const std::string &carrierName) {
    try {
        TAircraftCarrier &carrier = dynamic_cast<TAircraftCarrier &>(getBattleship(carrierName));
        TPlaneGroup &planeGroup = carrier.getPlaneInfo();
        planeGroup.deletePlane(planeName);
    }
    catch (std::bad_cast &e) {
        throw std::invalid_argument("Wrong carrier name");
    }
    catch (std::exception &e) {
        throw e;
    }
}

void TBattleshipGroup::removeBattleship(const std::string &name) {
    _battleshipGroup.remove(name);
}

size_t TBattleshipGroup::size() const {
    return _battleshipGroup.size();
}

void TBattleshipGroup::setAdmiral(TCaptainInfo &admiral) {
    _admiral = admiral;
}

void TBattleshipGroup::setStartingPoint(const std::string &startingPoint) {
    _startingPoint = startingPoint;
}

void TBattleshipGroup::setDestination(const std::string &destination) {
    _destination = destination;
}

void TBattleshipGroup::setDistance(double distance) {
    _distance = distance;
}

void TBattleshipGroup::relocatePlane(const std::string planeName, TPlaneType planeType, const std::string carrierName1, const std::string carrierName2) {
    try {
        TAircraftCarrier &carrier1 = dynamic_cast<TAircraftCarrier &>(getBattleship(carrierName1));
        TAircraftCarrier &carrier2 = dynamic_cast<TAircraftCarrier &>(getBattleship(carrierName2));
        relocatePlane(planeName, planeType, carrier1, carrier2);
    }
    catch (std::bad_cast &e) {
        throw std::invalid_argument("Wrong carrier name");
    }
}

void TBattleshipGroup::relocatePlane(std::string planeName, TPlaneType planeType, TAircraftCarrier &carrier1, TAircraftCarrier &carrier2) {
    TPlane plane = getPlane(planeName, planeType, carrier1.getName());
    TPlaneGroup &carrier2_planes = carrier2.getPlaneInfo();
    carrier2_planes.addPlane(plane);
    TPlaneGroup &carrier1_planes = carrier1.getPlaneInfo();
    carrier1_planes.deletePlane(plane.getName());
}

void TBattleshipGroup::simulateAttack(TPlaneGroup &attackingGroup, size_t numWorkers) {
    std::vector<std::thread> threads(numWorkers);
    for (auto i = _battleshipGroup.begin(); i != _battleshipGroup.end(); ++i) {
        for (size_t j = 0; j < numWorkers; ++j) {
            if (threads[j].joinable())
                threads[j].join();
            if (i != _battleshipGroup.end()) {
                threads[j] = std::thread(&TPlaneGroup::attack, std::ref(attackingGroup), std::ref((*i).value_));
                ++i;
            }
        }
        if (i == _battleshipGroup.end())
            break;
    }
    for (auto &thread : threads) {
        if (thread.joinable())
            thread.join();
    }
    for (auto &i : _battleshipGroup) {
        if (i.value_.getSurvivability() == 0.)
            _battleshipGroup.remove(i.key_);
    }
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

std::ostream &operator<<(std::ostream &out, const TBattleshipGroup &battleshipGroup) {
    battleshipGroup.dump(out);
    return out;
}

std::istream &operator>>(std::istream &in, TBattleshipGroup &battleshipGroup) {
    battleshipGroup.read(in);
    return in;
}
