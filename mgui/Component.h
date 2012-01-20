#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Sizeable.h"

namespace mgui{
    class Component : virtual public sf::Shape, virtual public Sizeable
    {
        public:
            //Default constructor
            Component(const char* name);
            Component(const char* name, sf::Vector2f pos, sf::Vector2f size);
            virtual ~Component();

            virtual void Create();

            virtual void SetVisible(bool toggle);
            virtual bool GetVisible(bool toggle) { return m_visible; }

            virtual void EnableOutline(bool enable);

            virtual void SetOutlineColor(sf::Color outlineCol);
            virtual sf::Color GetOutlineColor();
            virtual void SetColor(sf::Color color);
            virtual sf::Color GetColor();

            //////////////////////////////////////////
            /// Overrides sf::Shape::GetPosition
            /// Returns the Position-OutlineWidth
            /// use sf::Shape::GetPosition for the
            /// position without the outline
            //////////////////////////////////////////
            virtual sf::Vector2f GetPosition();

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

            virtual void SetName(const char* newName){ m_name = newName; }
            virtual const char* GetName(){ return m_name; }

            virtual void SetParent(Component* parent);
            virtual Component* GetParent(){return m_parent;}

            /////////////////////////////////////////////////////////////
            /// Check if an sf::Vector2f is within the bounds of this
            /// component
            /////////////////////////////////////////////////////////////
            virtual bool CheckBounds(sf::Vector2f coord);

            /////////////////////////////////////////////////////////////
            /// Update Component
            /////////////////////////////////////////////////////////////
            virtual void Format();

            ////////////////////////////////
            /// Handle component's events
            /// this essestially maps event
            /// types to their corresponding
            /// onNAME function
            ////////////////////////////////
            virtual bool onMouseEvent(sf::Event evt);

            /////////////////////////////////////
            /// Pure virtual mouse click handler
            /////////////////////////////////////
            virtual bool onMouseRelease(sf::Vector2f mouse_pos)  =   0;
            virtual bool onMousePress(sf::Vector2f mouse_pos)  =   0;
            virtual bool onMouseMove(sf::Vector2f mouse_pos)  =   0;

            void DebugOn();
            void DebugOff();

        protected:
        private:
            sf::Color       m_outlineColor;
            sf::Color       m_color;

            void init(float x, float y, float width, float height);

            const char* m_name;
            bool m_outline;
            bool m_isChild;
            bool m_created;
            bool m_visible;
            bool m_debug;
            Component* m_parent;

            //Debug things
            sf::Color debug_color;
            sf::Color debug_color_focus;
            sf::Shape debug_size_top;
            sf::Shape debug_size_left;
            sf::Shape debug_size_right;
            sf::Shape debug_size_bottom;


            void _CreateDebugLines();
            void _RemoveDebugLines();
            void _UpdateDebugLines();
    };
}

#endif // COMPONENT_H
