#ifndef LAB3_LIB_AIRCRAFT_CARRIER_H
#define LAB3_LIB_AIRCRAFT_CARRIER_H

#include "battleship.h"
#include "weaponry.h"
#include "plane_group.h"

class AircraftCarrier : virtual public TBattleship {
public:
    AircraftCarrier(TWeaponry weaponry, TPlaneGroup planes, const std::string &name, const std::string &captainName, 
            const std::string &captainRank, const size_t experience, double survivability, size_t crewMembersAmount);

    virtual std::pair<size_t, TPlaneGroup &> getPlaneInfo() const;
    virtual double calcPlaneDamage() const;
    virtual void setPlaneInfo(TPlaneGroup planes, size_t planeAmount);
    virtual void setPlaneAmount(size_t planeAmount);
    virtual void dump(std::ostream &out) const;

    virtual ~AircraftCarrier() = default;
private:
    TPlaneGroup _planes;
};

#endif //LAB3_LIB_AIRCRAFT_CARRIER_H
