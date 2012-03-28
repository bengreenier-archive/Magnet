#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <vector>

#include "Renderer/Graphics.h"
#include "Renderer/RenderObject.h"

class Renderer
{
    typedef std::vector<RenderObject*>  renderobjects_t; //Should be a ringbuffer

    renderobjects_t m_renderobjects;
    sf::Window*     m_window;

    public:
        static RenderObject* CreateSquare( Point pos = Point(), Vector size = Vector(5, 5) );
        static RenderObject* CreateCircle( Point pos = Point(), point_t radius = 5, unsigned int level = 6 );

        Renderer(sf::Window* window);
        virtual ~Renderer(){};

        void addRenderObject(RenderObject* newob);

        //Drawing
        void frame();
        void hook_initialize();
        void event_resized(sf::Event& evt);
        void setViewport();
};

#endif // RENDERER_H
