#ifndef LAB2_COCKTAIL_H
#define LAB2_COCKTAIL_H

#include <string>

class Cocktail
{
private:
    std::string name;
    double alcohol_percentage;
    double volume;
public:
    Cocktail();
    Cocktail(std::string name, double alchol_percentage, double volume);
};

#endif //LAB2_COCKTAIL_H
