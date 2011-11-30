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

    /*  TO ADD SOMETHING TO THE RENDER HANDLER  */
    sf::Shape* myRect = new sf::Shape::Rectangle(0, 0, 10, 10, sf::Color(255, 255, 255));
    Renderer::Link(dynamic_cast<sf::Drawable*>(myRect), Layer::GAME, 0);

    while (Renderer::Window()->IsOpened())
    {

        Renderer::draw();
        //Gun.DrawTo(Window);


        /*
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
