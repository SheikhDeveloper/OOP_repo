#ifndef LAB3_LIB_PLANE_H
#define LAB3_LIB_PLANE_H

#include "weaponry.h"

class TPlane {
public:
    TPlane(TWeaponry &weaponry, double survavability, double fuelUsage);

    TWeaponry GetWeaponry() const;
    double GetSurvavability() const;
    double GetFuelUsage() const;

    void SetWeaponry(TWeaponry &newWeaponry);
    void SetSurvavability(double newSurvavability);
    void SetFuelUsage(double newFuelUsage);

    ~TPlane() = default;

private:
    TWeaponry _weaponry;
    double _survavability;
    double _fuelUsage;
};

#endif //LAB3_LIB_PLANE_H
