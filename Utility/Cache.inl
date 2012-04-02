using namespace util;

template< typename T, typename F >
bool Cache::write(std::string name, T value, F flags, bool sign, uchar type_flags )
{
    if(!openStream(std::ios::in)){
        return false;
    }

    char* bindata = new char[sizeof(value)];

    data_t data;
    data.type.size = sizeof(value);

    uchar bitmask = 0xFF;

    for(int i = data.type.size-1; i >= 0; i--)
    {
        bindata[i] = ( value >> (i*8) ) & bitmask; //Use & operator to ensure we only get the first 8 bits;
        std::cout << "Writing bits " << (int)bindata[i] << std::endl;
    }

    std::cout << (int)bindata << std::endl;

    //Set type flags
    /*if(type_flags == 0)
    {
        if(data.type.size < 4){
            std::cout << "CHAR\n";
            data.type.flags = FLAG_CHAR;
        }else{
            if(static_cast<int>(value) == value)
            {
                data.type.flags = FLAG_INT;
            }else{
                std::cout << "FLOAT\n";
                data.type.flags = FLAG_FLOAT;
            }
        }
    }else{*/
        data.type.flags = type_flags;
    //}

    if(sign){
        data.type.sign = 1;
    }else{
        data.type.sign = 0;
    }

    std::cout << "Writing variable '" << name << " = " << value << "' of size " << (int)data.type.size << " and type ";

    switch(getType(data.type))
    {
        case FLAG_CHAR:
            std::cout << "char\n";
            break;
        case FLAG_INT:
            std::cout << "int\n";
            break;
        case FLAG_FLOAT:
            std::cout << "float\n";
            break;
        default:
            std::cout << "Flags: " << (int)data.type.flags << std::endl;
            std::cout << "unknown (" << (int)getType(data.type) << std::endl;
    }

    closeStream();
}
