#ifndef STATE_H
#define STATE_H


class State {
    public:
        enum _type{
            Null,       //initial state
            Load,
            Menu,       //In a menu
            Game,       //In game
            Initialize, //Initialize resources
            Setup,       //Setup resources
            Ready,
            Drawing,
            Pause
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
