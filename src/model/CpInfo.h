#ifndef CP_INFO_H
#define CP_INFO_H

#include <cstdint>
#include <vector>

class CpInfo {
    public:
        uint8_t tag; // CpTagConst
        std::vector<uint8_t> info;
};

#endif // CP_INFO_H