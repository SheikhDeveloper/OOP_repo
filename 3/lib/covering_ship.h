#ifndef LAB3_LIB_COVERING_SHIP_H
#define LAB3_LIB_COVERING_SHIP_H

#include "battleship.h"

class CoveringShip : virtual public TBattleship
{
public:
    CoveringShip(TBattleship &shipToCover, TWeaponry weaponry, const std::string &name, const std::string &captainName, 
            const std::string &captainRank, const size_t experience, double survivability, size_t crewMembersAmount);

    double getWeaponryDamage() const;
    void setWeaponryDamage(double damage);
    virtual void dump(std::ostream &out) const;
    virtual void read(std::istream &in);

private:
    TBattleship &shipToCover;
};

#endif //LAB3_LIB_COVERING_SHIP_H
