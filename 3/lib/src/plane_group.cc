#include "../headers/plane_group.h"
#include "../headers/aircraft_carrier.h"


#include <iostream>

TPlaneGroup::TPlaneGroup() : _planes(), _planeDamage(0.), _shipDamage(0.), _bomberAmount(0), _fightersAmount(0) {}

TPlaneGroup::TPlaneGroup(const TPlaneGroup &planeGroup) :
    _planes(planeGroup._planes),
    _planeDamage(planeGroup._planeDamage),
    _shipDamage(planeGroup._shipDamage),
    _bomberAmount(planeGroup._bomberAmount), 
    _fightersAmount(planeGroup._fightersAmount) {}


TPlaneGroup::TPlaneGroup(TPlaneGroup &&planeGroup) :
    _planes(std::move(planeGroup._planes)),
    _planeDamage(planeGroup._planeDamage), 
    _shipDamage(planeGroup._shipDamage), 
    _bomberAmount(planeGroup._bomberAmount), 
    _fightersAmount(planeGroup._fightersAmount) {}

void TPlaneGroup::addPlane(TPlane &plane) {
    TPlaneType planeType = plane.getType();
    std::string key = plane.getName() + std::to_string(static_cast<int>(planeType));
    _planes.insert(plane.getName(), plane);
    if (planeType == TPlaneType::bomber) {
        _bomberAmount++;
        _shipDamage += plane.getWeaponry().getDamage();
    }
    else if (planeType == TPlaneType::fighter)
        _fightersAmount++;
    _planeDamage += plane.getWeaponry().getDamage();
}

void TPlaneGroup::deletePlane(const std::string &name) {
    std::string key = name + std::to_string(static_cast<int>(TPlaneType::bomber));
    try {
        TPlane plane = _planes[key];
        _bomberAmount--;
        _shipDamage -= plane.getWeaponry().getDamage();
        _planes.remove(key);
        _planeDamage -= plane.getWeaponry().getDamage();
    }
    catch (std::exception &e) {
        std::string new_key = name + std::to_string(static_cast<int>(TPlaneType::fighter));
        try {
            TPlane plane = _planes[new_key];
            _fightersAmount--;
            _planes.remove(new_key);
            _planeDamage -= plane.getWeaponry().getDamage();
        }
        catch (std::exception &e) {
            throw std::invalid_argument("Wrong plane name");
        }
    }
}

TPlane &TPlaneGroup::getPlane(std::string &name, TPlaneType planeType) {
    std::string key = name + std::to_string(static_cast<int>(planeType));
    return _planes[name];
}

double TPlaneGroup::getTotalDamage() const {
    return _planeDamage + _shipDamage;
}

size_t TPlaneGroup::size() const {
    return _planes.size();
}

void TPlaneGroup::attack(TBattleship &target) {
    double shipSurvivability = target.getSurvivability();
    std::vector<std::string> to_remove;
    try {
        TAircraftCarrier &carrier = dynamic_cast<TAircraftCarrier &>(target);
        auto &aircraftPlanes = carrier.getPlaneInfo();
        auto planeDamage = _planeDamage;
        for (auto &i : aircraftPlanes._planes) {
            TPlane plane = i.value_;
            double newSurvivability = plane.getSurvivability() - planeDamage;
            if (newSurvivability < 0.) {
                newSurvivability = 0.;
                to_remove.push_back(plane.getName());
            }
            plane.setSurvivability(newSurvivability);
        }
        
        for (auto &i : to_remove) {
            aircraftPlanes.deletePlane(i);
        }
    }
    catch (std::bad_cast &e) {
        ;
    }
    shipSurvivability -= _shipDamage;
    if (shipSurvivability < 0.)
        shipSurvivability = 0.;
    target.setSurvivability(shipSurvivability);
}

void TPlaneGroup::dump(std::ostream &os) const {
    for (auto &i : _planes) {
        TPlane plane = i.value_;
        plane.dump(os);
    }
}

void TPlaneGroup::read(std::istream &is) {
    TPlane plane;
    while (is >> plane) {
        addPlane(plane);
    }
}

TPlane &TPlaneGroup::operator[](const std::string &name) {
    return _planes[name];
}

TPlaneGroup &TPlaneGroup::operator=(const TPlaneGroup &planeGroup) {
    if (this != &planeGroup) {
        _planes = planeGroup._planes;
        _planeDamage = planeGroup._planeDamage;
        _shipDamage = planeGroup._shipDamage;
        _bomberAmount = planeGroup._bomberAmount;
        _fightersAmount = planeGroup._fightersAmount;
    }
    return *this;
}


TPlaneGroup &TPlaneGroup::operator=(TPlaneGroup &&planeGroup) {
    if (this != &planeGroup) {
        _planes = std::move(planeGroup._planes);
        _planeDamage = planeGroup._planeDamage;
        _shipDamage = planeGroup._shipDamage;
        _bomberAmount = planeGroup._bomberAmount;
        _fightersAmount = planeGroup._fightersAmount;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const TPlaneGroup &planeGroup) {
    planeGroup.dump(out);
    return out;
}


std::istream &operator>>(std::istream &in, TPlaneGroup &planeGroup) {
    planeGroup.read(in);
    return in;
}
