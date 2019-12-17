#include "dictinfo.hpp"
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#ifdef WIN32
#include <QtZlib/zlib.h>
#else
#include <zlib.h>
#endif

DictInfo::DictInfo()
{
}

bool DictInfo::load(const std::string& fileName)
{
    std::fstream stream(fileName, std::ios::in);
    if(!stream.is_open()) {
        std::cerr << "file[" << fileName << "] cannot open!" << std::endl;
        return false;
    }

    std::string val;
    while(!stream.eof()) {
        std::getline(stream, val);
        if(val.size() == 0) {
            continue;
        } else if(boost::algorithm::starts_with(val,"version=")) {
            boost::algorithm::replace_first(val, "version=", "");
            this->version = val;
        }  else if(boost::algorithm::starts_with(val,"bookname=")) {
            boost::algorithm::replace_first(val, "bookname=", "");
            this->bookname = val;
        }  else if(boost::algorithm::starts_with(val,"wordcount=")) {
            boost::algorithm::replace_first(val, "wordcount=", "");
            this->wordcount = boost::lexical_cast<uint32_t>(val);
        }  else if(boost::algorithm::starts_with(val,"synwordcount=")) {
            boost::algorithm::replace_first(val, "synwordcount=", "");
            this->synwordcount = boost::lexical_cast<uint32_t>(val);
        }  else if(boost::algorithm::starts_with(val,"idxfilesize=")) {
            boost::algorithm::replace_first(val, "idxfilesize=", "");
            this->idxfilesize = boost::lexical_cast<uint32_t>(val);
        }  else if(boost::algorithm::starts_with(val,"idxoffsetbits=")) {
            boost::algorithm::replace_first(val, "idxoffsetbits=", "");
            this->idxoffsetbits = boost::lexical_cast<uint32_t>(val);
        }  else if(boost::algorithm::starts_with(val,"sametypesequence=")) {
            boost::algorithm::replace_first(val, "sametypesequence=", "");
            this->sametypesequence = val;
        }  else if(boost::algorithm::starts_with(val,"dicttype=")) {
            boost::algorithm::replace_first(val, "dicttype=", "");
            this->dicttype = val;
        }  else if(boost::algorithm::starts_with(val,"description=")) {
            boost::algorithm::replace_first(val, "description=", "");
            this->description = val;
        }  else if(boost::algorithm::starts_with(val,"copyright=")) {
            boost::algorithm::replace_first(val, "copyright=", "");
            this->copyright = val;
        }  else if(boost::algorithm::starts_with(val,"author=")) {
            boost::algorithm::replace_first(val, "author=", "");
            this->author = val;
        }  else if(boost::algorithm::starts_with(val,"email=")) {
            boost::algorithm::replace_first(val, "email=", "");
            this->email = val;
        }  else if(boost::algorithm::starts_with(val,"website=")) {
            boost::algorithm::replace_first(val, "website=", "");
            this->website = val;
        } else if(boost::algorithm::starts_with(val,"date=")) {
            boost::algorithm::replace_first(val, "date=", "");
            this->date = val;
        }
    }

    stream.close();

    return true;
}
