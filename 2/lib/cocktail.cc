#include "cocktail.h"

#include <string>
#include <iostream>

TCocktail::TCocktail() {
    name_ = L"";
    alcohol_percentage_ = 0.;
    volume_ = 0.;
}

TCocktail::TCocktail(std::wstring &custom_name_, double alc_percentage, double vol) {
    if (alc_percentage < 0. || vol < 0. || alc_percentage > 100.) {
        throw std::invalid_argument("Invalid alcohol percentage or volume");
    }
    name_ = custom_name_;
    alcohol_percentage_ = alc_percentage;
    volume_ = vol;
}

TCocktail::TCocktail(double vol) {
    if (vol < 0.) {
        throw std::invalid_argument("Invalid volume");
    }
    name_ = L"Water";
    alcohol_percentage_ = 0.;
    volume_ = vol;
}

const std::wstring &TCocktail::getName() const &{
    return name_;
}

const std::wstring TCocktail::getName() && {
    return std::move(name_);
}

double TCocktail::getAlcoholPercentage() const {
    return alcohol_percentage_;
}

double TCocktail::getVolume() const {
    return volume_;
}

void TCocktail::setName(const std::wstring &custom_name_) {
    name_ = custom_name_;
}

void TCocktail::setAlcoholPercentage(double alc_percentage) {
    if (alc_percentage < 0. || alc_percentage > 100.) {
        throw std::invalid_argument("Invalid alcohol percentage");
    }
    alcohol_percentage_ = alc_percentage;
}

void TCocktail::setVolume(double vol) {
    if (vol < 0.) {
        throw std::invalid_argument("Invalid volume");
    }
    volume_ = vol;
}

TCocktail operator+(const TCocktail cocktail1, const TCocktail &cocktail2) {
    const double new_alc_percentage = (cocktail1.getAlcoholPercentage() * cocktail1.getVolume() + cocktail2.getAlcoholPercentage() * cocktail2.getVolume()) / (cocktail1.getVolume() + cocktail2.getVolume());
    auto new_name = cocktail1.getName() + L" and " + cocktail2.getName();
    return TCocktail(new_name, new_alc_percentage, cocktail1.getVolume() + cocktail2.getVolume());
}

void TCocktail::operator>>(TCocktail &cocktail2) {
    if (volume_ <= 100.) {
        cocktail2.setVolume(cocktail2.volume_ + volume_);
        volume_ = 0.;
    }
    else {
        cocktail2.setVolume(cocktail2.volume_ + 100.);
        volume_ -= 100.;
    }
}

TCocktail operator*(const TCocktail cocktail, const double &multiplier) {
    if (multiplier < 0) {
        throw std::invalid_argument("Multiplier must be positive or equal to 0");
    }
    auto name = cocktail.getName();
    return TCocktail(name, cocktail.getAlcoholPercentage(), cocktail.getVolume() * multiplier);
}

void TCocktail::dump(std::wostream &out) const {
    out << name_ << L" - " << alcohol_percentage_ << L"%" << L" - " << volume_ << L"ml";
}

std::wostream &operator<<(std::wostream &out, const TCocktail &cocktail) {
    cocktail.dump(out);
    return out;
}

void TCocktail::read(std::wistream &in) {
    in >> name_ >> alcohol_percentage_ >> volume_;
}

std::wistream &operator>>(std::wistream &in, TCocktail &cocktail) {
    cocktail.read(in);
    return in;
}
