#include "FileAction.h"
#include <dirent.h>

FileAction::FileAction()
{
    //ctor
}

FileAction::~FileAction()
{
    //dtor
}

void FileAction::WriteTo(std::string Filename,std::string Msg)
{
    std::ofstream outfile(Filename.c_str());
    outfile <<Msg.c_str();
    outfile.close();

}

std::string FileAction::ReadFrom(std::string Filename)
{
    std::string result="";
    std::string line;
    std::ifstream infile(Filename.c_str());
    if (infile.is_open())
  {
    while ( infile.good() )
    {
      getline (infile,line);
      result+=line;
    }
    infile.close();
  }
    return result;
}

bool FileAction::FindFile(std::string Filename)
{
    std::ifstream infile(Filename.c_str());
    if (infile.is_open()){return true;}else{return false;}
}
bool FileAction::FindDir(std::string dir)
{
    DIR *pDir;
    bool bExists = false;

    pDir = opendir (dir.c_str());

    if (pDir != NULL)
    {
        bExists = true;
        (void) closedir (pDir);
    }

    return bExists;
}

void FileAction::MakeDir(std::string dir){
    mkdir(dir.c_str()); //I'm so schetched about this... platform safe?
}
