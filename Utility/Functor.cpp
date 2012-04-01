#include "Functor.h"
#include "Exception.h"

using namespace util;

Functor::~Functor()
{
    delete m_callback;
}

void Functor::execute() throw( util::Exception )
{
    m_callback->execute();
}

const Callback& Functor::callback() const
{
    return *m_callback;
}
