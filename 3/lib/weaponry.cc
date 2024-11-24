#include "weaponry.h"

#include <iostream>

std::ostream &operator<<(std::ostream &out, const WeaponryType &type) {
    switch (type) {
        case WeaponryType::light:
            out << "light";
            break;
        case WeaponryType::heavy:
            out << "heavy";
            break;
    }
    return out;
}

std::istream &operator>>(std::istream &in, WeaponryType &type) {
    std::string str;
    in >> str;
    if (str == "light") {
        type = WeaponryType::light;
    } else if (str == "heavy") {
        type = WeaponryType::heavy;
    } else {
        throw std::logic_error("Invalid weaponry type");
    }
    return in;
}

TWeaponry::TWeaponry(const std::string& name, const std::string& ammoName, size_t ammoAmount, double damage, WeaponryType type) :
    _name(name),
    _ammoName(ammoName),
    _ammoAmount(ammoAmount),
    _damage(damage),
    _type(type)
{
    if (damage < 0.) {
        _damage = 0.;
        throw std::logic_error("Damage can't be negative.Setting it to 0");
    }

    if (ammoAmount < 0) {
        _ammoAmount = 0;
        throw std::logic_error("Ammo amount can't be negative.Setting it to 0");
    }
}

std::string TWeaponry::GetName() const {
    return _name;
}

std::string TWeaponry::GetAmmoName() const {
    return _ammoName;
}

size_t TWeaponry::GetAmmoAmount() const {
    return _ammoAmount;
}

double TWeaponry::GetDamage() const {
    return _damage;
}

WeaponryType TWeaponry::GetType() const {
    return _type;
}

void TWeaponry::SetName(const std::string& name) {
    _name = name;
}

void TWeaponry::SetAmmoName(const std::string& ammoName) {
    _ammoName = ammoName;
}

void TWeaponry::SetAmmoAmount(size_t ammoAmount) {
    _ammoAmount = ammoAmount;
}

void TWeaponry::SetDamage(double damage) {
    if (damage < 0.)
        throw std::logic_error("Damage can't be negative");
    _damage = damage;
}

void TWeaponry::SetType(WeaponryType type) {
    _type = type;
}

void TWeaponry::dump(std::ostream &out) const {
    out << _name << " " << _ammoName << " " << _ammoAmount << " " << _damage << " " << _type;
}

void TWeaponry::read(std::istream &in) {
    in >> _name >> _ammoName >> _ammoAmount >> _damage >> _type;
}

std::ostream &operator<<(std::ostream &out, const TWeaponry &weaponry) {
    weaponry.dump(out);
    return out;
}

std::istream &operator>>(std::istream &in, TWeaponry &weaponry) {
    weaponry.read(in);
    return in;
}
