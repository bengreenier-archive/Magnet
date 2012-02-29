#ifndef SERIAL_H
#define SERIAL_H

#include <set>
#include "Exception.h"

const char SERIAL_MODIFIED      = 0X1;
const char SERIAL_WRITE_ONCE    = 0X2;
const char SERIAL_READ_ONCE     = 0X4;
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
//This class provides a tag that can be applied to shared variables
class Serial
{
    //friend class Magnet; //for testing, should be SharedVar<> in the future

    public:

    const unsigned char GetFlagsCopy() const;
    bool IsFlagged(const unsigned char& flag) const;
    const unsigned char GetSerialCopy() const;
    const unsigned char GetKeyCopy() const;

    bool operator==(const Serial& cmp) const;

    struct _serial_t{
        unsigned char flags        : 3;     //0 for Write has taken place, reset to 0 after read. Default 0
                                            //1 for write once per read.    Default 1
                                            //2 for read once per write.    Default 0
        unsigned char serial       : 5;    //3-7 The serial is modified every time a write takes place. Default 0.
    }key;



    Serial(const unsigned char& flags ); //Create a private constructor, so only friends may create a serial (This is to ensure that each serial is unique upon creation)
    Serial(); //Default


    void SetSerial(const unsigned char& _serial);
    void Flag(const unsigned char& _flags);
    void Unflag(const unsigned char& _flags);
};

#endif // SERIAL_H
