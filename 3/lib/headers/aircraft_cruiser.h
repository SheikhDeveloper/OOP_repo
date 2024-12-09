#ifndef LAB3_LIB_AIRCRAFT_CRUISER_H
#define LAB3_LIB_AIRCRAFT_CRUISER_H

#include "aircraft_carrier.h"
#include "covering_ship.h"

/*@brief class Aircraft-carrying Cruiser class. */
class TAircraftCarryingCruiser : virtual public TAircraftCarrier, virtual public TCoveringShip {
public:
    /* @brief Default Constructor. */
    TAircraftCarryingCruiser();

    /* @brief Constructor. 
     * @param name - name of the aircraft. 
     * @param captainName - name of the captain. 
     * @param captainRank - rank of the captain. 
     * @param experience - experience of the captain. 
     * @param survivability - survivability of the aircraft. 
     * @param speed - speed of the aircraft. 
     * @param crewMembersAmount - amount of crew members. 
     * @param fuelUsage - fuel usage of the aircraft. 
     * @param shipToCover - ship to cover. 
     * @param weaponry - weaponry of the aircraft. 
     * @param planes - planes of the aircraft. 
     **/
    TAircraftCarryingCruiser(TWeaponry weaponry, TPlaneGroup planes, TBattleship &shipToCover, const std::string &name, 
            const std::string &captainName, const std::string &captainRank, const size_t experience, double survivability, 
            double speed, size_t crewMembersAmount, double fuelUsage);

    /* @brief Copy Constructor. 
     * @param aircraftCarryingCruiser - Cruiser to copy. 
     * */
    TAircraftCarryingCruiser(const TAircraftCarryingCruiser &aircraftCarryingCruiser);

    /* @brief Move Constructor. 
     * @param aircraftCarryingCruiser - Cruiser to move. 
     * */
    TAircraftCarryingCruiser(TAircraftCarryingCruiser &&aircraftCarryingCruiser);

    /* @brief dump to std::ostream. 
     * @param out - output stream. 
     * */ 
    virtual void dump(std::ostream &out) const override;

    /* @brief read from std::istream. 
     * @param in - input stream.
     * */
    virtual void read(std::istream &in) override;

    /* @brief Destructor. */
    virtual ~TAircraftCarryingCruiser() = default;

    /* @brief Copy assignment. 
     * @param aircraftCarryingCruiser - Cruiser to copy. 
     * @return - this. 
     * */
    virtual TAircraftCarryingCruiser &operator=(const TAircraftCarryingCruiser &aircraftCarryingCruiser);

    /* @brief Move assignment. 
     * @param aircraftCarryingCruiser - Cruiser to move. 
     * @return - this. 
     * */
    virtual TAircraftCarryingCruiser &operator=(TAircraftCarryingCruiser &&aircraftCarryingCruiser);
}; 

std::ostream &operator<<(std::ostream &out, const TAircraftCarryingCruiser &aircraftCarryingCruiser);
std::istream &operator>>(std::istream &in, TAircraftCarryingCruiser &aircraftCarryingCruiser);


#endif //LAB3_LIB_AIRCRAFT_CRUISER_H
