#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "Param.h"

namespace util{

struct Callback;
class Functor
{
    public:
        template< typename F >
        Functor( F function );         //Pointer-to-function

        //template< typename F >
        //Functor( F function, const Param* params );         //Pointer-to-function
        //template< typename C >
        //Functor( void(C::*function)(), C* object );             //Pointer-to-member without arguments
        //template< typename C >
        //Functor(void(C::*_function)(Param), C* object, const Param* params );//Point-to-member with arguments


        virtual ~Functor();
        void begin();


    private:
        Callback* m_callback;
};

} //ns util


#include "Functor.inl"

#endif // FUNCTOR_H
