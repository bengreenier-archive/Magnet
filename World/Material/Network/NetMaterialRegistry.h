#ifndef NETMATERIALREGISTRY_H
#define NETMATERIALREGISTRY_H

#include "../Material.h"
#include "../../../Network/HttpReq.h"

#include <string>
#include <vector>
#include <stdlib.h>
namespace NetMaterial{

    class Registry{
        public:
            Registry() {}//!< Default Constructor

            static void Add(Material* in) { Access()->All.push_back(in); }//!< Add a Material to the registry
            static void Remove(Material* in) { for(int i=0;i<Access()->All.size();i++){ if (Access()->All[i] == in){ Access()->All.erase(Access()->All.begin()+(i-1));}} }//!< Remove a Material from the registry
            static void Remove(std::string name) { for(int i=0;i<Access()->All.size();i++){ if (Access()->All[i]->GetName() == name){ Access()->All.erase(Access()->All.begin()+(i-1));}} }//!< Remove a Material (by name) from the registry
            static Material* Get(std::string name) { for(int i=0;i<Access()->All.size();i++){ if (Access()->All[i]->GetName() == name){ return Access()->All[i]; }} }//!< Get/try to get a Material from the registry by material name


            static void Init(){ if (!Access()->m_ptr){Access()->m_ptr = new NetMaterial::Registry();}else{std::cout<<"[NetMaterial::Registry] Already Initted\n";} }//!< Set Singleton Pointer
            static NetMaterial::Registry* Access() { if (Access()->m_ptr){return Access()->m_ptr;}else{std::cout<<"[NetMaterial::Registry] Returning Null ptr..\n";} } //!< Get Singleton Ptr

            static void AddAll(std::string host,std::string path)
            {
                HttpReq req(sf::Http::Request::Get,host,path);
                std::string data,temp;
                if (req.Execute())
                {
                    data = req.GetResponse();
                    std::cout<<"[NetMaterial::Registry] [AddAll] Get Req Success! :)\n";
                    float density,rest,fric;
                    std::string name,color;
                    //std::cout<<"[NetMaterial::Registry] [AddAll] Response: \n|"<<data<<"|\n";
                    if ((data.length()>0)&&(data.find("No Entries")==std::string::npos)&&(data.find("\t")!=std::string::npos)){
                    temp = data.substr(0,data.find("\t")); //name
                    name = temp;
                    temp = data.substr(data.find("\t"),data.find("\t")+data.find("\t")); //color
                    color = temp;
                    temp = data.substr(data.find("\t",data.find("\t")+data.find("\t")+data.find("\t"))); //friction
                    fric = atoi(temp.c_str());
                    temp = data.substr(data.find("\t",data.find("\t")+data.find("\t")+data.find("\t")+data.find("\t"))); //dens
                    density = atoi(temp.c_str());
                    temp = data.substr(data.find("\t",data.find("\t")+data.find("\t")+data.find("\t")+data.find("\t")+data.find("\t"))); //rest
                    rest = atoi(temp.c_str());


                //parse the color string at some point..
                Access()->All.push_back(new Material(density,rest,fric,sf::Color(200,200,12),name));

                std::cout<<"[NetMaterial::Registry] [AddAll] Pushed back "<<name<<" .\n";
                    }else{ std::cout<<"[NetMaterial::Registry] [AddAll] GetResponse is null "<<data.length()<<" or no \\t.\n";}

                }else{ std::cout<<"[NetMaterial::Registry] [AddAll] Get Req Failure! :(\n"; }


            }//!< AddAll Materials parsed from a web address in the form of host.com path

        private:
            std::vector<Material*> All;
            NetMaterial::Registry* m_ptr;


    };



};



#endif
