#ifndef LAB2_LIB_COCKTAIL_CARD_H
#define LAB2_LIB_COCKTAIL_CARD_H

#include "cocktail.h"
#include <unordered_map>

class TCocktailCard {
private:
    std::unordered_map<std::wstring, TCocktail> card;

    void addCocktail(const TCocktail &cocktail);
    const TCocktail& findCocktail(const std::wstring &name) const;
public:
    TCocktailCard() = default;
    TCocktailCard(const TCocktail *cocktails, size_t cocktails_count);
    TCocktailCard(const TCocktailCard &other) = default;
    TCocktailCard(TCocktailCard &&other) = default;
    ~TCocktailCard() = default;

    bool isFull() const;
    bool isPartiallyFull() const;
    bool isEmpty() const;

    void removeCocktail(const std::wstring &name);

    const TCocktail getCocktail(const std::pair<const double, const double> alc_percentage_range, const double &volume=500.) const;
    const double getVolumeByQuartile(const std::pair<const double, const double> &quartile) const;
    void renameCocktail(const std::wstring &old_name, const std::wstring &new_name);
    void printCard() const;

    void operator+=(const TCocktail &cocktail);
    const TCocktail& operator[](const std::wstring &name);
    friend std::wostream& operator<<(std::wostream& out, const TCocktailCard& card);
    friend std::wistream& operator>>(std::wistream& in, TCocktailCard& card);
    TCocktailCard& operator=(const TCocktailCard &other) = default;
};

#endif //LAB2_LIB_COCKTAIL_CARD_H
