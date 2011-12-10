#ifndef GUNENUM_H
#define GUNENUM_H


struct GunEnum
{
    enum Type{
        Light, //Any gun considered light IE shoots fast does little damage
        Heavy, //Any gun considered heavy IE shoots slow foes large damage
        Special //Any gun that does not fall into the other categoryies
    };

    enum Component{
        Front,
        Middle,
        Rear
    };
};

#endif // GUNENUM_H
