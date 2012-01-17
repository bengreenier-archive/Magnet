#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Sizeable.h"
#include "Positionable.h"

namespace mgui{
    class Group;
    class Component : virtual public sf::Shape, virtual public Sizeable
    {
        public:
            //Default constructor
            Component(const char* name);
            Component(const char* name, sf::Vector2f pos, sf::Vector2f size);
            virtual ~Component();

            virtual void Create();

            void SetVisible(bool toggle);
            bool GetVisible(bool toggle) { return m_visible; }

            void EnableOutline(bool enable);

            void SetOutlineColor(sf::Color outlineCol);
            sf::Color GetOutlineColor();
            void SetColor(sf::Color color);
            sf::Color GetColor();

            //////////////////////////////////////////
            /// Overrides sf::Shape::GetPosition
            /// Returns the Position-OutlineWidth
            /// use sf::Shape::GetPosition for the
            /// position without the outline
            //////////////////////////////////////////
            sf::Vector2f GetPosition();

            //////////////////////////////////////////
            /// Overrides Sizeable::SetSize
            /// Provides same functionality, but calls
            /// format() after setting the size
            //////////////////////////////////////////
            virtual void SetSize(sf::Vector2f size);

            //////////////////////////////////////////
            /// Overrides Sizeable::GetSize
            /// Gets the total size (Size+border)
            /// *To get the size without the border,
            /// Call Sizeable::GetSize()
            //////////////////////////////////////////
            virtual sf::Vector2f GetSize();

            void SetName(const char* newName){ m_name = newName; }
            const char* GetName(){ return m_name; }

            void SetParent(Component* parent);
            Component* GetParent(){return m_parent;}

            /////////////////////////////////////////////////////////////
            /// Check if an sf::Vector2f is within the bounds of this
            /// component
            /////////////////////////////////////////////////////////////
            virtual bool CheckBounds(sf::Vector2f coord);

            virtual bool onClick(){ std::cout << "You clicked " << m_name << std::endl; return true; };
            //virtual void Update();
        protected:
        private:
            sf::Color       m_outlineColor;
            sf::Color       m_color;

            virtual void format();
            void init(float x, float y, float width, float height);

            const char* m_name;
            bool m_outline;
            bool m_isChild;
            bool m_created;
            bool m_visible;
            Component* m_parent;
    };
}

#endif // COMPONENT_H
