
#ifndef HOOK_H
#define HOOK_H

#include <map>
#include <iostream>
namespace Hook{
    enum Type {
        Frame       //Called immediately before the frame is drawn
                    //Should be used sparingly (is called every frame)
    };

    class Registry{
        public:
            typedef void (*HookCall)();
            typedef std::multimap<Type, HookCall>           hooks_t;
            typedef std::multimap<Type, HookCall>::iterator hooks_iterator_t;

            void Register(Type hookType, HookCall functionPtr){
                m_hooks.insert(std::pair<Type, HookCall>(hookType, functionPtr));
            }

            void Call(Type hookType){
                std::cout << "In call\n";
                hooks_iterator_t it;

                for(it  =   m_hooks.begin();
                    it  !=  m_hooks.end();
                    it++)
                {
                    if(it->first == hookType){
                        it->second();
                    }
                }
            }
        protected:
        private:
            hooks_t m_hooks;
    };

} //namespace hook
#endif
