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
        typedef void (*FuncType)();//used for function referencing and calling and etc.
        typedef int (*FuncTypeInt)();
        typedef std::string (*FuncTypeString)();
        typedef bool (*FuncTypeBool)();
        //need this to work!!! //typedef ALL (*FuncTypeAll)(ALL);

        Console();
        ~Console();
        static Console* GetObject();
        static void Listener(void* UserData);//does the listening/calls execution of command.

        bool listenerOn;

        static void AddCommand(std::string name,FuncType function);//add a command via name and function reference
        static void AddCommand(std::string name,FuncTypeBool function);
        static void AddCommand(std::string name,FuncTypeInt function);
        static void AddCommand(std::string name,FuncTypeString function);

        static void PrintCommands();//print all command names

        static void TellAJoke();

    protected:

    private:
    //the two f(x) below are static because they are called from a static scope, and cannot use GetObject.

        static void Executor(void* UserData);//launches command
        bool CanGetCommand(std::string name);//returns if you can Get said Command function

        std::vector< std::pair<std::string,FuncType> > commands;
        std::vector< std::pair<std::string,FuncTypeInt> > commandsI;
        std::vector< std::pair<std::string,FuncTypeString> > commandsS;
        std::vector< std::pair<std::string,FuncTypeBool> > commandsB;

        static Console* consolePtr;



};

#endif // CONSOLE_H
