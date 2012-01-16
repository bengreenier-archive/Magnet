#ifndef REGISTRY_H
#define REGISTRY_H

#include <map>
#include "Group.h"

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
            typedef std::map<const char*, Group*>           group_map_type;
            typedef std::map<const char*, Group*>::iterator  group_map_iterator_type;

            Registry();
            virtual ~Registry();

            ////////////////////////////////
            /// Register a group with the
            /// registry
            ////////////////////////////////
            void Register(Group* newGroup);

            ////////////////////////////////
            /// Get a group by it's name
            ////////////////////////////////
            Group* GetByName(const char* groupName);

            ////////////////////////////////
            /// Check if a group exists
            ////////////////////////////////
            bool GroupExists(Group* checkgrp);
            bool GroupExists(const char* grpname);

            ////////////////////////////////
            /// Called when an event occurs
            ////////////////////////////////
            void onEvent(sf::Event evt);
        protected:
        private:

            group_map_type          m_group_map;
            group_map_iterator_type m_group_map_it;



            ////////////////////////////////
            /// Begin group iteration
            ////////////////////////////////
            void group_iterator_start();
            ////////////////////////////////
            /// Get group iteration
            ////////////////////////////////
            group_map_iterator_type get_iterator();
            ////////////////////////////////
            /// Iterate
            /// returns false when map.end()
            /// is reached
            ////////////////////////////////
            bool do_iterate();

    };
}

#endif // REGISTRY_H
