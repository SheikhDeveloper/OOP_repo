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

TPlane::TPlane(const std::string name, TWeaponry &weaponry, double survavability, double fuelUsage) : _name(name), _weaponry(weaponry), _survavability(survavability), _fuelUsage(fuelUsage) {
    if (survavability < 0.) {
        survavability = 0.;
        throw std::logic_error("Survavability can't be negative.setting it to 0");
    }
    if (fuelUsage < 0.) {
        fuelUsage = 0.;
        throw std::logic_error("Fuel usage can't be negative.setting it to 0");
    }
}

TPlane::TPlane(std::string &&name, TWeaponry &&weaponry, double survavability, double fuelUsage) : _name(std::move(name)), _weaponry(std::move(weaponry)), _survavability(survavability), _fuelUsage(fuelUsage) {
    if (survavability < 0.) {
        survavability = 0.;
        throw std::logic_error("Survavability can't be negative.setting it to 0");
    }
    if (fuelUsage < 0.) {
        fuelUsage = 0.;
        throw std::logic_error("Fuel usage can't be negative.setting it to 0");
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

void TPlane::setWeaponry(TWeaponry &newWeaponry) {
    if (newWeaponry.getType() != WeaponryType::light) {
        throw std::logic_error("Can't set heavy weaponry on a plane");
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
    if (weaponryType != WeaponryType::light) {
        throw std::logic_error("Can't set heavy weaponry on a plane");
    }
    _weaponry.setType(weaponryType);
}

void TPlane::dump(std::ostream &out) const {
    _weaponry.dump(out);
    out << _survavability << " " << _fuelUsage;
}

void TPlane::read(std::istream &in) {
    _weaponry.read(in);
    in >> _survavability >> _fuelUsage;
}

std::ostream &operator<<(std::ostream &out, const TPlane &plane) {
    plane.dump(out);
    return out;
}

std::istream &operator>>(std::istream &in, TPlane &plane) {
    plane.read(in);
    return in;
}
