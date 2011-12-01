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
    sf::Image img;
    img.LoadFromFile("Gun/Sprites/assault1-front.png");
    sf::Sprite* mySprite = new sf::Sprite();
    mySprite->SetImage(img);

    Renderer::Link(mySprite);
    //Renderer::SetDepth(mySprite, 3);
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
