#ifndef LAB3_LIB_AIRCRAFT_CRUISER_H
#define LAB3_LIB_AIRCRAFT_CRUISER_H

#include "aircraft_carrier.h"
#include "covering_ship.h"

class TAircraftCarryingCruiser : virtual public TAircraftCarrier, virtual public TCoveringShip {
public:
    TAircraftCarryingCruiser();
    TAircraftCarryingCruiser(TWeaponry weaponry, TPlaneGroup planes, TBattleship &shipToCover, const std::string &name, 
            const std::string &captainName, const std::string &captainRank, const size_t experience, double survivability, 
            double speed, size_t crewMembersAmount, double fuelUsage);
    TAircraftCarryingCruiser(const TAircraftCarryingCruiser &aircraftCarryingCruiser);
    TAircraftCarryingCruiser(TAircraftCarryingCruiser &&aircraftCarryingCruiser);

    virtual void dump(std::ostream &out) const override;
    virtual void read(std::istream &in) override;


    virtual ~TAircraftCarryingCruiser() = default;

    virtual TAircraftCarryingCruiser &operator=(const TAircraftCarryingCruiser &aircraftCarryingCruiser);
    virtual TAircraftCarryingCruiser &operator=(TAircraftCarryingCruiser &&aircraftCarryingCruiser);
}; 

std::ostream &operator<<(std::ostream &out, const TAircraftCarryingCruiser &aircraftCarryingCruiser);
std::istream &operator>>(std::istream &in, TAircraftCarryingCruiser &aircraftCarryingCruiser);


#endif //LAB3_LIB_AIRCRAFT_CRUISER_H
