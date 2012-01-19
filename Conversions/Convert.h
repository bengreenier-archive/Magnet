#ifndef CONVERT_H
#define CONVERT_H
#include <string>

class Convert //! Provides a way to convert to a string (not sure if in use), Depreciated.
{
    public:
        Convert();
        static      Convert* Get();
        static std::string ToString(int i);
    protected:
    private:
        static Convert* ConvertPtr;
};

#endif // CONVERT_H
