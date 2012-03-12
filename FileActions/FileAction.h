#ifndef FILEACTION_H
#define FILEACTION_H

#include <iostream>
#include <string>
#include <fstream>

#include <vector>

#include "../Game/Exception.h"

namespace FileAction //! Allows program access to files.
{
        enum FileType{
            InvalidFile,
            ImageFile,
            SoundFile,
            FontFile,
            ConfigFile
        };

        struct file_node{
            std::string path;       //Full path:    dir1/dir2/
            std::string file;       //Filename:     file.type
            std::string type;
            bool        loaded;     //true when the file has been loaded.

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

        void WriteTo(std::string Filename,std::string Msg);
        std::string ReadFrom(std::string Filename);
        bool FindDir(std::string dir);
        bool FindFile(std::string file_path);
        bool Find(std::string path);
        void MakeDir(std::string dir);
        directory_tree_t CreateDirectoryTree(std::string dir) throw(Exception);
        void GrowDirectoryTree(directory_tree_t& tree, dir_node* cur_node=NULL) throw(Exception);
        void ExplodeString(std::string base, std::string delim, std::vector<std::string>& str_store);
        FileType GetFileType(std::string file_type)throw(Exception);
};

#endif // FILEACTION_H
