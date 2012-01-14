#ifndef MGUI_H
#define MGUI_H


namespace mgui {
    ////////////////////////////////////////////////////////////////////////////////////////////
    ///    Typedef:         bool *funcPtr_callBack_t
    ///    Params:          Any number of arguments, to be handled by the callback
    ///    Returns:         true/false callback execution succeed/fail
    ////////////////////////////////////////////////////////////////////////////////////////////
    typedef bool(*funcPtr_callBack_t)(...);

}

#include "Component.h"

#endif // MGUI_H
