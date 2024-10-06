#include "cocktail_card.h"

#include <stdexcept>
#include <iostream>


TCocktailCard::TCocktailCard(const TCocktail *cocktails, size_t cocktails_count) {
    card_ = THashTable<std::wstring, TCocktail>();
    for (size_t i = 0; i < cocktails_count; ++i) {
        card_.insert(cocktails[i].getName(), cocktails[i]);
    }
}

const TCocktail& TCocktailCard::findCocktail(const std::wstring &name) {
    if (!card_.contains(name)) {
        throw std::invalid_argument("Cocktail not found");
    }
    return card_[name];
}

void TCocktailCard::addCocktail(const TCocktail &cocktail) {
    try { card_[cocktail.getName()] = cocktail; }
    catch (std::out_of_range &e) {
        card_.insert(cocktail.getName(), cocktail);
    }
}

bool TCocktailCard::isEmpty() const {
    return card_.size() == 0;
}

size_t TCocktailCard::size() const {
    return card_.size();
}

size_t TCocktailCard::capacity() const {
    return card_.capacity();
}

void TCocktailCard::removeCocktail(const std::wstring &name) {
    card_.remove(name);
}

const TCocktail TCocktailCard::getCocktail(const std::pair<const double, const double> alc_percentage_range, const double &volume) {
    TCocktail new_cocktail;
    new_cocktail = TCocktail();
    for (const auto& node : card_) {
        auto cocktail = node.value;
        if (cocktail.getAlcoholPercentage() >= alc_percentage_range.first && cocktail.getAlcoholPercentage() <= alc_percentage_range.second && cocktail.getAlcoholPercentage() < new_cocktail.getAlcoholPercentage()) {
            new_cocktail = cocktail;
        }
        else if (new_cocktail.getAlcoholPercentage() < alc_percentage_range.first) {
            new_cocktail = new_cocktail + cocktail;
        }
    }
    if (new_cocktail.getAlcoholPercentage() < alc_percentage_range.first) {
        throw std::invalid_argument("No cocktail can be mixed with the given alcohol percentage range");
    }
    new_cocktail.setVolume(volume);
    return new_cocktail;
}

double TCocktailCard::getVolumeByQuartile(const std::pair<const double, const double> &quartile) {
    double volume = 0.;
    for (const auto& node : card_) {
        auto cocktail = node.value;
        if (cocktail.getAlcoholPercentage() >= quartile.first && cocktail.getAlcoholPercentage() <= quartile.second) {
            volume += cocktail.getVolume();
        }
    }
    return volume;
}

void TCocktailCard::renameCocktail(const std::wstring &old_name, const std::wstring &new_name) {
    if (card_.contains(old_name)) {
        TCocktail new_cocktail = card_[old_name];
        new_cocktail.setName(new_name);
        card_.insert(new_name, new_cocktail);
        card_.remove(old_name);
    }
}


void TCocktailCard::dump(std::wostream &out) {
    for (const auto& node : card_) {
        out << node.value << std::endl;
    }
}

void TCocktailCard::read(std::wistream &in) {
    size_t cocktail_count;
    in >> cocktail_count;
    TCocktail *cocktails = new TCocktail[cocktail_count];
    for (size_t i = 0; i < cocktail_count; ++i) {
        in >> cocktails[i];
    }
    card_ = TCocktailCard(cocktails, cocktail_count).card_;
    delete[] cocktails;
}

void TCocktailCard::operator+=(const TCocktail &cocktail) {
    addCocktail(cocktail);
}

const TCocktail& TCocktailCard::operator[](const std::wstring &name) {
    return findCocktail(name);
}


TCocktailCard& TCocktailCard::operator=(TCocktailCard &other) {
    card_ = other.card_;
    return *this;
}

TCocktailCard& TCocktailCard::operator=(const TCocktailCard &other) {
    card_ = other.card_;
    return *this;
}

TCocktailCard& TCocktailCard::operator=(TCocktailCard &&other) {
    card_ = std::move(other.card_);
    return *this;
}

TCocktailCard& TCocktailCard::operator=(const TCocktailCard &&other) {
    card_ = std::move(other.card_);
    return *this;
}

std::wostream& operator<<(std::wostream& out, TCocktailCard& card) {
    card.dump(out);
    return out;
}

std::wistream& operator>>(std::wistream& in, TCocktailCard& card) {
    card.read(in);
    return in;
}
