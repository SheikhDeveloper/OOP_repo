#ifndef LAB3_LIB_COVERING_SHIP_H
#define LAB3_LIB_COVERING_SHIP_H

#include "battleship.h"

class TCoveringShip : public TBattleship
{
public:
    TCoveringShip();
    TCoveringShip(TBattleship &shipToCover, TWeaponry weaponry, const std::string &name, const std::string &captainName, 
            const std::string &captainRank, const size_t experience, double survivability, double speed, size_t crewMembersAmount, double fuelUsage);
    TCoveringShip(TBattleship &shipToCover);

    TCoveringShip(const TCoveringShip &coveringShip);
    TCoveringShip(TCoveringShip &&coveringShip);

    double getWeaponryDamage() const;
    void setWeaponryDamage(double damage);
    TBattleship &getShipToCover();
    const TBattleship &getShipToCover() const;

    virtual void setShipToCover(TBattleship &shipToCover);
    virtual void dump(std::ostream &out) const override;
    virtual void read(std::istream &in) override;
    virtual void readShipToCover(std::istream &in);

    virtual ~TCoveringShip() = default;

    TCoveringShip &operator=(const TCoveringShip &coveringShip);
    TCoveringShip &operator=(TCoveringShip &&coveringShip);

private:
    TBattleship _shipToCover;
};

std::ostream &operator<<(std::ostream &out, const TCoveringShip &coveringShip);
std::istream &operator>>(std::istream &in, TCoveringShip &coveringShip);

#endif //LAB3_LIB_COVERING_SHIP_H
