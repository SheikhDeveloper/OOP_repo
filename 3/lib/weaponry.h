#ifndef LAB3_LIB_WEAPONRY_H
#define LAB3_LIB_WEAPONRY_H

#include <string>

enum WeaponryType
{
    light = 0,
    heavy = 1
};

class TWeaponry
{
public:
    TWeaponry(const std::string& name, const std::string& ammoName, size_t ammoAmount, double damage, WeaponryType type);

    std::string GetName() const;
    std::string GetAmmoName() const;
    size_t GetAmmoAmount() const;
    double GetDamage() const;
    WeaponryType GetType() const;

    void SetName(const std::string& name);
    void SetAmmoName(const std::string& ammoName);
    void SetAmmoAmount(size_t ammoAmount);
    void SetDamage(double damage);
    void SetType(WeaponryType type);

    ~TWeaponry() = default;

private:
    std::string _name;
    std::string _ammoName;
    size_t _ammoAmount;
    double _damage;
    WeaponryType _type;
};

#endif //LAB3_LIB_WEAPONRY_H
