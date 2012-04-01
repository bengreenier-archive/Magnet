#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <vector>

#include "Renderer/Graphics.h"
#include "Renderer/RenderObject.h"

#include "Utility.h"

class Renderer : util::Service
{
    typedef std::vector<RenderObject*>  renderobjects_t; //Should be a ringbuffer

    renderobjects_t m_renderobjects;
    sf::Window*     m_window;
    HookRegistry    m_hooks;
    State           m_state;
    sf::Thread      m_drawThread;

    public:
        RenderObject* ob;
        static RenderObject* CreateSquare( Point pos = Point(), Vector size = Vector(5, 5) );
        static RenderObject* CreateCircle( Point pos = Point(), point_t radius = 5, unsigned int level = 6 );

        Renderer(sf::Window* window);
        virtual ~Renderer(){};

        void addRenderObject(RenderObject* newob);

        HookRegistry*   hooks();
        State*          getState();

        void onThink();
        void onBeginFrame();
        void onDrawFrame();
        void event_resized(sf::Event& evt);
        void setViewport();

        //Virtual

        virtual void onInitialize();
        //virtual void onRegister();
};

#endif // RENDERER_H
