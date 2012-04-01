#include "Service.h"
#include "../Magnet.h"

using namespace util;

//
///Static definitions
//
ServiceRegistry*    ServiceRegistry::m_instance = 0;

void ServiceRegistry::RegisterHooks()
{
    mENGINE_REGISTER_IHOOK("intialize_serviceRegistry", Hook::onInitializeSingletons, &ServiceRegistry::onInitialize, Instance());
    mENGINE_REGISTER_IHOOK("think_serviceRegistry", Hook::onThink, &ServiceRegistry::onThink, Instance());
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

bool ServiceRegistry::IsPaused()
{
    return ((Instance()->m_state.get() == State::Pause) ? true : false );
}

//
///Constructors
//

ServiceRegistry::ServiceRegistry()
:   m_state(State::Initialize)
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

    Instance()->m_mutex.lock();
    Instance()->m_services.insert(nserv);
    Instance()->m_mutex.unlock();
}

void ServiceRegistry::Unregister(Service* oserv)
{
    if(IsPaused()) return;

    Instance()->m_mutex.lock();

    for( services_it_t it = Instance()->m_services.begin();
         it !=              Instance()->m_services.end();
         it++ )
    {
        if((*it) == oserv){
            Instance()->m_services.erase(it);
            break;
        }
    }

    Instance()->m_mutex.unlock();
}

void ServiceRegistry::onThink()
{
    switch(m_state.get())
    {
        case State::Null:
        case State::Ready:
            //Check if there are services waiting to be registered
            if(Hooks()->exists(Hook::onRegisterService))
            {
                //If there are, register them and delete the hook registration so we know that they have been called
                Hooks()->Call(Hook::onRegisterService, true);
            }
            break;
        case State::Pause: //Allows outside influences to stop services from being processed and their hooks from being called
            //Dont do anything until we are unpaused
            break;
    }

    Hooks()->Call(Hook::onThink);
}
