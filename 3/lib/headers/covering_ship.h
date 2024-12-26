#ifndef LAB3_LIB_COVERING_SHIP_H
#define LAB3_LIB_COVERING_SHIP_H

#include "battleship.h"

/*@brief TCovering Ship class */
class TCoveringShip : virtual public TBattleship
{
public:
    /*@brief Default constructor */
    TCoveringShip();

    /*@brief Constructor with ship to cover const lvalue reference
     * @param shipToCover - TBattleship object 
     * */
    TCoveringShip(const TBattleship &shipToCover);

    /*@brief Constructor with ship to cover rvalue reference
     * @param shipToCover - TBattleship object
     * */
    TCoveringShip(TBattleship &&shipToCover);

    /*@brief Constructor with all parameters
     * @param shipToCover - Battleship to cover
     * @param weaponry - Weaponry of the ship
     * @param name - name of the ship
     * @param captainName - name of the captain
     * @param captainRank - rank of the captain
     * @param experience - experience of the captain
     * @param survivability - survivability of the ship
     * @param speed - speed of the ship
     * @param crewMembersAmount - amount of crew members
     * @param fuelUsage - fuel usage of the ship
     * */
    TCoveringShip(TBattleship &shipToCover, TWeaponry weaponry, const std::string &name, const std::string &captainName, 
            const std::string &captainRank, const size_t experience, double survivability, double speed, size_t crewMembersAmount, double fuelUsage);

    /*@brief Copy constructor 
     * @param coveringShip - Covering ship to copy 
     * */
    TCoveringShip(const TCoveringShip &coveringShip);

    /*@brief Move constructor
     * @param coveringShip - Covering ship to move
     * */
    TCoveringShip(TCoveringShip &&coveringShip);

    /* @brief Get weaponry damage
     *
     * @return Weaponry damage
     * */
    double getWeaponryDamage() const;

    /* @brief Set weaponry damage
     *
     * @param damage - Weaponry damage
     * */
    void setWeaponryDamage(double damage);

    /* @brief Get ship to cover
     *
     * @return Ship to cover reference
     * */
    TBattleship &getShipToCover();

    /* @brief Get ship to cover const
     *
     * @return Ship to cover const reference
     * */
    const TBattleship &getShipToCover() const;

    /* @brief Set ship to cover
     *
     * @param shipToCover - Ship to cover
     * */
    virtual void setShipToCover(TBattleship &shipToCover);

    /* @brief Dump covering ship into output stream
     * 
     * @param out - Output stream
     * */
    virtual void dump(std::ostream &out) const override;

    /* @brief Read covering ship from input stream
     * 
     * @param in - Input stream
     * */
    virtual void read(std::istream &in) override;

    /* @brief Read ship to cover from input stream
     * 
     * @param in - Input stream
     * */
    virtual void readShipToCover(std::istream &in);

    /* @brief Default destructor */
    virtual ~TCoveringShip() = default;

    /* @brief Copy assignment operator
     * 
     * @param coveringShip - Covering ship to copy
     * 
     * @return Reference to this
     * */
    TCoveringShip &operator=(const TCoveringShip &coveringShip);

    /* @brief Move assignment operator
     * 
     * @param coveringShip - Covering ship to move
     * 
     * @return Reference to this
     * */
    TCoveringShip &operator=(TCoveringShip &&coveringShip);

private:
    /*@brief Ship to cover */
    TBattleship _shipToCover;
};

std::ostream &operator<<(std::ostream &out, const TCoveringShip &coveringShip);
std::istream &operator>>(std::istream &in, TCoveringShip &coveringShip);

#endif //LAB3_LIB_COVERING_SHIP_H
