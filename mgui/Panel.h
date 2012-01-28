#ifndef PANEL_H
#define PANEL_H

#include <SFML/Graphics.hpp>
#include "Component.h"

#include "Text.h"

namespace mgui{
    class Panel : virtual public Component
    {
        public:
            Panel(const char* name);
            Panel(const char* name, const char* label);
            virtual ~Panel();

            virtual void Format();
            virtual void Create();
            virtual void Remove();
            virtual void SetDepth(int depth);

            virtual void DebugOn();
            virtual void DebugOff();

            virtual bool onMouseRelease(sf::Event evt);
            virtual bool onMouseMove(sf::Vector2f mouse_pos);
            virtual bool onMousePress(sf::Event evt);
        protected:
        private:
            bool            m_mouse_down;
            sf::Vector2f    m_mouse_dist;
            Text            m_text;
            Renderer::Link* m_text_link;
    };
}

#endif // PANEL_H
