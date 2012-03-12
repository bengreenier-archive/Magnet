#include "FileAction.h"

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../Magnet.h"

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

bool FileAction::FindFile(std::string file_path){
    std::ifstream file(file_path.c_str());

    bool success = false;

    if(file.is_open()){
        success = true;
    }

    file.close();
    return success;
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

bool FileAction::Find(std::string path){
    if(FindFile(path)){
        return true;
    }

    if(FindDir(path)){
        return true;
    }

    return false;
}

void FileAction::MakeDir(std::string dir){
    mkdir(dir.c_str()); //I'm so schetched about this... platform safe?
}


FileAction::directory_tree_t FileAction::CreateDirectoryTree(std::string path)  throw(Exception){
    std::cout << "[FileAction][CreateDirectoryTree] Creating directory tree from '" << path << "'\n";
    FileAction::directory_tree_t tree;

    tree.push_back(new dir_node(path));
    std::cout << "[FileAction][CreateDirectoryTree] Created root node with path '" << tree.back()->full_path << "'\n";
    GrowDirectoryTree(tree);
    return tree;
}

FileAction::FileType FileAction::GetFileType(std::string file_type)throw(Exception){
    if(!Magnet::IsInitialized()){
        throw Exception(Exception::SyncError, "out of sync", "magnet is not initialzied, config could not be accessed");
    }


    Config::config_vect_type supported_files = Magnet::GlobalConfig()->GetCategory("supported_file_types");
    std::string name;
    std::string value;

    for(int i = 0; i < supported_files.size(); i++){
        name = supported_files[i]->GetName();
        value = supported_files[i]->GetString();

        if(name == "image"){
            if(value.find(file_type) != std::string::npos){
                return ImageFile;
            }
        }else if(name == "config"){
            if(value.find(file_type) != std::string::npos){
                return ConfigFile;
            }
        }else if(name == "font"){
            if(value.find(file_type) != std::string::npos){
                return FontFile;
            }
        }else if(name == "sound"){
            if(value.find(file_type) != std::string::npos){
                return SoundFile;
            }
        }
    }

    return InvalidFile;

}

void FileAction::GrowDirectoryTree(directory_tree_t& tree, dir_node* cur_node) throw(Exception){
    if(cur_node == NULL){
        cur_node = tree.back();
    }

    std::string current_path = cur_node->full_path;
    std::cout << "[FileAction][GrowDirectoryTree] Growing '" <<current_path<< "'\n";

    //Prepare for failure...
    std::string error = "\0";
    if(FindDir(current_path)){
        DIR *dp;
        struct dirent *dirp;
        struct stat filestat;
        std::string next_path = "";


        dp = opendir( current_path.c_str() );
        if (dp == NULL) { error = "[FileAction][GrowDirectoryTree] Could not open \"" + current_path + "\""; }

        while ((dirp = readdir( dp ))){
            if(*dirp->d_name != '.'){
                next_path = current_path + dirp->d_name;// + "/";
                if (stat( next_path.c_str(), &filestat )) continue;
                if (S_ISDIR( filestat.st_mode )){
                    dir_node* new_dir = new dir_node(std::string(dirp->d_name), false, cur_node);
                    cur_node->children.push_back(new_dir);
                    tree.push_back(new_dir);
                    GrowDirectoryTree(tree, new_dir);
                }else{
                    file_node* new_file = new file_node(next_path, dirp->d_name);
                    cur_node->files.push_back(new_file);
                }
            }
            /*filepath = dirp->d_name;
           // file = dirp->d_name;
            // If the file is a directory (or is in some way invalid) skip it
            if (stat( filepath.c_str(), &filestat )) continue;
            if (S_ISDIR( filestat.st_mode )){
                //Is a directory
                std::cout << "***Directory***\n";
                std::cout << "filepath: " << filepath << std::endl;
            }else{
                //Not a directory
                std::cout << "***Not a directory***\n";
                std::cout << "filepath: " << filepath << std::endl;
            }*/
        }

        closedir( dp );
    }else{
        throw Exception(Exception::MissingDir, "missing directory", "could not find \"" + current_path + "\" within search directories"); //this ends execution
    }
}

void FileAction::ExplodeString(std::string base, std::string delim, std::vector<std::string>& str_store){
    size_t pos = base.find(delim);

    if(pos == std::string::npos){
        if(base != ""){
            str_store.push_back(base);
        }
        return;
    }else{
        str_store.push_back(base.substr(0, pos));
        ExplodeString(base.substr(pos+1, base.length()), delim, str_store);
    }
}
