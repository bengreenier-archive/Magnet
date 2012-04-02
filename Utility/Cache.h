#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <SFML/System.hpp>

namespace util{

typedef unsigned char uchar;

class Cache
{
    public:
        enum FLAGS
        {
            FLAG_FLOAT = 1,
            FLAG_INT   = 2,
            FLAG_CHAR  = 4
        };


        struct var_t
        {
            uchar   size    : 4;
            uchar   flags   : 3;
            uchar   sign    : 1;
        };

        /*
            //Each variable has three fixed fields
            //  1 byte of flags
            //  1 byte of var type data
            //  1 byte of var name data
        */
        struct data_t
        {
            var_t type;
            uchar name_size;
            uchar flag_size;

            char* name;
            char* value;
            char* flags;
        };

        Cache(const std::string& file);
        virtual ~Cache();

        template< typename T, typename F >
        bool write(std::string name, T value, F flags, bool sign = false, uchar type_flags = 0);

        uchar getType( const var_t& var ) const;
    protected:
    private:
        bool openStream(std::_Ios_Openmode flags);
        bool closeStream();

        char*           m_file;
        std::fstream    m_stream;
        sf::Mutex       m_mutex;
};

}//ns util

#include "Cache.inl"

#endif // CACHE_H
