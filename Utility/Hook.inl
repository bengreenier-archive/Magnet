
using namespace util;

//Construct a hook from a static/free function
template< typename T >
Hook::Hook(const std::string& unique_name, Type htype, T function, hook_lifespan_t life)
:   m_name(unique_name.c_str()),
    m_type(htype),
    m_callback(function),
    m_lifespan(life)
{ }

//Construct a hook from a member function
template< typename T, typename C >
Hook::Hook(const std::string& unique_name, Type htype, T function, C* object, hook_lifespan_t life)
:   m_name(unique_name.c_str()),
    m_type(htype),
    m_callback(function, object),
    m_lifespan(life)
{ }
