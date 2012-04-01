#include "Hook.h"
#include "../Pipeline.h"

void HookRegistry::Call(Hook::Type hookType, bool rem) throw(){
    hooks_iterator_t it;

    m_mutex.lock();

    try{
        it = m_hooks.begin();
        bool inc = true;
        while( it != m_hooks.end() )
        {
            if((*it)->type() == hookType){
                (*it)->begin();

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

    }

    catch( ... ){
        Pipeline::SetScope(Pipeline::LOG); //Ensure we are using the log pipe
        pipe << "[HookRegistry][Call] Unhandled function call exeption" << std::endl;
    }

    m_mutex.unlock();
}

bool HookRegistry::exists(Hook::Type hookType)
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

