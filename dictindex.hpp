#ifndef DICTINDEX_HPP
#define DICTINDEX_HPP

#include <stdlib.h>
#include <vector>
#include "dictentry.hpp"

class DictIndex
{
public:
    DictIndex();
    ~DictIndex();

    bool load(const std::string& fileName);

    size_t entryCount();
    std::vector<DictEntry *>* getEntryList();

private:
    std::vector<DictEntry *>* m_entryList;
};

#endif // DICTINDEX_HPP
