#include "BaseState.h"
namespace mag{
    void BaseState::SetState(State_t newState){
        m_state = newState;
    }

    State_t BaseState::GetState(){
        return m_state;
    }
}
