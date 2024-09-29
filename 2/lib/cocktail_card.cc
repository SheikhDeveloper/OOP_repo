#include "cocktail_card.h"

#include <stdexcept>
#include <unordered_map>
#include <iostream>


TCocktailCard::TCocktailCard(const TCocktail *cocktails, size_t cocktails_count) {
    for (size_t i = 0; i < cocktails_count; ++i) {
        addCocktail(cocktails[i]);
    }
}

const TCocktail& TCocktailCard::findCocktail(const std::wstring &name) const {
    if (!card.contains(name)) {
        throw std::invalid_argument("Cocktail not found");
    }
    return card.at(name);
}

void TCocktailCard::addCocktail(const TCocktail &cocktail) {
    card[cocktail.getName()] = cocktail;
}

void TCocktailCard::printCard() const {
    for (const auto& [name, cocktail] : card) {
        std::wcout << cocktail << std::endl;
    }
}

bool TCocktailCard::isFull() const {
    return card.size() == 37;
}

bool TCocktailCard::isPartiallyFull() const {
    return card.size() > 0 && card.size() < 37;
}

bool TCocktailCard::isEmpty() const {
    return card.size() == 0;
}

void TCocktailCard::removeCocktail(const std::wstring &name) {
    card.erase(name);
}

const TCocktail TCocktailCard::getCocktail(const std::pair<const double, const double> alc_percentage_range, const double &volume) const {
    TCocktail new_cocktail;
    for (const auto& [name, cocktail] : card) {
        if (cocktail.getAlcoholPercentage() >= alc_percentage_range.first && cocktail.getAlcoholPercentage() <= alc_percentage_range.second) {
           new_cocktail = TCocktail(cocktail);
           new_cocktail.setVolume(volume);
           return new_cocktail;
        }
    }
    new_cocktail = TCocktail();
    for (const auto& [name, cocktail] : card) {
        new_cocktail = new_cocktail + cocktail;
    }
    new_cocktail.setVolume(volume);
    return new_cocktail;
}

const double TCocktailCard::getVolumeByQuartile(const std::pair<const double, const double> &quartile) const {
    double volume = 0;
    for (const auto& [name, cocktail] : card) {
        if (cocktail.getVolume() >= quartile.first && cocktail.getVolume() <= quartile.second) {
            volume += cocktail.getVolume();
        }
    }
    return volume;
}

void TCocktailCard::renameCocktail(const std::wstring &old_name, const std::wstring &new_name) {
    if (card.contains(old_name)) {
        card[new_name] = card[old_name];
        card.erase(old_name);
    }
}

void TCocktailCard::operator+=(const TCocktail &cocktail) {
    addCocktail(cocktail);
}

const TCocktail& TCocktailCard::operator[](const std::wstring &name) {
    return findCocktail(name);
}

std::wostream& operator<<(std::wostream& out, const TCocktailCard& card) {
    card.printCard();
    return out;
}

std::wistream& operator>>(std::wistream& in, TCocktailCard& card) {
    size_t cocktails_count;
    in >> cocktails_count;
    TCocktail *cocktails = new TCocktail[cocktails_count];
    for (size_t i = 0; i < cocktails_count; ++i) {
        in >> cocktails[i];
    }
    card = TCocktailCard(cocktails, cocktails_count);
    delete[] cocktails;
    return in;
}

