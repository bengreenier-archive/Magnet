#include "Magnet.h"

//Static memebetrs
Magnet*         Magnet::magnet_ptr           =   NULL;

Magnet::Magnet(sf::RenderWindow& window, sf::Thread& renderThread, sf::Thread& loadThread, State::_type defaultState) : gameState(defaultState)
{
    m_hooks.Register(Hook::Initialize, &Magnet::Hook_Initialize);
    m_hooks.Register(Hook::Setup, &Magnet::Hook_Setup);


    m_hooks.Register(Hook::Initialize,&Magnet::ben_testing_space);//call ben testing space

    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonReleased, Event_MouseButtonReleased));
    EventHandler::AddListener(new EventListener(sf::Event::MouseMoved, Event_MouseMove));
    EventHandler::AddListener(new EventListener(sf::Event::MouseButtonPressed, Event_MouseButtonPressed));
    EventHandler::AddListener(new EventListener(sf::Event::KeyPressed, Event_SpacePressed ));

    m_renderThread_ptr  =   &renderThread;
    m_loadThread_ptr    =   &loadThread;
    m_renderWindow      =   &window;

    m_renderWindow->SetFramerateLimit(30);

    m_mouseTrail.on = false;
    m_initialized   = false;
    m_load_started  = false;
    name = "test_cmp";
    test = NULL;

    CfgParse cfgparser("config.mcf");
    cfgparser.Parse(m_config);

    if(!cfgparser.IsParsed()){
        throw Exception(Exception::LoadFail, "Missing config", "The Magnet configuration file is missing");
    }
}

Magnet::~Magnet()
{
    //dtor
}

void Magnet::Hook_Initialize(){

}

void Magnet::Debug_CreateMenu(){
    std::cout << "Create menu\n";
    int r = rand() % 255 + 1;
    int g = rand() % 255 + 1;
    int b = rand() % 255 + 1;
    Object()->test = new mgui::Panel(name);
    Object()->test->SetColor(sf::Color(r, g, b)) ;
    Object()->test->SetVisible(true);
    Object()->test->DebugOn();
    Object()->test->Format();
    Object()->test->Create();
    Object()->m_menus.Register(Object()->test);

    /*mgui::Panel* panel = new mgui::Panel("button");
    panel->SetColor(sf::Color(100, 100, 100));
    panel->SetPosition(sf::Vector2f(100, 0));
    panel->SetOutlineWidth(1);
    panel->SetOutlineColor(sf::Color(0, 255, 255, 255));
    panel->EnableOutline(true);
    panel->DebugOn();
    panel->SetVisible(true);
    panel->Format();
    panel->Create();
    Object()->m_menus.Register(panel);*/

}

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
        if(Object()->test == NULL){
            std::cout << "Menu link exists:\t0\n";
        }else{
            bool linkExists = Renderer::Object()->LinkExists(Object()->test->GetRendererLink());
            std::cout << "Menu link exists:\t" << linkExists << std::endl;
        }
        std::cout << "Menu is registered:\t" << Object()->m_menus.ComponentExists(Object()->name) << std::endl;
    }else if(evt.Key.Code == sf::Key::R){
        try{
            //Resource::GetImage("images/guns/assault1.png");
            /*FileAction::directory_tree_t tree = FileAction::CreateDirectoryTree("resource/");
            std::cout << "Here\n";
            for(int i = 0; i < tree.size(); i++){
                FileAction::dir_node* dir = tree[i];
                if(dir->files.size() > 0){
                    std::cout << "Folder " << dir->name << " has " << dir->files.size() << " files ";
                }else{
                    std::cout << "Folder " << dir->name << " does not have files";
                }

                if(dir->children.size() > 0){
                    std::cout << " and has " << dir->children.size() << " sub folders\n";
                }else{
                    std::cout << " and has no sub folders\n";
                }
            }*/
        }

        catch(Exception e){
            e.output();
        }
        catch(...){
            std::cout << "[Magnet][KeyPress] Unhandled exception\n";
        }
        /*if(!Object()->once){
        Object()->spr->SetImage(Resource::GetImage("images/guns/assault1.png"));
        Renderer::CreateLink(Object()->spr);
        Object()->once = true;
        }*/
        //In setup hook
        //Magnet::Loader->Add(new Config("resource/config/test.mcf"));
        //data = Resource::GetConfig("test.mcf");
    }

    /*if(Object("Event_SpacePressed")->gameState.get() == State::Menu){
        Magnet::StartGame();
    }*/

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

void Magnet::Init(sf::RenderWindow& window, sf::Thread& renderThread, sf::Thread& loadThread) throw(Exception){
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

bool Magnet::Initialized(){
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

bool Magnet::LoadNeeded(){
    return !m_load_started;
}

Config* Magnet::GlobalConfig(){
    return &Object()->m_config;
}

void Magnet::State_Initialize(){
    if(!m_initialized){
        std::cout << "**********\tINITALIZE\t**********\n";
        std::cout << "[Magnet][Initialize] Initialize renderer...\n";
        Renderer::Init(*m_renderWindow, *Object()->m_renderThread_ptr);
        std::cout << "[Magnet][Initialize] Initialize resource...\n";
        Resource::Init(m_loadThread_ptr, "resource/");
        std::cout << "[Magnet][Initialize] Initialize WorldManager...\n";
        WorldManager::Init();

        m_initialized = true;


        Magnet::Hooks("Renderer::Render")->Call(Hook::Initialize);
    }else{
        if(LoadNeeded()){
            ChangeState(State::Setup);
        }else{
            ChangeState(State::Ready);
        }
    }
}

void Magnet::State_Setup(){
    std::cout << "**********\tSETUP\t**********\n";
    m_hooks.Call(Hook::Setup);

    ChangeState(State::Load);
}

void Magnet::State_Load(){
    if(!Resource::Loading() && Resource::Ready()){
        //m_load_started = false;
        Object()->ChangeState(State::Initialize); //Should return to previous state
    }else{
        if(!m_load_started){
            std::cout << "**********\tLOAD\t**********\n";
            m_hooks.Call(Hook::Load);

            m_load_started = true;
        }
    }
}

void Magnet::Think(){
    if(!Initialized()) return;

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
    }

    Hooks()->Call(Hook::Think);
}


void Magnet::ben_testing_space()
{
/*
    HttpReq demo(sf::Http::Request::Post,"http://bengreenier.com","/pages/magnet/network/query.php?name=magnet&desc=Program%20Made%20This&msg=so%20cool&score=100");
    if (demo.Execute())
    {
        std::cout<<"[Http] [Demo] Posted Successfully!\n";
    }else{ std::cout<<"[Http] [Demo] Failed.\n"; }
*/
/* //PULL TO CONSOLE EXAMPLE
    HttpReq demo(sf::Http::Request::Get,"http://bengreenier.com","/pages/magnet/network/output.php");
    if (demo.Execute())
    {
        std::cout<<"[Http] [Demo] Got Successfully!\n[Http] Response:\n"<<demo.GetResponse();
    }else{ std::cout<<"[Http] [Demo] Failed.\n"; }
*/
   // XmlParse ben("resource/config/AnimDemo.xml");
    //ben.Parse();
}
