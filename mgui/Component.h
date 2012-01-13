#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include "../Magnet.h"

namespace mgui{

    class Component : public sf::Shape
    {
        public:
            //Default constructor
            Component();
            Component(sf::Vector2f pos, sf::Vector2f size);
            virtual ~Component();

            virtual void Create();
            virtual void SetVisible(bool toggle);
            void EnableOutline(bool enable);

            void SetOutlineColor(sf::Color outlineCol);
            sf::Color GetOutlineColor();

            void SetSize(float width, float height);
            void SetSize(sf::Vector2f size);
        protected:
        private:
            sf::Vector2f    m_size;
            sf::Color       m_outlineColor;
            bool m_outline;

            void format();
            void init(float x, float y, float width, float height);

    };
}

#endif // COMPONENT_H
