#ifndef CALLBACK_H
#define CALLBACK_H

#include <SFML/Graphics.hpp>

template<class T>
class Callback
{
    public:
        enum Type{
            Static,
            Dynamic
        };
        typedef bool (*callback_func_type)(sf::Event);
        typedef T call_object_type; //callobject_type

        Callback(callback_func_type func){
            m_func = func;
            m_call_object = NULL;
            m_call_type = Static;
        }
        Callback(callback_func_type func, T* call_object ){
            m_func = func;
            m_call_object = call_object;
            m_call_type = Dynamic;
        }
        virtual ~Callback(){
            //delete [] m_object_ptr;
        }

        bool Call(sf::Event evt){
            if(m_call_type == Static){
                m_func(evt);
            }else{
                //call_object_type* obptr = static_cast<call_object_type*>(m_call_object)
                m_call_object->m_func(evt);
            }
        }

    private:
        Type m_call_type;
        T* m_call_object;
        callback_func_type m_func;
};

#endif // CALLBACK_H
