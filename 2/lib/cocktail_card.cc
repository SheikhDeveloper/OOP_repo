#include "cocktail_card.h"

#include <stdexcept>
#include <iostream>


TCocktailCard::TCocktailCard(const TCocktail *cocktails, size_t cocktails_count) {
    for (size_t i = 0; i < cocktails_count; ++i) {
        addCocktail(cocktails[i]);
    }
}

const TCocktail& TCocktailCard::findCocktail(const std::wstring &name) {
    if (!card.contains(name)) {
        throw std::invalid_argument("Cocktail not found");
    }
    return card[name];
}

void TCocktailCard::addCocktail(const TCocktail &cocktail) {
    card[cocktail.getName()] = cocktail;
}

bool TCocktailCard::isEmpty() const {
    return card.size() == 0;
}

size_t TCocktailCard::size() const {
    return card.size();
}

size_t TCocktailCard::capacity() const {
    return card.capacity();
}

void TCocktailCard::removeCocktail(const std::wstring &name) {
    card.remove(name);
}

const TCocktail TCocktailCard::getCocktail(const std::pair<const double, const double> alc_percentage_range, const double &volume) {
    TCocktail new_cocktail;
    for (const auto& node : card) {
        auto cocktail = node.value;
        if (cocktail.getAlcoholPercentage() >= alc_percentage_range.first && cocktail.getAlcoholPercentage() <= alc_percentage_range.second) {
           new_cocktail = TCocktail(cocktail);
           new_cocktail.setVolume(volume);
           return new_cocktail;
        }
    }
    new_cocktail = TCocktail();
    for (const auto& node : card) {
        auto cocktail = node.value;
        new_cocktail = new_cocktail + cocktail;
    }
    new_cocktail.setVolume(volume);
    return new_cocktail;
}

const double TCocktailCard::getVolumeByQuartile(const std::pair<const double, const double> &quartile) {
    double volume = 0;
    for (const auto& node : card) {
        auto cocktail = node.value;
        if (cocktail.getVolume() >= quartile.first && cocktail.getVolume() <= quartile.second) {
            volume += cocktail.getVolume();
        }
    }
    return volume;
}

void TCocktailCard::renameCocktail(const std::wstring &old_name, const std::wstring &new_name) {
    if (card.contains(old_name)) {
        card[new_name] = card[old_name];
        card.remove(old_name);
    }
}

void TCocktailCard::operator+=(const TCocktail &cocktail) {
    addCocktail(cocktail);
}

const TCocktail& TCocktailCard::operator[](const std::wstring &name) {
    return findCocktail(name);
}


TCocktailCard& TCocktailCard::operator=(TCocktailCard &other) {
    card = other.card;
    return *this;
}

TCocktailCard& TCocktailCard::operator=(const TCocktailCard &other) {
    card = other.card;
    return *this;
}

void TCocktailCard::printCard(std::wostream &out) {
    for (auto& node : card) {
        out << node.value << std::endl;
    }
}

std::wostream& operator<<(std::wostream& out, TCocktailCard& card) {
    card.printCard(out);
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
