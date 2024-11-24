#ifndef LAB3_LIB_PLANE_H
#define LAB3_LIB_PLANE_H

#include "weaponry.h"

class TPlane {
public:
    TPlane();
    TPlane(TWeaponry &weaponry, double survavability, double fuelUsage);

    TPlane(const TPlane &other) = default;
    TPlane(TPlane &&other) = default;

    TWeaponry getWeaponry() const;
    double getSurvavability() const;
    double getFuelUsage() const;
    std::string getName() const;

    void setName(const std::string &newName);
    void setWeaponry(TWeaponry &newWeaponry);
    void setSurvavability(double newSurvavability);
    void setFuelUsage(double newFuelUsage);

    void dump(std::ostream &out) const;
    void read(std::istream &in);

    TPlane &operator=(const TPlane &other) = default;
    TPlane &operator=(TPlane &&other) = default;

    ~TPlane() = default;

private:
    std::string _name;
    TWeaponry _weaponry;
    double _survavability;
    double _fuelUsage;
};

std::ostream &operator<<(std::ostream &out, const TPlane &plane);

std::istream &operator>>(std::istream &in, TPlane &plane);

#endif //LAB3_LIB_PLANE_H
