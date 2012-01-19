#ifndef SELECTIVECOLLISION_H
#define SELECTIVECOLLISION_H

#include "Material/Material.h"

namespace Collision //! defines the types of collisions that can be selectively controlled
{
    enum Type{
    Disengage,
    Engage,
    Toggleable
    };
}

class SelectiveCollision //! a selective collision is a collision that can be programmically manipulated.
{
    public:

        SelectiveCollision(Material* from,Material* to ,Collision::Type flag = Collision::Disengage); //!< Default constructor

        ~SelectiveCollision(); //!< Default destructor
    protected:
    private:
};

#endif // SELECTIVECOLLISION_H
