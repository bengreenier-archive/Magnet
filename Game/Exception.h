#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

struct Exception {
    enum Type {
        Unknown,
        ///////////////////////
        ///     Generic
        NullPointer,

        ///////////////////////
        ///     Resource
        LoadFail,
        MissingDir,
        MissingFile,
        SyncError
    };
    //Default
    Exception(){ type = Unknown; what = "UNKNOWN EXCEPTION"; why = "Unknown"; }
    Exception(Type exType, std::string  _what, std::string  _why)
    {
        type = exType;
        what = _what;
        why = _why;
    }

    void output() {
        std::cout << "*[EXCEPTION] A " << what << " exception has occured\n\tReason: " << why << std::endl;
    }

    Type            type;
    std::string     what;
    std::string     why;

};

#endif // EXCEPTION_H
