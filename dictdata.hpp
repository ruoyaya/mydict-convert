#ifndef DICTDATA_HPP
#define DICTDATA_HPP

#include <string>
#include <fstream>
#include "dictentry.hpp"

class DictData
{
public:
    DictData();
    ~DictData();
    bool load(const std::string& fileName);
    void loadArticle(const DictEntry* entry, std::string& articleText);
private:
    std::ifstream m_stream;
};

#endif // DICTDATA_HPP
