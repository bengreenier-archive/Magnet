#ifndef PANEL_H
#define PANEL_H

#include <SFML/Graphics.hpp>
#include "Component.h"

namespace mgui{
    class Panel : virtual public Component
    {
        public:
            Panel(const char* name);
            Panel(const char* name, const std::string label);
            virtual ~Panel();

            virtual void Format();
            virtual void Create();
            virtual void Remove();

            virtual bool onMouseRelease(sf::Event evt);
            virtual bool onMouseMove(sf::Vector2f mouse_pos);
            virtual bool onMousePress(sf::Event evt);
        protected:
        private:
            bool            m_mouse_down;
            sf::Vector2f    m_mouse_dist;
            sf::String      m_label;
    };
}

#endif // PANEL_H
