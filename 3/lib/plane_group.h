#ifndef LAB3_LIB_PLANE_GROUP_H
#define LAB3_LIB_PLANE_GROUP_H

#include "plane.h"
#include "hash_table.h"

class TPlaneGroup {
public:
    TPlaneGroup() = default;
    TPlaneGroup(const TPlaneGroup&);

    void addPlane(const TPlane&);
    void deletePlane(const std::string&);
    TPlane &getPlane() const;
    double getTotalDamage() const;

    ~TPlaneGroup() = default;

private:
    THashTable<std::string, TPlane> _planes;
    double _totalDamage;
};

#endif //LAB3_LIB_PLANE_GROUP_H
