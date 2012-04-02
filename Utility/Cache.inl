using namespace util;

template< typename T, typename F >
bool Cache::write(const std::string& name, const T& value, const F& flags, bool sign, FLAGS type_flags )
{
    if(!openStream(std::ios::in)){
        return false;
    }

    T*      copied_val = new T(value); //Make a copy of the value
    void*   bin_val = static_cast<void*>(copied_val);

    data_t data;
    data.type_data.size = sizeof(value);

    /*
    char* bindata = new char[sizeof(value)];
    uchar bitmask = 0xFF;
    uchar used_bytes = 0;

    for(int i = 0; i < data.type.size; i++)
    {
        bindata[i] = ( value >> (i*8) ) & bitmask; //Use & operator to ensure we only get the first 8 bits;
        std::cout << "Writing bits " << (int)bindata[i] << std::endl;
    }

    int converted = 0;
    std::cout << (int)bindata[0] << std::endl;
    */
    //Set type flags
    if(type_flags == 0)
    {
        if(data.type_data.size < 4){
            std::cout << "CHAR\n";
            data.type_data.type = FLAG_CHAR;
        }else{
            if(static_cast<int>(value) == value)
            {
                data.type_data.type = FLAG_INT;
            }else{
                std::cout << "FLOAT\n";
                data.type_data.type = FLAG_FLOAT;
            }
        }
    }else{
        data.type_data.type = type_flags;
    }

    if(sign){
        data.type_data.sign = 1;
    }else{
        data.type_data.sign = 0;
    }

    std::cout << "Writing variable '" << name << " = " << value << "' of size " << (int)data.type_data.size << " and type ";

    switch(data.type_data.type)
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
            std::cout << "Flags: " << (int)data.type_data.type << std::endl;
            std::cout << "unknown type (" << (int)data.type_data.type << std::endl;
    }

    closeStream();
}
