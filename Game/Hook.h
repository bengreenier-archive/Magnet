
#ifndef HOOK_H
#define HOOK_H

#include <map>
#include <iostream>

namespace Hook{
    enum Type {
        Frame,              //Called immediately before the frame is drawn
                            //Should be used sparingly (is called every frame)
        Think,              //Called every main iteration
        Close,              //Called when the game closes
        GameStateChange,    //Called after the game state has been changed
        Load,               //Called when resources should begin loading
        Initialize,         //Called after static classes have been initialized
                            //      *Add resources in this hook
        Setup               //Called after resources have been loaded
                            //      *Create sf::Drawables here
    };
    struct Settings{
        Settings(int _lifespan=0)
        {
            lifespan    = _lifespan;
        }
        unsigned int lifespan;

    };

    class Registry{
        public:
            typedef void (*HookCall_p)(Parameter);
            typedef void (*HookCall)();

            void Register(Type hookType, HookCall functionPtr, Settings hook_settings = Settings()){
                hook_data data;
                data.hook     = functionPtr;
                data.settings   = hook_settings;
                data.hook_type  = hookType;
                data.callback_type = void_void;
                data.count      = 0;

                m_hooks.push_back(data);
            }

            void Register(Type hookType, HookCall_p functionPtr, Settings hook_settings = Settings()){
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
                               if(it->settings.lifespan != 0){
                                   it->count++;

                                   if(it->count > it->settings.lifespan){
                                        Remove(it->hook);
                                   }
                               }
                               break;
                            case void_p:
                               it->hook_p(p);
                               it->count++;

                               if(it->count > it->settings.lifespan){
                                    Remove(it->hook);
                               }
                               break;
                        }
                    }
                }
            }
        protected:
        private:
            enum function_type{
                void_void, //Returns void, takes no params:     HookCall
                void_p    //Returns void, takes a Parameter:   HookCall_p
            };

            struct hook_data{
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
