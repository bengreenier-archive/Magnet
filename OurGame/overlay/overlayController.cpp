#include "overlayController.h"
#include <iostream>

overlayController* overlayController::overlay_pointer=NULL;

overlayController::overlayController()
{
    //ctor
}

overlayController* overlayController::get()
{
    if (overlay_pointer==NULL)
        overlay_pointer=new overlayController();

    return overlay_pointer;

}

