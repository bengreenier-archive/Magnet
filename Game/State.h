#ifndef STATE_H
#define STATE_H


class State {
    public:
        enum _type{
            Null,       //initial state
            Loading,    //Loading initial game resources, I.E.
            Menu,       //In a menu
            InGame,
            Initialize
        };

        State(_type init) : type(Null), initialState(init) {}

        _type get() { return type; }
        void set(_type newType){ type = newType; }
        //Resets state to default
        void reset() { type = initialState; }

    private:
        _type type;
        _type initialState;

};
#endif // STATE_H
