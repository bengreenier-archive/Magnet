/*
#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <queue>
#include "../Game/Exception.h"
#include "../Game/Renderer.h"
#include "Component.h"

////////////////////////////////////////////////////////////////
///     This class acts as medium through
///     which static classes can pass events
///     to grouped components
////////////////////////////////////////////////////////////////
namespace mgui {
    class Registry
    {
        public:
            ////////////////////////////////
            ///     This typedef provides a
            ///     map to map a unique name
            ///     to the group of components
            ////////////////////////////////
            typedef std::vector<Component*>                    cmp_vect_type;
            typedef std::vector<Component*>::iterator          cmp_vect_iterator_type;
            typedef std::queue<Component*>                       cmp_queue_type;

            Registry();
            virtual ~Registry();

            ////////////////////////////////
            /// Register a group with the
            /// registry
            ////////////////////////////////
            void Register(Component* newGroup);

            ////////////////////////////////
            /// Get a group by it's name
            ////////////////////////////////
            Component* GetByName(const char* groupName) throw(Exception);

            cmp_queue_type  GetComponentQueue(sf::Vector2f coord);
            Component* GetTop(cmp_queue_type stack);

            ////////////////////////////////
            /// Check if a group exists
            ////////////////////////////////
            bool ComponentExists(Component* checkgrp, Component* cmp = NULL);
            bool ComponentExists(const char* grpname, Component* cmp = NULL);

            Component* GetFocus();
            void       SetFocus(Component* cmp);
            void       ReleaseFocus();

            int GetNextDepth();

            void Remove(Component* remove);

            ////////////////////////////////
            /// Called when an event occurs
            ////////////////////////////////
            bool onEvent(sf::Event evt);
        protected:
        private:

            cmp_vect_type              m_cmp_vect;
            cmp_vect_iterator_type          m_cmp_vect_it;
            Component*      m_focus;
            int         m_nextdepth;

            ////////////////////////////////
            /// Begin group iteration
            ////////////////////////////////
            bool cmp_iterator_start();
            ////////////////////////////////
            /// Get group iteration
            ////////////////////////////////
            cmp_vect_iterator_type get_iterator();
            ////////////////////////////////
            /// Iterate
            /// returns false when map.end()
            /// is reached
            ////////////////////////////////
            bool do_iterate();

    };
}

#endif // REGISTRY_H
*/
