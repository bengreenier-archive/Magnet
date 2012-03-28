#ifndef FUNCTOR_H
#define FUNCTOR_H

#include <SFML/System.hpp>
#include "Param.h"

namespace util{

struct Callback;
class Functor : sf::NonCopyable
{
    public:
        //Construct from a static/free function
        template< typename F >
        Functor( F function );

        //Construct from a static/free function with arguments
        //template< typename F >
        //Functor( F function, const Param* params );

        //Construct from a member function
        template< typename C >
        Functor( void(C::*function)(), C* object );

        //Construct from a member function with arguments
        //template< typename C >
        //Functor(void(C::*_function)(Param), C* object, const Param* params );


        //Functor(const Functor& cpy); //Static/Free function copy constructor

        virtual ~Functor();
        void execute();
        const Callback& callback() const;


    private:
        Callback* m_callback;
};

} //ns util


#include "Functor.inl"

#endif // FUNCTOR_H
