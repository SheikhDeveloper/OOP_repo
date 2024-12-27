#include "../headers/covering_ship.h"

#include <iostream>

TCoveringShip::TCoveringShip(): TBattleship(), _shipToCover(TBattleship()) {}

TCoveringShip::TCoveringShip(const TBattleship &shipToCover): TBattleship(), _shipToCover(shipToCover) {}

TCoveringShip::TCoveringShip(TBattleship &&shipToCover): TBattleship(), _shipToCover(std::move(shipToCover)) {}

TCoveringShip::TCoveringShip(TBattleship &shipToCover, TWeaponry weaponry, 
                             const std::string &name, const std::string &captainName, 
                             const std::string &captainRank, const size_t experience, 
                             double survivability, double speed, size_t crewMembersAmount, double fuelUsage) :
    TBattleship(weaponry, name, captainName, captainRank, experience, speed, survivability, crewMembersAmount, fuelUsage),
    _shipToCover(shipToCover) {

        if (getWeaponryDamage() < 0.) {
            setWeaponryDamage(0.);
            throw std::logic_error("Weaponry damage can't be negative.Setting it to 0");
        }

        if (getSurvivability() < 0.) {
            setSurvivability(0.);
            throw std::logic_error("Survivability can't be negative.Setting it to 0");
        }

        if (getSpeed() < 0.) {
            setSpeed(0.);
            throw std::logic_error("Speed can't be negative.Setting it to 0");
        }
}

TCoveringShip::TCoveringShip(const TCoveringShip &coveringShip) :
    TBattleship(coveringShip),
    _shipToCover(coveringShip._shipToCover) {}

TCoveringShip::TCoveringShip(TCoveringShip &&coveringShip) :
    TBattleship(std::move(coveringShip)),
    _shipToCover(std::move(coveringShip._shipToCover)) {}

double TCoveringShip::getWeaponryDamage() const {
    return getWeaponry().getDamage();
}

TBattleship &TCoveringShip::getShipToCover() {
    return _shipToCover;
}

const TBattleship &TCoveringShip::getShipToCover() const {
    return _shipToCover;
}

void TCoveringShip::setShipToCover(TBattleship &shipToCover) {
    _shipToCover = shipToCover;
}

void TCoveringShip::setWeaponryDamage(double damage) {
    TWeaponry newWeaponry(TWeaponry(getWeaponry().getName(), getWeaponry().getAmmoName(), getWeaponry().getAmmoAmount(), damage, getWeaponry().getType()));
    setWeaponry(newWeaponry);
}

void TCoveringShip::dump(std::ostream &out) const {
    TBattleship::dump(out);
    out << "Ship to cover: " << _shipToCover.getName() << std::endl;
}

void TCoveringShip::read(std::istream &in) {
    TBattleship::read(in);
    std::string shipToCoverName;
    in >> shipToCoverName;
    _shipToCover.setName(shipToCoverName);
}

void TCoveringShip::readShipToCover(std::istream &in) {
    _shipToCover.read(in);
}

TCoveringShip &TCoveringShip::operator=(const TCoveringShip &coveringShip) {
    if (this != &coveringShip) {
        TBattleship::operator=(coveringShip);
        _shipToCover = coveringShip._shipToCover;
    }
    return *this;
}

TCoveringShip &TCoveringShip::operator=(TCoveringShip &&coveringShip) {
    if (this != &coveringShip) {
        TBattleship::operator=(std::move(coveringShip));
        _shipToCover = std::move(coveringShip._shipToCover);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const TCoveringShip &coveringShip) {
    coveringShip.dump(out);
    return out;
}

std::istream &operator>>(std::istream &in, TCoveringShip &coveringShip) {
    coveringShip.read(in);
    return in;
}
