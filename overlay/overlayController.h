#ifndef OVERLAYCONTROLLER_H
#define OVERLAYCONTROLLER_H
#include <map>
#include <string>
#include "overlay.h"

class overlayController //! Old, useless and Depreciated.
{
    public:
        overlayController();
        static overlayController* get();
    protected:
    private:


        static overlayController* overlay_pointer;
        std::map <std::string, overlay> object_map;

};

#endif // OVERLAYCONTROLLER_H
