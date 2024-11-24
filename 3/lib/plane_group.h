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
    size_t size() const;

    void setPlaneAmount(size_t planeAmount);
    void dump(std::ostream&) const;
    void read(std::istream&);

    ~TPlaneGroup() = default;

    TPlaneGroup &operator=(const TPlaneGroup& planeGroup);

    TPlaneGroup &operator=(TPlaneGroup&& planeGroup);

private:
    THashTable<std::string, TPlane> _planes;
    size_t _planeAmount;
    double _totalDamage;
};

#endif //LAB3_LIB_PLANE_GROUP_H
