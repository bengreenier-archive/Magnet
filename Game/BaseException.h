#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <iostream>
#include <string>

class BaseException
{
    public:
        enum Type {
            NullPointer,

            ///////////////////////
            ///     Resource
            LoadFail
            ///////////////////////
        };

        BaseException(Type what, std::string why) : m_what(what), m_why(why) {}
        virtual void what()  = 0;
        virtual void why()   = 0;
        virtual void error(){
            what();
            std::cout << "\n\t";
            why();
            std::cout << std::endl;
        }
    protected:
        std::string m_why;
        Type m_what;
};

#endif // BASEEXCEPTION_H
