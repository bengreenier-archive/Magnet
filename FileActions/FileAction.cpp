#include "FileAction.h"

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

bool FileAction::IfExists(std::string Filename)
{
    std::ifstream infile(Filename.c_str());
    if (infile.is_open()){return true;}else{return false;}
}
