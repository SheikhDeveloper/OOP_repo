#ifndef LAB3_LIB_WEAPONRY_H
#define LAB3_LIB_WEAPONRY_H

#include <string>

enum class WeaponryType
{
    light = 0,
    heavy = 1
};

std::ostream &operator<<(std::ostream &out, const WeaponryType &type);
std::istream &operator>>(std::istream &in, WeaponryType &type);

class TWeaponry
{
public:
    TWeaponry(const std::string& name, const std::string& ammoName, size_t ammoAmount, double damage, WeaponryType type);

    TWeaponry(const TWeaponry& other) = default;
    TWeaponry(TWeaponry&& other) = default;

    std::string getName() const;
    std::string getAmmoName() const;
    size_t getAmmoAmount() const;
    double getDamage() const;
    WeaponryType getType() const;

    void setName(const std::string& name);
    void setAmmoName(const std::string& ammoName);
    void setAmmoAmount(size_t ammoAmount);
    void setDamage(double damage);
    void setType(WeaponryType type);

    void dump(std::ostream &out) const;
    void read(std::istream &in);

    ~TWeaponry() = default;

    TWeaponry& operator=(const TWeaponry& other) = default;
    TWeaponry& operator=(TWeaponry&& other) = default;

private:
    std::string _name;
    std::string _ammoName;
    size_t _ammoAmount;
    double _damage;
    WeaponryType _type;
};

std::ostream &operator<<(std::ostream &out, const TWeaponry &weaponry);
std::istream &operator>>(std::istream &in, TWeaponry &weaponry);

#endif //LAB3_LIB_WEAPONRY_H
