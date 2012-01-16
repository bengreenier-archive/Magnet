#include "GunLocker.h"
#include "GunComponent.h"
#include "../Conversions/Convert.h"
#include "../FileActions/FileAction.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <typeinfo>
GunLocker* GunLocker::GunLockerPtr = NULL;

/*********************
    The constructor for
    the gun locker,
    creates all the
    available components.

*********************/
GunLocker::GunLocker()
{
    //create initial (core/main loaded/non manual/etc) components from raw data here.
/*    AddFrontComponent(new GunComponent(2,"Pain","Gun/Sprites/Assault/assault1-front.png"));
    AddMiddleComponent(new GunComponent(4,"In The","Gun/Sprites/Assault/assault1-middle.png"));
    AddRearComponent(new GunComponent(1,"Ass","Gun/Sprites/Assault/assault1-rear.png"));

    AddFrontComponent(new GunComponent(8,"Burn","Gun/Sprites/Assault/assault2-front.png"));
    AddMiddleComponent(new GunComponent(2,"Near Your","Gun/Sprites/Assault/assault2-middle.png"));
    AddRearComponent(new GunComponent(3,"Eyes","Gun/Sprites/Assault/assault2-rear.png"));

    AddFrontComponent(new GunComponent(5,"Sting","Gun/Sprites/Assault/assault3-front.png"));
    AddMiddleComponent(new GunComponent(11,"Up Your","Gun/Sprites/Assault/assault3-middle.png"));
    AddRearComponent(new GunComponent(7,"Toes","Gun/Sprites/Assault/assault3-rear.png"));*/

    //ctor


    ParseList("Resources/Words/Nouns.mgf",nouns);
    ParseList("Resources/Words/Verbs.mgf",verbs);
    ParseList("Resources/Words/Adjectives.mgf",adjectives);
}


std::string GunLocker::GetRandomName(){
    std::cout << "Generating random name...\n";
    std::string name = "";
    int r = rand() % 3;
    int noun_index, verb_index, adj_index;

    switch(r){
        case 0:
            std::cout << "Generating short name\n";
            noun_index = rand() % nouns.size();
            verb_index = -1;
            adj_index = -1;
            break;
        case 1:
            std::cout << "Generating medium name\n";
            noun_index = rand() % nouns.size();
            verb_index = rand() % verbs.size();
            adj_index = -1;
            break;
        case 2:
            std::cout << "Generating long name\n";
            noun_index = rand() % nouns.size();
            verb_index = rand() % verbs.size();
            adj_index = rand() % adjectives.size();
            break;
    }

    if(adj_index != -1){
        name += adjectives[adj_index] + " ";
    }

     name += nouns[noun_index];

    if(verb_index != -1){
        name += " " + verbs[verb_index];
    }


    return name;
}

int GunLocker::Random(int range){
    return rand()%range;
}


/**************************

    The Getter For GunLocker,
    as we only want to have one
     instance of this class,
      as near as i can tell.

**************************/
GunLocker* GunLocker::Get()
{
    if(GunLockerPtr==NULL)
        GunLockerPtr=new GunLocker();

    return GunLockerPtr;
}

/**************************************************

    A helper function for GunLocker() to
    return a sf::Image that consists of
    a file (image) from the given path.

**************************************************/
sf::Image GunLocker::ImageFromPath(std::string Path)
{
    sf::Image Image;

    if (!Image.LoadFromFile(Path))
    {
        std::cout<<"Failure To Load Image From: "<<Path<<"\n";
    }

    return Image;
}

/********************************************************

    Takes a GunComponent and adds it to the vector
    of front components, which is to signify it can be
    used at any point in the game.

********************************************************/
void GunLocker::AddFrontComponent(GunComponent* Component)
{
    Front.push_back(Component);
}

/********************************************************

    Takes a GunComponent and adds it to the vector
    of middle components, which is to signify it can be
    used at any point in the game.

********************************************************/
void GunLocker::AddMiddleComponent(GunComponent* Component)
{
    Middle.push_back(Component);
}


/********************************************************

    Takes a GunComponent and adds it to the vector
    of rear components, which is to signify it can be
    used at any point in the game.

********************************************************/
void GunLocker::AddRearComponent(GunComponent* Component)
{
    Rear.push_back(Component);
}

/************************
    return Front.size()
************************/
int GunLocker::FrontSize()
{
    return Front.size();
}

/************************
    return Middle.size()
************************/
int GunLocker::MiddleSize()
{
    return Middle.size();
}

/************************
    return Rear.size()
************************/
int GunLocker::RearSize()
{
    return Rear.size();
}

GunComponent GunLocker::GetFrontComponent(int Index)
{
    return *Front[Index];
}

GunComponent GunLocker::GetMiddleComponent(int Index)
{
    return *Middle[Index];
}

GunComponent GunLocker::GetRearComponent(int Index)
{
    return *Rear[Index];
}

GunComponent GunLocker::GetRandomComponent( GunEnum::Component comp, GunEnum::Type type){
    switch(comp){
        case GunEnum::Front:
            return GetRandomFrontComponent(type);
        case GunEnum::Middle:
            return GetRandomMiddleComponent(type);
        case GunEnum::Rear:
            return GetRandomRearComponent(type);
    }
}

GunComponent GunLocker::GetRandomFrontComponent(GunEnum::Type type){
    std::string imgid = Convert::ToString(rand()%3 +1);

    GunComponent* newComponent = new GunComponent();
    newComponent->type = type;

    std::string id;
    newComponent->SetImagePath("Resources/Sprites/Guns/Assault/assault" + imgid + "-front.png");

    AddFrontComponent(newComponent);

    return *newComponent;
}

GunComponent GunLocker::GetRandomMiddleComponent(GunEnum::Type type){

    std::string imgid = Convert::ToString(rand()%3 +1);

    GunComponent* newComponent = new GunComponent();
    newComponent->type = type;
    newComponent->SetImagePath("Resources/Sprites/Guns/Assault/assault" + imgid + "-middle.png");

    AddMiddleComponent(newComponent);

    return *newComponent;
}

GunComponent GunLocker::GetRandomRearComponent(GunEnum::Type type){
    std::string imgid = Convert::ToString(rand()%3 +1);

    GunComponent* newComponent = new GunComponent();
    newComponent->type = type;
    newComponent->SetImagePath("Resources/Sprites/Guns/Assault/assault" + imgid + "-rear.png");

    AddFrontComponent(newComponent);

    return *newComponent;
}





/***********************
    Takes a ListPath, to read into the passed stringlist.
    We use this to read in gun name things (noun,verb,etc)
***********************/
void GunLocker::ParseList(std::string ListPath,std::vector<std::string>& List)
{
    if(!FileAction::FindFile(ListPath))
    {
        std::cout<<"ParseList("<<ListPath<<") Failed.\n";
        return;
    }

    //
    std::string File=FileAction::ReadFrom(ListPath);
    std::string Line="";
    //get the file.
    for (int i=0;i<File.length();i++)
    {
        //
        if (File[i]==';'){std::cout<<"Pushing "<<Line<<"\n"; List.push_back(Line); Line="";}else{Line+=File[i];}
    }


}


GunMaker GunLocker::StaticGunsGet(std::string name)
{
    //read from staticGuns iterate until staticGuns[i].name = name;
}

void  GunLocker::StaticGunsLoad()
{
    //load from Guns/static.mgs
}

void GunLocker::StaticGunsAdd(GunMaker in)
{
    //append to static.mgs, add to staticGuns
}
