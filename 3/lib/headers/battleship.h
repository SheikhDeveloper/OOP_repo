#ifndef LAB3_LIB_BATTLESHIP_H
#define LAB3_LIB_BATTLESHIP_H

#include "captain_info.h"
#include "weaponry.h"

class TBattleship {
public:
    TBattleship();
    TBattleship(TWeaponry weaponry, const std::string &name, const std::string &captainName, const std::string &captainRank,
                const size_t experience, const double speed, const double survivability, const size_t crewMembersAmount,
                const double fuelUsage);
    TBattleship(TWeaponry weaponry, TCaptainInfo captainInfo, const std::string &name, const double speed, 
                const double survivability, const size_t crewMembersAmount, const double fuelUsage);
    TBattleship(const TBattleship &battleship);
    TBattleship(TBattleship &&battleship);

    std::string getName() const;
    TCaptainInfo getCaptain() const;
    double getSurvivability() const;
    size_t getCrewMembersAmount() const;
    double getSpeed() const;
    TWeaponry getWeaponry() const;
    double getFuelUsage() const;

    virtual void setWeaponry(TWeaponry &weaponry);
    void setSpeed(double speed);
    void setSurvivability(double survivability);
    void setCrewMembersAmount(size_t crewMembersAmount);
    void setCaptain(const std::string &captainName, const std::string &captainRank, const size_t experience);
    void setCaptain(const TCaptainInfo &captainInfo);
    void setName(const std::string &name);
    void setFuelUsage(double fuelUsage);

    virtual double calcMaxDistance(double fuelAmount) const;

    virtual void dump(std::ostream &out) const;
    virtual void read(std::istream &in);

    virtual ~TBattleship() = default;

    TBattleship &operator=(const TBattleship &battleship);
    TBattleship &operator=(TBattleship &&battleship);
private:
    std::string _name;
    TCaptainInfo _captain;
    double _speed;
    double _survivability;
    size_t _crewMembersAmount;
    TWeaponry _weaponry;
    double _fuelUsage;
};

std::ostream &operator<<(std::ostream &out, const TBattleship &battleship);
std::istream &operator>>(std::istream &in, TBattleship &battleship);


#endif //LAB3_LIB_BATTLESHIP_H
