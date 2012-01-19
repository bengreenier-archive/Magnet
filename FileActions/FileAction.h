#ifndef FILEACTION_H
#define FILEACTION_H

#include <iostream>
#include <string>
#include <fstream>

class FileAction //! Allows program access to files.
{
    public:
        FileAction();
        ~FileAction();
        static void WriteTo(std::string Filename,std::string Msg);
        static std::string ReadFrom(std::string Filename);
        static bool FindFile(std::string Filename);
        static bool FindDir(std::string dir);
        static void MakeDir(std::string dir);
    protected:
    private:
};

#endif // FILEACTION_H
