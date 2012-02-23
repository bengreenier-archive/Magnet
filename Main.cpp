#include <iostream>

#include "Magnet.h"


//Out main is all we have for our game so far. It represents the most simple possible implementation of the Magnet game engine.
int main()
{
    //Console::AddCommand("Console::PrintCommands()",&Console::PrintCommands) ;
    //Console::AddCommand("Console::TellAJoke()",&Console::TellAJoke);

    //sf::Thread ConsoleListenThread(&Console::Listener);//add the ability to console things in thread.
    //Console::GetObject()->consoleThread_ptr = &ConsoleListenThread; //LEt us access the console thread from anywhere that the console is accessible from

    //EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, &Console::LaunchConsoleThread));

    /*************************************************
    **********=>     Main loop
    **************************************************/

    sf::Thread RenderThread(&Renderer::Render);
    sf::Thread ResourceLoader(&Resource::Load);

    sf::Window Window(sf::VideoMode(800, 600), "Magnet", sf::Style::Titlebar); //sf::WindowSettings(24, 8, 4)
    Window.EnableVerticalSync(true);
    Window.SetActive(false);


    while(Window.IsOpen()){
        if(Magnet::IsInitialized()){
            EventHandler::Listen(Window);
            Magnet::Think();
        }else{
            try{
                Magnet::Init(Window, RenderThread, ResourceLoader);
            }

            catch(Exception e){
                std::cout << "ABORT MAGNET INITIALIZATION\n";
                return -1;
            }
        }
    }

    return 1;
}

