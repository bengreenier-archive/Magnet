#include <iostream>

namespace util {


struct Callback
{
    virtual ~Callback() {}
    virtual void execute() = 0;
    virtual void debug() const
    {
        //std::cout << "ERROR CALLBACK NOT OVERWRITTEN!\n";
    }
};

/// Static/Free function without arguments
template< typename F >
struct _cb_static_na : Callback{
    _cb_static_na( F _function ) : m_function(_function)
    {}

    virtual void execute()
    {
        //std::cout << "executing functor " << m_function << "\n";
        m_function();
    }

    virtual void debug() const{
        //std::cout << "Static functor with no arguments\n";
    }

    F m_function;
};
/*
template< typename F >
struct _cb_static_a : Callback{
    _cb_static_a( F _function, const Param* _params )
    :   function(_function),
        params(_params)
    {}

    virtual void execute()
    {
        std::cout << "_cb_static_a\n";
        function(params);
    }

    F function;
    const Param* params;
};
*/

/// Member function without arguments

template< typename C >
struct _cb_member_na : Callback{
    _cb_member_na( void(C::*_function)(), C* _object )
    :   function(_function),
        object(_object)
    {}

    virtual void execute() throw(Exception)
    {
        //std::cout << "_cb_member_na\n";
        (object->*function)();
    }

    void(C::*function)();
    C*  object;
};
/*
template< typename C >
struct _cb_member_a : Callback{
    _cb_member_a( void(C::*_function)(Param), C* _object, Param _params )
    :   function(_function),
        object(_object),
        params(_params)
    {}
    virtual ~_cb_member_a(){ delete params; }

    virtual void execute()
    {
        std::cout << "_cb_member_a\n";
        object->*function(params);
    }

    void(C::*function)(Param);
    C*  object;
    const Param* params;
};
*/


/// Static constructor function without arguments
template< typename F >
Functor::Functor( F _function )
:   m_callback( new _cb_static_na< F >( _function) )
{
    //std::cout << "[Functor] Constructing static functor with no args!\n";
}

/*
template< typename F >
Functor::Functor( F _function, const Param* params ) //Pointer-to-function
:   m_callback( new _cb_static_a< F >( _function, params) )
{}
*/


/// Member constructor function without arguments
template< typename C >
Functor::Functor( void(C::*_function)(), C* object )             //Pointer-to-member without arguments
:   m_callback( new _cb_member_na< C >( _function, object) )
{}

/*
template< typename C >
Functor::Functor(void(C::*_function)(Param), C* object, const Param* params ) //Point-to-member with arguments
:   m_callback( new _cb_member_a< C >( _function, object, params) )
{}
*/
} //ns util
