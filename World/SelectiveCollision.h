#ifndef SELECTIVECOLLISION_H
#define SELECTIVECOLLISION_H

#include "Material/Material.h"

namespace Collision
{
    enum Type{
    Disengage,
    Engage,
    Toggleable
    };
}

class SelectiveCollision
{
    public:
        /** Default constructor */
        SelectiveCollision(Material* from,Material* to ,Collision::Type flag = Collision::Disengage);
        /** Default destructor */
        ~SelectiveCollision();
    protected:
    private:
};

#endif // SELECTIVECOLLISION_H
