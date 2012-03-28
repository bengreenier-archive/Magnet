#include "Functor.h"
#include <iostream>
using namespace util;

Functor::~Functor()
{
    delete m_callback;
}

void Functor::execute()
{
    //m_callback->debug();
    //std::cout << "Execute called\n";
    m_callback->execute();
}

const Callback& Functor::callback() const
{
    return *m_callback;
}
