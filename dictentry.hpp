#ifndef DICTENTRY_HPP
#define DICTENTRY_HPP

#include <string>
#include "dictinfo.hpp"

class DictEntry
{
public:
    DictEntry();
    DictEntry(std::string key, uint32_t offset, uint32_t size);

    std::string key;
    uint32_t offset;
    uint32_t size;
};

#endif // DICTENTRY_HPP
