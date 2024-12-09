#ifndef LAB3_LIB_WEAPONRY_H
#define LAB3_LIB_WEAPONRY_H

#include <string>

/*@brief Weaponry type enum */
enum class WeaponryType
{
    light = 0,
    heavy = 1
};

std::ostream &operator<<(std::ostream &out, const WeaponryType &type);
std::istream &operator>>(std::istream &in, WeaponryType &type);

/*@brief TWeaponry class */
class TWeaponry
{
public:

    /*@brief Default constructor */
    TWeaponry();

    /*@brief Constructor
     * @param name - name of the weaponry
     * @param ammoName - name of the ammunition
     * @param ammoAmount - amount of ammunition
     * @param damage - damage of the weaponry 
     * @param type - type of the weaponry 
     * */
    TWeaponry(const std::string& name, const std::string& ammoName, size_t ammoAmount, double damage, WeaponryType type);

    /*@brief Copy constructor 
     * @param other - another TWeaponry object to copy
     * */
    TWeaponry(const TWeaponry& other) = default;

    /*@brief Move constructor 
     * @param other - another TWeaponry object to move
     * */
    TWeaponry(TWeaponry&& other) = default;

    /* @brief Get weaponry name 
     * @return name of the weaponry 
     * */
    std::string getName() const;

    /* @brief Get weaponry ammunition name
     * @return name of the ammunition
     * */
    std::string getAmmoName() const;

    /* @brief Get weaponry ammunition amount
     * @return amount of ammunition
     * */
    size_t getAmmoAmount() const;

    /* @brief Get weaponry damage
     * @return damage of the weaponry
     * */
    double getDamage() const;

    /* @brief Get weaponry type
     * @return type of the weaponry
     * */
    WeaponryType getType() const;

    /* @brief Set weaponry name
     * @param name - new name of the weaponry
     * */
    void setName(const std::string& name);

    /* @brief Set ammunition name
     * @param ammoName - new name of the ammunition
     * */
    void setAmmoName(const std::string& ammoName);

    /* @brief Set ammunition amount
     * @param ammoAmount - new amount of ammunition
     * */
    void setAmmoAmount(size_t ammoAmount);

    /* @brief Set weaponry damage
     * @param damage - new damage of the weaponry
     * */
    void setDamage(double damage);

    /* @brief Set weaponry type
     * @param type - new type of the weaponry
     * */
    void setType(WeaponryType type);

    /* @brief Print information about the object
     * @param out - output stream
     * */
    void dump(std::ostream &out) const;

    /* @brief Read information about the object
     * @param in - input stream
     * */
    void read(std::istream &in);

    /* @brief Destructor */
    ~TWeaponry() = default;

    /* @brief Copy assignment operator 
     * @param other - Weaponry to copy
     * @return Weaponry
     * */
    TWeaponry& operator=(const TWeaponry& other) = default;

    /* @brief Move assignment operator 
     * @param other - Weaponry to move
     * @return Weaponry
     * */
    TWeaponry& operator=(TWeaponry&& other) = default;

private:

    /* @brief Name of the weaponry */
    std::string _name;

    /* @brief Name of the ammunition */
    std::string _ammoName;

    /* @brief Amount of ammunition */
    size_t _ammoAmount;

    /* @brief Damage of the weaponry */
    double _damage;

    /* @brief Type of the weaponry */
    WeaponryType _type;
};

std::ostream &operator<<(std::ostream &out, const TWeaponry &weaponry);
std::istream &operator>>(std::istream &in, TWeaponry &weaponry);

#endif //LAB3_LIB_WEAPONRY_H
