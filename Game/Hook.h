#ifndef HOOK_H
#define HOOK_H

#include <map>
#include <iostream>

#include "Parameter.h"

namespace Hook{
    enum Type {
        DEFAULT,            //THIS HOOK IS NEVER CALLED, it is for internal use only
        Frame,              //Called immediately before the frame is drawn
                            //Should be used sparingly (is called every frame)
        Think,              //Called every main iteration
        Close,              //Called when the game closes
        GameStateChange,    //Called after the game state has been changed
        StartLoad,               //Called when resources should begin loading
        Initialized,         //Called after static classes have been initialized
                            //      *Add resources in this hook
        Setup,               //Called before resources are loaded
                            //      *Create sf::Drawables here
        LoadComplete        //Called after resources have been loaded (directly before Magnet::State == ready
    };
    struct Settings{
        Settings(Type _hooktype, int _lifespan=-1) : hooktype(_hooktype), lifespan(_lifespan) //Lifespan -1 or 0 for infinite
        {
            setDefaults();
        }

        void setDefaults(){
            //Default settings (only if a lifespan was specified as -1)
            if(lifespan == -1){
                if(hooktype == Setup || hooktype == Initialized){
                    lifespan = 1;
                }
            }
        }
        int lifespan;
        Type hooktype;

    };

    class Registry{
        public:
            typedef void (*HookCall_p)(Parameter);
            typedef void (*HookCall)();

            void Register(Type hookType, HookCall functionPtr, Settings hook_settings = Settings(DEFAULT)){
                if(hook_settings.hooktype == DEFAULT){
                    hook_settings.hooktype = hookType;
                    hook_settings.setDefaults();
                }

                hook_data data;
                data.hook     = functionPtr;
                data.settings   = hook_settings;
                data.hook_type  = hookType;
                data.callback_type = void_void;
                data.count      = 0;

                m_hooks.push_back(data);
            }

            void Register(Type hookType, HookCall_p functionPtr, Settings hook_settings = Settings(DEFAULT)){
                if(hook_settings.hooktype == DEFAULT){
                    hook_settings.hooktype = hookType;
                    hook_settings.setDefaults();
                }

                hook_data data;
                data.hook_p       = functionPtr;
                data.settings   = hook_settings;
                data.hook_type  = hookType;
                data.callback_type = void_p;
                data.count      = 0;

                m_hooks.push_back(data);
            }

            void Remove(HookCall unique_func){}
            void Remove(HookCall_p unique_func){}

            void Prune(){
                for(hooks_iterator_t it  =   m_hooks.begin();
                    it  !=  m_hooks.end();
                    it++)
                {
                   if(it->settings.lifespan > 0 ){
                       if(it->count >= it->settings.lifespan){
                            Remove(it->hook);
                       }
                   }
                }
            }

            void Call(Type hookType, Parameter p = Parameter()){
                hooks_iterator_t it;

                for(it  =   m_hooks.begin();
                    it  !=  m_hooks.end();
                    it++)
                {
                    if(it->hook_type == hookType){
                        switch(it->callback_type){
                            case void_void:
                                it->hook();
                                it->count++;
                               break;
                            case void_p:
                               it->hook_p(p);
                                it->count++;
                               break;
                        }
                    }
                }


                Prune();
            }
        protected:
        private:
            enum function_type{
                void_void, //Returns void, takes no params:     HookCall
                void_p    //Returns void, takes a Parameter:   HookCall_p
            };

            struct hook_data{
                hook_data() : settings(DEFAULT){}
                HookCall_p  hook_p;
                HookCall    hook;

                Settings settings;
                function_type callback_type;
                Type hook_type;
                unsigned int count; //The amount of times hook has been called
            };

            typedef std::vector<hook_data>           hooks_t;
            typedef std::vector<hook_data>::iterator hooks_iterator_t;

            hooks_t m_hooks;


    };

} //namespace hook
#endif
