#ifndef Renderer_H
#define Renderer_H

#include<SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <string>
#include <iostream>
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

        static void RemoveLink(sf::Drawable* drawable_ptr);
        static void SetLinkLayer(sf::Drawable* drawable_ptr, Layer newLayer);
        /*********************************************
            "Close the RenderWindow"
        *********************************************/
        static void Close(sf::Event evt);

        /*********************************************
            "Creates the render window and sets renderTreadPtr"
        *********************************************/
        static void SetRenderWindow(sf::RenderWindow& Window);

        static void SetRenderThread(sf::Thread& renderThread);

        /*********************************************
            "Change the layer of a drawable"
        *********************************************/
        // static void SetLayer(sf::Drawable* drawable_ptr, Layer newLayer);
        /*********************************************
            "Change the depth of a drawable"
        *********************************************/
       // static void SetDepth(sf::Drawable* drawable_ptr, int newDepth);

       ////////////////////////////////////////////////
       ///  Gets the unique index assigned to a link
       ///  returns -1 if the index is not found
       ////////////////////////////////////////////////
       int GetLinkIndex(sf::Drawable* drawable_ptr);

       ////////////////////////////////////////////////
       ///  Checks to see if a drawable is linked
       ////////////////////////////////////////////////
       bool LinkExists(sf::Drawable* drawable_ptr);

       static sf::Mutex* Mutex();

    protected:
        Renderer();
    private:
        struct link{
            sf::Drawable*   object;
            Layer           layer;
            int             depth;
        };

        typedef vector<link>            links_t;
        typedef vector<link>::iterator  links_iterator_t;
        typedef queue<link>             link_queue_t;




        sf::RenderWindow*     RenderWindow_ptr;
        sf::Thread*           renderThread_ptr;

        bool m_wait;

        links_t          links;
        link_queue_t     newlink_queue;
        link_queue_t      delete_queue;

        void _RemoveLink(link oldLink);
        void _CreateLink(link newLink);

        static Renderer*               RendererPtr;

        bool            m_isValid;
        bool            m_shouldDraw;
        unsigned int    m_cindex; //Current mapping index

};

#endif // Renderer_H
