#ifndef LAB3_LIB_AIRCRAFT_CARRIER_H
#define LAB3_LIB_AIRCRAFT_CARRIER_H

#include "battleship.h"
#include "weaponry.h"
#include "plane_group.h"

class TAircraftCarrier : virtual public TBattleship {
public:
    TAircraftCarrier(TWeaponry weaponry, TPlaneGroup planes, const std::string &name, const std::string &captainName, 
            const std::string &captainRank, const size_t experience, double survivability, size_t crewMembersAmount);

    TAircraftCarrier(const TAircraftCarrier &aircraftCarrier);
    TAircraftCarrier(TAircraftCarrier &&aircraftCarrier);

    virtual std::pair<size_t, TPlaneGroup &> getPlaneInfo() const;
    virtual double calcPlaneDamage() const;
    virtual void setPlaneInfo(TPlaneGroup planes, size_t planeAmount);
    virtual void setPlaneAmount(size_t planeAmount);
    void setPlaneType(TPlane &plane);
    virtual void dump(std::ostream &out) const;

    virtual ~TAircraftCarrier() = default;

    virtual TAircraftCarrier &operator=(const TAircraftCarrier &aircraftCarrier);
    virtual TAircraftCarrier &operator=(const TAircraftCarrier &&aircraftCarrier);
private:
    TPlaneGroup _planes;
};

#endif //LAB3_LIB_AIRCRAFT_CARRIER_H
