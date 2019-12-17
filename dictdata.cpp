#include "dictdata.hpp"
#include "dictinfo.hpp"
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#ifdef WIN32
#include <QtZlib/zlib.h>
#else
#include <zlib.h>
#endif

DictData::DictData(){

}

DictData::~DictData() {
    if(m_stream.is_open()) {
        m_stream.close();
    }
}

bool DictData::load(const std::string& fileName)
{
    m_stream.open(fileName, std::ios::in | std::ios::binary);

    return true;
}

void DictData::loadArticle(const DictEntry* entry, std::string& articleText) {
    uint32_t idxitem_offset = entry->offset;
    uint32_t idxitem_size = entry->size;
    articleText.resize(idxitem_size);
//    articleText.resize(idxitem_size + sizeof(uint32_t));
//    memcpy(const_cast<char*>(articleText.c_str()), boost::lexical_cast<std::string>(idxitem_size).c_str(), sizeof(uint32_t));
    m_stream.seekg(idxitem_offset);
    m_stream.read(const_cast<char*>(articleText.c_str()), idxitem_size);
}
