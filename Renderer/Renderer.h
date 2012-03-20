#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "RenderObject.h"
#include <GL/glew.h>

#include <vector>

class Renderer
{
    typedef std::vector<RenderObject*>  renderobjects_t; //Should be a ringbuffer

    renderobjects_t m_renderobjects;
    sf::Window*     m_window;

    public:
        Renderer(sf::Window* window);
        virtual ~Renderer(){};

        void addRenderObject(RenderObject* newob);

        //Drawing
        void frame();
        void hook_initialized();
        void event_resized(sf::Event& evt);
        void setViewport();
};

#endif // RENDERER_H
