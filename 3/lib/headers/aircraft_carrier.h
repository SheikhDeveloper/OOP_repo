#ifndef LAB3_LIB_AIRCRAFT_CARRIER_H
#define LAB3_LIB_AIRCRAFT_CARRIER_H

#include "battleship.h"
#include "weaponry.h"
#include "plane_group.h"

/** @brief Class for Aircraft carrier */
class TAircraftCarrier : public TBattleship {
public:
    /** @brief default constructor */
    TAircraftCarrier();

    /** @brief constructor 
     * @param weaponry - weaponry of the aircraft carrier
     * @param planes - planes of the aircraft carrier
     * @param name - name of the aircraft carrier
     * @param captainName - name of the captain of the aircraft carrier
     * @param captainRank - rank of the captain of the aircraft carrier
     * @param experience - experience of the aircraft carrier
     * @param survivability - survivability of the aircraft carrier
     * @param speed - speed of the aircraft carrier
     * @param crewMembersAmount - amount of crew members of the aircraft carrier
     * @param fuelUsage - fuel usage of the aircraft carrier
     * */
    TAircraftCarrier(TWeaponry weaponry, TPlaneGroup planes, const std::string &name, const std::string &captainName, 
            const std::string &captainRank, const size_t experience, double survivability, double speed, size_t crewMembersAmount, double fuelUsage);

    /** @brief copy constructor 
     * @param aircraftCarrier - aircraft carrier to copy
     * */
    TAircraftCarrier(const TAircraftCarrier &aircraftCarrier);

    /** @brief move constructor 
     * @param aircraftCarrier - aircraft carrier to move
     * */
    TAircraftCarrier(TAircraftCarrier &&aircraftCarrier);

    /** @brief getter for planes 
     * 
     * @return planes 
     * */
    virtual TPlaneGroup &getPlaneInfo();

    /** @brief getter for plane damage
     * 
     * @return plane damage
     * */
    virtual double calcPlaneDamage() const;

    /** @brief setter for weaponry
     * @param weaponry - weaponry
     * */
    virtual void setWeaponry(TWeaponry &weaponry) override;

    /** @brief setter for planes
     * @param planes - planes
     * */
    virtual void setPlaneInfo(TPlaneGroup &planes);

    /** @brief getter for plane
     * @param name - name of the plane
     * @param planeType - type of the plane
     * @return plane
     * */
    TPlane &getPlane(std::string &name, TPlaneType planeType);

    /** @brief add plane
     * @param plane - plane to add
     * */
    virtual void addPlane(TPlane &plane);

    /** @brief delete plane
     * @param planeName - name of the plane to delete
     * */
    virtual void deletePlane(const std::string &planeName);

    /** @brief dump to stream
     * @param out - stream
     * */
    virtual void dump(std::ostream &out) const override;

    /** @brief read from stream
     * @param in - stream
     * */
    virtual void read(std::istream &in) override;

    /** @brief destructor */
    virtual ~TAircraftCarrier() = default;

    /** @brief copy assignment operator
     * @param aircraftCarrier - aircraft carrier to copy
     * @return aircraft carrier
     * */
    virtual TAircraftCarrier &operator=(const TAircraftCarrier &aircraftCarrier);

    /** @brief move assignment operator
     * @param aircraftCarrier - aircraft carrier to move
     * @return aircraft carrier
     * */
    virtual TAircraftCarrier &operator=(TAircraftCarrier &&aircraftCarrier);
private:
    /** @brief planes */
    TPlaneGroup _planes;
};

std::ostream &operator<<(std::ostream &out, const TAircraftCarrier &aircraftCarrier);

std::istream &operator>>(std::istream &in, TAircraftCarrier &aircraftCarrier);

#endif //LAB3_LIB_AIRCRAFT_CARRIER_H
