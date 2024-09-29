#include "cocktail.h"

#include <string>
#include <iostream>

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
    const double new_alc_percentage = (alcohol_percentage * volume + cocktail2.alcohol_percentage * cocktail2.volume) / (volume + cocktail2.volume);
    return TCocktail(name + L" and " + cocktail2.name, new_alc_percentage, volume + cocktail2.volume);
}

void TCocktail::operator>>(TCocktail &cocktail2) {
    if (cocktail2.volume <= 100.) {
        volume += cocktail2.volume;
        cocktail2.setVolume(0.);
    }
    else {
        cocktail2.setVolume(cocktail2.volume - 100.);
        volume += 100.;
    }
}

TCocktail TCocktail::operator*(const double &multiplier) const {
    return TCocktail(name, alcohol_percentage, volume * multiplier);
}

std::wostream &operator<<(std::wostream &out, const TCocktail &cocktail) {
    out << cocktail.name << L" - " << cocktail.alcohol_percentage << L"%" << L" - " << cocktail.volume << L"ml";
    return out;
}

std::wistream &operator>>(std::wistream &in, TCocktail &cocktail) {
    in >> cocktail.name >> cocktail.alcohol_percentage >> cocktail.volume;
    return in;
}
