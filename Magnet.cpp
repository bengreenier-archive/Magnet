#include "Magnet.h"

Magnet*         Magnet::magnet_ptr           =   NULL;

Magnet::Magnet(sf::Window& window, sf::Thread& renderThread, sf::Thread& loadThread, State::_type defaultState) : gameState(defaultState)
{
    /*m_hooks.Register(Hook::Initialize, &Magnet::Hook_Initialize);



    m_hooks.Register(Hook::Initialize,&Magnet::ben_testing_space);//call ben testing space

    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonReleased, Event_MouseButtonReleased));
    EventHandler::AddListener(new EventListener(sf::Event::MouseMoved, Event_MouseMove));
    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonPressed, Event_MouseButtonPressed));
    EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, Event_SpacePressed ));*/

    m_hooks.Register(Hook::Setup, &Magnet::Hook_Setup);

    m_renderThread_ptr  =   &renderThread;
    m_loadThread_ptr    =   &loadThread;
    m_renderWindow      =   &window;

    m_renderWindow->SetFramerateLimit(30);

    m_services_initialized   = false;

    CfgParse cfgparser("resource/config/magnet.mcf");
    cfgparser.Parse(m_config);

    if(!cfgparser.IsParsed()){
        throw Exception(Exception::LoadFail, "Missing config", "The Magnet configuration file is missing");
    }

    if(m_config.GetKeyObject("debug")->GetBool()){
        dbg_timer = new sf::Clock();
        dbg_timer->Restart();
    }
}

Magnet::~Magnet()
{
    delete magnet_ptr;
}

/*
void Magnet::Hook_Initialize(){

}
*/
void Magnet::Hook_Setup(){
    try{
        Resource::AddDir(Resource::GetRootPath());
        Resource::AddFile("resource/font/tahoma.ttf");
        Resource::AddFile("resource/image/earth.png");
    }

    catch(Exception e){
        e.output();
        std::cout << "[Magnet][Hook_Setup] Could not add files from directory '" << Resource::GetRootPath() << "'\n";
    }
}

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

bool Magnet::Event_SpacePressed(sf::Event evt){
    if(evt.Key.Code == sf::Keyboard::Space){
        Object()->Debug_CreateMenu();
    }else if(evt.Key.Code == sf::Keyboard::A){
       // if(Object()->test == NULL){
         //   std::cout << "Menu link exists:\t0\n";
        //}else{
         //   bool linkExists = Renderer::Object()->LinkExists(Object()->test->GetRendererLink());
          //  std::cout << "Menu link exists:\t" << linkExists << std::endl;
        //}
        //std::cout << "Menu is registered:\t" << Object()->m_menus.ComponentExists(Object()->name) << std::endl;
    }else if(evt.Key.Code == sf::Keyboard::R){
        try{

        }

        catch(Exception e){
            e.output();
        }
        catch(...){
            std::cout << "[Magnet][KeyPress] Unhandled exception\n";
        }

        //In setup hook
        //Magnet::Loader->Add(new Config("resource/config/test.mcf"));
        //data = Resource::GetConfig("test.mcf");
    }

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

Hook::Registry* Magnet::Hooks(){
    return &Object()->m_hooks;
}
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

void Magnet::Init(sf::Window& window, sf::Thread& renderThread, sf::Thread& loadThread) throw(Exception){
    if(magnet_ptr == NULL){
        try{
            magnet_ptr = new Magnet(window, renderThread, loadThread, State::Null);
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
    m_hooks.Call(Hook::GameStateChange);
}

Config* Magnet::GlobalConfig(){
    return &Object()->m_config;
}

void Magnet::State_Initialize(){
    if(!m_services_initialized){
        std::cout << "**********\tINITALIZE\t**********\n";
        std::cout << "[Magnet][Initialize] Initialize renderer...\n";
        Renderer::Init(*m_renderWindow, *Object()->m_renderThread_ptr);
        std::cout << "[Magnet][Initialize] Initialize resource...\n";
        Resource::Init(m_loadThread_ptr, "resource/");
        std::cout << "[Magnet][Initialize] Initialize WorldManager\n";
        WorldManager::Init();

        m_services_initialized = true;

        Magnet::Hooks()->Call(Hook::Initialized);
    }else{
        if(Object()->dbg_timer != NULL){
            std::cout << "[Magnet] Initialized in " << Object()->dbg_timer->GetElapsedTime().AsMilliseconds()  << "ms\n";
            Object()->dbg_timer->Restart();
        }

        ChangeState(State::Setup);
    }
}

void Magnet::State_Setup(){
    std::cout << "**********\tSETUP\t**********\n";
    m_hooks.Call(Hook::Setup);

    ChangeState(State::Load);
}

void Magnet::State_Load(){
    if(Resource::Loading()) return; //Wait

    if(Resource::Ready()){
        Magnet::Hooks()->Call(Hook::LoadComplete);
        ChangeState(State::Ready);
    }else{
        if(Resource::NeedLoad()){
            std::cout << "**********\tLOAD\t**********\n";
            Magnet::Hooks()->Call(Hook::StartLoad);
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
            if(Magnet::GlobalConfig()->GetKeyObject("debug")->GetBool()){
                if(Object()->dbg_timer != NULL){
                    std::cout << "[Magnet] Loaded in " << Object()->dbg_timer->GetElapsedTime().AsMilliseconds()  << "ms\n";
                    delete Object()->dbg_timer;
                    Object()->dbg_timer = 0;
                }
            }
            //Wait for state change requests
            break;
    }

    Hooks()->Call(Hook::Think);
}
