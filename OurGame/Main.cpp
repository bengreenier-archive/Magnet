#include <iostream>
#include "Gun/GunMaker.h"
#include <SFML/Graphics.hpp>

int main()
{
    std::cout<<"This is OurGame\n";
    GunMaker Gun;
    Gun.ConsoleAGun();

     sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "OurGame");

 while (Window.IsOpened())
    {
    Gun.DrawTo(Window);

        sf::Event Event;
        while (Window.GetEvent(Event))
        {
            // Close window : exit
            if ((Event.Type == sf::Event::Closed)||((Event.Type == sf::Event::KeyReleased)&&(Event.Key.Code == sf::Key::Escape)))
                Window.Close();
        }

        // Clear the screen (fill it with black color)
        Window.Clear();

        // Display window contents on screen
        Window.Display();
    }
    return 0;
}
