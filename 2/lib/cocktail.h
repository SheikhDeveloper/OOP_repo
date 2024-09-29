#ifndef LAB2_LIB_COCKTAIL_H
#define LAB2_LIB_COCKTAIL_H

#include <string>

class TCocktail
{
private:
    std::wstring name;
    double alcohol_percentage;
    double volume;
public:
    TCocktail();
    TCocktail(std::wstring name, double alchol_percentage, double volume);
    TCocktail(double volume);

    const std::wstring &getName() const;
    double getAlcoholPercentage() const;
    double getVolume() const;

    void setName(const std::wstring &name);
    void setAlcoholPercentage(double alchol_percentage);
    void setVolume(double volume);
    TCocktail operator+(const TCocktail &cocktail2) const;
    void operator>>(const TCocktail &cocktail2) const;
    TCocktail operator*(const double &multiplier) const;
};

#endif //LAB2_COCKTAIL_H
