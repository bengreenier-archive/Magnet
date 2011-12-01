#include <iostream>
#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "Gun/GunMaker.h"
#include "Renderer/Layer.h"

int main()
{
    std::cout<<"This is OurGame\n";

    GunMaker Gun;
    Gun.ConsoleAGun(); //debug?

    //sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "OurGame");

/****************THIS IS TEST CODE *******************/
    /*  TO ADD SOMETHING TO THE RENDER HANDLER  */

    //Creaste any gereric sf::Drawable*
    sf::Shape shape1 = sf::Shape::Rectangle(0, 0, 100, 100, sf::Color(255, 255, 255));
    sf::Shape shape2 = sf::Shape::Rectangle(50, 0, 150, 100, sf::Color(0, 0, 255));
    sf::Shape shape3 = sf::Shape::Rectangle(0, 50, 100, 150, sf::Color(255, 0, 0));
    sf::Shape shape4 = sf::Shape::Rectangle(50, 50, 150, 150, sf::Color(0, 255,0));



    //Link it to the renderer so it knows to draw it.
    Renderer::Link(&shape1, RenderHandler::GAME_LAYER, 0);
    Renderer::Link(&shape3, RenderHandler::HUD_LAYER, 0);
    Renderer::Link(&shape4, RenderHandler::GUI_LAYER, 2);
    Renderer::Link(&shape2, RenderHandler::HUD_LAYER, 1);
    //Renderer::SetDepth(mySprite, 3);
/****************END TEST CODE *******************/


    while (Renderer::Window()->IsOpened())
    {

        Renderer::draw();
        //Gun.DrawTo(Window);


        /**
            Write event handler
        */
        sf::Event Event;
        while (Renderer::Window()->GetEvent(Event))
        {
            // Close window : exit
            if ((Event.Type == sf::Event::Closed)||((Event.Type == sf::Event::KeyReleased)&&(Event.Key.Code == sf::Key::Escape)))
                Renderer::Window()->Close();
        }

        /*
        // Clear the screen (fill it with black color)
        Window.Clear();

        // Display window contents on screen
        Window.Display();
        */
    }

    return 0;
}
