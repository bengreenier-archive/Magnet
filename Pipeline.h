#ifndef PIPELINE_H
#define PIPELINE_H

#include <sstream>
#include <iostream>
#include <fstream>

#include "Console.h"

class Pipeline
{
    public:
        //these allow endl/etc
        typedef std::ostream& (*ostreamfunc)(std::ostream& os);
        typedef std::ios_base& (*iosbasefunc)(std::ios_base& str);

        enum Scope{LOG,DEBUGLOG,SCREEN,CONSOLE};
        Pipeline();

        static Pipeline* Instance();

        static void SetScope(std::ostream& cstream);
        static void SetScope(Pipeline::Scope scope);
        static void SetFileMode(std::_Ios_Openmode omode);

        //!! All out/<< parameter names should probably be a.

        static void out(std::string a);
        static void out(char* a);
        static void out(int a);
        static void out(char a);
        static void out(float a);
        static void out(double a);
        static void out(std::ostream& os);
        static void out(ostreamfunc fn);
        static void out(iosbasefunc fn);

        //this is the key part. add more of these to output more things
        Pipeline& operator<<(ostreamfunc fn);
        Pipeline& operator<<(std::ostream& os);
        Pipeline& operator<<(std::string a);
        Pipeline& operator<<(char* a);
        Pipeline& operator<<(int a);
        Pipeline& operator<<(char a);
        Pipeline& operator<<(float a);
        Pipeline& operator<<(double a);
        Pipeline& operator<<(iosbasefunc fn);
        #define pipe *Pipeline::Instance()
        //the above chunk is the work
    protected:
    private:

        enum Type{FILE,COUT,INGAME};
        static Pipeline* m_ptr;
        std::ostream* m_curStream;
        std::ofstream* m_file;
        std::string m_file_name;
        Pipeline::Type m_curType;
        std::_Ios_Openmode m_ios_flag;
};



#endif // PIPELINE_H
