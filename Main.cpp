#include <iostream>
#include "Gun/GunMaker.h"
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "ImageHandler.h"
#include "State/GameState.h"

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
    std::cout<<"GunsMade";

   Gun.DrawTo(0,0);
    Gun2.DrawTo(0,130);
    Gun3.DrawTo(0,250);
    Gun4.DrawTo(0,380);
/*
    sf::Sprite sp1;
    sp1.SetImage(ImageHandler::GetImage("Gun/Sprites/assault1.png"));
    sp1.SetPosition(0, 0);
    sf::Sprite sp2;
    sp2.SetImage(ImageHandler::GetImage("Gun/Sprites/assault1.png"));
    sp2.SetPosition(0, 200);
    sf::Sprite sp3;
    sp3.SetImage(ImageHandler::GetImage("Gun/Sprites/assault1.png"));
    sp3.SetPosition(0, 400);
    sf::Sprite sp4;
    sp4.SetImage(ImageHandler::GetImage("Gun/Sprites/assault1.png"));
    sp4.SetPosition(0, 600);

    Renderer::Link(sp1);
    Renderer::Link(sp2);
    Renderer::Link(sp3);
    Renderer::Link(sp4);*/


    /*************************************************
    **********=>    End debug code
    **************************************************/

     //sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "OurGame");

//    GameState currentState();

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
                ImageHandler::PrintAvailableImages();
                Renderer::Window()->Close();
            }
        }

        // Clear the screen (fill it with black color)
        Renderer::Render();

        /*To draw these guns you need to:
            Renderer::Link(sf::Drawable*);  //sf::Drawable being the sprite that is the gun
        */
    }
    return 0;
}
