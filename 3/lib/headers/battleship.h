#ifndef LAB3_LIB_BATTLESHIP_H
#define LAB3_LIB_BATTLESHIP_H

#include "captain_info.h"
#include "weaponry.h"

/* @brief Battleship class */
class TBattleship {
public:
    /* @brief Default constructor */
    TBattleship();

    /* @brief Constructor 
     * @param [in] crewMembersAmount - Amount of crew members 
     * @param [in] fuelUsage - Fuel usage 
     * @param [in] weaponry - Weaponry 
     * @param [in] captainName - Captain name
     * @param [in] captainRank - Captain rank
     * @param [in] experience - Captain experience
     * @param [in] name - Name 
     * @param [in] speed - Speed 
     * @param [in] survivability - Survivability 
     * */
    TBattleship(TWeaponry weaponry, const std::string &name, const std::string &captainName, const std::string &captainRank,
                const size_t experience, const double speed, const double survivability, const size_t crewMembersAmount,
                const double fuelUsage);

    /* @brief Constructor 
     * @param [in] crewMembersAmount - Amount of crew members 
     * @param [in] fuelUsage - Fuel usage 
     * @param [in] weaponry - Weaponry 
     * @param [in] captainInfo - Captain info
     * @param [in] name - Name 
     * @param [in] speed - Speed 
     * @param [in] survivability - Survivability 
     * */
    TBattleship(TWeaponry weaponry, TCaptainInfo captainInfo, const std::string &name, const double speed, 
                const double survivability, const size_t crewMembersAmount, const double fuelUsage);

    /* @brief Copy constructor 
     * @param [in] battleship - TBattleship object to copy 
     * */
    TBattleship(const TBattleship &battleship);

    /* @brief Move constructor 
     * @param [in] battleship - TBattleship object to move
     * */
    TBattleship(TBattleship &&battleship);

    /* @brief Name getter 
     *
     * @return name of the TBattleship object */
    std::string getName() const;

    /* @brief Captain getter 
     *
     * @return captain of the TBattleship object */
    TCaptainInfo getCaptain() const;

    /* @brief Get survivability
     *
     * @return survivability */
    double getSurvivability() const;

    /* @brief Get crew members amount
     *
     * @return crew members amount */
    size_t getCrewMembersAmount() const;

    /* @brief Get speed
     *
     * @return speed */
    double getSpeed() const;

    /* @brief Get weaponry
     *
     * @return weaponry */
    TWeaponry getWeaponry() const;

    /* @brief Get fuel usage
     *
     * @return fuel usage */
    double getFuelUsage() const;

    /* @brief Set weaponry
     * @param [in] weaponry - Weaponry
     * */
    virtual void setWeaponry(TWeaponry &weaponry);

    /* @brief Set speed
     * @param [in] speed - Speed
     * */
    void setSpeed(double speed);

    /* @brief Set survivability
     * @param [in] survivability - Survivability
     * */
    void setSurvivability(double survivability);

    /* @brief Set crew members amount
     * @param [in] crewMembersAmount - Amount of crew members
     * */
    void setCrewMembersAmount(size_t crewMembersAmount);

    /* @brief Set captain
     * @param [in] captainName - Name of the captain
     * @param [in] captainRank - Rank of the captain
     * @param [in] experience - Experience of the captain
     * */
    void setCaptain(const std::string &captainName, const std::string &captainRank, const size_t experience);

    /* @brief Set captain
     * @param [in] captainInfo - Captain info
     * */
    void setCaptain(const TCaptainInfo &captainInfo);

    /* @brief Set name
     * @param [in] name - Name
     * */
    void setName(const std::string &name);

    /* @brief Set fuel usage
     * @param [in] fuelUsage - Fuel usage
     * */
    void setFuelUsage(double fuelUsage);

    /* @brief Calculate max distance
     * @param [in] fuelAmount - Fuel amount
     * @return Max distance the ship can pass
     * */
    virtual double calcMaxDistance(double fuelAmount) const;


    /* @brief Dump information about the TBattleship object
     * @param [in] out - Output stream
     * */
    virtual void dump(std::ostream &out) const;

    /* @brief Read information about the TBattleship object
     * @param [in] in - Input stream
     * */
    virtual void read(std::istream &in);

    /* @brief Virtual destructor */
    virtual ~TBattleship() = default;

    /* @brief Copy assignment operator 
     * @param[in] battleship - Battleship to copy
     *
     * @return Copied TBattleship object 
     * */
    TBattleship &operator=(const TBattleship &battleship);

    /* @brief Move assignment operator 
     * @param[in] battleship - Battleship to move
     *
     * @return Moved TBattleship object 
     * */
    TBattleship &operator=(TBattleship &&battleship);
private:
    /* @brief Name of the TBattleship object */
    std::string _name;

    /* @brief Captain of the TBattleship object */
    TCaptainInfo _captain;

    /* @brief Speed of the TBattleship object */
    double _speed;

    /* @brief Survivability of the TBattleship object */
    double _survivability;

    /* @brief Amount of crew members of the TBattleship object */
    size_t _crewMembersAmount;

    /* @brief Weaponry of the TBattleship object */
    TWeaponry _weaponry;

    /* @brief Fuel usage of the TBattleship object */
    double _fuelUsage;
};

std::ostream &operator<<(std::ostream &out, const TBattleship &battleship);
std::istream &operator>>(std::istream &in, TBattleship &battleship);


#endif //LAB3_LIB_BATTLESHIP_H
