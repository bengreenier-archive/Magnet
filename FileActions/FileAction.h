#ifndef FILEACTION_H
#define FILEACTION_H

#include <iostream>
#include <string>
#include <fstream>

class FileAction
{
    public:
        FileAction();
        ~FileAction();
        static void WriteTo(std::string Filename,std::string Msg);
        static std::string ReadFrom(std::string Filename);
        static bool IfExists(std::string Filename);
    protected:
    private:
};

#endif // FILEACTION_H
