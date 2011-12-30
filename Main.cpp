#include <iostream>
#include "Gun/GunMaker.h"
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Magnet.h"
#include "ImageHandler.h"
#include "State/GameState.h"
#include "Console/Console.h"
#include "Handlers/EventHandler.h"

int main()
{
    /*************************************************
    **********=>    This is the debug
    **********=>      code.
    **************************************************/
    std::cout<<"This is OurGame\n";
    srand ( time(NULL) );//random seeder for guns
    GunMaker Gun(.3f);

    GunMaker Gun2(.3f);

    GunMaker Gun3(.3f);

    GunMaker Gun4(.3f);

    Gun.SetPosition(0,0);
    Gun2.SetPosition(0,130);
    Gun3.SetPosition(0,250);
    Gun4.SetPosition(0,380);
    /*************************************************
    **********=>    End debug code
    **************************************************/

    Console::AddCommand("Console::PrintCommands()",&Console::PrintCommands);
    Console::AddCommand("Console::TellAJoke()",&Console::TellAJoke);

    sf::Thread ConsoleListenThread(&Console::Listener);//add the ability to console things in thread.
    Console::GetObject()->consoleThread_ptr = &ConsoleListenThread; //LEt us access the console thread from anywhere that the console is accessible from

    EventHandler::AddKeyListener(sf::Key::C, &Console::LaunchConsoleThread);

    /*************************************************
    **********=>     Main loop
    **************************************************/
    sf::Thread RenderThread(&Renderer::Render);
    Renderer::SetRenderThread(RenderThread);

    sf::RenderWindow Window(sf::VideoMode::GetMode(3), "Magnet");
    Window.SetActive(false);
    Renderer::SetRenderWindow(Window);

    RenderThread.Launch();

    while(Renderer::GetRenderWindow()->IsOpened()){
        //We always listen for events
        EventHandler::Listen();
    }

    //Crashes if we don't end this
    //RenderThread.Terminate();

    return EXIT_SUCCESS;
}

