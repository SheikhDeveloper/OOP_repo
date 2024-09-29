#include "cocktail.h"

#include <string>

TCocktail::TCocktail() {
    name = L"";
    alcohol_percentage = 0.;
    volume = 0.;
}

TCocktail::TCocktail(std::wstring custom_name, double alc_percentage, double vol) {
    name = custom_name;
    alcohol_percentage = alc_percentage;
    volume = vol;
}

TCocktail::TCocktail(double vol) {
    name = L"Water";
    alcohol_percentage = 0.;
    volume = vol;
}

const std::wstring &TCocktail::getName() const {
    return name;
}

double TCocktail::getAlcoholPercentage() const {
    return alcohol_percentage;
}

double TCocktail::getVolume() const {
    return volume;
}

void TCocktail::setName(const std::wstring &custom_name) {
    name = custom_name;
}

void TCocktail::setAlcoholPercentage(double alc_percentage) {
    alcohol_percentage = alc_percentage;
}

void TCocktail::setVolume(double vol) {
    volume = vol;
}

TCocktail TCocktail::operator+(const TCocktail &cocktail2) const {
    return TCocktail(name + L" and " + cocktail2.name, alcohol_percentage + cocktail2.alcohol_percentage, volume + cocktail2.volume);
}

