#include "../headers/plane.h"
#include <iostream>

std::ostream &operator<<(std::ostream &out, const TPlaneType &planeType) {
    switch (planeType) {
        case TPlaneType::fighter:
            out << "Fighter";
            break;
        case TPlaneType::bomber:
            out << "Bomber";
            break;
    }
    return out;
}

std::istream &operator>>(std::istream &in, TPlaneType &type) {
    std::string str;
    in >> str;
    if (str == "Fighter") {
        type = TPlaneType::fighter;
    } else if (str == "Bomber") {
        type = TPlaneType::bomber;
    } else {
        throw std::logic_error("Unknown plane type");
    }
    return in;
}

TPlane::TPlane(const std::string name, TWeaponry &weaponry, double survavability, double fuelUsage, TPlaneType type) : 
    _name(name), _weaponry(weaponry), _type(type),
    _survavability(survavability), _fuelUsage(fuelUsage) {
    if (survavability < 0.) {
        survavability = 0.;
        throw std::logic_error("Survavability can't be negative.setting it to 0");
    }
    if (fuelUsage < 0.) {
        fuelUsage = 0.;
        throw std::logic_error("Fuel usage can't be negative.setting it to 0");
    }
    if (type == TPlaneType::bomber && weaponry.getType() != WeaponryType::heavy) {
        throw std::logic_error("Can't set light weaponry on a bomber");
    }
}

TPlane::TPlane(std::string &&name, TWeaponry &&weaponry, double survavability, double fuelUsage, TPlaneType type) : 
    _name(std::move(name)), _weaponry(std::move(weaponry)), 
    _survavability(survavability), _fuelUsage(fuelUsage), _type(type) {
    if (survavability < 0.) {
        survavability = 0.;
        throw std::logic_error("Survavability can't be negative.setting it to 0");
    }
    if (fuelUsage < 0.) {
        fuelUsage = 0.;
        throw std::logic_error("Fuel usage can't be negative.setting it to 0");
    }
    if (type == TPlaneType::bomber && weaponry.getType() != WeaponryType::heavy) {
        throw std::logic_error("Can't set light weaponry on a bomber");
    }
}

TWeaponry &TPlane::getWeaponry() {
    return _weaponry;
}

double TPlane::getSurvavability() const {
    return _survavability;
}

double TPlane::getFuelUsage() const {
    return _fuelUsage;
}

std::string TPlane::getName() const {
    return _name;
}

TPlaneType TPlane::getType() const {
    return _type;
}

void TPlane::setType(TPlaneType newType) {
    _type = newType;
}

void TPlane::setName(const std::string &newName) {
    _name = newName;
}

void TPlane::setWeaponry(TWeaponry &newWeaponry) {
    if (newWeaponry.getType() != WeaponryType::heavy && _type == TPlaneType::bomber) {
        throw std::logic_error("Can't set light weaponry on a bomber");
    }
    _weaponry = newWeaponry;
}

void TPlane::setSurvavability(double newSurvavability) {
    if (newSurvavability < 0.) {
        throw std::logic_error("Survavability can't be negative");
    }
    _survavability = newSurvavability;
}

void TPlane::setFuelUsage(double newFuelUsage) {
    if (newFuelUsage < 0.) {
        throw std::logic_error("Fuel usage can't be negative");
    }
    _fuelUsage = newFuelUsage;
}

void TPlane::setWeaponryType(WeaponryType weaponryType) {
    if (weaponryType != WeaponryType::heavy && _type == TPlaneType::bomber) {
        throw std::logic_error("Can't set light weaponry on a bomber");
    }
    _weaponry.setType(weaponryType);
}

void TPlane::dump(std::ostream &out) const {
    _weaponry.dump(out);
    out << _survavability << " " << _fuelUsage << _name << " " << _type;
}

void TPlane::read(std::istream &in) {
    _weaponry.read(in);
    in >> _survavability >> _fuelUsage >> _name >> _type;
}

std::ostream &operator<<(std::ostream &out, const TPlane &plane) {
    plane.dump(out);
    return out;
}

std::istream &operator>>(std::istream &in, TPlane &plane) {
    plane.read(in);
    return in;
}
