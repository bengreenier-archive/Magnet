#ifndef SERVICE_H
#define SERVICE_H

#include <SFML/System.hpp>
#include "State.h"
#include "Hook.h"

#include <set>
#include <queue>

#define mSERVICE_REGISTER_SHOOK(hook_name, hook_enum, func_pointer)      ServiceRegistry::Hooks()->registerHook(new Hook(hook_name, hook_enum, func_pointer));    //Static hook (a hook that points to a static/free function)
#define mSERVICE_REGISTER_IHOOK(hook_name, hook_enum, func_pointer, ob)  ServiceRegistry::Hooks()->registerHook(new Hook(hook_name, hook_enum, func_pointer, ob));      //Instance hook (a hook that points to a member function)

namespace util {

class ServiceRegistry;
class Service : sf::NonCopyable
{
    public:
        Service(const std::string& name, State::_type istate = State::Null);
        virtual ~Service();

        virtual const std::string& name() const;

        virtual bool onRegister();
        virtual bool onInitialize() = 0;
    protected:
        const std::string         m_name;
    private:
        State                     m_state;
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
        static inline bool IsPaused()
            { return (Instance()->m_state.get() == State::Pause); }
        void onThink();
    private:
        typedef std::set<Service*>               services_t;
        typedef std::set<Service*>::iterator     services_it_t;
        typedef std::queue<Service*>             register_queue_t;

        friend class Service;
        static void Register(Service* new_service);
        static void Unregister(Service* new_service);
        static ServiceRegistry* m_instance;
        services_t              m_services;
        register_queue_t        m_newqueue;
        HookRegistry            m_hooks;
        sf::Mutex               m_ssmutex; //Service Set mutex
        sf::Mutex               m_rqmutex; //Service egister queue mutex
        State                   m_state;

};

} //ns util

#endif // SERVICE_H
