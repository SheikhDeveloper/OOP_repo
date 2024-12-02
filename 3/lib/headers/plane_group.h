#ifndef LAB3_LIB_PLANE_GROUP_H
#define LAB3_LIB_PLANE_GROUP_H

#include "plane.h"
#include "hash_table.h"
#include "battleship.h"


class TPlaneGroup {
public:
    TPlaneGroup() = default;
    TPlaneGroup(const TPlaneGroup&);

    TPlaneGroup(TPlaneGroup&&);

    void addPlane(TPlane& plane);
    void deletePlane(const std::string& name);
    TPlane &getPlane(std::string &name, TPlaneType planeType);
    double getTotalDamage() const;
    size_t size() const;
    void attack(TBattleship &target);

    void dump(std::ostream &out) const;
    void read(std::istream &in);

    ~TPlaneGroup() = default;

    TPlane &operator[](const std::string &name);
    TPlaneGroup &operator=(const TPlaneGroup& planeGroup);
    TPlaneGroup &operator=(TPlaneGroup&& planeGroup);

private:
    THashTable<std::string, TPlane> _planes;
    double _planeDamage;
    double _shipDamage;
    double _bomberAmount;
    double _fightersAmount;
};

std::ostream &operator<<(std::ostream &out, const TPlaneGroup &planeGroup);
std::istream &operator>>(std::istream &in, TPlaneGroup &planeGroup);

#endif //LAB3_LIB_PLANE_GROUP_H
