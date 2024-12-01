#ifndef LAB3_LIB_BOMBER_H
#define LAB3_LIB_BOMBER_H

#include "plane.h"
#include "weaponry.h"

class TBomberPlane : public TPlane {
public:

    TBomberPlane();

    TBomberPlane(std::string& name, TWeaponry& weaponry, double survivability, double fuelUsage);
    TBomberPlane(std::string&& name, TWeaponry&& weaponry, double survivability, double fuelUsage); 

    TBomberPlane(const TBomberPlane& plane);
    TBomberPlane(TBomberPlane&& plane);

    TPlaneType getPlaneType() const override;

    TBomberPlane& operator=(const TBomberPlane& plane) = default;
    TBomberPlane& operator=(TBomberPlane&& plane) = default;

    void dump(std::ostream& os) const override;
    void read(std::istream& is) override;

    virtual ~TBomberPlane() = default;
};

std::ostream& operator<<(std::ostream& os, const TBomberPlane& plane);
std::istream& operator>>(std::istream& is, TBomberPlane& plane);

#endif //LAB3_LIB_BOMBER_H
