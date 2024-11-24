#ifndef LAB3_LIB_PLANE_H
#define LAB3_LIB_PLANE_H

#include "weaponry.h"

class TPlane {
public:
    TPlane(TWeaponry &weaponry, double survavability, double fuelUsage);

    TPlane(const TPlane &other) = default;
    TPlane(TPlane &&other) = default;

    TWeaponry GetWeaponry() const;
    double GetSurvavability() const;
    double GetFuelUsage() const;

    void SetWeaponry(TWeaponry &newWeaponry);
    void SetSurvavability(double newSurvavability);
    void SetFuelUsage(double newFuelUsage);

    void dump(std::ostream &out) const;
    void read(std::istream &in);

    TPlane &operator=(const TPlane &other) = default;
    TPlane &operator=(TPlane &&other) = default;

    ~TPlane() = default;

private:
    TWeaponry _weaponry;
    double _survavability;
    double _fuelUsage;
};

std::ostream &operator<<(std::ostream &out, const TPlane &plane);

std::istream &operator>>(std::istream &in, TPlane &plane);

#endif //LAB3_LIB_PLANE_H
