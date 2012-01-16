#ifndef GROUP_H
#define GROUP_H

#include <map>

#include "Positionable.h"
#include "Component.h"

////////////////////////////////////////////////////////////////
///     This classes organizes compoenents together
///     into a group
////////////////////////////////////////////////////////////////
namespace mgui{
    class Group : public Positionable
    {
        public:
            typedef std::map<const char*, Component*>           component_map_type;
            typedef std::map<const char*, Component*>::iterator component_map_iterator_type;

            //default ctor
            Group();
            //Construct with name
            Group(const char* name);
            virtual ~Group();

            ////////////////////////////////
            /// Add a component to the group
            ////////////////////////////////
            void AddComponent(Component* newCmp);

            ////////////////////////////////
            /// Set the group's position
            /// relative to where the
            /// components are
            ////////////////////////////////
            virtual void SetPosition(sf::Vector2f newPosition);

            ////////////////////////////////
            /// Get a group's name
            ////////////////////////////////
            const char* GetName();

            ////////////////////////////////
            /// Check if a component has
            /// Been added to the group
            ////////////////////////////////
            bool ComponentExists(Component* checkcmp);

            ////////////////////////////////
            /// Call component's events
            ////////////////////////////////
            void onEvent(sf::Event evt);
        protected:
        private:
            const char* m_name;
            component_map_type m_component_map;
    };
}

#endif // GROUP_H
