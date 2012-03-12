#ifndef SERIAL_H
#define SERIAL_H

#include <set>
#include "../Game/Exception.h"

#include <SFML/System.hpp>

//const char SERIAL_REG_INDEX_LESS = 0x1; //The maximum possible indices is less than maximum storage space. (Maximum capacity will never be reached)

/*
                    NOTE: This class is depracated. It is kept here because it is the same design as the magnet cache and may be useful when
                          writing that.

//A unique identifier containing an index unique to all other in the registry and a key
struct Serial;

//In the future this should inhrit CacheObject, so that it can be managed by magnet's memory manager
class SerialRegistry32{
    typedef std::set<Serial*>             registry_type;
    typedef std::set<Serial*>::iterator   registry_type_iterator;

    //Non-copyable
    SerialRegistry32(const SerialRegistry32& cpy);
    SerialRegistry32& operator=(const SerialRegistry32& cpy);

    //Private memebers
    registry_type   m_registry;
    size_t          m_serial_reserve_size;
    size_t          m_reg_reserve_size;


    Serial* createIndex(unsigned int* index);

    //////////////
    //  PUBLIC  //
    //////////////
    public:
    SerialRegistry32(size_t registrySize);    //Default constructor
    virtual ~SerialRegistry32();                                //virtual destructor

    //Attemps to register an empry a new serial in the registry.
    //Throws on failure:
    //  *No more unique indices
    //  *No more space to allocate
    Serial* NewSerial() throw(Exception);
};
*/

class Serial : public sf::NonCopyable{
    //friend class SharedVar;
    //Serial(); //Serials may only be constructed by a serial registry


    uint8_t serial;

    public:
        typedef uint8_t serial_t;

        Serial();
        const unsigned char Copy() const;
        //void    Enable(uint8_t flag);
        //void    Disable(uint8_t flag);

        bool operator==(const Serial& cmp) const;
        Serial& operator++(int cmp);
};

#endif // SERIAL_H
