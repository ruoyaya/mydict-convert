#include "dictentry.hpp"

DictEntry::DictEntry():
    offset(0), size(0)
{

}

DictEntry::DictEntry(std::string pkey, uint32_t poffset, uint32_t psize):
    key(pkey),offset(poffset), size(psize)
{

}
