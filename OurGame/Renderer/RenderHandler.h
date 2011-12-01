#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include<map>

#include <SFML/Graphics.hpp>

using std::map;
using std::multimap;
using std::pair;

class RenderData;

//Handles the updating of GUI compoentns
class RenderHandler
{
    public:

        enum Layer{
            GUI_LAYER,
            HUD_LAYER,
            GAME_LAYER
        };

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
        void Render();

        /*********************************************
            "Add a RenderObject to the handler"

            When an object is mapped, it is assinged a unique index
        *********************************************/
        void Map(sf::Drawable* linkerObj, Layer layer, int depth);

        /*********************************************
            "Set the depth of a mapped object"
        *********************************************/
        void RemapDepth(sf::Drawable* linkedObj, int depth);

        void SwitchLayer(sf::Drawable* linkedObj, Layer layer);

    protected:
        RenderHandler();
    private:
        //Map the drawable to its render data
        map<int, sf::Drawable*> object_map;
        //Map the sorted struct of the renederer
        multimap<int, multimap<int, int> > struct_map;

        static RenderHandler*       RenderHandlerPtr;

        //Each render handler should have a new RenderWindow
        //Accessed through RenderHandler
        sf::RenderWindow*           WindowPtr;
        bool            m_isValid; //Set false by public member invalidate(), this causes the frame to be redrawn
        unsigned int    m_cindex; //Current mapping index



        void test();
};

#endif // RenderHandler
