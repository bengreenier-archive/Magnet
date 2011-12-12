#include <iostream>
#include "Gun/GunMaker.h"
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "ImageHandler.h"
#include "State/GameState.h"
#include "Console/Console.h"

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

    while (Renderer::Window()->IsOpened())
    {
        /***Load Handlers **/
        /*switch(currentState.GetState()){
            case GameState::NULL:
                //What to do here?
                break;
            case GameState::LOADING:

                //Compress to ResourceHandler
                ImageHandler::Init();
                //FontHandler::Init();


                RenderHandler::Init();


                break;
            case GameState::READY:
                //On
                break;
        }*/


        sf::Event Event;
        while (Renderer::Window()->GetEvent(Event))
        {
            // Close window : exit
            if ((Event.Type == sf::Event::Closed)||((Event.Type == sf::Event::KeyReleased)&&(Event.Key.Code == sf::Key::Escape))){
                    Renderer::Window()->Close();
            }
            if ((Event.Type == sf::Event::KeyReleased)&&(Event.Key.Code == sf::Key::C)){
                    Console::GetObject()->Init();
            }
        }

        Renderer::Render();
    }
    return 0;
}
