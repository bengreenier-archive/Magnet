#ifndef MOVEMENTBASE_H
#define MOVEMENTBASE_H

//because everything needs to move, but not all is user controlled, or random or other..diff movements all inherit this

namespace Movement
    {
        enum Type{
            Up,
            Down,
            Left,
            Right,
            Jump
        };
    };


class MovementBase
{
    public:
        MovementBase();
        ~MovementBase();
        int MovementSpeed;
        void SetSpeed(int i);
    protected:
    private:
};

#endif // MOVEMENTBASE_H
