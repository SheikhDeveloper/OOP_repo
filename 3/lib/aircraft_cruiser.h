#ifndef LAB3_LIB_AIRCRAFT_CRUISER_H
#define LAB3_LIB_AIRCRAFT_CRUISER_H

#include "aircraft_carrier.h"
#include "covering_ship.h"

class AircraftCarryingCruiser : public AircraftCarrier, public CoveringShip {
public:

    AircraftCarryingCruiser(TWeaponry weaponry, TPlaneGroup planes, TBattleship &shipToCover, const std::string &name, 
            const std::string &captainName, const std::string &captainRank, const size_t experience, double survivability, 
            size_t crewMembersAmount);
    AircraftCarryingCruiser(const AircraftCarryingCruiser &aircraftCarryingCruiser);
    AircraftCarryingCruiser(AircraftCarryingCruiser &&aircraftCarryingCruiser);

    virtual std::pair<size_t, TPlaneGroup &> getPlaneInfo() const override;
    virtual double calcPlaneDamage() const override;
    virtual void setPlaneInfo(TPlaneGroup planes, size_t planeAmount) override;
    virtual void setPlaneAmount(size_t planeAmount) override;
    virtual void dump(std::ostream &out) const override;


    virtual ~AircraftCarryingCruiser() = default;

    virtual AircraftCarryingCruiser &operator=(const AircraftCarryingCruiser &aircraftCarryingCruiser);
    virtual AircraftCarryingCruiser &operator=(AircraftCarryingCruiser &&aircraftCarryingCruiser);
}; 


#endif //LAB3_LIB_AIRCRAFT_CRUISER_H
