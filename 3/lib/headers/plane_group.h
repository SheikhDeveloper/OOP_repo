#ifndef LAB3_LIB_PLANE_GROUP_H
#define LAB3_LIB_PLANE_GROUP_H

#include "plane.h"
#include "hash_table.h"

class TPlaneGroup {
public:
    TPlaneGroup() = default;
    TPlaneGroup(const TPlaneGroup&);

    TPlaneGroup(TPlaneGroup&&);

    void addPlane(const TPlane&);
    void deletePlane(const std::string& name);
    TPlane &getPlane(std::string &name);
    double getTotalDamage() const;
    size_t size() const;

    void dump(std::ostream &out) const;
    void read(std::istream &in);

    ~TPlaneGroup() = default;

    TPlaneGroup &operator=(const TPlaneGroup& planeGroup);

    TPlaneGroup &operator=(TPlaneGroup&& planeGroup);

private:
    THashTable<std::string, TPlane> _planes;
    double _totalDamage;
};

std::ostream &operator<<(std::ostream &out, const TPlaneGroup &planeGroup);
std::istream &operator>>(std::istream &in, TPlaneGroup &planeGroup);

#endif //LAB3_LIB_PLANE_GROUP_H
