#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <SFML/System.hpp>

#include "ConsoleThread.h"

class Console
{
    public:
        Console();
        ~Console();
        static Console* GetObject();
        void Init(); //start listening in console for commands to be entered. also, begin threading.



    protected:
    private:
    //the two f(x) below are static because they are called from a static scope, and cannot use GetObject.
        static void Listener(void* UserData);//does the listening/calls execution of command.
        static void Executor(void* UserData);//launches command

        static Console* consolePtr;
         bool listenerOn;

};

#endif // CONSOLE_H
