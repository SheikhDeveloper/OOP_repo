#ifndef LAB2_LIB_COCKTAIL_CARD_H
#define LAB2_LIB_COCKTAIL_CARD_H

#include "cocktail.h"
#include "hash_table.h"

/**
 * Represents a collection of cocktails.
 */
class TCocktailCard {
public:
    /**
     * Default constructor. Initializes an empty collection.
     */
    TCocktailCard() = default;

    /**
     * Constructor with an array of cocktails. Initializes a collection with the given cocktails.
     *
     * @param cocktails Array of cocktails to add
     * @param cocktails_count Number of cocktails in the array
     */
    TCocktailCard(const TCocktail *cocktails, size_t cocktails_count);

    /**
     * Copy constructor. Initializes a collection as a copy of another collection.
     *
     * @param other Collection to copy
     */
    TCocktailCard(const TCocktailCard &other);

    /**
     * Move constructor. Initializes a collection by moving another collection.
     *
     * @param other Collection to move
     */
    TCocktailCard(TCocktailCard &&other) = default;

    /**
     * Destructor. Releases any resources held by the collection.
     */
    ~TCocktailCard() = default;

    /**
     * Checks if the collection is empty.
     *
     * @return True if the collection is empty, false otherwise
     */
    bool isEmpty() const;

    /**
     * Gets the size of the collection.
     *
     * @return Size of the collection
     */
    size_t size() const;

    /**
     * Gets the capacity of the collection.
     *
     * @return Capacity of the collection
     */
    size_t capacity() const;

    /**
     * Removes a cocktail from the collection by name.
     *
     * @param name Name of the cocktail to remove
     */
    void removeCocktail(const std::wstring &name);

    /**
     * Gets a cocktail from the collection by alcohol percentage range and volume.
     *
     * @param alc_percentage_range Range of alcohol percentages
     * @param volume Volume of the cocktail (default: 500)
     * @return Found cocktail
     */
    const TCocktail getCocktail(const std::pair<const double, const double> alc_percentage_range, const double &volume=500.);

    /**
     * Gets the volume of cocktails in a given alcohol percentage quartile.
     *
     * @param quartile Quartile of cocktails
     * @return Volume of cocktails within the given alcohol percentage quartile
     */
    double getVolumeByQuartile(const std::pair<const double, const double> &quartile);

    /**
     * Renames a cocktail in the collection.
     *
     * @param old_name Old name of the cocktail
     * @param new_name New name of the cocktail
     */
    void renameCocktail(const std::wstring &old_name, const std::wstring &new_name);

    /**
     * Prints the collection to an output stream.
     *
     * @param out Output stream to print to
     */
    void printCard(std::wostream &out);

    /**
     * Finds a cocktail in the collection by name.
     *
     * @param name Name of the cocktail to find
     * @return Found cocktail
     */
    const TCocktail& findCocktail(const std::wstring &name);


    /**
     * Dumps the collection to an output stream.
     * 
     * @param out Output stream to dump to
     */
    void dump(std::wostream &out);

    /**
     * Reads the collection from an input stream.
     * 
     * @param in Input stream to read from
     */
    void read(std::wistream &in);

    /**
     * Adds a cocktail to the collection.
     *
     * @param cocktail Cocktail to add
     * @return Reference to the collection
     */
    void operator+=(const TCocktail &cocktail);

    /**
     * Gets a cocktail from the collection by name.
     *
     * @param name Name of the cocktail to get
     * @return Found cocktail
     */
    const TCocktail& operator[](const std::wstring &name);

    /**
     * Assigns the contents of another const collection to this collection.
     *
     * @param other const Collection to assign from
     * @return Reference to this collection
     */
    TCocktailCard& operator=(const TCocktailCard &other);

    /**
     * Assigns the contents of another collection to this collection, moving the contents.
     *
     * @param other Collection to assign from
     * @return Reference to this collection
     */
    TCocktailCard& operator=(TCocktailCard &other);

    /**
     * Moves the contents of another collection to this collection.
     *
     * @param other Collection to move from
     * @return Reference to this collection
     */
    TCocktailCard& operator=(TCocktailCard &&other);

    /**
     * Moves the contents of another const collection to this collection, moving the contents.
     *
     * @param other const Collection to move from
     * @return Reference to this collection
     */
    TCocktailCard& operator=(const TCocktailCard &&other);

private:
    /**
     * Hash table storing the cocktails in the collection, keyed by name.
     */
    THashTable<std::wstring, TCocktail> card_;

    /**
     * Adds a cocktail to the collection.
     *
     * @param cocktail Cocktail to add
     */
    void addCocktail(const TCocktail &cocktail);

};

/**
 * Inserts the collection into an output stream.
 *
 * @param out Output stream to insert into
 * @param card Collection to insert
 * @return Output stream
 */
std::wostream& operator<<(std::wostream& out, TCocktailCard& card);

/**
 * Extracts a collection from an input stream.
 *
 * @param in Input stream to extract from
 * @param card Collection to extract into
 * @return Input stream
 */
std::wistream& operator>>(std::wistream& in, TCocktailCard& card);

#endif //LAB2_LIB_COCKTAIL_CARD_H
