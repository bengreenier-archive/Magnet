#include "Cache.h"
#include "FileAction.h"
#include "../Pipeline.h"
#include "../Magnet.h"

using namespace util;

Cache::Cache(const std::string& name)
:   Service(name + "_cache"),
    m_file(new char[name.size() + 4])
{
    std::string file = name + ".bin";
    strcpy(m_file, name.c_str());

    //Create the file if it doens't exist.
    if( !FindFile(m_file) )
    {
        openStream(std::ios::out);
        closeStream();
    }

    if( !FindFile(m_file) )
    {
        throw(Exception("file io", "file '" + file + "' could not be written"));
    }

    m_stream.clear();
}

Cache::~Cache()
{
    delete [] m_file;
}

bool Cache::openStream(std::_Ios_Openmode flags)
{
    m_mutex.lock();
    m_stream.open(m_file, flags | std::ios::binary);

    if(m_stream.good())
    {
        return true;
    }else{
        m_mutex.unlock();

        if(m_stream.eof()){
            std::cout << "[Cache] '" << m_file << "' is empty.\n";
            debuglog << m_file;
        }

        if(m_stream.fail()){
            std::cout << "[Cache] '" << m_file << "' failbit is set.\n";
        }

        if(m_stream.bad()){
            std::cout << "[Cache] '" << m_file << "' badbit is set.\n";
        }

        m_stream.close();
        return false;
    }
}

bool Cache::closeStream()
{
    m_stream.close();
    m_mutex.unlock();
}

void Cache::onInitialize()
{
    dbgconsole << "Cache initialize\n";
    //mENGINE_REGISTER_IHOOK("close_" + name(), Hook::onClose, &Cache::onClose, this);
}

void Cache::onClose()
{
    //Write changes
}
