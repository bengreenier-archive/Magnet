#include "Hook.h"
#include "../Pipeline.h"


HookRegistry::HookRegistry(const std::string& name)
:   m_name(name)
{}

void HookRegistry::Call(Hook::Type hookType, bool rem) throw(){
    hooks_iterator_t it;

    m_mutex.lock();

    int ct = 0;
    for(int i = 0; i < m_hooks.size(); i++){
        if(m_hooks[i]->type() == hookType){
            ct++;
        }
    }

    try{
        it = m_hooks.begin();
        bool inc = true;
        std::string name;
        while( it != m_hooks.end() )
        {
            *it;
            if((*it)->type() == hookType){
                name = (*it)->name();
                //std::cout << "[" << this->name() << "] Calling '" << name << "'" <<  std::endl;
                (*it)->begin();
                //std::cout << "[" << this->name() << "] ****&Called '" << name << "'" <<  std::endl;

                if(rem){
                    it = m_hooks.erase(it);
                    inc = false;
                }

            }

            if(inc){
                it++;
            }
            inc = true;

        }



    } catch( util::Exception& error ) {

        error.log();

    } catch( ... ){
        Pipeline::SetScope(Pipeline::LOG); //Ensure we are using the log pipe
        pipe << "[HookRegistry][Call] Unhandled function call exeption" << std::endl;
    }

    m_mutex.unlock();

    //std::cout << "[" << this->name() << "] Completed hook call\n";
}

bool HookRegistry::exists(const Hook::Type& hookType)
{
    m_mutex.lock();

    for(int i = 0; i < m_hooks.size(); i++)
    {
        if(m_hooks[i]->type() == hookType){
            m_mutex.unlock();
            return true;
        }
        //prune(it);
    }
    m_mutex.unlock();
    return false;
}

bool HookRegistry::exists(const std::string& name)
{
    m_mutex.lock();

    for(int i = 0; i < m_hooks.size(); i++)
    {
        if(m_hooks[i]->name() == name){
            m_mutex.unlock();
            return true;
        }
        //prune(it);
    }
    m_mutex.unlock();
    return false;
}

const std::string& HookRegistry::name() const
{
    return m_name;
}

void HookRegistry::registerHook(Hook* inhook)
{
    m_mutex.lock();
    std::cout << "[" << name() << "][registerHook] Registering hook " << inhook->name() << std::endl;
    m_hooks.push_back(inhook);
    m_mutex.unlock();
}

