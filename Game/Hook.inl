
//Construct a hook from a static/free function
template< typename T >
Hook::Hook(Type htype, T function, hook_lifespan_t life)
:   m_type(htype),
    m_callback(function),
    m_lifespan(life)
{ }

//Construct a hook from a member function
template< typename T, typename C >
Hook::Hook(Type htype, T function, C* object, hook_lifespan_t life)
:   m_type(htype),
    m_callback(function, object),
    m_lifespan(life)
{ }
