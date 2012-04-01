#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

namespace util{

class Exception
{
    public:
        Exception( std::string name, std::string msg );
        virtual ~Exception();

        //Log the exception
        virtual void log();
    private:
        std::string m_name;
        std::string m_msg;
};

}//ns util
#endif // EXCEPTION_H
