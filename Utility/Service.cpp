#include "Service.h"
#include "../Pipeline.h"
#include "../Magnet.h"

using namespace util;

Service::Service(std::string name, bool ienabled, State::_type istate)
:   m_name(name),
    m_enabled(ienabled),
    m_state(istate)
{
    std::string hook_name = "register_" + name + "_service";
    mSERVICE_REGISTER_IHOOK(hook_name.c_str(), Hook::onRegisterService, &Service::onRegister, this);
}

void Service::onRegister()
{
    ServiceRegistry::Register(this);

    std::string hook_name = "register_" + name() + "_service";
    mENGINE_REGISTER_IHOOK(hook_name.c_str(), Hook::onInitialize, &Service::onInitialize, this);
    dbgconsole << "[Service] Registered " << name() << std::endl;
}

Service::~Service()
{
    m_enabled = false;
    m_state.set(State::Pause);
    ServiceRegistry::Unregister(this);
}

const std::string& Service::name()
{
    return m_name;
}
