#ifndef Renderer_H
#define Renderer_H

#include "Magnet.h"

#include<SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
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

class Renderer
{
    public:

       /****
            typedef: Layer

            Allows map names to be stored
        *****/
        typedef int Layer;

        /*******Layer definitions******************
            Each layer is assigned to its depth
            You can safely add layers here
        ******************************************/
        static const Layer   GameLayer   =   0;
        static const Layer   HudLayer    =   1;
        static const Layer   MenuLayer   =   2;


        struct exception{
            enum ENAME{
                NullType
            };

            ENAME       type;
            std::string why;
        };


        ~Renderer();

        /*********************************************
            "Get the RenderHandler object"

            Returns a pointer to the RenderHandler

            *Uses lazy initialization
        *********************************************/
        static Renderer* GetObject();
        static sf::RenderWindow* GetRenderWindow();

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
        static void Render(void* threadData);

        /*********************************************
            "Add a drawable to the handler"

            When an object is mapped, it is assinged a unique index
        *********************************************/
        static void CreateLink(sf::Drawable* drawable_ptr, Layer layer, int depth);
        static void CreateLink(sf::Drawable* drawable_ptr, Layer layer);
        static void CreateLink(sf::Drawable* drawable_ptr);

        /*********************************************
            "Close the RenderWindow"
        *********************************************/
        static void Close(sf::Event evt);

        /*********************************************
            "Creates the render window and sets renderTreadPtr"
        *********************************************/
        void SetRenderWindow(sf::RenderWindow& Window);

        void InitRenderThread(void* threadData);

        /*********************************************
            "Change the layer of a drawable"
        *********************************************/
        // static void SetLayer(sf::Drawable* drawable_ptr, Layer newLayer);
        /*********************************************
            "Change the depth of a drawable"
        *********************************************/
       // static void SetDepth(sf::Drawable* drawable_ptr, int newDepth);

    protected:
        Renderer();
    private:
        Magnet::managed_thread* renderThreadPtr;
        sf::RenderWindow*     RenderWindow_ptr;
        //Sort the layers into order.
        void sort();

        //Map a unique index to a drawable
        map<int, sf::Drawable*>             drawable_map;
        map<int, sf::Drawable*>::iterator   drawable_iterator;


        //Make a multimap that maps a layer to the depth map on that layer
        //  Nested multimap maps depths to a unique index
        map<Layer, multimap<int, int> >           struct_map;
        map<Layer, multimap<int, int> >::iterator struct_iterator;

        //Each render handler should have a new RenderWindow
        //Accessed through RenderHandler
        static Renderer*               RendererPtr;

        bool            m_isValid; //Set false by public member invalidate(), this causes the frame to be redrawn
        unsigned int    m_cindex; //Current mapping index

};

#endif // Renderer_H
