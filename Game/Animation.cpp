#include "Animation.h"
//#include "Resource.h"


/*
Animation::Animation(std::string name,int eachVisibleFor,sf::Drawable& shape)
{
    //ctor
    m_mainPath = "NULL";
    m_Fps = eachVisibleFor;
    m_curframe=0;
    m_cyclecounter=0;
    Sprite = new sf::Sprite();

    Sprite->SetCenter(shape.GetCenter());
    Sprite->SetRotation(shape.GetRotation());
    Sprite->SetPosition(shape.GetPosition());
    Sprite->SetScale(shape.GetScale());
    //map over our shit



    if (animationglobals::debug)
        std::cout<<"[Animation] Trying...\n";

    Config poof_config;
    CfgParse poof_parse("Animations.mcf");
    poof_parse.Load();
    poof_parse.Parse(poof_config);

    if (animationglobals::debug)
        std::cout<<"[Animation] Parsed...\n";

    int total_poof_files = atoi(poof_config.GetKeyValue(name,"count").c_str());
    std::string path = poof_config.GetKeyValue(name,"image-path");

    for (int i = 0 ; i< total_poof_files; i++)
    {
        std::string temp = path+"/"+name+"/"+name+"-";
        temp+=(i+1);
        temp+=".png";
        m_files.push_back(temp);
    }

    if (animationglobals::debug)
        std::cout<<"[Animation] Pushed Files...\n";

    if (total_poof_files>0)
        Sprite->SetImage(Resource::GetImage(m_files[0]));

    if (animationglobals::debug)
        std::cout<<"[Animation] Set Image...\n";

        shape = *Sprite;

}

Animation::~Animation()
{
    //dtor
    delete Sprite;
}

void Animation::Cycle()
{

    if (animationglobals::debug)
        std::cout<<"[Animation] Cycling...\n";

   // if (m_curframe < m_files.size()){
   //     m_cyclecounter++;
   //     if ( m_Fps == m_cyclecounter )
   //     {
   //         std::cout<<"Cycles match "<<m_cyclecounter<<" .\n";
   //         m_curframe++; m_cyclecounter=0;
   //         Sprite->SetImage(Resource::GetImage(m_files[m_curframe]));
   //     }
   // std::cout<<"b";
   // }else{std::cout<<"a";}//only allow cycle if we haven't displayed all files already.

}

void Animation::Reset()
{
    m_curframe = 0;
}
*/
