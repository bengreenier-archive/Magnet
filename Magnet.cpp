#include "Magnet.h"

#include <typeinfo>

//Static memebetrs
Magnet*         Magnet::magnet_ptr           =   NULL;

Magnet::Magnet(State::_type defaultState) : gameState(defaultState)
{
    m_hooks.Register(Hook::Frame, &Magnet::Frame);

    EventHandler::AddKeyListener(sf::Key::Space, &Magnet::Event_SpacePressed);
    EventHandler::AddEventListener(sf::Event::MouseMoved, &Magnet::Event_MouseMove);
}

Magnet::~Magnet()
{
    //dtor
}

void Magnet::Event_MouseMove(sf::Event evt){
    if(Object()->m_mouseTrail.on){
        const sf::Input& Input = Renderer::GetRenderWindow()->GetInput();
        Object()->m_mouseTrail.MouseMove(sf::Vector2i(Input.GetMouseX(), Input.GetMouseY()));
    }
}

void Magnet::Event_SpacePressed(sf::Event evt){
    if(Object()->gameState.get() == State::Menu){
        Magnet::StartGame();
    }
}

void Magnet::StartGame(){
    if(Object()->gameState.get() == State::Menu){
        Object()->ChangeState(State::InGame);
    }
}



sf::Mutex* Magnet::GlobalMutex(){
    return &Object()->m_globalMutex;
}

Hook::Registry* Magnet::Hooks(){
    return &Object()->m_hooks;
}

Magnet* Magnet::Object(){
    if(magnet_ptr == NULL)
        magnet_ptr = new Magnet(State::Null);

    return magnet_ptr;
}

void Magnet::ChangeState(State::_type newState){
    if(newState == gameState.get()) return;

    switch(newState){
        case State::Null:
            gameState.set(newState);
            std::cout << "**********\tNULL\t**********\n";
            break;
        case State::Loading:
            gameState.set(newState);
            std::cout << "**********\tLOADING\t**********\n";
            break;
        case State::Menu:
            gameState.set(newState);
            std::cout << "**********\tMENU\t**********\n";
            break;
        case State::InGame:
            gameState.set(newState);
            std::cout << "**********\tINGAME\t**********\n";
            break;
        default:
            std::cout << "*** ERROR: State \"" << typeid(newState).name() << "\" is not a valid game state! Setting to default state.\n";
            gameState.reset();
    }

    m_hooks.Call(Hook::GameStateChange);


}

void Magnet::Frame(){
    //Should be called every frame
    switch(Object()->gameState.get()){
        case State::Null:
            Object()->ChangeState(State::Loading);
            break;
        case State::Loading:
            //Load menu resources
            Object()->ChangeState(State::Menu);
            break;
        case State::Menu:
            //Wait for user to start game
            break;
        case State::InGame:
            //Wait for user to resturn to menu/exit game
            break;
    }

    if(Object()->m_mouseTrail.on){
        Object()->m_mouseTrail.Frame();
    }
}
