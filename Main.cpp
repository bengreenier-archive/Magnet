#include <iostream>
#include "Gun/GunMaker.h"
#include <SFML/Graphics.hpp>

#include "Magnet.h"

int main()
{
    /*************************************************
    **********=>    This is the debug
    **********=>      code.
    **************************************************/
    std::cout<<"This is OurGame\n";
    srand ( time(NULL) );//random seeder for guns
    /*GunMaker Gun(.3f);

    GunMaker Gun2(.3f);

    GunMaker Gun3(.3f);

    GunMaker Gun4(.3f);

    Gun.SetPosition(0,0);
    Gun2.SetPosition(0,130);
    Gun3.SetPosition(0,250);

    Gun4.SetPosition(0,380);*/

    /*************************************************
    **********=>    End debug code
    **************************************************/

    Console::AddCommand("Console::PrintCommands()",&Console::PrintCommands) ;
    Console::AddCommand("Console::TellAJoke()",&Console::TellAJoke);

    sf::Thread ConsoleListenThread(&Console::Listener);//add the ability to console things in thread.
    Console::GetObject()->consoleThread_ptr = &ConsoleListenThread; //LEt us access the console thread from anywhere that the console is accessible from

    //EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, &Console::LaunchConsoleThread));

    /*************************************************
    **********=>     Main loop
    **************************************************/

    sf::Thread RenderThread(&Renderer::Render);
    sf::Thread ResourceLoader(&Resource::Load);


    sf::RenderWindow Window(sf::VideoMode::GetMode(0), "Magnet", sf::Style::Titlebar); //sf::WindowSettings(24, 8, 4)
    Window.SetActive(false);


    while(Window.IsOpened()){
        if(Magnet::Initialized()){
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

    //RenderThread.Terminate();

    return EXIT_SUCCESS;
}

