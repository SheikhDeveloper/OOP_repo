#ifndef LAB3_LIB_BATTLESHIP_GROUP_H
#define LAB3_LIB_BATTLESHIP_GROUP_H

#include "hash_table.h"
#include "captain_info.h"
#include "aircraft_carrier.h"
#include "covering_ship.h"
#include "aircraft_cruiser.h"

#include <vector>

/* @brief Type of the ship enum for getShipAmount function */
enum class ShipType
{
    AIRCRAFT_CARRIER = 0,
    COVERING_SHIP,
    AIRCRAFT_CARRYING_CRUISER,
};

std::istream &operator>>(std::istream &in, ShipType &shipType);
std::ostream &operator<<(std::ostream &out, const ShipType &shipType);


/* @brief Battleship group class */
class TBattleshipGroup
{
public:
    /* @brief Default Constructor */
    TBattleshipGroup();

    /* @brief Constructor with parameters 
     * @param[in] admiralName - name of the admiral
     * @param[in] admiralRank - rank of the admiral
     * @param[in] admiralExperience - experience of the admiral 
     * @param[in] startingPoint - starting point of the battleship group 
     * @param[in] destination - destination of the battleship group 
     * @param[in] distance - distance of the battleship group path 
     * */
    TBattleshipGroup(std::string admiralName, std::string admiralRank, size_t admiralExperience, 
                     const std::string &startingPoint, const std::string &destination, double distance);

    /* @brief Constructor with parameters and vector of TBattleship
     * @param[in] admiralName - name of the admiral
     * @param[in] admiralRank - rank of the admiral
     * @param[in] admiralExperience - experience of the admiral 
     * @param[in] startingPoint - starting point of the battleship group 
     * @param[in] destination - destination of the battleship group 
     * @param[in] distance - distance of the battleship group path 
     * @param[in] battleships - vector of TBattleship
     * */
    TBattleshipGroup(std::string admiralName, std::string admiralRank, size_t admiralExperience, 
                     const std::string &startingPoint, const std::string &destination, double distance,
                     std::vector<TBattleship> &battleships);

    /* @brief Constructor with parameters and admiral info
     * @param[in] admiral - Admiral info
     * @param[in] startingPoint - starting point of the battleship group
     * @param[in] destination - destination of the battleship group
     * @param[in] distance - distance of the battleship group path
     * */
    TBattleshipGroup(TCaptainInfo &admiral, const std::string &startingPoint, 
                     const std::string &destination, double distance);

    /* @brief Constructor with parameters and admiral info and vector of TBattleship
     * @param[in] admiral - Admiral info
     * @param[in] startingPoint - starting point of the battleship group
     * @param[in] destination - destination of the battleship group
     * @param[in] distance - distance of the battleship group path
     * @param[in] battleships - vector of TBattleship
     * */
    TBattleshipGroup(TCaptainInfo &admiral, const std::string &startingPoint, const std::string &destination, 
                     double distance, std::vector<TBattleship> &battleships);

    /* @brief Copy Constructor 
     * @param[in] battleshipGroup - battleship group to copy
     * */
    TBattleshipGroup(const TBattleshipGroup &battleshipGroup);

    /* @brief Move Constructor 
     * @param[in] battleshipGroup - battleship group to move
     * */
    TBattleshipGroup(TBattleshipGroup &&battleshipGroup);

    /* @brief Plane Getter
     * @param[in] planeName - name of the plane
     * @param[in] planeType - type of the plane
     * @param[in] carrierName - name of the carrier
     *
     * @return - plane
     * */
    TPlane &getPlane(std::string &planeName, TPlaneType planeType, const std::string &carrierName);

    /* @brief Battleship Getter
     * @param[in] battleshipName - name of the battleship
     *
     * @return - battleship
     * */
    TBattleship &getBattleship(const std::string &battleshipName);

    /* @brief get amount of ships of specified type
     * @param[in] shipType - type of the ship
     *
     * @return - amount of the ships of shipType in the group
     * */
    size_t getShipAmount(ShipType shipType) const;

    /* @brief get Admiral Info copy
     *
     * @return - admiral info copy
     * */
    TCaptainInfo getAdmiralInfo() const;

    /* @brief get Admiral Info reference
     *
     * @return - admiral info reference
     * */
    TCaptainInfo &getAdmiralInfo();

    /* @brief Get starting point
     *
     * @return - starting point
     * */
    std::string getStartingPoint() const;

    /* @brief Get destination
     *
     * @return - destination
     * */
    std::string getDestination() const;

    /* @brief Get distance
     *
     * @return - distance
     * */
    double getDistance() const;

    /* @brief Add plane
     * @param[in] plane - plane to add
     * @param[in] carrierName - name of the carrier
     * */
    void addPlane(TPlane &plane, const std::string &carrierName);

    /* @brief Add battleship
     * @param[in] battleship - battleship to add
     * */
    void addBattleship(TBattleship &battleship);

    /* @brief Remove plane
     * @param[in] planeName - name of the plane
     * @param[in] carrierName - name of the carrier
     * */
    void removePlane(const std::string &planeName, const std::string &carrierName);

    /* @brief Remove battleship
     * @param[in] battleshipName - name of the battleship
     * */
    void removeBattleship(const std::string &battleshipName);

    /* @brief Size of the group
     *
     * @return - size of the group
     * */
    size_t size() const;

    /* @brief Set admiral
     * @param[in] admiral - new admiral
     * */
    void setAdmiral(TCaptainInfo &admiral);

    /* @brief Set starting point
     * @param[in] startingPoint - new starting point
     * */
    void setStartingPoint(const std::string &startingPoint);

    /* @brief Set destination
     * @param[in] destination - new destination
     * */
    void setDestination(const std::string &destination);

    /* @brief Set distance
     * @param[in] distance - new distance
     * */
    void setDistance(double distance);

    /* @brief Relocate plane
     * @param[in] planeName - name of the plane
     * @param[in] planeType - type of the plane
     * @param[in] carrierName1 - name of the carrier from which the plane will be relocated
     * @param[in] carrierName2 - name of the carrier to which the plane will be relocated
     * */
    void relocatePlane(std::string planeName, TPlaneType planeType, const std::string carrierName1, const std::string carrierName2);

    /* @brief Simulate attack
     * @param[in] attackingGroup - attacking group
     * @param[in] numWorkers - number of parallel threads
     * */
    void simulateAttack(TPlaneGroup &attackingGroup, size_t numWorkers = 3);

    /* @brief Dump
     * @param[in] out - output stream
     * */
    virtual void dump(std::ostream &out) const;

    /* @brief Read
     * @param[in] in - input stream
     * */
    virtual void read(std::istream &in);

    /* @brief Default Destructor */
    virtual ~TBattleshipGroup() = default;

    /* @brief Copy assignment operator 
     * @param[in] battleshipGroup - battleship group to copy
     * @return - copy of the battleship group
     * */
    TBattleshipGroup &operator=(const TBattleshipGroup &battleshipGroup) = default;

    /* @brief Move assignment operator 
     * @param[in] battleshipGroup - battleship group to move
     * @return - move of the battleship group
     * */
    TBattleshipGroup &operator=(TBattleshipGroup &&battleshipGroup) = default;
private:

    /* @brief Vessel class to contain Battleship and correctly cast it to derived classes
     * */
    class BattleshipVessel {
        public:
        /* Battleship pointer */
        TBattleship *battleshipPtr_ = nullptr;

        /* @brief Default constructor */
        BattleshipVessel() = default;

        /* @brief Constructor with parameters
         * @param[in] battleship - battleship to store
         * */
        BattleshipVessel(TBattleship &battleship);

        /* @brief Constructor with parameters
         * @param[in] battleship_ptr - pointer to the battleship
         * */
        BattleshipVessel(TBattleship *battleship_ptr);

        /* @brief dereference operator */
        TBattleship &operator*();

        /* @brief Destructor */
        ~BattleshipVessel() = default;
    };

    /* @brief Hash table of the vessels */
    THashTable<std::string, BattleshipVessel> _battleshipGroup;

    /* @brief Admiral info */
    TCaptainInfo _admiral;

    /* @brief Starting point */
    std::string _startingPoint;

    /* @brief Destination */
    std::string _destination;

    /* @brief Distance */
    double _distance;

    /* @brief Get Battleship Vessel
     * @param[in] battleshipName - name of the battleship
     * @return - Vessel reference
     * */
    BattleshipVessel &getBattleshipVessel(const std::string &battleshipName);

    /* @brief Relocate plane
     * @param[in] planeName - name of the plane
     * @param[in] planeType - type of the plane
     * @param[in] aircraftCarrier1 - carrier from which the plane will be relocated
     * @param[in] aircraftCarrier2 - carrier to which the plane will be relocated
     * */
    void relocatePlane(std::string planeName, TPlaneType planeType, BattleshipVessel &aircraftCarrier1, BattleshipVessel &aircraftCarrier2);
};

std::ostream &operator<<(std::ostream &out, const TBattleshipGroup &battleshipGroup);
std::istream &operator>>(std::istream &in, TBattleshipGroup &battleshipGroup);



#endif //LAB3_LIB_BATTLESHIP_GROUP_H
