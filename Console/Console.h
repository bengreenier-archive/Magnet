#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "ConsoleThread.h"
#include "FunctionPtrTemplate.h"

class Console //! Our threaded console that works while in game. currently uses cout
{
    public:
        typedef void (*FuncType)();//used for function referencing and calling and etc.
        typedef int (*FuncTypeInt)();
        typedef std::string (*FuncTypeString)();
        typedef bool (*FuncTypeBool)();
        //need this to work!!! //typedef ALL (*FuncTypeAll)(ALL);

        Console(); //!< Default Constructor
        ~Console(); //!< Default Destructor
        static Console* GetObject(); //!< Get the singleton class (only instance) of Console
        static void Listener(void* UserData);//!< Does the listening and spawns executor.

        static void LaunchConsoleThread(sf::Event evt); //!< Launches the thread.

        bool listenerOn;

        static void AddCommand(std::string name,FuncType function);//!< Add (void* userdata) function to console interface
        static void AddCommand(std::string name,FuncTypeBool function);//!< Add (bool) function to console interface
        static void AddCommand(std::string name,FuncTypeInt function);//!< Add (int) function to console interface
        static void AddCommand(std::string name,FuncTypeString function);//!< Add (string) function to console interface

        static void PrintCommands();//!< Print all commands that you can call via console

        static void TellAJoke();//!< Test function, to be sure console is working.

        sf::Thread* consoleThread_ptr;  //A pointer to the console thread

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
