#ifndef RESOURCE_H
#define RESOURCE_H

#include "../Magnet.h"
#include <string>
#include <queue>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "Handlers/ImageHandler.h"

#include "Exception.h"
#include "Resource/ResourcePointer.h"

////////////////////////////////
/// Static class to handle
/// Resources
////////////////////////////////
class Resource
{
    public:
        const std::string ResourceDir;
        const std::string ConfigDir;
        const std::string ImageDir;
        const std::string FontDir;
        const std::string ErrorImage;

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

        ////////////////////////////////
        /// Add a directory
        ////////////////////////////////
        static void AddDir(std::string dir, bool recursive = false) throw(Exception);

        ////////////////////////////////
        /// Add a directory recursively
        ////////////////////////////////
        static void AddDirRecursive(std::string dir, bool recursive) throw(Exception);

        ////////////////////////////////
        /// Check if a directory exists
        /// in search paths
        ////////////////////////////////
        static bool FindDir(std::string dir);

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
          if(Object()->m_load_state.get() == State::Loading){
            return true;
          }

          return false;
        };

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
        static void Load(void* data);

        ////////////////////////////////
        /// Get an image
        ////////////////////////////////
        static sf::Image& GetImage(std::string file);
        ////////////////////////////////
        /// Get a font
        ////////////////////////////////
        static sf::Font& GetFont(std::string file);
    protected:
        Resource(sf::Thread* loadThread, std::string resourceDir);
    private:
        static Resource* _resource_ptr;
        sf::Thread*     m_loadThread_ptr;

        typedef std::queue<std::string>                              load_queue_t;
        typedef std::map<std::string, ResourcePointer*>              resource_vect_t;
        typedef std::map<std::string, ResourcePointer*>::iterator    resource_vect_it_t;

        resource_vect_t m_resource_vect;
        load_queue_t    m_load_queue;
        State           m_load_state;
        int             m_loadSize;         //load total
        int             m_loadLeft;         //current queue size
        bool            m_loading;          //True when loading is in process
        bool            m_debug;



};

#endif // RESOURCE_H
