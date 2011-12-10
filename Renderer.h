#ifndef RENDERER_H
#define RENDERER_H

#include<SFML/Graphics.hpp>
#include <map>

/*
#include "Renderer/RenderHandler.h"
#include "Renderer/RenderData.h"
#include "Renderer/Layer.cpp"
*/
/*************************************
    Renderer is a static class allows
        an easy API with RenderHandler

    **This class is always initialized
        therefore, states are not
        needed.
**************************************/

using std::map;
using std::multimap;
using std::pair;
using std::vector;

class LinkableSprite;

class Renderer
{
    public:

       /****
            Enum: layer_t

            Allows map names to be stored
        *****/

        enum layer_t{
            GameLayer,
            HudLayer,
            MenuLayer
        } LayerEnum;


        enum invalidation_t{
            InvalidSort,
            InvalidWindow,
            InvalidAll
        };

        static void Link(LinkableSprite& sprite);
        //static void Link(sf::Drawable* linkedObj, Layer layer);

        static sf::RenderWindow* Window();



        ~Renderer();

        /*********************************************
            "Get the RenderHandler object"

            Returns a pointer to the RenderHandler

            *Uses lazy initialization
        *********************************************/
        static Renderer* GetObject();

        /*********************************************
            "Check if the screen is valid"

            returns TRUE if the screen is valid
                    FALSE if the screen is invalid, aka doesn't represent the current data
        *********************************************/
        bool isValid();

        /*********************************************
            "Force the screen to redraw"
        *********************************************/
        static void invalidate();

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

            When an object is mapped, it is assinged a unique index
        *********************************************/
        void Map(LinkableSprite object);

        /*********************************************
            "Set the depth of a mapped object"
        *********************************************/
        //void RemapDepth(sf::Drawable* linkedObj, int depth);

        //void SwitchLayer(sf::Drawable* linkedObj, Layer layer);

    protected:
        Renderer();
    private:
        //Sort the layers into order.
        void sort();
/*
        map<int, sf::Drawable*> drawable_map;   //>   map a unique index to an sf::Drawable*
        map<int, sf::Sprite*>   sprite_map;     //>   map a unique index to an sf::Sprite*
        map<int, map_t> object_map;             //>   map a unique index to a map_t
*/
        //Map the sorted struct of the renederer
        //map<int, multimap<int, int>, std::greater<int>  > struct_map;

        //Map a layer to a depth to a Linkable at the depth
        vector<LinkableSprite>             linkables;
        vector<LinkableSprite>::iterator   linkables_it;

        static Renderer*       RendererPtr;

        //Each render handler should have a new RenderWindow
        //Accessed through RenderHandler
        sf::RenderWindow*           WindowPtr;
        bool            m_isValid; //Set false by public member invalidate(), this causes the frame to be redrawn
        unsigned int    m_cindex; //Current mapping index

};

#endif // RENDERER_H
