#ifndef HOOK_H
#define HOOK_H

#include <vector>
#include <iostream>

#include "Functor.h"
#include "Exception.h"

namespace util {

typedef unsigned char hook_lifespan_t;

class Functor;
class Hook{
public:
    enum Type {
        DEFAULT,            //THIS HOOK IS NEVER CALLED, it is for internal use only
        onBeginFrame,
        onDraw,
        Frame,              //Called immediately before the frame is drawn
                            //Should be used sparingly (is called every frame)
        onThink,              //Called every main iteration
        Close,              //Called when the game closes
        GameStateChange,    //Called after the game state has been changed
        StartLoad,               //Called when resources should begin loading
        onInitialize,         //Called after static classes have been initialized
                            //      *Add resources in this hook
        Setup,               //Called before resources are loaded
                            //      *Create sf::Drawables here
        LoadComplete,        //Called after resources have been loaded (directly before Magnet::State == ready
        onRegisterService,
        onClose
    };

    template< typename T >
    Hook(const std::string& name, Type htype, T function, hook_lifespan_t life=0);

    template< typename T, typename C >
    Hook(const std::string& name, Type htype, T function, C* object, hook_lifespan_t life=0);

    const Type& type() const
    {
        return m_type;
    }

    const hook_lifespan_t& lifespan() const { return m_lifespan; }
    const util::Functor& callback() const { return m_callback; }
    const std::string& name();

    void begin() throw();
private:
    Type                  m_type;
    hook_lifespan_t       m_lifespan; //0 for infinite (default), 1-255 for that number of operations before being removed
    util::Functor         m_callback;
    const std::string     m_name;
}; //class hook

class HookRegistry{
    public:
        HookRegistry(const std::string& name);
        void registerHook(Hook* inhook);

        void Call(Hook::Type hookType, bool remove = false) throw();

        bool exists(const Hook::Type& hookType);
        bool exists(const std::string& name);
        const std::string& name() const;
    protected:
    private:
        enum function_type{
            void_void, //Returns void, takes no params:     HookCall
            void_p    //Returns void, takes a Parameter:   HookCall_p
        };

        typedef std::vector<Hook*>           hooks_t;
        typedef std::vector<Hook*>::iterator hooks_iterator_t;

        const std::string m_name;
        hooks_t m_hooks;
        sf::Mutex m_mutex;

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

}

#include "Hook.inl"

#endif
