#ifndef RESOURCE_H
#define RESOURCE_H

#include "../Magnet.h"
#include <string>
#include <queue>
#include <map>
#include <iterator>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <SFML/Audio.hpp>

#include "../FileActions/Cfg/CfgInclude.h"
#include "../FileActions/FileAction.h"


#include "Exception.h"


template<class T>
class ResourceHandler{
    public:
        virtual ~ResourceHandler()
        {
            for(int i = 0; i < m_resource_map.size(); i++){
                //delete &m_resource_map[i].second;
            }
            m_resource_map.clear();
        }

        bool Load(FileAction::file_node* fnode){
            T* new_resource = new T();

            //if(dynamic_cast<Config*>(new_resource) == 0){ //Specialization if new_resource is config, see else
                if(new_resource->LoadFromFile(fnode->path)){
                    m_resource_map.insert(resource_pair_type(fnode->path, new_resource));
                    fnode->loaded = true;
                }else{
                    fnode->loaded = false;
                }
            /*}else{
                CfgParse parser(fnode->path);
                parser.Parse(*new_resource);
                if(parser.IsParsed()){
                    fnode->loaded = true;
                }else{
                    fnode->loaded = false;
                }
            }*/

            return fnode->loaded;
        }

        T* Get(FileAction::file_node* fnode) throw(Exception){
            return Get(fnode->path);
        }

        T* Get(std::string file) throw(Exception){
            if(m_resource_map.count(file) == 0){
                throw (Exception(Exception::NullPointer, "null pointer", "resource '" + file + "' does not exist"));
            }

            return m_resource_map.find(file)->second;
        }
    private:
        typedef std::map<std::string, T*>            resource_map_type;
        //typedef std::map<std::string, T*>::iterator  resource_map_it_type;
        typedef std::pair<std::string, T*>           resource_pair_type;
        resource_map_type m_resource_map;
};

////////////////////////////////
/// Static class to handle
/// Resources
////////////////////////////////
class Resource
{
    public:
        virtual ~Resource();

        ////////////////////////////////
        /// Get the Resource object
        ////////////////////////////////
        static Resource* Object();

        ////////////////////////////////
        /// Initialize the resource object
        ////////////////////////////////
        static void Init(sf::Thread* loadThread, std::string resourceDir);

        ////////////////////////////////
        /// Add a resource of any type
        /// The resource will be loaded
        /// on the next Load hook
        ////////////////////////////////
        static void AddFile(std::string file) throw(Exception);
        static void AddFile(FileAction::file_node* filenode) throw(Exception);

        ////////////////////////////////
        /// Add a directory
        ////////////////////////////////
        static void AddDir(std::string dir, bool recursive = false) throw(Exception);

        ////////////////////////////////
        /// Check if a directory exists
        /// in search paths or if the dir
        /// is a search directory
        ////////////////////////////////
        bool FindInSearchDirectory(std::string dir);

        ////////////////////////////////
        /// Get the root path
        ////////////////////////////////
        static const std::string& GetRootPath();
        ////////////////////////////////
        /// Get the full path of a
        /// search directory.
        ///
        ///dir = image
        ///if image is a search directory
        ///this function will return
        ///[root]/image/
        ////////////////////////////////
        static std::string GetFullPath(std::string dir);
        static std::string GetSearchPath(std::string path_name);
        //Returns true if the
        static bool SearchPathExists(std::string path_name);

        ////////////////////////////////
        /// Gets the full path of a dir
        /// based on Resource search
        /// directories
        ////////////////////////////////
        static std::string GetRealPath(std::string dir);

        ////////////////////////////////
        /// Load queue resources
        ////////////////////////////////
        static void Hook_Load();

        ////////////////////////////////
        /// Return true when the
        /// resources are loading
        ////////////////////////////////
        static bool Loading(){
          if(Object()->m_load_state.get() == State::Load){
            return true;
          }

          return false;
        };

        static FileAction::file_node* GetFileNode(std::string file_path);

        ////////////////////////////////
        /// Return true when the
        /// resources have been
        /// loaded and the queue is
        /// empty
        ////////////////////////////////
        static bool Ready(){
          if(Object()->m_load_state.get() == State::Ready){
            return true;
          }

          return false;
        };

        ////////////////////////////////
        /// Returns true when resources
        /// are queued but have not yet
        /// been loaded.
        ////////////////////////////////
        static bool NeedLoad();

        ////////////////////////////////
        /// Return m_loadPercent
        ////////////////////////////////
        static int LoadProgress(){
            if(Object()->m_loadSize == 0) return 100;

            float m_loadLeft = Object()->m_loadLeft;
            float m_loadSize = Object()->m_loadSize;

            return (((m_loadSize-m_loadLeft)/m_loadSize)*100);
        }
        static void Load();

        ////////////////////////////////
        /// Get an image
        ////////////////////////////////
        static const sf::Image& GetImage(std::string file) throw(Exception);
        ////////////////////////////////
        /// Get a font
        ////////////////////////////////
        static const sf::Font& GetFont(std::string file);

        static void PrependRootPath(std::string& str);
    protected:
        Resource(sf::Thread* loadThread, std::string resourceDir);
    private:
        static Resource* _resource_ptr;
        sf::Thread*     m_loadThread_ptr;

        typedef std::queue<FileAction::file_node*>                              load_queue_t;
        typedef ResourceHandler<sf::Image>          image_handler_type;
        typedef ResourceHandler<sf::Font>           font_handler_type;
        typedef ResourceHandler<sf::SoundBuffer>    soundbuffer_handler_type;
        typedef ResourceHandler<Config>             config_handler_type;

        //Define handlers
        image_handler_type          m_image_handler;
        font_handler_type           m_font_handler;
        soundbuffer_handler_type    m_soundbuffer_handler;
        config_handler_type         m_config_handler;

        load_queue_t    m_load_queue;
        State           m_load_state;
        int             m_loadSize;         //load total
        int             m_loadLeft;         //current queue size
        bool            m_loading;          //True when loading is in process
        bool            m_debug;
        std::vector<std::string>  m_search_directories;
        std::string     m_rootdir;
        FileAction::directory_tree_t m_resource_tree;

        Config m_config;



};



#endif // RESOURCE_H
