#include "Magnet.h"

//Static memebetrs
Magnet*         Magnet::magnet_ptr           =   NULL;

Magnet::Magnet(sf::RenderWindow& window, sf::Thread& renderThread, sf::Thread& loadThread, State::_type defaultState) : gameState(defaultState)
{
    m_hooks.Register(Hook::Initialize, &Magnet::Hook_Initialize);
    m_hooks.Register(Hook::Setup, &Magnet::Hook_Setup);

    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonReleased, Event_MouseButtonReleased));
    EventHandler::AddListener(new EventListener(sf::Event::MouseMoved, Event_MouseMove));
    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonPressed, Event_MouseButtonPressed));
    EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, Event_SpacePressed ));

    m_renderThread_ptr  =   &renderThread;
    m_loadThread_ptr    =   &loadThread;
    m_renderWindow      =   &window;

    m_renderWindow->SetFramerateLimit(30);

    m_mouseTrail.on = false;
    name = "test_cmp";
    m_initialized = false;
}

Magnet::~Magnet()
{
    //dtor
}

void Magnet::Hook_Initialize(){
    try{
        Resource::AddDir("images/", true);
    }

    catch(Exception e){
        e.output();
    }
}

void Magnet::Debug_CreateMenu(){
    std::cout << "Create menu\n";
    int r = rand() % 255 + 1;
    int g = rand() % 255 + 1;
    int b = rand() % 255 + 1;
    Object()->test = new mgui::Panel(name);
    Object()->test->SetColor(sf::Color(r, g, b)) ;
    Object()->test->SetVisible(true);
    Object()->test->Create();
    Object()->m_menus.Register(Object()->test);
}

void Magnet::Hook_Setup(){
    Object()->Debug_CreateMenu();
}

bool Magnet::Event_MouseMove(sf::Event evt){
    if(Object() == NULL) return true;

    if(Object("Event_MouseMove")->m_mouseTrail.on){
       Object("Event_MouseMove")->m_mouseTrail.MouseMove(sf::Vector2i(evt.MouseMove.X, evt.MouseMove.Y));
    }

    return Object()->m_menus.onEvent(evt);
}

bool Magnet::Event_MouseButtonPressed(sf::Event evt){
    return Object()->m_menus.onEvent(evt);
}

bool Magnet::Event_MouseButtonReleased(sf::Event evt){
    return Object()->m_menus.onEvent(evt);
}

bool Magnet::Event_SpacePressed(sf::Event evt){
    if(evt.Key.Code == sf::Key::Space){
        Object()->Debug_CreateMenu();
    }else if(evt.Key.Code == sf::Key::A){
        bool linkExists = Renderer::Object("Magnet")->LinkExists(Renderer::Object("Magnet")->GetLinkByDrawable(static_cast<sf::Shape*>(Object("Magnet")->test)));
        std::cout << "Menu link exists:\t" << linkExists << std::endl;
        std::cout << "Menu is registered:\t" << Object()->m_menus.ComponentExists(Object()->name) << std::endl;
    }else if(evt.Key.Code == sf::Key::R){
        Object()->test->Remove();

        int wait = 0;
        while(wait<1000000000){
            wait ++;
        }
        Object()->Debug_CreateMenu();
    }

    /*if(Object("Event_SpacePressed")->gameState.get() == State::Menu){
        Magnet::StartGame();
    }*/

    return true;
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

mgui::Registry* Magnet::Menus(){
    return &Object()->m_menus;
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

void Magnet::Init(sf::RenderWindow& window, sf::Thread& renderThread, sf::Thread& loadThread){
    if(magnet_ptr == NULL){
        magnet_ptr = new Magnet(window, renderThread, loadThread, State::Null);
    }else{
        if(Object()->gameState.get() == State::Null){
            Object()->ChangeState(State::Initialize);
        }
    }
}

bool Magnet::Initialized(){
    if(magnet_ptr == NULL){
        return false;
    }

    if(!Object()->m_initialized){
        return false;
    }


    return true;
}

void Magnet::ChangeState(State::_type newState){
    if(newState == gameState.get()) return;
    switch(newState){
        case State::Null:
            std::cout << "**********\tNULL\t**********\n";

            gameState.set(newState);
            break;
        case State::Initialize:
            std::cout << "**********\tINITALIZE\t**********\n";
            std::cout << "[Magnet][Initialize] Initialize renderer...\n";
            Renderer::Init(*Object()->m_renderWindow, *Object()->m_renderThread_ptr);
            std::cout << "[Magnet][Initialize] Initialize resource...\n";
            Resource::Init(Object("ChangeState")->m_loadThread_ptr, "resource/");
            std::cout << "[Magnet][Initialize] Initialize world...\n";
            World::Init();

            Object()->m_initialized = true;
            Magnet::Hooks("Renderer::Render")->Call(Hook::Initialize);

            gameState.set(newState);
            break;
        case State::Loading:
            std::cout << "**********\tLOADING\t**********\n";
            m_hooks.Call(Hook::Load);

            gameState.set(newState);
            break;
        case State::Setup:
            std::cout << "**********\tSETUP\t**********\n";
            m_hooks.Call(Hook::Setup);

            gameState.set(newState);
            break;
        case State::Menu:
            std::cout << "**********\tMENU\t**********\n";


            gameState.set(newState);
            break;
        case State::Game:
            std::cout << "**********\tGAME\t**********\n";

            gameState.set(newState);
            break;
        default:
            std::cout << "*** ERROR: State \"" << typeid(newState).name() << "\" is not a valid game state! Setting to default state.\n";
            gameState.reset();
    }
    m_hooks.Call(Hook::GameStateChange);


}

void Magnet::Frame(){
    if(magnet_ptr == NULL) return;

    switch(Object("Frame")->gameState.get()){
        case State::Initialize:
            Object("ChangeState")->ChangeState(State::Loading);
            break;
        case State::Loading:
            if(Resource::Loading()){
                std::cout << "[Magnet][Frame] Loading progress:\t" << Resource::LoadProgress() << std::endl;
            }else{
                if(Resource::Ready()){
                    Object("Frame")->ChangeState(State::Setup);
                }
            }
            break;
        case State::Setup:
            StartGame();
            break;
    }

    if(Object("Frame")->m_mouseTrail.on){
        Object("Frame")->m_mouseTrail.Frame();
    }

    Magnet::Hooks("Renderer::Render")->Call(Hook::Frame);

    if(!Renderer::IsRunning()){
        //Draw the frame
        Object()->m_renderThread_ptr->Launch();
    }
}
