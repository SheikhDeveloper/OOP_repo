#include "cocktail_card.h"

#include <stdexcept>
#include <iostream>


TCocktailCard::TCocktailCard(const TCocktail *cocktails, size_t cocktails_count) {
    card_ = THashTable<std::wstring, TCocktail>();
    for (size_t i = 0; i < cocktails_count; ++i) {
        card_.insert(cocktails[i].getName(), cocktails[i]);
    }
}

TCocktail& TCocktailCard::findCocktail(const std::wstring &name) {
    try { return card_[name]; } 
    catch (std::out_of_range &e) {
        throw std::invalid_argument("Cocktail not found");
    }
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
    TCocktail new_cocktail{};
    for (const auto& node : card_) {
        auto cocktail = node.value;
        if (cocktail.getAlcoholPercentage() >= alc_percentage_range.first && cocktail.getAlcoholPercentage() < new_cocktail.getAlcoholPercentage()) {
            new_cocktail = cocktail;
        }
        else if (new_cocktail.getAlcoholPercentage() < alc_percentage_range.first || new_cocktail.getAlcoholPercentage() > alc_percentage_range.second) {
            bool is_unnamed = false;
            if (new_cocktail.getName() == L"") is_unnamed = true;
            new_cocktail = new_cocktail + cocktail;
            if (is_unnamed)
                new_cocktail.setName(cocktail.getName());
        }
    }
    if (new_cocktail.getAlcoholPercentage() < alc_percentage_range.first || new_cocktail.getAlcoholPercentage() > alc_percentage_range.second) {
        throw std::invalid_argument("No cocktail can be mixed with the given alcohol percentage range");
    }
    new_cocktail.setVolume(volume);
    return new_cocktail;
}

double TCocktailCard::getVolumeByPercentageRange(const std::pair<const double, const double> &range) {
    if (range.first > range.second || range.first < 0. || range.second > 100. || range.second < 0.) {
        throw std::invalid_argument("Invalid range");
    }
    double volume = 0.;
    for (const auto& node : card_) {
        auto cocktail = node.value;
        if (cocktail.getAlcoholPercentage() >= range.first && cocktail.getAlcoholPercentage() <= range.second) {
            volume += cocktail.getVolume();
        }
    }
    return volume;
}

double TCocktailCard::getVolumeByQuartile(TQuartile quartile){ 
    if (quartile == TQuartile::Q1) {
        return getVolumeByPercentageRange({0., 25.});
    }
    else if (quartile == TQuartile::Q2) {
        return getVolumeByPercentageRange({25., 50.});
    }
    else if (quartile == TQuartile::Q3) {
        return getVolumeByPercentageRange({50., 75.});
    }
    else if (quartile == TQuartile::Q4) {
        return getVolumeByPercentageRange({75., 100.});
    }
    else {
        throw std::invalid_argument("Invalid quartile");
    }
}

void TCocktailCard::renameCocktail(const std::wstring &old_name, const std::wstring &new_name) {
    if (card_.contains(old_name)) {
        TCocktail new_cocktail = card_[old_name];
        new_cocktail.setName(new_name);
        card_.remove(old_name);
        card_.insert(new_name, new_cocktail);
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

TCocktailCard& TCocktailCard::operator+=(const TCocktail &cocktail) {
    addCocktail(cocktail);
    return *this;
}

TCocktail& TCocktailCard::operator[](const std::wstring &name) {
    return findCocktail(name);
}

std::wostream& operator<<(std::wostream& out, TCocktailCard& card) {
    card.dump(out);
    return out;
}

std::wistream& operator>>(std::wistream& in, TCocktailCard& card) {
    card.read(in);
    return in;
}
