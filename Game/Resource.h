#ifndef RESOURCE_H
#define RESOURCE_H

#include "../Magnet.h"
#include <string>
#include <queue>

#include "Handlers/ImageHandler.h"

#include "BaseException.h"
#include "Resource/ResourcePointer.h"

class ResourceException : public BaseException
{
    public:
    ResourceException(Type what, std::string why) : BaseException(what, why){}
    virtual void what(){
        std::cout << "Exception \"";
        switch(m_what){
            case LoadFail:
                std::cout << "LoadFail\": Resource could not be loaded.";
            default:
                std::cout << "UNKOWN EXCEPTION";
        }
    }

    virtual void why(){
        std::cout << "Reason: " << m_why;
    }
};
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
        /// Return m_loading
        ////////////////////////////////
        static bool IsLoading(){return Object()->m_loading; };

        ////////////////////////////////
        /// Return m_loadPercent
        ////////////////////////////////
        static int LoadProgress(){
            float m_loadLeft = Object()->m_loadLeft;
            float m_loadSize = Object()->m_loadSize;

            return ((m_loadLeft/m_loadSize)*100);
        }


        static void Load(void* data);
    protected:
        Resource(sf::Thread* loadThread, std::string resourceDir);
    private:
        static Resource* _resource_ptr;
        sf::Thread*     m_loadThread_ptr;

        typedef std::queue<std::string>           load_queue_t;
        typedef std::map<std::string, ResourcePointer>    resource_vect_t;

        resource_vect_t m_resource_vect;
        load_queue_t    m_load_queue;
        int             m_loadSize;         //load total
        int             m_loadLeft;         //current queue size
        bool            m_loading;          //True when loading is in process
        bool            m_debug;



};

#endif // RESOURCE_H
