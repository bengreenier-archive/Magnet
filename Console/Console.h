#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SFML/System.hpp>

#include "ConsoleThread.h"

class Console
{
    public:
        typedef void (*FuncType)(void*);//used for function referencing and calling and etc.

        Console();
        ~Console();
        static Console* GetObject();
        static void Listener(void* UserData);//does the listening/calls execution of command.

        bool listenerOn;

        static void AddCommand(std::string name,FuncType function);//add a command via name and function reference
        static void PrintCommands(void* UserData);//print all command names

        static void TellAJoke(void* UserData);

    protected:

    private:
    //the two f(x) below are static because they are called from a static scope, and cannot use GetObject.

        static void Executor(void* UserData);//launches command
        FuncType GetCommand(std::string name);//returns command function

        std::vector< std::pair<std::string,FuncType> > commands;

        static Console* consolePtr;



};

#endif // CONSOLE_H
