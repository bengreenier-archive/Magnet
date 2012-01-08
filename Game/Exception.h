#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

namespace Exception {
    enum Type {
        ///////////////////////
        ///     Generic
        NullPointer,

        ///////////////////////
        ///     Resource
        LoadFail
    };

    struct ob{
        ob(Type exType, std::string _what, std::string _why)
        {
            type = exType;
            what = _what;
            why = _why;
        }

        void message() {
            std::cout << "*[EXCEPTION] A " << what << " exception has occured\n\tReason: " << why << std::endl;
        }

        Type            type;
        std::string     what;
        std::string     why;
    };

}

#endif // EXCEPTION_H
