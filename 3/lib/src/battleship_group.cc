#include "../headers/battleship_group.h"

#include <iostream>

TBattleshipGroup::TBattleshipGroup() { 
    _admiral = TCaptainInfo();
    _startingPoint = "";
    _destination = "";
    _distance = 0;
}

TBattleshipGroup::TBattleshipGroup(std::string admiralName, std::string admiralRank, size_t admiralExperience, const std::string &startingPoint, const std::string &destination, double distance) {
    _admiral = TCaptainInfo(admiralName, admiralRank, admiralExperience);
    _startingPoint = startingPoint;
    _destination = destination;
    _distance = distance;
}

TBattleshipGroup::TBattleshipGroup(std::string admiralName, std::string admiralRank, size_t admiralExperience, const std::string &startingPoint, const std::string &destination, double distance,
                                 std::vector<TBattleship> &battleships) {
    _admiral = TCaptainInfo(admiralName, admiralRank, admiralExperience);
    _startingPoint = startingPoint;
    _destination = destination;
    _distance = distance;
    for (auto &battleship : battleships) {
        _battleshipGroup.insert(battleship.getName(), battleship);
    }
}

TBattleshipGroup::TBattleshipGroup(TCaptainInfo &admiral, const std::string &startingPoint, const std::string &destination, double distance) {
    _admiral = TCaptainInfo(admiral);
    _startingPoint = startingPoint;
    _destination = destination;
    _distance = distance;
    _battleshipGroup = THashTable<std::string, TBattleship>();
}

TBattleshipGroup::TBattleshipGroup(TCaptainInfo &admiral, const std::string &startingPoint, const std::string &destination, double distance, std::vector<TBattleship> &battleships) {
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
    relocatePlane(planeName, carrierName1, carrierName2);
}

void TBattleshipGroup::relocatePlane(const std::string planeName, TAircraftCarrier &carrier1, TAircraftCarrier &carrier2) {
    TPlane &plane = getPlane(planeName, carrier1.getName());
    TPlaneGroup carrier2_planes = carrier2.getPlaneInfo().second;
    carrier2_planes.addPlane(plane);
    carrier2.setPlaneInfo(carrier2_planes);
    TPlaneGroup carrier1_planes = carrier1.getPlaneInfo().second;
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
        TBattleship battleship;
        in >> battleship;
        _battleshipGroup.insert(battleship.getName(), battleship);
    }
}
