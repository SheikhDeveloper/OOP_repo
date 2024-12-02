#include "../headers/bomber.h"


TBomberPlane::TBomberPlane() : TPlane("Bomber", TWeaponry(), 0.5, 0.5) {}

TBomberPlane::TBomberPlane(std::string &name, TWeaponry &weaponry, double survivability, double fuelUsage) : TPlane(name, weaponry, survivability, fuelUsage) {}

TBomberPlane::TBomberPlane(std::string &&name, TWeaponry &&weaponry, double survivability, double fuelUsage) : TPlane(std::move(name), std::move(weaponry), survivability, fuelUsage) {}

TBomberPlane::TBomberPlane(const TBomberPlane &plane) : TPlane(plane) {}

TBomberPlane::TBomberPlane(TBomberPlane &&plane) : TPlane(std::move(plane)) {}

void TBomberPlane::attack(TBattleship &target) {
    auto damage = getWeaponry().getDamage();
    auto targetSurvivability = target.getSurvivability();
    targetSurvivability -= damage;
    if (targetSurvivability < 0.)
        targetSurvivability = 0.;
    target.setSurvivability(targetSurvivability);
}


void TBomberPlane::dump(std::ostream &os) const {
    TPlane::dump(os);
    os << TPlaneType::bomber;
}

void TBomberPlane::read(std::istream &is) {
    TPlane::read(is);
}
