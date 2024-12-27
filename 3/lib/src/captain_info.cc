#include "../headers/captain_info.h"

#include <iostream>

TCaptainInfo::TCaptainInfo() {
    _name = "";
    _rank = "";
    _experience = 0;
}

TCaptainInfo::TCaptainInfo(const std::string &name, const std::string &rank, size_t experience) :
    _name(name),
    _rank(rank),
    _experience(experience) {}

std::ostream &operator<<(std::ostream &out, const TCaptainInfo &captain) {
    out << captain._name << " " << captain._rank << " " << captain._experience;
    return out;
}

std::istream &operator>>(std::istream &in, TCaptainInfo &captain) {
    in >> captain._name >> captain._rank >> captain._experience;
    return in;
}
