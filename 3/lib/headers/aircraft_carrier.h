#ifndef LAB3_LIB_AIRCRAFT_CARRIER_H
#define LAB3_LIB_AIRCRAFT_CARRIER_H

#include "battleship.h"
#include "weaponry.h"
#include "plane_group.h"

class TAircraftCarrier : virtual public TBattleship {
public:
    TAircraftCarrier();
    TAircraftCarrier(TWeaponry weaponry, TPlaneGroup planes, const std::string &name, const std::string &captainName, 
            const std::string &captainRank, const size_t experience, double survivability, size_t crewMembersAmount);

    TAircraftCarrier(TPlaneGroup planes);

    TAircraftCarrier(const TAircraftCarrier &aircraftCarrier);
    TAircraftCarrier(TAircraftCarrier &&aircraftCarrier);

    virtual std::pair<size_t, TPlaneGroup> getPlaneInfo() const;

    virtual double calcPlaneDamage() const;

    virtual void setWeaponry(TWeaponry weaponry) override;
    virtual void setPlaneInfo(TPlaneGroup planes);
    void setPlaneType(TPlane &plane);
    virtual void dump(std::ostream &out) const override;
    virtual void read(std::istream &in) override;

    virtual ~TAircraftCarrier() = default;

    virtual TAircraftCarrier &operator=(const TAircraftCarrier &aircraftCarrier);
    virtual TAircraftCarrier &operator=(TAircraftCarrier &&aircraftCarrier);
private:
    TPlaneGroup _planes;
};

std::ostream &operator<<(std::ostream &out, const TAircraftCarrier &aircraftCarrier);

std::istream &operator>>(std::istream &in, TAircraftCarrier &aircraftCarrier);

#endif //LAB3_LIB_AIRCRAFT_CARRIER_H
