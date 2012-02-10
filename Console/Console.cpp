/*#include "Console.h"

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


void Console::Listener()
{
    //this should be called via thread, and it will launch its own thread of Executor after a command has been typed


    GetObject()->listenerOn=true;

    ConsoleThread Data;
    std::cout<<"------------CONSOLE ACTIVATED------------\n";
    std::cout<<"\n";
    Console::PrintCommands();
    std::cout<<"\n";

    std::cin>>Data.listenerToExecutor;
    std::cout<<"------------CONSOLE DEACTIVATED------------\n";
    sf::Thread ExecuteThread(&Console::Executor,&Data);

    ExecuteThread.Launch();

    //now we want this gone. done. not still running.
    ExecuteThread.Wait();
    //this should be okay, just wait in here till we finish executing cmd.



return;
}

void Console::Executor()
{
    //this executes a command. thats it.
    ConsoleThread* Info= static_cast<ConsoleThread*>(UserData);
    bool found=false;
    std::cout<<"------------EXECUTING------------\n";

    //here is where we check what cmd was typed: and then call it. for all types.

    for (int i=0;i<GetObject()->commands.size();i++)
    {

        if (Info->listenerToExecutor == GetObject()->commands[i].first)
        {
            std::cout<<"Your Command Matched "<<GetObject()->commands[i].first<<"\n";
            GetObject()->commands[i].second();

            found=true;
        }

    }

    for (int i=0;i<GetObject()->commandsI.size();i++)
    {

        if (Info->listenerToExecutor == GetObject()->commandsI[i].first)
        {
            std::cout<<"Your Command Matched "<<GetObject()->commandsI[i].first<<"\n";
            std::cout<<GetObject()->commandsI[i].second()<<std::endl;

            found=true;
        }

    }

    for (int i=0;i<GetObject()->commandsB.size();i++)
    {

        if (Info->listenerToExecutor == GetObject()->commandsB[i].first)
        {
            std::cout<<"Your Command Matched "<<GetObject()->commandsB[i].first<<"\n";
            std::cout<<GetObject()->commandsB[i].second()<<std::endl;

            found=true;
        }

    }

    for (int i=0;i<GetObject()->commandsS.size();i++)
    {

        if (Info->listenerToExecutor == GetObject()->commandsS[i].first)
        {
            std::cout<<"Your Command Matched "<<GetObject()->commandsS[i].first<<"\n";
            std::cout<<GetObject()->commandsS[i].second()<<std::endl;

            found=true;
        }

    }

    if (!found)
        std::cout<<"Invalid Command.\n";

    std::cout<<"------------EXECUTION DONE------------\n";

    GetObject()->listenerOn=false;

    std::cout<<"------------CONSOLE DEAD------------\n";
    //now we want this gone. done. not still running.


}


void Console::PrintCommands()
{
    for (int i=0;i<GetObject()->commands.size();i++)
    {
        std::cout<<GetObject()->commands[i].first<<" , ";
    }

    for (int i=0;i<GetObject()->commandsI.size();i++)
    {
        std::cout<<GetObject()->commandsI[i].first<<" , ";
    }

    for (int i=0;i<GetObject()->commandsB.size();i++)
    {
        std::cout<<GetObject()->commandsB[i].first<<" , ";
    }

    for (int i=0;i<GetObject()->commandsS.size();i++)
    {
        std::cout<<GetObject()->commandsS[i].first<<" , ";
    }

    std::cout<<"\n";
}


void Console::AddCommand(std::string name, FuncType function)
{
    if (!GetObject()->CanGetCommand(name))
    GetObject()->commands.push_back(std::pair<std::string,FuncType>(name,function));
    //might need to push back a function reference &function or something...
}

void Console::AddCommand(std::string name, FuncTypeInt function)
{
    if (!GetObject()->CanGetCommand(name))
    GetObject()->commandsI.push_back(std::pair<std::string,FuncTypeInt>(name,function));
    //might need to push back a function reference &function or something...
}

void Console::AddCommand(std::string name, FuncTypeBool function)
{
    if (!GetObject()->CanGetCommand(name))
    GetObject()->commandsB.push_back(std::pair<std::string,FuncTypeBool>(name,function));
    //might need to push back a function reference &function or something...
}

void Console::AddCommand(std::string name, FuncTypeString function)
{
    if (!GetObject()->CanGetCommand(name))
    GetObject()->commandsS.push_back(std::pair<std::string,FuncTypeString>(name,function));
    //might need to push back a function reference &function or something...
}


void Console::TellAJoke()
{
    std::cout<<"Why was six afraid of seven? 7 8 9. Comedy at its finest.\n";
}


bool Console::CanGetCommand(std::string in)
{

    for (int i=0;i<GetObject()->commands.size();i++)
    {
        if (in == GetObject()->commands[i].first)
            return true;
    }

    for (int i=0;i<GetObject()->commandsI.size();i++)
    {
        if (in == GetObject()->commandsI[i].first)
            return true;
    }

    for (int i=0;i<GetObject()->commandsB.size();i++)
    {
        if (in == GetObject()->commandsB[i].first)
            return true;
    }

    for (int i=0;i<GetObject()->commandsS.size();i++)
    {
        if (in == GetObject()->commandsS[i].first)
            return true;
    }


    return false;
}


void Console::LaunchConsoleThread(sf::Event evt)
{
        if (!Console::GetObject()->listenerOn){
        Console::GetObject()->consoleThread_ptr->Launch();
    }else{
        std::cout<<"CONSOLE ALREADY ACTIVATED.\n";
    }
}
*/
