#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
//#include <boost/iostreams/filtering_stream.hpp>
//#include <boost/iostreams/filter/bzip2.hpp>
//#include <boost/iostreams/copy.hpp>
//#include <boost/iostreams/device/file_descriptor.hpp>
//#include <boost/iostreams/device/file.hpp>
#include "dictinfo.hpp"
#include "dictindex.hpp"
#include "dictdata.hpp"
#include "tar.hpp"

int convert();

int main() {
    std::string filename = "/Users/wujing/Desktop/词典/stardict-hanyuchengyucidian_fix-2.4.2.tar.bz2";
    std::string tarFilename = "/Users/wujing/Desktop/词典/stardict-hanyuchengyucidian_fix-2.4.2";

    //    using namespace std;
    //    using namespace boost::iostreams;

    //    ifstream file(filename, ios_base::in |  ios_base::binary);
    //    ofstream ofile(tarFilename, ios_base::out |  ios_base::binary);

    //    filtering_streambuf<input> in;
    //    in.push(bzip2_decompressor());
    //    in.push(file);
    //    boost::iostreams::copy(in, ofile);


    //    std::ostringstream ss_decomp(tarFilename);
    //    boost::iostreams::filtering_istream in;
    //    in.push(boost::iostreams::bzip2_decompressor());
    //    in.push(boost::iostreams::file_source(filename)); //从文件中解压
    //    boost::iostreams::copy(in, ss_decomp);
    return convert();
}

int convert() {


    std::string ifoFileName("E:\\Workspaces\\Qt\\cidian\\stardict-poemstory-2.4.2\\poemstory.ifo");

    if(!boost::filesystem::exists(ifoFileName)) {
        std::cerr << "not exists" << std::endl;
        return -1;
    }

    DictInfo dict;
    dict.load(ifoFileName);
    std::cout << "version=" << dict.version << std::endl;

    std::string idxFileName("E:\\Workspaces\\Qt\\cidian\\stardict-poemstory-2.4.2\\poemstory.idx");
    if(!boost::filesystem::exists(idxFileName)) {
        std::cerr << "File[" << idxFileName << "]not exists" << std::endl;
        return -1;
    }


    std::string dictFileName("E:\\Workspaces\\Qt\\cidian\\stardict-poemstory-2.4.2\\poemstory.dict");
    if(!boost::filesystem::exists(dictFileName)) {
        std::cerr << "File[" << dictFileName << "]not exists" << std::endl;
        return -1;
    }

    DictData data;
    data.load(dictFileName);


    DictIndex index;
    index.load(idxFileName);
    std::cout << "entryCount=" << index.entryCount() << std::endl;


    std::string xmlFileName("E:\\Workspaces\\Qt\\cidian\\stardict-poemstory-2.4.2\\poemstory.dict.xml");
    std::ofstream xmlstream(xmlFileName, std::ios::out);
//    std::ostream& xmlstream = std::cout;
    xmlstream<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<std::endl;
    xmlstream<<"<d:dictionary xmlns=\"http://www.w3.org/1999/xhtml\" "
               "xmlns:d=\"http://www.apple.com/DTDs/DictionaryService-1.0.rng\">"<<std::endl;
    int articleIndex = 0;
    std::string articleText;

    for (std::vector<DictEntry *>::iterator i = index.getEntryList()->begin(); i != index.getEntryList()->end(); i++) {
        DictEntry* entry = *i;
        if(entry) {
            data.loadArticle(entry, articleText);
            xmlstream<<"<d:entry id=\""<<++articleIndex<<"\" d:title=\""<<entry->key<<"\">"<<std::endl;
            xmlstream<<"  <d:index d:value=\""<<entry->key<<"\"/>"<<std::endl;
            xmlstream<<"  <h1>"<<entry->key<<"</h1>"<<std::endl;
            xmlstream<<"  <div class=\"article\">"<<articleText <<"</div>"<<std::endl;
            xmlstream<<"</d:entry>"<<std::endl;

//            std::cout<<"<entry word=\""<<entry->key<<"\" size=\""<<entry->size<<"\"></entry>"<<std::endl;
            //std::cout << "key=" << entry->key << ", articleText=" << articleText << std::endl;
        } else {
            //std::cout << "key=" << entry->key << ", no article exist!" << std::endl;
        }
    }
    xmlstream<<"</d:dictionary>"<<std::endl;
    xmlstream.close();

    std::cout << "success!" << std::endl;

    return 0;
}
