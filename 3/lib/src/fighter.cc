#include "../headers/fighter.h"

TFighterPlane::TFighterPlane(): TPlane("Fighter", TWeaponry(), 0.5, 0.5) {}

TFighterPlane::TFighterPlane(const std::string& name, TWeaponry& weaponry, double survavability, double fuelUsage):
    TPlane(name, weaponry, survavability, fuelUsage) {}

TFighterPlane::TFighterPlane(std::string&& name, TWeaponry&& weaponry, double survavability, double fuelUsage):
    TPlane(std::move(name), std::move(weaponry), survavability, fuelUsage) {}

TFighterPlane::TFighterPlane(const TFighterPlane& other): TPlane(other) {}

TFighterPlane::TFighterPlane(TFighterPlane&& other) noexcept: TPlane(std::move(other)) {}

void TFighterPlane::dump(std::ostream &os) const {
    TPlane::dump(os);
    os << TPlaneType::fighter;
}

void TFighterPlane::read(std::istream &in) {
    TPlane::read(in);
}

std::ostream &operator<<(std::ostream &os, const TFighterPlane &plane) {
    plane.dump(os);
    return os;
}

std::istream &operator>>(std::istream &is, TFighterPlane &plane) {
    plane.read(is);
    return is;
}
