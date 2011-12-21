#ifndef HOOK_H
#define HOOK_H

#include <map>

//Static class to manage hooks
class Hook{
    public:
        enum Type{
            OnCall       //Called every time a hook is called
        };

        typedef void (*FuncType)();
        typedef std::multimap<Type, FuncType>          hooks_t;
        typedef std::multimap<Type, FuncType>::iterator hooks_iterator_t;

        static void Add(Type hookType, FuncType functionPtr){
            Object()->hooks.insert(std::pair<Type, FuncType>(hookType, functionPtr));
        }

        static void Call(Type hookType){
            hooks_iterator_t it;

            for(it  =   Object()->hooks.begin();
                it  !=  Object()->hooks.end();
                it++)
            {
                if(it->first == hookType){
                    it->second();
                }
            }
        }

        static Hook* Object(){
            if(hook_ptr == NULL)
                hook_ptr = new Hook();

            return hook_ptr;
        }

        ~Hook(){ delete [] hook_ptr; }
    protected:
        Hook();
    private:
        static Hook* hook_ptr;

        hooks_t hooks;
};

#endif
