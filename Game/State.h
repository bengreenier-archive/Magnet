#ifndef STATE_H
#define STATE_H


class State {
    public:
        enum _type{
            NullPointer,    //Pointers still need to be set
            Ready           //Pointers are set, threads are running
        };

        State(_type init) : type(init), initialState(init) {}

        _type get() { return type; }
        void set(_type newType){ type = newType; }
        //Resets state to default
        void reset() { type = initialState; }

    private:
        _type type;
        _type initialState;

};
#endif // STATE_H
