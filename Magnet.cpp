#include "Magnet.h"

//Static memebetrs
Magnet*         Magnet::magnet_ptr           =   NULL;

Magnet::Magnet(sf::Thread& renderThread, sf::Thread& loadThread, State::_type defaultState) : gameState(defaultState)
{
    m_hooks.Register(Hook::Frame, &Magnet::Frame);
    m_hooks.Register(Hook::Initialize, &Magnet::Hook_Initialize);
    m_hooks.Register(Hook::Setup, &Magnet::Hook_Setup);

    EventHandler::AddKeyListener(sf::Key::Space, &Magnet::Event_SpacePressed);
    EventHandler::AddEventListener(sf::Event::MouseMoved, &Magnet::Event_MouseMove);

    m_renderThread_ptr  =   &renderThread;
    m_loadThread_ptr    =   &loadThread;

    m_mouseTrail.on = true;
}

Magnet::~Magnet()
{
    //dtor
}

void Magnet::Hook_Initialize(){
    Resource::Add("guns/assault1.png");
}

void Magnet::Hook_Setup(){
    //Renderer::CreateLink(new sf::Sprite(ImageHandler::GetImage("resource/image/guns/assault1.png"), sf::Vector2f(100, 100), sf::Vector2f(1, 1), 0.0f, sf::Color(255, 255, 255)));
    //Renderer::CreateLink(new sf::Shape(sf::Shape::Rectangle(100, 100, 110, 110, sf::Color(0, 255, 0))));
}

void Magnet::Event_MouseMove(sf::Event evt){
    if(Object("Event_MouseMove")->m_mouseTrail.on){
        const sf::Input& Input = Renderer::GetRenderWindow()->GetInput();
        Object("Event_MouseMove")->m_mouseTrail.MouseMove(sf::Vector2i(Input.GetMouseX(), Input.GetMouseY()));
    }
}

void Magnet::Event_SpacePressed(sf::Event evt){
    if(Object("Event_SpacePressed")->gameState.get() == State::Menu){
        Magnet::StartGame();
    }
}

void Magnet::StartGame(){
    Object("StartGame")->ChangeState(State::Game);
}



sf::Mutex* Magnet::GlobalMutex(){
    return &Object("GlobalMutex")->m_globalMutex;
}

Hook::Registry* Magnet::Hooks(std::string from){
    return &Object(from + "->Hooks")->m_hooks;
}

Hook::Registry* Magnet::Hooks(){
    return &Object()->m_hooks;
}

Magnet* Magnet::Object(std::string from){
    if(magnet_ptr == NULL)
        std::cout << "Magnet::Object(" << from << ")-> WARNING: Magnet not initialized! Null pointer returned\n";

    return magnet_ptr;
}

Magnet* Magnet::Object(){
    if(magnet_ptr == NULL)
        std::cout << "Magnet::Object()-> WARNING: Magnet not initialized! Null pointer returned\n";

    return magnet_ptr;
}

void Magnet::Init(sf::Thread& renderThread, sf::Thread& loadThread){
    if(magnet_ptr == NULL){
        magnet_ptr = new Magnet(renderThread, loadThread, State::Null);
    }else{
        if(Object()->gameState.get() == State::Null){
            Object()->ChangeState(State::Initialize);
        }
    }
}

bool Magnet::Initialized(){
    if(magnet_ptr == NULL)
        return false;

    return true;
}

void Magnet::ChangeState(State::_type newState){
    if(newState == gameState.get()) return;

    switch(newState){
        case State::Null:
            gameState.set(newState);
            std::cout << "**********\tNULL\t**********\n";
            break;
        case State::Initialize:
            gameState.set(newState);
            std::cout << "**********\tINITALIZE\t**********\n";
            std::cout << "[Magnet][Initialize] Initialize resource...\n";
            Resource::Init(Object("ChangeState")->m_loadThread_ptr, "resource/");
            std::cout << "[Magnet][Initialize] Initialize world...\n";
            World::Init();
            std::cout << "[Magnet][Initialize] Calling setup hook\n";
            Object("ChangeState")->m_hooks.Call(Hook::Initialize);

            m_renderThread_ptr->Launch();

            Object("ChangeState")->ChangeState(State::Loading);
            break;
        case State::Loading:
            gameState.set(newState);
            std::cout << "**********\tLOADING\t**********\n";
            std::cout << "[Magnet][State][Loading] Start...\n";
            m_hooks.Call(Hook::Load);
            break;
        case State::Setup:
            gameState.set(newState);
            std::cout << "**********\tSETUP\t**********\n";
            std::cout << "[Magnet][State][Setup] Start...\n";
            m_hooks.Call(Hook::Setup);
            break;
        case State::Menu:
            gameState.set(newState);
            std::cout << "**********\tMENU\t**********\n";
            break;
        case State::Game:
            gameState.set(newState);
            std::cout << "**********\tGAME\t**********\n";
            break;
        default:
            std::cout << "*** ERROR: State \"" << typeid(newState).name() << "\" is not a valid game state! Setting to default state.\n";
            gameState.reset();
    }

    m_hooks.Call(Hook::GameStateChange);


}

void Magnet::Frame(){
    if(magnet_ptr == NULL) return;

    //Should be called every frame
    switch(Object("Frame")->gameState.get()){
        case State::Loading:
            if(Resource::IsLoading()){
                std::cout << "Loading progress:\t" << Resource::LoadProgress() << std::endl;
            }else{
                std::cout << "Loading progress:\t" << Resource::LoadProgress() << std::endl;
                Object("Frame")->ChangeState(State::Setup);
            }
            break;
        case State::Setup:
            StartGame();
            break;
    }

    if(Object("Frame")->m_mouseTrail.on){
        Object("Frame")->m_mouseTrail.Frame();
    }
}
