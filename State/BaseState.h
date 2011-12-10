#ifndef BASESTATE_H
#define BASESTATE_H

/**
    BaseState is an abstract class that defines
    how all states should behave
**/

namespace mag{

    typedef const int State_t;

    class BaseState
    {
        public:
            virtual void SetState(State_t newState);
            virtual State_t GetState();

            virtual void think(State_t parentState) = 0;
            virtual void think() = 0;
        protected:
        private:
            State_t m_state;
    };
}

#endif // BASESTATE_H
