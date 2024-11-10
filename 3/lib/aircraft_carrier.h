#ifndef LAB3_LIB_AIRCRAFT_CARRIER_H
#define LAB3_LIB_AIRCRAFT_CARRIER_H

#include "battleship.h"
#include "weaponry.h"
#include "plane_group.h"

class AircraftCarrier : virtual public TBattleship {
public:
    AircraftCarrier(TWeaponry weaponry, TPlaneGroup planes, const std::string &name, const std::string &captainName, 
            const std::string &captainRank, const size_t experience, double survivability, size_t crewMembersAmount) : TBattleship(weaponry, planes, name, captainName, captainRank, experience, survivability, crewMembersAmount),
            _weaponry(weaponry), _planes(planes) {}
private:
    TWeaponry _weaponry;
    TPlaneGroup _planes;
};

#endif //LAB3_LIB_AIRCRAFT_CARRIER_H
