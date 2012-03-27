#include "Magnet.h"

#include "Memory/SharedVar.h"

using util::Functor;

Magnet*         Magnet::magnet_ptr           =   NULL;

Magnet::Magnet(size_t _serial_entity_size, sf::Window& window, sf::Thread& loadThread, State::_type defaultState)
    :   gameState(defaultState),
        m_renderer(new Renderer(&window))
{
    std::cout << "Creating functor ... ";
    Functor intialize_functor( &Magnet::Think );

    //m_hooks.Register(new Hook(Hook::Initialize, intialize_functor));
    //m_hooks.Register(new Hook(Hook::Setup,      &Magnet::Hook_Setup));

    EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, &Magnet::event_keyPressed));

    m_renderThread_ptr  =   new sf::Thread(&Renderer::frame, m_renderer);
    m_loadThread_ptr    =   &loadThread;
    m_renderWindow      =   &window;

    m_renderWindow->setFramerateLimit(30);

    m_services_initialized   = false;
    CfgParse cfgparser("resource/config/magnet.mcf");
    std::cout << "Config\n";
    cfgparser.Parse(m_config);

    if(!cfgparser.IsParsed()){
        throw Exception(Exception::LoadFail, "Missing config", "The Magnet configuration file is missing");
    }

    if(m_config.GetVar("debug")->GetBool()){
        dbg_timer = new sf::Clock();
        dbg_timer->restart();
    }
}

Magnet::~Magnet()
{
    delete magnet_ptr;
}

bool Magnet::event_keyPressed(sf::Event evt)
{
    if(evt.key.code == sf::Keyboard::Escape){
        Object()->m_renderWindow->close();
    }
}


/*void Magnet::Hook_Initialize(){
    Object()->m_renderer->initialize();
}
*/
//void Magnet::Hook_Setup(){
    //Magnet does not need any resources on the Initial load
    /*
    try{
        Resource::AddDir("image/", true);
    }

    catch(Exception e){
        e.output();
        std::cout << "[Magnet][Hook_Setup] Could not add files from directory '" << Resource::GetRootPath() << "'\n";
    }
    */
//}

/*

bool Magnet::Event_MouseMove(sf::Event evt){
   // if(Object() == NULL) return true;

    //return Object()->m_menus.onEvent(evt);
    return true;
}

bool Magnet::Event_MouseButtonPressed(sf::Event evt){
   // return Object()->m_menus.onEvent(evt);
   return true;
}

bool Magnet::Event_MouseButtonReleased(sf::Event evt){
   // return Object()->m_menus.onEvent(evt);
   return true;
}



void Magnet::StartGame(){
    Object("StartGame")->ChangeState(State::Game);
}

Achievements::Registry* Magnet::Achieves(){
    return &Object()->m_acheivs;
}

sf::Mutex* Magnet::GlobalMutex(){
    return &Object("GlobalMutex")->m_globalMutex;
}*/

/*HookRegistry* Magnet::Hooks(){
    return &Object()->m_hooks;
}
*/
/*
mgui::Registry* Magnet::Menus(){
    return &Object()->m_menus;
}
*/

Magnet* Magnet::Object(){
    if(magnet_ptr == NULL)
        std::cout << "Magnet::Object()-> WARNING: Magnet not initialized! Null pointer returned\n";

    return magnet_ptr;
}

void Magnet::Init(size_t _serial_entity_size, sf::Window& window, sf::Thread& loadThread) throw(Exception){
    if(magnet_ptr == NULL){
        try{
            magnet_ptr = new Magnet(_serial_entity_size, window, loadThread, State::Null);
        }

        catch(Exception e){
            e.output();
            magnet_ptr = NULL;
            throw e;
        }
    }
}

bool Magnet::IsInitialized(){
    if(magnet_ptr == NULL){
        return false;
    }

    return true;
}

void Magnet::ChangeState(State::_type newState){
    if(newState == gameState.get()) return;

    gameState.set(newState);
    //m_hooks.Call(Hook::GameStateChange);
}

Config* Magnet::GlobalConfig(){
    return &Object()->m_config;
}

void Magnet::State_Initialize() {
    if(!m_services_initialized){
        std::cout << "**********\tINITALIZE\t**********\n";
        //Magnet::Hooks()->Call(Hook::InitialzeSingletons);

        //std::cout << "[Magnet][Initialize] Initialize renderer...\n";
        //Renderer::Init(*m_renderWindow, *Object()->m_renderThread_ptr);
        std::cout << "[Magnet][Initialize] Initialize resource...\n";
        Resource::Init(m_loadThread_ptr, "resource/");
        std::cout << "[Magnet][Initialize] Initialize Sandbox\n";
        //Sandbox::Init();

        m_services_initialized = true;

        std::cout << "Calling initialized hook\n";
//        Magnet::Hooks()->Call(Hook::Initialize);
        std::cout << "called initialized hook\n";
    }else{
        if(Object()->dbg_timer != NULL){
            Object()->dbg_resetTimer("[Magnet] Initialization took ");
        }

        std::cout << "Changing state to setup\n";
        ChangeState(State::Setup);
        std::cout << "state changed to setup\n";
    }
}

void Magnet::State_Setup(){
    std::cout << "**********\tSETUP\t**********\n";
//    Magnet::Hooks()->Call(Hook::Setup);

    ChangeState(State::Load);
}

void Magnet::State_Load(){
    if(Resource::Loading()) return; //Wait

    if(Resource::Ready()){
//        Magnet::Hooks()->Call(Hook::LoadComplete);
        ChangeState(State::Ready);
    }else{
        if(Resource::NeedLoad()){
            std::cout << "**********\tLOAD\t**********\n";
//            Magnet::Hooks()->Call(Hook::StartLoad);
        }else{
            std::cout << "**********\tSKIP LOAD ( no resources )\t**********\n";
            ChangeState(State::Ready);
        }
    }
}

void Magnet::Think(){
    if(!IsInitialized()) return;

    switch(Object()->gameState.get()){
        case State::Null:
            Object()->ChangeState(State::Initialize);
        case State::Initialize:
            Object()->State_Initialize();
            break;
        case State::Load:
            Object()->State_Load();
            break;
        case State::Setup:
            Object()->State_Setup();
            break;
        case State::Ready:
            if(Magnet::GlobalConfig()->GetVar("debug")->GetBool()){
                if(Object()->dbg_timer != NULL){
                    Object()->dbg_resetTimer("[Magnet] Initial load took ");
                    Object()->dbg_deleteTimer();
                }
            }
            //Wait for state change requests
            break;
    }

//    Hooks()->Call(Hook::Think);
}

void Magnet::dbg_deleteTimer(){
    delete Object()->dbg_timer;
    Object()->dbg_timer = 0;
}
void Magnet::dbg_resetTimer(std::string msg){
    /*if(Object()->dbg_timer->GetElapsedTime().AsMilliseconds() > 1000){
        std::cout << msg << Object()->dbg_timer->GetElapsedTime().AsSeconds()  << "s\n";
    }else{
        std::cout << msg << Object()->dbg_timer->GetElapsedTime().AsMilliseconds()  << "ms\n";
    }*/
    //dbg_timer->Restart();
}
