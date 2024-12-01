#include "../headers/battleship.h"

#include <iostream>


TBattleship::TBattleship() {
    _weaponry = TWeaponry();
    _name = "";
    _captain = TCaptainInfo();
    _speed = 0.;
    _survivability = 0.;
    _crewMembersAmount = 0;
    _fuelUsage = 0.;
}

TBattleship::TBattleship(TWeaponry weaponry, const std::string &name, 
                         const std::string &captainName, const std::string &captainRank, 
                         const size_t experience, double speed, double survivability, 
                         size_t crewMembersAmount, double fuelUsage) :
    _weaponry(weaponry),
    _name(name),
    _captain(captainName, captainRank, experience),
    _speed(speed),
    _survivability(survivability),
    _crewMembersAmount(crewMembersAmount),
    _fuelUsage(fuelUsage) {

        if (_survivability < 0.) {
            _survivability = 0;
            throw std::logic_error("Survivability can't be negative.Setting it to 0");
        }

        if (_crewMembersAmount < 0) {
            _crewMembersAmount = 0;
            throw std::logic_error("Crew members amount can't be negative.Setting it to 0");
        }

        if (_speed < 0.) {
            _speed = 0.;
            throw std::logic_error("Speed can't be negative.Setting it to 0");
        }
}

TBattleship::TBattleship(const TBattleship &battleship) :
    _weaponry(battleship._weaponry),
    _name(battleship._name),
    _captain(battleship._captain),
    _speed(battleship._speed),
    _survivability(battleship._survivability),
    _crewMembersAmount(battleship._crewMembersAmount),
    _fuelUsage(battleship._fuelUsage) {}

TBattleship::TBattleship(TBattleship &&battleship) :
    _weaponry(std::move(battleship._weaponry)),
    _name(std::move(battleship._name)),
    _captain(std::move(battleship._captain)),
    _speed(std::move(battleship._speed)),
    _survivability(std::move(battleship._survivability)),
    _crewMembersAmount(std::move(battleship._crewMembersAmount)),
    _fuelUsage(std::move(battleship._fuelUsage)) {}

std::string TBattleship::getName() const {
    return _name;
}

TCaptainInfo TBattleship::getCaptain() const {
    return _captain;
}

double TBattleship::getSurvivability() const {
    return _survivability;
}

size_t TBattleship::getCrewMembersAmount() const {
    return _crewMembersAmount;
}

double TBattleship::getSpeed() const {
    return _speed;
}

TWeaponry TBattleship::getWeaponry() const {
    return _weaponry;
}

double TBattleship::getFuelUsage() const {
    return _fuelUsage;
}

void TBattleship::setWeaponry(TWeaponry &weaponry) {
    _weaponry = weaponry;
}

void TBattleship::setSpeed(double speed) {
    if (speed < 0.) {
        throw std::logic_error("Speed can't be negative");
    }
    _speed = speed;
}

void TBattleship::setSurvivability(double survivability) {
    if (survivability < 0.) {
        throw std::logic_error("Survivability can't be negative");
    }
    _survivability = survivability;
}

void TBattleship::setCrewMembersAmount(size_t crewMembersAmount) {
    if (crewMembersAmount < 0) {
        throw std::logic_error("Crew members amount can't be negative");
    }
    _crewMembersAmount = crewMembersAmount;
}

void TBattleship::setCaptain(const std::string &captainName, const std::string &captainRank, const size_t experience) {
    _captain = TCaptainInfo(captainName, captainRank, experience);
}

void TBattleship::setName(const std::string &name) {
    _name = name;
}

void TBattleship::setFuelUsage(double fuelUsage) {
    if (fuelUsage < 0.) {
        throw std::logic_error("Fuel usage can't be negative");
    }
    _fuelUsage = fuelUsage;
}

double TBattleship::calcMaxDistance(double fuelAmount) const {
    return fuelAmount / _fuelUsage;
}

void TBattleship::dump(std::ostream &out) const {
    out << _name << " " << _captain << " " << _speed << " " << _survivability << " " << _crewMembersAmount << " " << _weaponry << " " << _fuelUsage;
}

void TBattleship::read(std::istream &in) {
    in >> _name >> _captain >> _speed >> _survivability >> _crewMembersAmount >> _weaponry >> _fuelUsage;
}

TBattleship &TBattleship::operator=(const TBattleship &battleship) {
    if (this != &battleship) {
        _weaponry = battleship._weaponry;
        _name = battleship._name;
        _captain = battleship._captain;
        _speed = battleship._speed;
        _survivability = battleship._survivability;
        _crewMembersAmount = battleship._crewMembersAmount;
        _fuelUsage = battleship._fuelUsage;
    }
    return *this;
}

TBattleship &TBattleship::operator=(TBattleship &&battleship) {
    if (this != &battleship) {
        _weaponry = std::move(battleship._weaponry);
        _name = std::move(battleship._name);
        _captain = std::move(battleship._captain);
        _speed = std::move(battleship._speed);
        _survivability = std::move(battleship._survivability);
        _crewMembersAmount = std::move(battleship._crewMembersAmount);
        _fuelUsage = std::move(battleship._fuelUsage);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const TBattleship &battleship) {
    battleship.dump(out);
    return out;
}

std::istream &operator>>(std::istream &in, TBattleship &battleship) {
    battleship.read(in);
    return in;
}
