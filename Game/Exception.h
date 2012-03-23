#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

struct Exception {
    enum Type {
        Unknown,
        ///////////////////////
        ///     Generic
        NullPointer,
        SyncError,

        ///////////////////////
        ///     Resource
        LoadFail,
        MissingDir,
        MissingFile,
        Recursive,

        ///////////////////////
        ///     SharedVar
        SharedReadDenied,
        SharedWriteDenied
    };
    //Default
    Exception(){ what = "UNKNOWN EXCEPTION"; why = "Unknown"; }
    Exception(Type _type, std::string  _what, std::string  _why)
    {
        type = _type;
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
