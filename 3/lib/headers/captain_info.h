#ifndef LAB3_LIB_CAPTAIN_INFO_H
#define LAB3_LIB_CAPTAIN_INFO_H

#include <string>

struct TCaptainInfo {
    std::string _name;
    std::string _rank;
    size_t _experience;

    TCaptainInfo(const std::string &name, const std::string &rank, size_t experience);
    ~TCaptainInfo() = default;
};

typedef struct TCaptainInfo TCaptainInfo;

std::ostream &operator<<(std::ostream &out, const TCaptainInfo &captain);
std::istream &operator>>(std::istream &in, TCaptainInfo &captain);

#endif //LAB3_LIB_CAPTAIN_INFO_H
