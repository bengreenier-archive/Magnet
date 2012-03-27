#include "Pipeline.h"

Pipeline* Pipeline::m_ptr = NULL;

Pipeline::Pipeline()
{
    m_curStream = &std::cout;
    m_curType = Pipeline::COUT;
    m_ios_flag = std::ios::app;
}

Pipeline* Pipeline::Instance()
{
    if (!m_ptr)
    m_ptr = new Pipeline();

    return m_ptr;
}

void Pipeline::out(iosbasefunc fn)
{
        if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<fn;
        else
        *Console::Stream()<<fn;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<fn;

//    return *Instance();
}

void Pipeline::out(ostreamfunc fn)
{
        if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<fn;
        else
        *Console::Stream()<<fn;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<fn;

//    return *Instance();
}

void Pipeline::out(std::ostream& os)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<os;
        else
        *Console::Stream()<<os;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<os;

//    return *Instance();

}

void Pipeline::out(std::string a)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

//    return *Instance();

}

void Pipeline::out(char* a)
{
    std::string t=a;
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<t;
        else
        *Console::Stream()<<t;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<t;

//    return *Instance();
}

void Pipeline::out(int a)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

//    return *Instance();
}

void Pipeline::out(char a)
{

    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

//    return *Instance();
}

void Pipeline::out(float a)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

//    return *Instance();
}

void Pipeline::out(double a)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

//    return *Instance();
}

Pipeline& Pipeline::operator<<(std::ostream& os)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<os;
        else
        *Console::Stream()<<os;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<os;

    return *Instance();
}

Pipeline& Pipeline::operator<<(std::string a)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

    return *Instance();
}

Pipeline& Pipeline::operator<<(char* a)
{
    std::string t=a;
     if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

    return *Instance();
}

Pipeline& Pipeline::operator<<(int a)
{
     if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

    return *Instance();
}

Pipeline& Pipeline::operator<<(char a)
{
       if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

    return *Instance();
}

Pipeline& Pipeline::operator<<(float a)
{
      if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

    return *Instance();
}

Pipeline& Pipeline::operator<<(double a)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<a;
        else
        *Console::Stream()<<a;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<a;

    return *Instance();
}

Pipeline& Pipeline::operator<<(ostreamfunc fn)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<fn;
        else
        *Console::Stream()<<fn;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<fn;

    return *Instance();
}

Pipeline& Pipeline::operator<<(iosbasefunc fn)
{
    if (Instance()->m_curType == Pipeline::FILE)
    {
        Instance()->m_file->open(Instance()->m_file_name.c_str(),Instance()->m_ios_flag);

        if (Instance()->m_file->good())
        *Instance()->m_curStream<<fn;
        else
        *Console::Stream()<<fn;


        Instance()->m_file->close();

    }
    else
    *Instance()->m_curStream<<fn;

    return *Instance();
}

void Pipeline::SetScope(std::ostream& cstream)
{
    Instance()->m_curStream = &cstream;
}

void Pipeline::SetScope(Pipeline::Scope scope)
{
    if (scope == Pipeline::SCREEN)
    {
        Instance()->m_curStream = &std::cout;
        Instance()->m_curType = Pipeline::COUT;
    }
    else if (scope == Pipeline::DEBUGLOG)
    {
        Instance()->m_file = new std::ofstream;
        Instance()->m_file_name = "debug.log";
        Instance()->m_curStream = Instance()->m_file;
        Instance()->m_curType = Pipeline::FILE;
    }
    else if (scope == Pipeline::LOG)
    {
        Instance()->m_file = new std::ofstream;
        Instance()->m_file_name = "log.log";
        Instance()->m_curStream = Instance()->m_file;
        Instance()->m_curType = Pipeline::FILE;
    }
    else if (scope == Pipeline::CONSOLE)
    {
        Instance()->m_curStream = Console::Stream();
        Instance()->m_curType = Pipeline::INGAME;
    }

}

void Pipeline::SetFileMode(std::_Ios_Openmode omode)
{
    Instance()->m_ios_flag = omode;
}
