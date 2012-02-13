#ifndef Renderer_H
#define Renderer_H

#include<SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <string>

#include "EventListener.h"
#include "Hook.h"
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
        static Renderer* Object();
        static sf::RenderWindow* GetRenderWindow();

        static void Init(sf::RenderWindow& window, sf::Thread& renderThread);
        static void Hook_Initialize();

        /*********************************************
            "Draw the screen"
        *********************************************/
        static void Render();

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

        static void SetLinkDepth(Link* link, int new_depth);
        static void SetLinkLayer(Link* link, Layer new_layer);

        Link* GetLinkByDrawable(sf::Drawable* drawable_ptr);
        bool LinkExists(Renderer::Link* link_ptr);
        int GetLinkIndex(Link* link_ptr);

        static void SetRenderThread(sf::Thread& renderThread);
        static sf::Mutex* Mutex();

        static bool IsRunning(){ return Object()->m_running; }

        static void Think();
        static Hook::Registry* Hooks();

        void RefreshFPS();
        void UpdateConfigVars();

    protected:
        Renderer();
    private:

        typedef vector<Link*>            links_t;
        typedef vector<Link*>::iterator  links_iterator_t;
        typedef queue<Link*>             link_queue_t;
        typedef std::pair<Link*, int>    depth_pair_t;
        typedef std::pair<Link*, Layer>  layer_pair_t;
        typedef queue<depth_pair_t>      depth_queue_t;
        typedef queue<layer_pair_t>      layer_queue_t;




        sf::RenderWindow*     RenderWindow_ptr;
        sf::Thread*           renderThread_ptr;
        sf::Mutex             renderMutex;
        Hook::Registry*       m_hooks;

        bool m_wait; //what is>?

        links_t          links;
        link_queue_t     newlink_queue;
        link_queue_t     delete_queue;
        depth_queue_t    depth_queue;
        layer_queue_t    layer_queue;

        void _SetLinkDepth(depth_pair_t depth_pair);
        void _SetLinkLayer(layer_pair_t layer_pair);
        void _RemoveLink(Link* oldLink);
        void _CreateLink(Link* newLink);
        void _InsertLink(Link* newLink); //WARNING: This function should only be called by a function with a renderMutex lock!

        static Renderer*               RendererPtr;

        bool            m_isValid;
        bool            m_shouldDraw;
        bool            m_running;
        int             m_max_process;
        int             m_max_attempts;
        unsigned int    m_cindex; //Current mapping index

        bool            cfg_show_fps;

        sf::Text        m_fps_text;
        sf::Clock       m_frame_clock;

};

#endif // Renderer_H
