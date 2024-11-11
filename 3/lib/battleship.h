#ifndef LAB3_LIB_BATTLESHIP_H
#define LAB3_LIB_BATTLESHIP_H

#include "captain_info.h"
#include "weaponry.h"

class TBattleship {
public:

    TBattleship(TWeaponry weaponry, const std::string &name, const std::string &captainName, const std::string &captainRank, const size_t experience, double survivability, size_t crewMembersAmount);

    std::string getName() const;
    TCaptainInfo getCaptain() const;
    double getSurvivability() const;
    size_t getCrewMembersAmount() const;
    double getSpeed() const;

    void setSpeed(double speed);
    void setSurvivability(double survivability);
    void setCrewMembersAmount(size_t crewMembersAmount);
    void setCaptain(const std::string &captainName, const std::string &captainRank, const size_t experience);
    void setName(const std::string &name);

    void dump(std::ostream &out) const;
    void read(std::istream &in);

    virtual ~TBattleship() = default;

private:
    std::string _name;
    TCaptainInfo _captain;
    double _speed;
    double _survivability;
    size_t _crewMembersAmount;
    TWeaponry _weaponry;
};

#endif //LAB3_LIB_BATTLESHIP_H
