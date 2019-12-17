#ifndef DICTINFO_HPP
#define DICTINFO_HPP

#include <stdlib.h>
#include <string>

class DictInfo
{
public:
    DictInfo();
    bool load(const std::string& fileName);

    uint32_t wordcount;
    uint32_t synwordcount;
    uint32_t idxfilesize;
    uint32_t idxoffsetbits;
    std::string version;
    std::string bookname;
    std::string author;
    std::string email;
    std::string website;
    std::string date;
    std::string copyright;
    std::string description;
    std::string sametypesequence;
    std::string dicttype;

};

#endif // DICTINFO_HPP
