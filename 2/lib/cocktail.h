#ifndef LAB2_LIB_COCKTAIL_H
#define LAB2_LIB_COCKTAIL_H

#include <string>

/**
 * Represents a cocktail with its name, alcohol percentage, and volume.
 */
class TCocktail
{
public:
    /**
     * Default constructor. Initializes a new TCocktail object with default values.
     */
    TCocktail();

    /**
     * Constructor with parameters. Initializes a new TCocktail object with the given name, alcohol percentage, and volume.
     *
     * @param name Name of the cocktail
     * @param alchol_percentage Alcohol percentage of the cocktail
     * @param volume Volume of the cocktail
     */
    TCocktail(std::wstring &name, double alchol_percentage, double volume);


    TCocktail(std::wstring &&custom_name_, double alc_percentage, double vol);

    /**
     * Constructor with a single parameter. Initializes a new TCocktail object with the given volume and default values for name and alcohol percentage.
     *
     * @param volume Volume of the cocktail
     */
    TCocktail(double volume);

    /**
     * Destructor. Releases any resources held by the TCocktail object.
     */
    ~TCocktail() = default;

    /**
     * Returns the name of the cocktail.
     *
     * @return Name of the cocktail
     */
    const std::wstring getName() const;

    /**
     * Returns the alcohol percentage of the cocktail.
     *
     * @return Alcohol percentage of the cocktail
     */
    double getAlcoholPercentage() const;

    /**
     * Returns the volume of the cocktail.
     *
     * @return Volume of the cocktail
     */
    double getVolume() const;

    /**
     * Sets the name of the cocktail.
     *
     * @param name Name of the cocktail
     */
    void setName(const std::wstring &name);

    /**
     * Sets the alcohol percentage of the cocktail.
     *
     * @param alchol_percentage Alcohol percentage of the cocktail
     */
    void setAlcoholPercentage(double alchol_percentage);

    /**
     * Sets the volume of the cocktail.
     *
     * @param volume Volume of the cocktail
     */
    void setVolume(double volume);

    /**
     * Pours <=100. ml of the cocktail2 into the current cocktail.
     *
     * @param cocktail2 Cocktail to pour.
     */
    void operator>>(TCocktail &cocktail2);

    /**
     * Dumps the cocktail's data to the output stream out.
     *
     * @param out Output stream
     */
    void dump(std::wostream &out) const;

    /**
     * Reads the cocktail's data from the input stream in.
     *
     * @param in Input stream
     */
    void read(std::wistream &in);
    
    private:
    std::wstring name_{L""}; ///< Name of the cocktail
    double alcohol_percentage_ = 0.; ///< Alcohol percentage of the cocktail
    double volume_ = 0.; ///< Volume of the cocktail
};

     /**
     * Returns a new TCocktail object that is the mix of the current cocktail and the given cocktail2.
     *
     * @param cocktail2 Cocktail to add to the current object
     * @return New TCocktail object
     */
    TCocktail operator+(const TCocktail &cocktail1, const TCocktail &cocktail2);

    /**
     * Multiplies the current cocktail volume by the given multiplier.
     *
     * @param multiplier Multiplier
     * @return New TCocktail object
     */
    TCocktail operator*(const TCocktail cocktail, const double multiplier);

    /**
     * Multiplies the current cocktail volume by the given multiplier.
     *
     * @param multiplier Multiplier
     * @return New TCocktail object
     */
    TCocktail operator*(const double multiplier, const TCocktail cocktail);

    /**
     * Inserts the given cocktail object's data into the output stream out.
     *
     * @param out Output stream to insert data into
     * @param cocktail Cocktail to insert data from
     * @return Output stream
     */
    std::wostream &operator<<(std::wostream &out, const TCocktail &cocktail);

    /**
     * Extracts data from the input stream in and inserts it into the given cocktail object.
     *
     * @param in Input stream to extract data from
     * @param cocktail Cocktail to insert data into
     * @return Input stream
     */
    std::wistream &operator>>(std::wistream &in, TCocktail &cocktail);

    /**
     * Checks if the given cocktail objects are equal.
     * 
     * @param cocktail1 First cocktail
     * @param cocktail2 Second cocktail
     * @return True if the objects are equal, false otherwise
     */
    bool operator==(const TCocktail &cocktail1, const TCocktail &cocktail2);

#endif //LAB2_COCKTAIL_H
