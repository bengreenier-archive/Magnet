#include "Functor.h"
#include <iostream>
using namespace util;

Functor::~Functor()
{
    delete m_callback;
}

void Functor::begin()
{
    this->m_callback->execute();
}
