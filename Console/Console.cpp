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
    ExecuteThread.Wait();
    //this should be okay, just wait in here till we finish executing cmd.



return;
}

void Console::Executor(void* UserData)
{
    //this executes a command. thats it.
    ConsoleThread* Info= static_cast<ConsoleThread*>(UserData);
    bool found=false;
    std::cout<<"Executing...\n";

    //here is where we check what cmd was typed: and then call it.

    for (int i=0;i<GetObject()->commands.size();i++)
    {

        if (Info->listenerToExecutor == GetObject()->commands[i].first)
        {
            std::cout<<"Your Command Matched "<<GetObject()->commands[i].first<<"\n";
            GetObject()->commands[i].second(NULL);
            std::cout<<"Execution Done...\n";
            found=true;
        }

    }

    if (!found)
        std::cout<<"Invalid Command.\n";

    GetObject()->listenerOn=false;

    std::cout<<"CONSOLE DEAD.\n";
    //now we want this gone. done. not still running.


}


void Console::PrintCommands(void* UserData)
{
    for (int i=0;i<GetObject()->commands.size();i++)
    {
        std::cout<<GetObject()->commands[i].first<<" , ";
    }

    std::cout<<"\n";
}


void Console::AddCommand(std::string name, FuncType function)
{
    GetObject()->commands.push_back(std::pair<std::string,FuncType>(name,function));
    //might need to push back a function reference &function or something...
}


void Console::TellAJoke(void* UserData)
{
    std::cout<<"Why was six afraid of seven? 7 8 9. Comedy at its finest.\n";
    return;
}
