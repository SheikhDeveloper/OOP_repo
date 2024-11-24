#include "plane.h"
#include <iostream>

TPlane::TPlane(TWeaponry &weaponry, double survavability, double fuelUsage) : _weaponry(weaponry), _survavability(survavability), _fuelUsage(fuelUsage) {
    if (survavability < 0.) {
        survavability = 0.;
        throw std::logic_error("Survavability can't be negative.Setting it to 0");
    }
    if (fuelUsage < 0.) {
        fuelUsage = 0.;
        throw std::logic_error("Fuel usage can't be negative.Setting it to 0");
    }
}

TWeaponry TPlane::GetWeaponry() const {
    return _weaponry;
}

double TPlane::GetSurvavability() const {
    return _survavability;
}

double TPlane::GetFuelUsage() const {
    return _fuelUsage;
}

void TPlane::SetWeaponry(TWeaponry &newWeaponry) {
    if (newWeaponry.GetType() != WeaponryType::light) {
        throw std::logic_error("Can't set heavy weaponry on a plane");
    }
    _weaponry = newWeaponry;
}

void TPlane::SetSurvavability(double newSurvavability) {
    if (newSurvavability < 0.) {
        throw std::logic_error("Survavability can't be negative");
    }
    _survavability = newSurvavability;
}

void TPlane::SetFuelUsage(double newFuelUsage) {
    if (newFuelUsage < 0.) {
        throw std::logic_error("Fuel usage can't be negative");
    }
    _fuelUsage = newFuelUsage;
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
