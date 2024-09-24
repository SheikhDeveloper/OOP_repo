#include "cocktail.h"

#include <string>

Cocktail::Cocktail() {
    this->name = "";
    this->alcohol_percentage = 0.;
    this->volume = 0.;
}

Cocktail::Cocktail(std::string name, double alcohol_percentage, double volume) {
    this->name = name;
    this->alcohol_percentage = alcohol_percentage;
    this->volume = volume;
}
