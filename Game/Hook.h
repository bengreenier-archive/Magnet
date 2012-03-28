#ifndef HOOK_H
#define HOOK_H

#include <map>
#include <iostream>

#include "Parameter.h"
#include "../Utility/Functor.h"


using namespace util;

typedef unsigned char hook_lifespan_t;

class Hook{
public:
    enum Type {
        DEFAULT,            //THIS HOOK IS NEVER CALLED, it is for internal use only
        Frame,              //Called immediately before the frame is drawn
                            //Should be used sparingly (is called every frame)
        Think,              //Called every main iteration
        Close,              //Called when the game closes
        GameStateChange,    //Called after the game state has been changed
        StartLoad,               //Called when resources should begin loading
        Initialize,         //Called after static classes have been initialized
                            //      *Add resources in this hook
        Setup,               //Called before resources are loaded
                            //      *Create sf::Drawables here
        LoadComplete,        //Called after resources have been loaded (directly before Magnet::State == ready
        InitialzeServices
    };

    template< typename T >
    Hook(Type htype, T function, hook_lifespan_t life=0);

    template< typename T, typename C >
    Hook(Type htype, T function, C* object, hook_lifespan_t life=0);

    const Type& type() const
    {
        return m_type;
    }

    const hook_lifespan_t& lifespan() const { return m_lifespan; }
    const util::Functor& callback() const { return m_callback; }


    void begin()
    {
        m_callback.execute();
    }
private:
    Type                  m_type;
    hook_lifespan_t       m_lifespan; //0 for infinite (default), 1-255 for that number of operations before being removed
    util::Functor        m_callback;
}; //class hook

class HookRegistry{
    public:
        void Register(Hook* inhook){
            m_hooks.push_back(inhook);
        }

        void Call(Hook::Type hookType, Parameter p = Parameter()){
            hooks_iterator_t it;

            for(int i = 0; i < m_hooks.size(); i++)
            {
                if(m_hooks[i]->type() == hookType){

                    //std::cout << "Call hook\n";
                    m_hooks[i]->begin();
                    //std::cout << "Call end\n";
                }
                //prune(it);
            }


        }
    protected:
    private:
        enum function_type{
            void_void, //Returns void, takes no params:     HookCall
            void_p    //Returns void, takes a Parameter:   HookCall_p
        };

        typedef std::vector<Hook*>           hooks_t;
        typedef std::vector<Hook*>::iterator hooks_iterator_t;

        hooks_t m_hooks;

        hooks_iterator_t remove(hooks_iterator_t it){
            return m_hooks.erase(it);
        }

        hooks_iterator_t prune(hooks_iterator_t it, unsigned char type){ //0 for no param hook, 1 for param hook
           /*if(it->settings.lifespan > 0 ){
               if(it->count >= it->settings.lifespan){
                    return remove(it);
               }
           }else{
                return it;
           }*/
        }


};

#include "Hook.inl"

#endif
