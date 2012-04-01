#include <iostream>
#include "Renderer.h"
#include "Magnet.h"
#include "Pipeline.h"

//This is just a temporary test function
void load_resources(){
    Pipeline::SetScope(Pipeline::SCREEN);
    pipe << "Resources not being loaded.\n";
}

int main(int argc, char **argv)
{
    sf::Window window(sf::VideoMode(800, 600), "Magnet", sf::Style::Titlebar); //sf::WindowSettings(24, 8, 4)
    sf::Thread ResourceLoader(&load_resources); //&Resource::Load


    //This is now useless
    size_t _serial_entity_size = 5000;

    while(window.isOpen()){
        if(Magnet::IsInitialized()){
            EventHandler::Listen(window);
            Magnet::Think();
        }else{
            try{
                Magnet::Init(_serial_entity_size, window, ResourceLoader);
            }

            catch(util::Exception e){
                std::cout << "ABORT MAGNET INITIALIZATION\n";
                return -1;
            }
        }
    }


    return 0;
}

