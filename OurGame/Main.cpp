#include <iostream>
#include "Gun/GunMaker.h"
#include <SFML/Graphics.hpp>

int main()
{
    std::cout<<"This is OurGame\n";
    srand ( time(NULL) );//random seeder for guns
    GunMaker Gun(.3f);
        Gun.ConsoleAGun();
    GunMaker Gun2(.3f);
        Gun2.ConsoleAGun();
    GunMaker Gun3(.3f);
        Gun3.ConsoleAGun();
    GunMaker Gun4(.3f);
        Gun4.ConsoleAGun();

     sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "OurGame");

 while (Window.IsOpened())
    {


        sf::Event Event;
        while (Window.GetEvent(Event))
        {
            // Close window : exit
            if ((Event.Type == sf::Event::Closed)||((Event.Type == sf::Event::KeyReleased)&&(Event.Key.Code == sf::Key::Escape)))
                Window.Close();
        }

        // Clear the screen (fill it with black color)
        Window.Clear();

        Gun.DrawTo(Window,0,0);
        Gun2.DrawTo(Window,0,130);
        Gun3.DrawTo(Window,0,250);
        Gun4.DrawTo(Window,0,380);
         //Display window contents on screen
        Window.Display();
    }
    return 0;
}
