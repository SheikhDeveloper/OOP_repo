#include "../headers/plane_group.h"

#include <iostream>


TPlaneGroup::TPlaneGroup(const TPlaneGroup &planeGroup) :
    _planes(planeGroup._planes),
    _totalDamage(planeGroup._totalDamage) {}


TPlaneGroup::TPlaneGroup(TPlaneGroup &&planeGroup) :
    _planes(std::move(planeGroup._planes)),
    _totalDamage(planeGroup._totalDamage) {}

void TPlaneGroup::addPlane(TPlane &plane) {
    std::string key = plane.getName() + std::to_string(static_cast<int>(plane.getPlaneType()));
    _planes.insert(plane.getName(), plane);
    auto &plane_weaponry = plane.getWeaponry();
    _totalDamage += plane_weaponry.getDamage();
}

void TPlaneGroup::deletePlane(const std::string &name) {
    _totalDamage -= _planes[name].getWeaponry().getDamage();
    _planes.remove(name);
}

TPlane &TPlaneGroup::getPlane(std::string &name, TPlaneType planeType) {
    std::string key = name + std::to_string(static_cast<int>(planeType));
    return _planes[name];
}

double TPlaneGroup::getTotalDamage() const {
    return _totalDamage;
}

size_t TPlaneGroup::size() const {
    return _planes.size();
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

TPlaneGroup &TPlaneGroup::operator=(const TPlaneGroup &planeGroup) {
    if (this != &planeGroup) {
        _planes = planeGroup._planes;
        _totalDamage = planeGroup._totalDamage;
    }
    return *this;
}


TPlaneGroup &TPlaneGroup::operator=(TPlaneGroup &&planeGroup) {
    if (this != &planeGroup) {
        _planes = std::move(planeGroup._planes);
        _totalDamage = planeGroup._totalDamage;
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
