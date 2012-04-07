#include "Magnet.h"
#include "Pipeline.h"
#include "Utility.h"

using util::Functor;

Magnet*         Magnet::magnet_ptr           =   NULL;

Magnet::Magnet(size_t _serial_entity_size, sf::Window& window, sf::Thread& loadThread, State::_type defaultState)
    :   gameState(defaultState),
        m_renderer(new Renderer(&window)),
        m_cache("Magnet cache"),
        m_hooks("MagnetHooks")
    //,   m_config()
{
    m_hooks.registerHook(new Hook("initialize_magnet", Hook::onInitialize, &Magnet::Hook_Initialize));
    //m_hooks.Register(new Hook(Hook::Setup,      &Magnet::Hook_Setup));

    EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, &Magnet::event_keyPressed));

    m_renderThread_ptr  =   new sf::Thread(&Renderer::onDrawFrame, m_renderer);
    m_loadThread_ptr    =   &loadThread;
    m_renderWindow      =   &window;

    m_renderWindow->setFramerateLimit(30);

    m_services_initialized   = false;
   /* CfgParse cfgparser("resource/config/magnet.mcf");
    std::cout << "Config\n";
    cfgparser.Parse(m_config);

    if(!cfgparser.IsParsed()){
        throw Exception(Exception::LoadFail, "Missing config", "The Magnet configuration file is missing");
    }
    */

    //if(m_config.GetVar("debug")->GetBool()){
        dbg_timer = new sf::Clock();
        dbg_timer->restart();
    //}
}

Magnet::~Magnet()
{
    delete magnet_ptr;
}

bool Magnet::ServicesInitialized()
{
    return Object()->m_services_initialized;
}

bool Magnet::event_keyPressed(sf::Event evt)
{
    if(evt.key.code == sf::Keyboard::Escape){
        Object()->m_renderWindow->close();
    }
}


void Magnet::Hook_Initialize(){
    //Object()->m_renderer->initialize();
    std::cout << "Magnet initialize\n";
}

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

void Magnet::Init(size_t& _serial_entity_size, sf::Window& window, sf::Thread& loadThread) throw(util::Exception){
    if(magnet_ptr == NULL){
        try{
            magnet_ptr = new Magnet(_serial_entity_size, window, loadThread, State::Null);
        }

        catch(util::Exception e){
            //e.output();
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

//Config* Magnet::GlobalConfig(){
//    return &Object()->m_config;
//}

void Magnet::State_Initialize() {
    if(!m_services_initialized){
        dbgconsole << "\n[Magnet] *** INITIALIZE STATE ***\n";
        Magnet::Hooks()->Call(Hook::onInitializeSingletons);
        Magnet::Hooks()->Call(Hook::onInitialize);

        m_services_initialized = true;
    }else{
        if(Object()->dbg_timer != NULL){
            Object()->dbg_resetTimer("[Magnet] Initialization took ");
        }

        ChangeState(State::Load);
    }
}

void Magnet::State_Setup(){
//    Magnet::Hooks()->Call(Hook::Setup);

    ChangeState(State::Load);
}

void Magnet::State_Load(){
    dbgconsole << "\n[Magnet] *** LOAD STATE ***\n";
    Magnet::Hooks()->Call(Hook::Setup);
//    if(Resource::Loading()) return; //Wait

   // if(Resource::Ready()){
//        Magnet::Hooks()->Call(Hook::LoadComplete);
        ChangeState(State::Ready);
   // }else{
       // if(Resource::NeedLoad()){
        //    std::cout << "**********\tLOAD\t**********\n";
//            Magnet::Hooks()->Call(Hook::StartLoad);
     //   }else{
            std::cout << "[Magnet][State_Load] Load skipped, no resources\n";
            ChangeState(State::Ready);
       // }
   // }
}

void Magnet::State_Entry()
{
    dbgconsole << "\n[Magnet] *** ENTRY STATE ***\n";
    //Registry service registry hooks
    util::ServiceRegistry::RegisterHooks();

    Object()->ChangeState(State::Initialize);
    Object()->dbg_resetTimer("[Magnet] Entry took ");
}

void Magnet::Think(){
    if(!IsInitialized()) return;

    switch(Object()->gameState.get()){
        case State::Null:
            Object()->State_Entry();
            break;
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
            /*
            if(Magnet::GlobalConfig()->GetVar("debug")->GetBool()){
                if(Object()->dbg_timer != NULL){
                    Object()->dbg_resetTimer("[Magnet] Initial load took ");
                    Object()->dbg_deleteTimer();
                }
            }
            */
            //Wait for state change requests
            break;
    }

    Hooks()->Call(Hook::onThink);
}

void Magnet::dbg_deleteTimer(){
    delete Object()->dbg_timer;
    Object()->dbg_timer = 0;
}
void Magnet::dbg_resetTimer(std::string msg){
    if(Object()->dbg_timer->getElapsedTime().asMilliseconds() > 1000){
        debuglog << msg << Object()->dbg_timer->getElapsedTime().asSeconds()  << "s\n";
    }else if(Object()->dbg_timer->getElapsedTime().asMicroseconds() > 1000){
        debuglog<< msg << Object()->dbg_timer->getElapsedTime().asMilliseconds()  << "ms\n";
    }else{
        if(Object()->dbg_timer->getElapsedTime().asMicroseconds() > 0)
        {
            debuglog << msg << (int)Object()->dbg_timer->getElapsedTime().asMicroseconds()  << (char)(230) << "s\n";
        }else{
            debuglog << msg << " < 1 " << (char)(230) << "s\n";
        }
    }
    dbg_timer->restart();
}
