#ifndef LAB3_LIB_FIGHTER_H
#define LAB3_LIB_FIGHTER_H

#include "plane.h"

class TFighterPlane : public TPlane {
public:
    TFighterPlane();
    TFighterPlane(const std::string& name, TWeaponry& weaponry, double survavability, double fuelUsage);
    TFighterPlane(std::string&& name, TWeaponry&& weaponry, double survavability, double fuelUsage);

    TFighterPlane(const TFighterPlane& other);
    TFighterPlane(TFighterPlane&& other) noexcept;

    virtual TPlaneType getPlaneType() const override;

    virtual ~TFighterPlane() = default;

    TFighterPlane& operator=(const TFighterPlane& other) = default;
    TFighterPlane& operator=(TFighterPlane&& other) noexcept = default;

    virtual void dump(std::ostream& out) const override;
    virtual void read(std::istream& in) override;
};

std::ostream& operator<<(std::ostream& os, const TFighterPlane& plane);

std::istream& operator>>(std::istream& is, TFighterPlane& plane);

#endif //LAB3_LIB_FIGHTER_H
