#include "Resource.h"

Resource*   Resource::_resource_ptr =   NULL;

Resource::Resource(sf::Thread* loadThread, std::string resourceDir)
    :   m_load_state(State::Null)/*,
        m_image_handler(),
        m_font_handler(),
        m_soundbuffer_handler(),
        m_config_handler()*/

{
    m_debug = true;

    if(m_debug)
        std::cout << "\n[Resource] Initializing...\n\tSetting vars...\n";
    m_loadSize  =   0;
    m_loadLeft  =   0;
    m_loading   =   false;

    if(m_debug)
        std::cout << "\tInitializing directories...\n";

    m_rootdir = (Magnet::GlobalConfig()->KeyExists("resource", "root")) ? Magnet::GlobalConfig()->GetKeyValue("resource", "root") : "resource/";
    m_resource_tree = FileAction::CreateDirectoryTree(m_rootdir);

    for(int i = 0; i < m_resource_tree.size(); i++){
        FileAction::dir_node* dir = m_resource_tree[i];
        if(dir->parent != NULL){
            if(dir->parent->name+"/" == m_rootdir){
                m_search_directories.push_back(dir->full_path);
            }
        }
    }

    m_loadThread_ptr    =   loadThread;

    if(m_debug)
        std::cout << "\tSetting hooks...\n";

    Magnet::Hooks()->Register(Hook::StartLoad, &Resource::Hook_Load);

    if(m_debug)
        std::cout << "[Resource] Initialized.\n\n";
}

Resource::~Resource()
{
    delete [] _resource_ptr;
}

Resource* Resource::Object(){
    if(_resource_ptr == NULL){
        if(Object()->m_debug)
            std::cout << "Resource::Object()-> WARNING: Resource as not been initialized! Null pointer returned!\n";
    }
    return _resource_ptr;
}

void Resource::Init(sf::Thread* loadThread, std::string resourceDir){
    _resource_ptr   =   new Resource(loadThread, resourceDir);
}

const std::string& Resource::GetRootPath(){
    return Object()->m_rootdir;
}

std::string Resource::GetFullPath(std::string dir){
    std::cout << "[Resource][GetFullPath] Converting " << dir;
    if(SearchPathExists(dir)){
        if(dir.find(GetRootPath()) == std::string::npos){
            dir = GetRootPath() + dir;
        }

        if(dir.find("/", dir.length()-1)){
            dir = dir + "/";
        }
    }

    std::cout << " to " << dir << std::endl;

    return dir;
}

bool Resource::SearchPathExists(std::string path_name){
    if(CfgGlobals::DEBUG && CfgGlobals::VERBOSE)
        std::cout << "[Resource][SearchPathExists] Checking '" << path_name << "' ... ";
    if(GetRootPath() == path_name){

        if(CfgGlobals::DEBUG && CfgGlobals::VERBOSE)
            std::cout << "is root. Return true.\n";
        return true;
    }
    std::cout << "!!!\n";
    for(int i = 0; i < Object()->m_search_directories.size(); i++){
        if(Object()->m_search_directories[i] == path_name){
            if(CfgGlobals::DEBUG && CfgGlobals::VERBOSE)
                std::cout << "is search directory. Return true.\n";
            return true;
        }
    }


    if(CfgGlobals::DEBUG && CfgGlobals::VERBOSE)
        std::cout << "doesn't exist. Return false.\n";
    return false;
}

void Resource::AddFile(FileAction::file_node* filenode) throw(Exception){
    if(Resource::Loading()){
        throw(Exception(Exception::SyncError, "out of sync", "cannot add resources when a load is in progress"));
    }

    if(!FileAction::FindFile(filenode->path)){
        throw(Exception(Exception::MissingFile, "missing file", "file '" + filenode->path + "' doesn't exist"));
    }

    if(filenode->loaded){
        throw(Exception(Exception::SyncError, "out of sync", "file '" + filenode->path + "' is already loaded"));
    }

    if(Object()->m_load_state.get() == State::Ready){
        Object()->m_load_state.set(State::Null);
    }

    Object()->m_load_queue.push(filenode);
    Object()->m_loadSize = Object()->m_load_queue.size();
    Object()->m_loadLeft = Object()->m_load_queue.size();

    if(Magnet::GlobalConfig()->GetKeyObject("resource", "debug")->GetBool())
        std::cout << "[Resource] Added \"" << filenode->path << "\"\n";
}

FileAction::file_node* Resource::GetFileNode(std::string file_path){
    for(int i = 0; i < Object()->m_resource_tree.size(); i++){
        if(!Object()->m_resource_tree[i]->files.empty()){
            for(int j = 0; j < Object()->m_resource_tree[i]->files.size(); j++){
                if(Object()->m_resource_tree[i]->files[j]->path == file_path){
                    return Object()->m_resource_tree[i]->files[j];
                }
            }
        }
    }

    return NULL;
}

void Resource::AddFile(std::string file_path) throw(Exception){
    Resource::PrependRootPath(file_path);
    FileAction::file_node* fnode = GetFileNode(file_path);

    if(!fnode){
        throw(Exception(Exception::MissingFile, "missing file", "file '" + file_path + "' doesn't exist in the node tree"));
    }

    AddFile(fnode);
}

void Resource::AddDir(std::string dir, bool recursive) throw(Exception){
    Resource::PrependRootPath(dir);

    if(Magnet::GlobalConfig()->GetKeyObject("resource", "debug")->GetBool()){
        std::cout << "[Resource][AddDir] Adding " << dir;
        if(recursive){
            std::cout << " recursively\n";
        }else{
            std::cout << std::endl;
        }
    }

    if(Resource::Object()->FindInSearchDirectory(dir) || dir == GetRootPath()){
        if(dir == GetRootPath() && recursive){
            throw Exception(Exception::Recursive, "recursive attempt", "cannot add root dir recursivley");
        }

        for(int i = 0; i < Object()->m_resource_tree.size(); i++){
            if(Object()->m_resource_tree[i]->full_path == dir){
                if(!Object()->m_resource_tree[i]->files.empty()){
                    for(int j = 0; j < Object()->m_resource_tree[i]->files.size(); j ++){
                        if(Magnet::GlobalConfig()->GetKeyObject("resource", "debug")->GetBool())
                            std::cout << "[Resource][AddDir] Found file '" << Object()->m_resource_tree[i]->files[j]->file << "' path '" << Object()->m_resource_tree[i]->files[j]->path << "'" << std::endl;

                        Resource::AddFile(Object()->m_resource_tree[i]->files[j]);
                    }
                }

                if(recursive && !Object()->m_resource_tree[i]->children.empty()){
                    for(int j = 0; j < Object()->m_resource_tree[i]->children.size(); j ++){
                        if(Magnet::GlobalConfig()->GetKeyObject("resource", "debug")->GetBool())
                            std::cout << "Resource][AddDir] Found folder '" << Object()->m_resource_tree[i]->children[j]->name << "' path '" << Object()->m_resource_tree[i]->children[j]->full_path << "'" << std::endl;

                        Resource::AddDir(Object()->m_resource_tree[i]->children[j]->full_path, true);
                    }
                }
            }
        }
    }else{
        throw Exception(Exception::MissingDir, "missing directory", "directory '" + dir + "' doesn't exist within search paths");
    }

}


bool Resource::FindInSearchDirectory(std::string dir){
    Resource::PrependRootPath(dir);
    if(FileAction::Find(dir)) return true;
    for(int i = 0; i < m_search_directories.size(); i++){
        if(FileAction::Find(GetFullPath(m_search_directories[i]) + dir)){
            return true;
        }
    }

    return false;
}

bool Resource::NeedLoad(){
    if(Object()->m_load_state.get() == State::Null && Object()->m_loadSize > 0){
        return true;
    }

    return false;

}

void Resource::Hook_Load(){
    if(Resource::NeedLoad()){
        Object()->m_load_state.set(State::Load);

        if(Object()->m_debug)
            std::cout << "[Resource][Load] Loading...\n";
        Object()->m_loadThread_ptr->Launch();
    }else{
        Object()->m_load_state.set(State::Ready);
    }
}

void Resource::Load(){
    //Process load queue
    while(!Object()->m_load_queue.empty()){
        FileAction::file_node* filenode = Object()->m_load_queue.front();

        if(!filenode->loaded){
            if(FileAction::GetFileType(filenode->type) != FileAction::Invalid){
                switch(FileAction::GetFileType(filenode->type)){
                    case FileAction::Image:
                        Object()->m_image_handler.Load(filenode);
                        break;
                    case FileAction::Font:
                        Object()->m_font_handler.Load(filenode);
                        break;
                    case FileAction::Config:
                        //Object()->m_config_handler.Load(filenode);
                        break;
                    case FileAction::Sound:
                        Object()->m_soundbuffer_handler.Load(filenode);
                        break;
                }
            }else{
                if(Magnet::GlobalConfig()->GetKeyObject("resource", "debug")->GetBool())
                    std::cout << "[Resource][Load] Could not load '" << filenode->path << "', file type " << filenode->type << "' is not supported\n";
            }
        }

        Object()->m_load_queue.pop();
        Object()->m_loadLeft = Object()->m_load_queue.size();

        std::cout << "[Resource][Load]\t" << LoadProgress() << "%\n ";
    }

    if(Magnet::GlobalConfig()->GetKeyObject("resource", "debug")->GetBool())
        std::cout << "[Resource][Load] Done loading\n";

    Object()->m_load_state.set(State::Ready);
}

void Resource::PrependRootPath(std::string& str){
    if(str.find(GetRootPath()) == std::string::npos){
        str = GetRootPath() + str;
    }
}

const sf::Image& Resource::GetImage(std::string file) throw(Exception){
    if(file.find(GetRootPath()) == std::string::npos){
        file = GetRootPath() + file;
    }

    FileAction::file_node* fnode = GetFileNode(file);
    sf::Image* img;
    bool user_error = false;
    if(fnode != 0){
        try{
            img = Object()->m_image_handler.Get(file);
        }

        catch(Exception e){
            user_error = true;
            e.output();
        }
    }else{
        if(Magnet::GlobalConfig()->GetKeyObject("resource", "debug")->GetBool())
            std::cout << "[Resource][GetImage] Image " << file << " doesn't exist\n";

        user_error = true;
    }

    if(user_error){
        img = new sf::Image();
        img->Create(32, 32, sf::Color(255, 0, 0, 60));
    }

    return *img;
}

const sf::Font& Resource::GetFont(std::string file){
    if(file.find(GetRootPath()) == std::string::npos){
        file = GetRootPath() + file;
    }

    std::cout << file << std::endl;

    FileAction::file_node* fnode = GetFileNode(file);
    const sf::Font* font;
    bool user_error = false;
    if(Resource::GetFileNode(file)){
        try{
            font = Object()->m_font_handler.Get(file);
        }

        catch(Exception e){
            user_error = true;
            e.output();
        }
    }else{
        if(Magnet::GlobalConfig()->GetKeyObject("resource", "debug")->GetBool())
            std::cout << "[Resource][GetImage] Font " << file << " node doesn't exist\n";

        user_error = true;
    }

    if(user_error){
        if(Magnet::GlobalConfig()->GetKeyObject("resource", "debug")->GetBool())
            std::cout << "[Resource][GetImage] Font " << file << " doesn't exist, using default\n";
        font = &sf::Font::GetDefaultFont();
    }

    return *font;
}
