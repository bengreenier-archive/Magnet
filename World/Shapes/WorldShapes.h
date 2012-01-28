#ifndef WORLDSHAPES_H
#define WORLDSHAPES_H

namespace WorldShapes //! Contains WorldShape type enums, to tell what shape an object is.
{
    enum Type //!< The definitions of all the types that can be created in World
    {
        Rect,
        Circle,
        StaticRect,
        StaticCircle,
        Triangle,
        StaticTriange,
        Projectile
    };
}
#endif
