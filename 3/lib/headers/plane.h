#ifndef LAB3_LIB_PLANE_H
#define LAB3_LIB_PLANE_H

#include "weaponry.h"

/* @brief Type of plane */
enum class TPlaneType
{
    fighter = 0,
    bomber
};

std::ostream &operator<<(std::ostream &out, const TPlaneType &type);
std::istream &operator>>(std::istream &in, TPlaneType &type);

/* @brief Plane class */
class TPlane {
public:
    /* @brief Default constructor */
    TPlane();

    /* @brief Constructor with lvalue parameters 
     * @param name - name of plane 
     * @param weaponry - weaponry of plane 
     * @param survivability - survivability of plane 
     * @param fuelUsage - fuel usage of plane 
     * @param type - type of plane 
     * */
    TPlane(const std::string name, TWeaponry &weaponry, double survivability, double fuelUsage, TPlaneType type);

    /* @brief Constructor with rvalue parameters 
     * @param name - name of plane 
     * @param weaponry - weaponry of plane 
     * @param survivability - survivability of plane 
     * @param fuelUsage - fuel usage of plane 
     * @param type - type of plane 
     * */
    TPlane(std::string &&name, TWeaponry &&weaponry, double survivability, double fuelUsage, TPlaneType type);

    /* @brief Copy constructor 
     * @param other - plane to copy
     * */
    TPlane(const TPlane &other) = default;

    /* @brief Move constructor 
     * @param other - plane to move
     * */
    TPlane(TPlane &&other) = default;

    /*@brief Get weaponry of plane 
     * @return Weaponry of plane 
     * */
    TWeaponry &getWeaponry();

    /* @brief Get survivability of plane 
     * @return Survivability of plane 
     * */
    double getSurvivability() const;

    /* @brief Get fuel usage of plane 
     * @return Fuel usage of plane 
     * */
    double getFuelUsage() const;

    /* @brief Get name of plane 
     * @return Name of plane 
     * */
    std::string getName() const;

    /* @brief Get type of plane 
     * @return Type of plane 
     * */
    TPlaneType getType() const;

    /* @brief Set type of plane 
     * @param newType - new type of plane 
     * */
    void setType(TPlaneType newType);

    /* @brief Set name of plane 
     * @param newName - new name of plane 
     * */
    void setName(const std::string &newName);

    /* @brief Set weaponry of plane
     * @param newWeaponry - new weaponry of plane
     * */
    virtual void setWeaponry(TWeaponry &newWeaponry);

    /* @brief Set survivability of plane
     * @param newSurvivability - new survivability of plane
     * */
    void setSurvivability(double newSurvivability);

    /* @brief Set fuel usage of plane
     * @param newFuelUsage - new fuel usage of plane
     * */
    void setFuelUsage(double newFuelUsage);

    /* @brief Set type of plane
     * @param weaponryType - new type of weaponry of plane
     *
     * @throws std::logic_error when trying to set light type to bomber
     * */
    virtual void setWeaponryType(WeaponryType weaponryType);

    /* @brief Dump plane data to output stream
     * @param out - stream to dump into
     * */
    virtual void dump(std::ostream &out) const;

    /* @brief Read plane data from input stream
     * @param in - stream to read from
     * */
    virtual void read(std::istream &in);

    /* @brieft Copy Assignment operator
     * @param other - plane to copy
     * @return Copied plane
     * */
    TPlane &operator=(const TPlane &other) = default;

    /* @brieft Move Assignment operator
     * @param other - plane to move
     * @return Moved plane
     * */
    TPlane &operator=(TPlane &&other) = default;

    /* @brief Destructor */
    virtual ~TPlane() = default;

private:
    /* @brief Name of plane */
    std::string _name;

    /* @brief Weaponry of plane */
    TWeaponry _weaponry;

    /* @brief Survivability of plane */
    double _survivability;

    /* @brief Fuel usage of plane */
    double _fuelUsage;

    /* @brief Type of plane */
    TPlaneType _type;
};

std::ostream &operator<<(std::ostream &out, const TPlane &plane);

std::istream &operator>>(std::istream &in, TPlane &plane);

#endif //LAB3_LIB_PLANE_H
