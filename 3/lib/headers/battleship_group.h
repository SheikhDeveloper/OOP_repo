#ifndef LAB3_LIB_BATTLESHIP_GROUP_H
#define LAB3_LIB_BATTLESHIP_GROUP_H

#include "hash_table.h"
#include "captain_info.h"
#include "aircraft_carrier.h"
#include "covering_ship.h"
#include "aircraft_cruiser.h"

#include <vector>

enum class ShipType
{
    AIRCRAFT_CARRIER = 0,
    COVERING_SHIP,
    AIRCRAFT_CARRYING_CRUISER,
};

std::istream &operator>>(std::istream &in, ShipType &shipType);
std::ostream &operator<<(std::ostream &out, const ShipType &shipType);

class TBattleshipGroup
{
public:
    TBattleshipGroup();
    TBattleshipGroup(std::string admiralName, std::string admiralRank, size_t admiralExperience, 
                     const std::string &startingPoint, const std::string &destination, double distance);
    TBattleshipGroup(std::string admiralName, std::string admiralRank, size_t admiralExperience, 
                     const std::string &startingPoint, const std::string &destination, double distance,
                     std::vector<TBattleship> &battleships);
    TBattleshipGroup(TCaptainInfo &admiral, const std::string &startingPoint, 
                     const std::string &destination, double distance);
    TBattleshipGroup(TCaptainInfo &admiral, const std::string &startingPoint, const std::string &destination, 
                     double distance, std::vector<TBattleship> &battleships);

    TBattleshipGroup(const TBattleshipGroup &battleshipGroup);
    TBattleshipGroup(TBattleshipGroup &&battleshipGroup);

    TPlane &getPlane(std::string &planeName, TPlaneType planeType, const std::string &carrierName);
    TBattleship &getBattleship(const std::string &battleshipName);
    size_t getShipAmount(ShipType shipType) const;

    void addPlane(TPlane &plane, const std::string &carrierName);
    void addBattleship(TBattleship &battleship);
    void removePlane(const std::string &planeName, const std::string &carrierName);
    void removeBattleship(const std::string &battleshipName);

    void setAdmiral(TCaptainInfo &admiral);
    void setStartingPoint(const std::string &startingPoint);
    void setDestination(const std::string &destination);
    void setDistance(double distance);
    void relocatePlane(const std::string planeName, const std::string carrierName1, const std::string carrierName2);
    void simulateAttack(TPlaneGroup &attackingGroup);
    virtual void dump(std::ostream &out) const;
    virtual void read(std::istream &in);
    virtual ~TBattleshipGroup() = default;

    TBattleshipGroup &operator=(const TBattleshipGroup &battleshipGroup) = default;
    TBattleshipGroup &operator=(TBattleshipGroup &&battleshipGroup) = default;
private:
    THashTable<std::string, TBattleship> _battleshipGroup;
    TCaptainInfo _admiral;
    std::string _startingPoint;
    std::string _destination;
    double _distance;

    void relocatePlane(const std::string planeName, TAircraftCarrier &aircraftCarrier1, TAircraftCarrier &aircraftCarrier2);
};



#endif //LAB3_LIB_BATTLESHIP_GROUP_H
