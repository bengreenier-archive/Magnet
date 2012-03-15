#if defined(USE_HOARD)
#pragma comment(lib, "winhoard.lib")
#endif

#include <iostream>

#include "Magnet.h"
#include "Renderer/Graphics.h"

//Out main is all we have for our game so far. It represents the most simple possible implementation of the Magnet game engine.
int main()
{
    //Console::AddCommand("Console::PrintCommands()",&Console::PrintCommands) ;
    //Console::AddCommand("Console::TellAJoke()",&Console::TellAJoke);

    //sf::Thread ConsoleListenThread(&Console::Listener);//add the ability to console things in thread.
    //Console::GetObject()->consoleThread_ptr = &ConsoleListenThread; //LEt us access the console thread from anywhere that the console is accessible from

    //EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, &Console::LaunchConsoleThread));

    Matrix<float> matrix1(2, 5, 1);
    Matrix<float> matrix2(5, 5, 1);

    try{
        Matrix<float> result = matrix1 * matrix2;
    }
    catch(int e){
        std::cout << "EXCEPTION\n";
    }
    //result.debug_output();



    /*************************************************
    **********=>     Main loop
    **************************************************/

    sf::Thread RenderThread(&Renderer::Render);
    sf::Thread ResourceLoader(&Resource::Load);

    sf::RenderWindow Window(sf::VideoMode(800, 600), "Magnet", sf::Style::Titlebar); //sf::WindowSettings(24, 8, 4)
    Window.EnableVerticalSync(true);
    Window.SetActive(false);

    //This should be created more dynamically (Checking available RAM at install time or run-tim)
    //Should also consider storing these in an object
    size_t _serial_entity_size = 5000;  //bytes of storage for entity serials, i.e. how many entities can exits within the engine
                                        //at 5000 bytes for storage, and 4 bytes per serial 1250 entities can exist in the engine

    while(Window.IsOpen()){
        if(Magnet::IsInitialized()){
            EventHandler::Listen(Window);
            Magnet::Think();
        }else{
            try{
                Magnet::Init(_serial_entity_size, Window, RenderThread, ResourceLoader);
            }

            catch(Exception e){
                std::cout << "ABORT MAGNET INITIALIZATION\n";
                return -1;
            }
        }
    }

    return 0;
}

