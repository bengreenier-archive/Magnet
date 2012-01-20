#ifndef Renderer_H
#define Renderer_H

#include<SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <string>
#include <iostream>

#include "EventListener.h"
/*************************************
    Renderer is a static class allows
        an easy API with RenderHandler

    **This class is always initialized
        therefore, states are not
        needed.
**************************************/

using std::queue;
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

        struct Link{
            sf::Drawable*   object;
            Layer           layer;
            int             depth;
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
            "Draw the screen"
        *********************************************/
        static void Render(void* threadData);

        /*********************************************
            "Add a drawable to the handler"

            When an object is mapped, it is assinged a unique index
        *********************************************/
        static Link* CreateLink(sf::Drawable* drawable_ptr, Layer layer, int depth);
        static Link* CreateLink(sf::Drawable* drawable_ptr, Layer layer);
        static Link* CreateLink(sf::Drawable* drawable_ptr);
        static void CreateLink(Link* link_ptr);

        static void RemoveLink(sf::Drawable* drawable_ptr);
        static void RemoveLink(Link* link_ptr);
        static void SetLinkLayer(sf::Drawable* drawable_ptr, Layer newLayer);
        /*********************************************
            "Close the RenderWindow"
        *********************************************/
        static bool Close(sf::Event evt);
        static bool Event_KeyPressed(sf::Event evt);

        /*********************************************
            "Creates the render window and sets renderTreadPtr"
        *********************************************/
        static void SetRenderWindow(sf::RenderWindow& Window);

        Link* GetLinkByDrawable(sf::Drawable* drawable_ptr);
        bool LinkExists(Renderer::Link* link_ptr);
        int GetLinkIndex(Link* link_ptr);

        static void SetRenderThread(sf::Thread& renderThread);
       static sf::Mutex* Mutex();

    protected:
        Renderer();
    private:

        typedef vector<Link*>            links_t;
        typedef vector<Link*>::iterator  links_iterator_t;
        typedef queue<Link*>             link_queue_t;




        sf::RenderWindow*     RenderWindow_ptr;
        sf::Thread*           renderThread_ptr;

        bool m_wait;

        links_t          links;
        link_queue_t     newlink_queue;
        link_queue_t      delete_queue;

        void _RemoveLink(Link* oldLink);
        void _CreateLink(Link* newLink);

        static Renderer*               RendererPtr;

        bool            m_isValid;
        bool            m_shouldDraw;
        unsigned int    m_cindex; //Current mapping index

};

#endif // Renderer_H
