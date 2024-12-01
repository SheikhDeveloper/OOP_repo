#ifndef LAB3_LIB_PLANE_H
#define LAB3_LIB_PLANE_H

#include "weaponry.h"

enum class TPlaneType
{
    fighter = 0,
    bomber
};

std::ostream &operator<<(std::ostream &out, const TPlaneType &type);
std::istream &operator>>(std::istream &in, TPlaneType &type);

class TPlane {
public:
    TPlane(const std::string name, TWeaponry &weaponry, double survavability, double fuelUsage);
    TPlane(std::string &&name, TWeaponry &&weaponry, double survavability, double fuelUsage);
    TPlane(const TPlane &other) = default;
    TPlane(TPlane &&other) = default;

    TWeaponry &getWeaponry();
    double getSurvavability() const;
    double getFuelUsage() const;
    std::string getName() const;
    virtual TPlaneType getPlaneType() const = 0; 

    void setName(const std::string &newName);
    virtual void setWeaponry(TWeaponry &newWeaponry);
    void setSurvavability(double newSurvavability);
    void setFuelUsage(double newFuelUsage);
    virtual void setWeaponryType(WeaponryType weaponryType);

    virtual void dump(std::ostream &out) const;
    virtual void read(std::istream &in);

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
