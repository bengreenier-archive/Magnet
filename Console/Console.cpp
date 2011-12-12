#include "Console.h"

Console* Console::consolePtr=NULL;

Console::Console()
{
    //ctor
   listenerOn=false;
}

Console::~Console()
{
    //dtor
}

Console* Console::GetObject()
{
    if (consolePtr==NULL)
        consolePtr=new Console();

    return consolePtr;
}

void Console::Init()
{
    //create a thread if one not already started.
    //this thread is a thread of Listener()

    if (listenerOn)
    {
        std::cout<<"listenerOn is true...\n";
        return;
    }else{
        //thread listener
        sf::Thread ListenThread(&Console::Listener);

        ListenThread.Launch();
    }

return;
}

void Console::Listener(void* UserData)
{
    //this should be called via thread, and it will launch its own thread of Executor after a command has been typed
    GetObject()->listenerOn=true;

    ConsoleThread Data;
    std::cout<<"CONSOLE ACTIVATED. INPUT BEING ACCEPTED.\n";
    std::cin>>Data.listenerToExecutor;
    std::cout<<"CONSOLE DEACTIVATED. NO LONGER TAKING INPUT.\n";
    sf::Thread ExecuteThread(&Console::Executor,&Data);

    ExecuteThread.Launch();

    //now we want this gone. done. not still running.

return;
}

void Console::Executor(void* UserData)
{
    //this executes a command. thats it.
    ConsoleThread* Info= static_cast<ConsoleThread*>(UserData);
    std::cout<<"Executing...\n";

    //here is where we check what cmd was typed: and then call it.

    if (Info->listenerToExecutor == "TellAJoke()")
        Info->TellAJoke();
    else
        std::cout<<"Invalid Command.";


    std::cout<<"\n";

    GetObject()->listenerOn=false;

    //now we want this gone. done. not still running.

return;
}
