#ifndef RESOURCE_H
#define RESOURCE_H

#include "../Magnet.h"
#include <string>
#include <queue>

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
        const std::string ResourceDir;//           =   "resource/";
        const std::string ConfigDir;//     =   Dir + "config/";
        const std::string ImageDir;//     =   Dir + "image/"
        const std::string FontDir;//       =   Dir + "font/";
        const std::string ErrorImage;//       =   Dir + "font/";

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
        static void Add(std::string file);

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

            return ((m_loadLeft/m_loadSize)*100);
        }
        static void Load(void* data);

        ////////////////////////////////
        /// Get an image
        ////////////////////////////////
        static sf::Image& GetImage(std::string file);
    protected:
        Resource(sf::Thread* loadThread, std::string resourceDir);
    private:
        static Resource* _resource_ptr;
        sf::Thread*     m_loadThread_ptr;

        typedef std::queue<std::string>           load_queue_t;
        typedef std::map<std::string, ResourcePointer*>    resource_vect_t;

        resource_vect_t m_resource_vect;
        load_queue_t    m_load_queue;
        State           m_load_state;
        int             m_loadSize;         //load total
        int             m_loadLeft;         //current queue size
        bool            m_loading;          //True when loading is in process
        bool            m_debug;



};

#endif // RESOURCE_H
