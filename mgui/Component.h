#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>

namespace mgui{

    class Component : public sf::Shape
    {
        public:
            //Default constructor
            Component(const char* name);
            Component(const char* name, sf::Vector2f pos, sf::Vector2f size);
            virtual ~Component();

            virtual void Create();
            virtual void SetVisible(bool toggle);
            void EnableOutline(bool enable);

            void SetOutlineColor(sf::Color outlineCol);
            sf::Color GetOutlineColor();
            void SetColor(sf::Color color);
            sf::Color GetColor();

            void SetSize(float width, float height);
            void SetSize(sf::Vector2f size);

            void SetName(const char* newName){ m_name = newName; }
            const char* GetName(){ return m_name; }

            virtual bool onClick(){};
            void Update();
        protected:
        private:
            sf::Vector2f    m_size;
            sf::Color       m_outlineColor;
            sf::Color       m_color;

            bool m_outline;

            void format();
            void init(float x, float y, float width, float height);
            const char* m_name;
    };
}

#endif // COMPONENT_H
