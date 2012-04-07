#include "Service.h"
#include "../Pipeline.h"
#include "../Magnet.h"

using namespace util;

Service::Service(const std::string& name, State::_type istate)
:   m_name(name),
    m_state(istate)
{
    ServiceRegistry::Register(this);
}

bool Service::onRegister()
{
    dbgconsole << "[" << name() << "] Registered " << std::endl;
    return true;
}

Service::~Service()
{
    m_state.set(State::Pause);
    ServiceRegistry::Unregister(this);
}

const std::string& Service::name() const
{
    return m_name;
}
