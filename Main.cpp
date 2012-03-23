#include <iostream>
#include "Renderer.h"
#include "Magnet.h"

int main(int argc, char **argv)
{
    //Console::AddCommand("Console::PrintCommands()",&Console::PrintCommands) ;
    //Console::AddCommand("Console::TellAJoke()",&Console::TellAJoke);

    //sf::Thread ConsoleListenThread(&Console::Listener);//add the ability to console things in thread.
    //Console::GetObject()->consoleThread_ptr = &ConsoleListenThread; //LEt us access the console thread from anywhere that the console is accessible from

    //EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, &Console::LaunchConsoleThread));

    /*

            ///GLRENDERER TEST

    sf::Window window(sf::VideoMode(800, 800), "Magnet");
    Renderer* renderer =  new Renderer(&window);
    renderer->hook_initialized();

    RenderObject* ob = Renderer::CreateSquare(Point(.51, .51), Vector(1, 1));
    renderer->addRenderObject(ob);

    bool left = false;

    sf::Event evt;
    while(window.isOpen()){
        //Poll events
        while(window.pollEvent(evt)){
            if(evt.type == sf::Event::KeyPressed){
                if(evt.key.code == sf::Keyboard::Escape){
                    window.close();
                }
            }

            if(evt.type == sf::Event::Resized)
            {
                renderer->event_resized(evt);
            }
        }
        renderer->frame();

    }
    */

    sf::Window window(sf::VideoMode(800, 600), "Magnet", sf::Style::Titlebar); //sf::WindowSettings(24, 8, 4)
    window.setActive(false);


    sf::Thread ResourceLoader(&Resource::Load);



    //This should be created more dynamically (Checking available RAM at install time or run-tim)
    //Should also consider storing these in an object
    size_t _serial_entity_size = 5000;  //bytes of storage for entity serials, i.e. how many entities can exits within the engine
                                        //at 5000 bytes for storage, and 4 bytes per serial 1250 entities can exist in the engine

    while(window.isOpen()){
        if(Magnet::IsInitialized()){
            EventHandler::Listen(window);
            Magnet::Think();
        }else{
            try{
                Magnet::Init(_serial_entity_size, window, ResourceLoader);
            }

            catch(Exception e){
                std::cout << "ABORT MAGNET INITIALIZATION\n";
                return -1;
            }
        }
    }

    return 0;
}

