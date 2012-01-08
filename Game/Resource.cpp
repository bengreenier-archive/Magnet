#include "Resource.h"

Resource::Handle*   Resource::Handle::_resource_ptr =   NULL;

Resource::Handle::Handle(sf::Thread* loadThread, std::string resourceDir)
    :   ResourceDir(resourceDir),
        ConfigDir(ResourceDir+"config/"),
        ImageDir(ResourceDir+"image/"),
        FontDir(ResourceDir+"font/")
{
    std::cout << "\n***********INITIALIZE RESOURCE HANDLER***********\n";
    std::cout << "Setting vars...\n";
    m_loadSize  =   0;
    m_loadLeft  =   0;
    m_loading   =   false;
    std::cout << "Initializing directories...\n";
    if(!FileAction::FindDir(ResourceDir)){
        FileAction::MakeDir(ResourceDir);

        std::cout << "  Created\t" << ResourceDir << "\n";
    }

    if(!FileAction::FindDir(ConfigDir)){
        FileAction::MakeDir(ConfigDir);

        std::cout << "  Created\t" << ConfigDir << "\n";
    }

    if(!FileAction::FindDir(ImageDir)){
        FileAction::MakeDir(ImageDir);

        std::cout << "  Created\t" << ImageDir << "\n";
    }

    if(!FileAction::FindDir(FontDir)){
        FileAction::MakeDir(FontDir);

        std::cout << "  Created\t" << FontDir << "\n";
    }

    m_loadThread_ptr    =   loadThread;

    std::cout << "Setting hooks...\n";
    Magnet::Hooks("Resource::Constructor")->Register(Hook::Load, &Resource::Handle::Hook_Load);


    std::cout << "*************************************************\n\n";
}

Resource::Handle::~Handle()
{
    delete [] _resource_ptr;
}

Resource::Handle* Resource::Handle::Object(){
    if(_resource_ptr == NULL){
        std::cout << "Resource::Object()-> WARNING: Resource as not been initialized! Null pointer returned!\n";
    }
    return _resource_ptr;
}

void Resource::Handle::Init(sf::Thread* loadThread, std::string resourceDir){
    _resource_ptr   =   new Handle(loadThread, resourceDir);
}

void Resource::Handle::Add(std::string file){
    if(Object()->m_loading) return;

    Object()->m_load_queue.push(file);
    Object()->m_loadSize = Object()->m_load_queue.size();
    Object()->m_loadLeft = Object()->m_load_queue.size();

    std::cout << "Resource \"" << file << "\" has been added, validity still not checked\n";
}

void Resource::Handle::Hook_Load(){
    if(Object()->m_load_queue.empty()) return;


    Object()->m_loading =   true;
    Object()->m_loadThread_ptr->Launch();
}

void Resource::Handle::Load(void* data){
    //Process load queue
    while(!Object()->m_load_queue.empty()){
        std::string file = Object()->m_load_queue.front();

        Pointer resource(file);

        if(resource.isValid()){
            Object()->m_resource_vect.insert(std::pair<std::string, Pointer>(resource.file(), resource));
        }

        Object()->m_load_queue.pop();

        Object()->m_loadLeft = Object()->m_load_queue.size();
    }

    Object()->m_loading =   false;
}
