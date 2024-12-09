#ifndef LAB3_LIB_CAPTAIN_INFO_H
#define LAB3_LIB_CAPTAIN_INFO_H

#include <string>

/*@brief Captain info */
struct TCaptainInfo {

    /*@brief Captain name */
    std::string _name;

    /*@brief Captain rank */
    std::string _rank;

    /*@brief Captain experience */
    size_t _experience;

    /*@brief Default constructor */
    TCaptainInfo();

    /*@brief Parameterized constructor 
     * @param name - captain name
     * @param rank - captain rank
     * @param experience - captain experience
     * */
    TCaptainInfo(const std::string &name, const std::string &rank, size_t experience);

    /*@brief Destructor */
    ~TCaptainInfo() = default;
};

typedef struct TCaptainInfo TCaptainInfo;

std::ostream &operator<<(std::ostream &out, const TCaptainInfo &captain);
std::istream &operator>>(std::istream &in, TCaptainInfo &captain);

#endif //LAB3_LIB_CAPTAIN_INFO_H
