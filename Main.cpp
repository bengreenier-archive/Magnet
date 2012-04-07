#include <iostream>
#include "Renderer.h"
#include "Magnet.h"
#include "Pipeline.h"
#include "Utility.h"
#include "Utility/SLinkedList.h"

//This is just a temporary test function
void load_resources(){
    Pipeline::SetScope(Pipeline::SCREEN);
    pipe << "Resources not being loaded.\n";
}

int main(int argc, char **argv)
{

    //Chache testing
    /*
    try{
        util::Cache test( "test" );
        test.write("hello", 1.010102, 0, false, util::Cache::FLAG_FLOAT);
    } catch ( util::Exception e ) {
        e.log();
        dbgconsole << "Chache exception has occured...\n";
    }
    */

    //Linked list testing
    /*
    dbgconsole << "Constructing list\n";
    util::SLinkedList<int> list;
    dbgconsole << "list constructing, inserting 1\n";
    list.insert(1);
    dbgconsole << "Inserted\n";
    list.insert(2);
    list.insert(3);

    list.debug_output();
    */

    sf::Window window(sf::VideoMode(800, 600), "Magnet", sf::Style::Titlebar, sf::ContextSettings(24, 0, 4)); //sf::WindowSettings(24, 8, 4)
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

