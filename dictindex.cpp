#include "dictindex.hpp"
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#ifdef WIN32
#include <QtZlib/zlib.h>
#include<Winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <zlib.h>
#endif

DictIndex::DictIndex():
    m_entryList(nullptr)
{
    m_entryList = new std::vector<DictEntry *>();
}

DictIndex::~DictIndex()
{
    if(m_entryList->size() > 0) {
        for (std::vector<DictEntry *>::iterator i = m_entryList->begin(); i != m_entryList->end(); i++) {
            delete *i;
        }
    }
    delete m_entryList;
}

size_t DictIndex::entryCount()
{
    return m_entryList->size();
}

std::vector<DictEntry *>* DictIndex::getEntryList()
{
    return m_entryList;
}

bool DictIndex::load(const std::string& fileName)
{
    if(fileName.size() == 0) {
        std::cerr << "fileName is empty!" << std::endl;
        return false;
    }

    gzFile stardictIdx = gzopen( fileName.c_str(), "rb");
    if ( !stardictIdx ) {
        std::cerr << "exCantReadFile[" << fileName << "]" << std::endl;
        return false;
    }

    std::vector< char > image;

    for( ; ; )
    {
        size_t oldSize = image.size();

        image.resize( oldSize + 65536 );

        int rd = gzread( stardictIdx, &image.front() + oldSize, 65536 );

        if ( rd < 0 )
        {
            gzclose( stardictIdx );
            std::cerr << "exCantReadFile[" << fileName << "]" << std::endl;
            return false;
        }

        if ( rd != 65536 )
        {
            image.resize( oldSize + rd + 1 );
            break;
        }
    }
    gzclose( stardictIdx );

    // We append one zero byte to catch runaway string at the end, if any

    image.back() = 0;

    // Now parse it
    bool isSynFile = false;

    for( char const * ptr = &image.front(); ptr != &image.back(); )
    {
        size_t wordLen = strlen( ptr );

        if ( ptr + wordLen + 1 + ( isSynFile ? sizeof( uint32_t ) :
                                   sizeof( uint32_t ) * 2 ) >
             &image.back() )
        {
            std::cerr << "Warning: sudden end of file [" << fileName << "]" << std::endl;
            break;
        }

        char const * word = ptr;

        ptr += wordLen + 1;

        if( strstr( word, "&#" ) )
        {
            // Decode some html-coded symbols in headword
            std::string unescapedWord = word;
            strncpy( const_cast<char *>(word), unescapedWord.c_str(), wordLen );
            wordLen = strlen( word );
        }

        uint32_t articleOffset = 0;
        uint32_t articleSize = 0;

        if ( !isSynFile )
        {
            // We're processing the .idx file

            memcpy( &articleOffset, ptr, sizeof( uint32_t ) );
            ptr += sizeof( uint32_t );
            memcpy( &articleSize, ptr, sizeof( uint32_t ) );
            ptr += sizeof( uint32_t );

            articleOffset = ntohl( articleOffset );
            articleSize = ntohl( articleSize );

            // Create an entry for the article in the chunked storage

            //        offset = chunks.startNewBlock();

            //        if ( articleOffsets )
            //          articleOffsets->push_back( offset );

            //        chunks.addToBlock( &articleOffset, sizeof( uint32_t ) );
            //        chunks.addToBlock( &articleSize, sizeof( uint32_t ) );
            //        chunks.addToBlock( word, wordLen + 1 );
        }
        else
        {

            // Some StarDict dictionaries are in fact badly converted Babylon ones.
            // They contain a lot of superfluous slashed entries with dollar signs.
            // We try to filter them out here, since those entries become much more
            // apparent in GoldenDict than they were in StarDict because of
            // punctuation folding. Hopefully there are not a whole lot of valid
            // synonyms which really start from slash and contain dollar signs, or
            // end with dollar and contain slashes.
            if ( *word == '/' )
            {
                if ( strchr( word, '$' ) )
                    continue; // Skip this entry
            }
            else
                if ( wordLen && word[ wordLen - 1 ] == '$' )
                {
                    if ( strchr( word, '/' ) )
                        continue; // Skip this entry
                }
        }

        // Insert new entry into an index
//        std::cout << "word=" << word << ",articleOffset=" << articleOffset << ",articleSize=" << articleSize << std::endl;
        DictEntry* entry = new DictEntry(word, articleOffset, articleSize);
        m_entryList->push_back(entry);
    }

    return true;
}
