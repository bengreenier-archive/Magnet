#ifndef FILEACTION_H
#define FILEACTION_H

#include <iostream>
#include <string>
#include <fstream>

#include <vector>

#include "../Game/Exception.h"

class FileAction //! Allows program access to files.
{
    public:
        enum FileType{
            Invalid,
            Image,
            Sound,
            Font,
            Config
        };

        struct file_node{
            std::string path;       //Full path:    dir1/dir2/file.type
            std::string file;       //Filename:     file.type
            bool loaded;
            std::string type;

            file_node(std::string _path, std::string _file, bool _loaded=false) :
                path(_path),
                file(_file),
                loaded(_loaded)
            {
                type = file.substr(file.find("."), file.length()-1);
            }
        };

        struct dir_node{
            dir_node(std::string _name, bool _isRoot=true, dir_node* _parent=NULL) :
                name(_name),
                isRoot(_isRoot),
                parent(_parent),
                children(),
                files()
            {
                    if(parent == NULL){
                        full_path = (name.find("/") == std::string::npos) ? (name + "/") : name;
                    }else{
                        full_path = parent->full_path + ((name.find("/") == std::string::npos) ? (name + "/") : name);
                    }
            }

            dir_node* parent;  //branch or leaf
            bool isRoot;  //branch or leaf
            std::string name;
            std::string full_path;

            std::vector<dir_node*>     children;
            std::vector<file_node*>    files;
        };

        typedef std::vector<dir_node*> directory_tree_t;

        FileAction();
        ~FileAction();
        static void WriteTo(std::string Filename,std::string Msg);
        static std::string ReadFrom(std::string Filename);
        static bool FindDir(std::string dir);
        static bool FindFile(std::string file_path);
        static bool Find(std::string path);
        static void MakeDir(std::string dir);
        static directory_tree_t CreateDirectoryTree(std::string dir) throw(Exception);
        static void GrowDirectoryTree(directory_tree_t& tree, dir_node* cur_node=NULL) throw(Exception);
        static void ExplodeString(std::string base, std::string delim, std::vector<std::string>& str_store);
        static FileType GetFileType(std::string file_type)throw(Exception);
    protected:
    private:
};

#endif // FILEACTION_H
