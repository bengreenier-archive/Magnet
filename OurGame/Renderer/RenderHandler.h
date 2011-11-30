#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include <SFML/Graphics.hpp>
#include "RenderObject.h"

using namespace std;

//Handles the updating of GUI compoentns
class RenderHandler
{
    public:

        ~RenderHandler();

        /*********************************************
            "Get the RenderHandler object"

            Returns a pointer to the RenderHandler

            *Uses lazy initialization
        *********************************************/
        static RenderHandler* GetObject();

        /*********************************************
            "Gets a pointer to the current window"

            Returns a pointer to the sf::RenderWindow
        *********************************************/
        sf::RenderWindow* Window();

        /*********************************************
            "Check if the screen is valid"

            returns TRUE if the screen is valid
                    FALSE if the screen is invalid, aka doesn't represent the current data
        *********************************************/
        bool isValid();

        /*********************************************
            "Force the screen to redraw"
        *********************************************/
        void invalidate();

        /*********************************************
            "sets m_isValid to true"
        *********************************************/
        void validate();

        /*********************************************
            "Draw the screen"
        *********************************************/
        static void Render();

        /*********************************************
            "Add a RenderObject to the handler"
        *********************************************/
        void Map(sf::Drawable* linkedObj, Layer layer, int depth);
    protected:
        RenderHandler();
    private:
        //Map the layer to the depth
            //Map the depth to the sf::Drawable pointer
        multimap<int, multimap<int, sf::Drawable*> >rmap;

        static RenderHandler*       RenderHandlerPtr;

        //Each render handler should have a new RenderWindow
        //Accessed through RenderHandler
        sf::RenderWindow*           WindowPtr;
        bool        m_isValid; //Set false by public member invalidate(), this causes the frame to be redrawn



        void test();
};

#endif // RenderHandler
