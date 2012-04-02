#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <SFML/System.hpp>

#include "Service.h"

namespace util{

typedef unsigned char uchar;

class Cache : Service
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
            uchar   type    : 3;
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
            var_t type_data;
            var_t name_type_data;
            var_t flag_type_data;

            char* name;
            void* value;
            void* flags;
        };

        Cache( const std::string& name );
        virtual ~Cache();

        virtual void onInitialize();
        void onClose();

        template< typename T, typename F >
        bool write(const std::string& name, const T& value, const F& flags = 0, bool sign = false, FLAGS type_flags = 0);

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
