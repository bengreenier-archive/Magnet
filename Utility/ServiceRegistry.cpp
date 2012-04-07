#include "Service.h"
#include "../Magnet.h"

using namespace util;

//
///Static definitions
//
ServiceRegistry*    ServiceRegistry::m_instance = 0;

void ServiceRegistry::RegisterHooks()
{
     mENGINE_REGISTER_IHOOK("intialize_service_registry", Hook::onInitializeSingletons, &ServiceRegistry::onInitialize, Instance());
     mENGINE_REGISTER_IHOOK("think_service_registry", Hook::onThink, &ServiceRegistry::onThink, Instance());
}


ServiceRegistry* ServiceRegistry::Instance(){
    if(!m_instance)
        m_instance = new ServiceRegistry();

    return m_instance;
}

HookRegistry* ServiceRegistry::Hooks()
{
    return &(Instance()->m_hooks);
}
//
///Constructors
//

ServiceRegistry::ServiceRegistry()
:   m_state(State::Initialize),
    m_hooks("ServiceRegistryHooks")
{

}

ServiceRegistry::~ServiceRegistry()
{
    //Should unregister hooks in the future
    m_services.clear();
    delete m_instance;
}

void ServiceRegistry::onInitialize()
{
    if(IsPaused()) return;

    Instance()->m_state.set(State::Ready);
}

void ServiceRegistry::Register(Service* nserv)
{
    if(IsPaused()) return;

    Instance()->m_rqmutex.lock();
    std::cout << "[ServiceRegistry] Queuing " << nserv->name() << " for registry" << std::endl;
    Instance()->m_newqueue.push(nserv);
    Instance()->m_rqmutex.unlock();
}

void ServiceRegistry::Unregister(Service* oserv)
{
    if(IsPaused()) return;

    Instance()->m_ssmutex.lock();

    for( services_it_t it = Instance()->m_services.begin();
         it !=              Instance()->m_services.end();
         it++ )
    {
        if((*it) == oserv){
            Instance()->m_services.erase(it);
            break;
        }
    }

    Instance()->m_ssmutex.unlock();
}

void ServiceRegistry::onThink()
{
    switch(m_state.get())
    {
        case State::Pause: //Allows outside influences to stop services from being processed and their hooks from being called
            //Dont do anything until we are unpaused
            break;
        default:
            //Check if there are services waiting to be registered
            if(!m_newqueue.empty())
            {
                m_rqmutex.lock();
                m_ssmutex.lock();

                while(!m_newqueue.empty())
                {
                    if(m_newqueue.front()->onRegister())
                    {
                        if(m_newqueue.front()->onInitialize())
                        {
                            m_services.insert(m_newqueue.front());
                        }
                    }

                    m_newqueue.pop();
                }
                m_ssmutex.unlock();
                m_rqmutex.unlock();
            }
    }

    Hooks()->Call(Hook::onThink);
}
