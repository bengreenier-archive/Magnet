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
            typedef std::map<const char*, Group*>    group_map_type;

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
        protected:
        private:

            group_map_type m_group_map;
    };
}

#endif // REGISTRY_H
