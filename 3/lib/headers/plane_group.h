#ifndef LAB3_LIB_PLANE_GROUP_H
#define LAB3_LIB_PLANE_GROUP_H

#include "plane.h"
#include "hash_table.h"
#include "battleship.h"

/*@brief Plane Group class*/
class TPlaneGroup {
public:

    /*@brief Default Constructor*/
    TPlaneGroup();
    
    /*@brief Copy Constructor
     * @param planeGroup - plane group to copy
     * */
    TPlaneGroup(const TPlaneGroup&);

    /*@brief Move Constructor
     * @param planeGroup - plane group to move
     * */
    TPlaneGroup(TPlaneGroup&&);

    /*@brief Add plane
     * @param plane - plane to add
     * */
    void addPlane(TPlane& plane);

    /*@brief Delete plane
     * @param name - name of plane to delete
     *
     * @throws std::invalid_argument if plane with given name doesn't exist
     * */
    void deletePlane(const std::string& name);

    /*@brief Get plane
     * @param name - name of plane
     * @param planeType - type of plane
     *
     * @throws std::invalid_argument if plane with given name doesn't exist
     * */
    TPlane &getPlane(std::string &name, TPlaneType planeType);

    /*@brief Get total damage
     * @return total damage
     * */
    double getTotalDamage() const;

    /*@brief Get size of the plane group
     * @return size
     * */
    size_t size() const;

    /*@brief Attack a Battleship
     * @param target - target of attack
     * */
    void attack(TBattleship &target);

    /*@brief Dump plane group into output stream
     * @param out - output stream
     * */
    void dump(std::ostream &out) const;

    /*@brief Read plane group from input stream
     * @param in - input stream
     * */
    void read(std::istream &in);

    /*@brief Destructor*/
    ~TPlaneGroup() = default;

    /*@brief Brace operator
     * @param name - name of plane to get
     * @return plane
     * */
    TPlane &operator[](const std::string &name);

    /*@brief Copy assignment operator
     * @param planeGroup - plane group to copy
     * @return plane group
     * */
    TPlaneGroup &operator=(const TPlaneGroup& planeGroup);

    /*@brief Move assignment operator
     * @param planeGroup - plane group to move
     * @return plane group
     * */
    TPlaneGroup &operator=(TPlaneGroup&& planeGroup);

private:

    /*@brief Hash table of planes */
    THashTable<std::string, TPlane> _planes;

    /*@brief Total damage to planes from planes in the group*/
    double _planeDamage = 0.;

    /*@brief Total damage to ships from planes in the group*/
    double _shipDamage = 0.;

    /*@brief Amount of Bombers in the group*/
    size_t _bomberAmount = 0;

    /*@brief Amount of Fighters in the group*/
    size_t _fightersAmount = 0;
};

std::ostream &operator<<(std::ostream &out, const TPlaneGroup &planeGroup);
std::istream &operator>>(std::istream &in, TPlaneGroup &planeGroup);

#endif //LAB3_LIB_PLANE_GROUP_H
