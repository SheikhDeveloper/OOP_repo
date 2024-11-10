#ifndef LAB3_LIB_CAPTAIN_INFO_H
#define LAB3_LIB_CAPTAIN_INFO_H

#include <string>

struct TCaptainInfo {
    std::string name;
    std::string rank;
    size_t experience;

    TCaptainInfo(const std::string &name, const std::string &rank, size_t experience);
    ~TCaptainInfo() = default;
};

typedef struct TCaptainInfo TCaptainInfo;

#endif //LAB3_LIB_CAPTAIN_INFO_H
