#ifndef CONVERT_H
#define CONVERT_H
#include <string>

class Convert
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
