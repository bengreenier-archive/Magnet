#ifndef NETMATERIALREGISTRY_H
#define NETMATERIALREGISTRY_H

#include "../Material.h"
#include "../../../Network/HttpReq.h"

#include <string>
#include <vector>
#include <stdlib.h>
namespace NetMaterial{

static const bool debug = false;

    class Registry{
        public:
            Registry() {}//!< Default Constructor

            void Add(Material* in) { All.push_back(in); }//!< Add a Material to the registry
            void Remove(Material* in) { for(int i=0;i<All.size();i++){ if (All[i] == in){ All.erase(All.begin()+(i-1));}} }//!< Remove a Material from the registry
            void Remove(std::string name) { for(int i=0;i<All.size();i++){ if (All[i]->GetName() == name){ All.erase(All.begin()+(i-1));}} }//!< Remove a Material (by name) from the registry
            Material* Get(std::string name) { for(int i=0;i<All.size();i++){ if (All[i]->GetName() == name){ return All[i]; }} }//!< Get/try to get a Material from the registry by material name

            std::vector<Material*>* GetVector() { return &All;}//!< Get the vector of all loaded Materials

           // static void Init(){m_ptr = new NetMaterial::Registry(); }//!< Set Singleton Pointer
           // static NetMaterial::Registry* Access() { if (m_ptr){return m_ptr;}else{std::cout<<"[NetMaterial::Registry] Returning Null ptr..\n"; return NULL;} } //!< Get Singleton Ptr

            void AddAll(std::string host,std::string path)
            {
                std::cout<<"[NetMaterial::Registry] [AddAll] Loading...\n";

                HttpReq req(sf::Http::Request::Get,host,path);
                std::string data,temp;
                if (req.Execute())
                {
                    data = req.GetResponse();
                    if (NetMaterial::debug)
                        std::cout<<"[NetMaterial::Registry] [AddAll] Get Req Success! :)\n";

                    float density,rest,fric;
                    std::string name,color,split=data,total=data;
                    //std::cout<<"[NetMaterial::Registry] [AddAll] Response: \n|"<<data<<"|\n";
                    if ((data.length()>0)&&(data.find("No Entries")==std::string::npos)&&(data.find("\t")!=std::string::npos)){
                    //std::cout<<data.find("\n")+1<<" - "<<data.find("\t")-1<<"\n"<<data[2]<<" - "<<data[8]<<"\n";

                    total = total.substr(total.find("\n")+1);
                    //std::cout<<"{"<<total<<"}\n";

                    while (total.find("\n")!=std::string::npos)
                    {

                        split = total.substr(0,total.find("\n"));

                        name = split.substr(split.find("\n")+1,split.find("\t")); //name


                        //from first right after /t to end
                        split = split.substr(split.find_first_of("\t")+1);



                        temp = split.substr(0,split.find("\t")-1); //color
                        color = temp;

                        temp = split.substr(split.find("\t")); //fric
                        fric = atof(temp.c_str());



                         //from first right after /t to end
                        split = split.substr(split.find_first_of("\t")+1);

                        temp = split.substr(split.find("\t")); //dens
                        density = atof(temp.c_str());


                         //from first right after /t to end
                        split = split.substr(split.find_first_of("\t")+1);


                        //uh....

                         //from first right after /t to end
                        split = split.substr(split.find_first_of("\t")+1);


                        temp = split.substr(0,split.find("\t")-1); //rest
                        rest = atof(temp.c_str());


                        //parse the color string at some point..

                            temp = color.substr(0,color.find("-"));
                            int r = atoi(temp.c_str());

                            color = color.substr(color.find("-")+1);
                            //std::cout<<"|"<<color<<"|\n";
                            temp = color.substr(0,color.find("-")+1);

                            int g = atoi(temp.c_str());

                            color = color.substr(color.find("-")+1);
                            temp = color.substr(0,color.find("-")+1);
                            int b = atoi(temp.c_str());

                            //std::cout<<"|g="<<g<<"|\n";

                        All.push_back(new Material(density,rest,fric,sf::Color(r,g,b),name));

                        //std::cout<<"|"<<name<<"|"<<color<<"|"<<fric<<"|"<<density<<"|"<<rest<<"|\n";

                        if (NetMaterial::debug)
                            std::cout<<"[NetMaterial::Registry] [AddAll] Pushed back.\n";

                        //do for all lines of data
                        total = total.substr(total.find("\n")+1);
                    }
                        m_cur_mat = All[0]; //assume we added one...
                    }else{ if (NetMaterial::debug){std::cout<<"[NetMaterial::Registry] [AddAll] GetResponse is null "<<data.length()<<" or no \\t.\n";} }

                }else{ if (NetMaterial::debug){std::cout<<"[NetMaterial::Registry] [AddAll] Get Req Failure! :(\n";} }

            std::cout<<"[NetMaterial::Registry] [AddAll] Loaded.\n";



            }//!< AddAll Materials parsed from a web address in the form of host.com path


            Material* NextMaterial() {

                for (int i=0;i<All.size();i++)
                {
                    if (All[i]->GetName()==m_cur_mat->GetName()){
                        if (i+1 < All.size())
                            m_cur_mat = All[i+1];
                        else
                            m_cur_mat = All[0];

                        return m_cur_mat;
                    }


                }

    std::cout<<"failure to find next, returning current\n";
                 return m_cur_mat;
                 }//!< Cycle to next thing

            Material* CurrentMaterial() { return m_cur_mat; }//!< the current cycled material

        private:
            std::vector<Material*> All;
            Material* m_cur_mat;// used for cycling



    };



};



#endif
