#ifndef SERVICE_H
#define SERVICE_H

#include <SFML/System.hpp>
#include "State.h"
#include "Hook.h"

#include <set>

#define mSERVICE_REGISTER_SHOOK(hook_name, hook_enum, func_pointer)      ServiceRegistry::Hooks()->registerHook(new Hook(hook_name, hook_enum, func_pointer));    //Static hook (a hook that points to a static/free function)
#define mSERVICE_REGISTER_IHOOK(hook_name, hook_enum, func_pointer, ob)  ServiceRegistry::Hooks()->registerHook(new Hook(hook_name, hook_enum, func_pointer, ob));      //Instance hook (a hook that points to a member function)

namespace util {

class ServiceRegistry;
class Service : sf::NonCopyable
{
    public:
        Service(std::string name, bool ienabled = true, State::_type istate = State::Null);
        virtual ~Service();

        virtual const std::string& name();

        virtual void onRegister();
        virtual void onInitialize() = 0;
    private:
        bool                m_enabled;
        std::string         m_name;
        State               m_state;
};

class ServiceRegistry : sf::NonCopyable
{
    public:
        ServiceRegistry();
        virtual ~ServiceRegistry();
        void    onInitialize();
        static  ServiceRegistry* Instance();
        static  HookRegistry* Hooks();
        static  void          RegisterHooks();
        static bool IsPaused();
        void onThink();
    private:
        typedef std::set<Service*>               services_t;
        typedef std::set<Service*>::iterator     services_it_t;

        friend class Service;
        static void Register(Service* new_service);
        static void Unregister(Service* new_service);
        static ServiceRegistry* m_instance;
        services_t   m_services;
        HookRegistry            m_hooks;
        sf::Mutex               m_mutex;
        State                   m_state;

};

} //ns util

#endif // SERVICE_H
