/*
#include "WorldStats.h"
#include "../../Magnet.h"
#include <sstream>

WorldStats::WorldStats(b2World* in)
{
    //ctor
    m_managedWorldPtr = in;
}

WorldStats::~WorldStats()
{
    //dtor
}

void WorldStats::ShowAll(int x,int y)
{
    ShowFps(x,y);
    ShowWorldCount(x,y);
}

void WorldStats::HideAll()
{
    HideFps();
    HideWorldCount();
}


void WorldStats::ShowFps(int x, int y)
{
    //std::stringstream ss;
    //ss << (float)(1/Renderer::GetRenderWindow();
    //m_fps = new sf::String(ss.str()+" FPS");
    //m_fps->SetPosition(x,y);
    //m_fps->SetColor(sf::Color(255,255,255));
    //Renderer::CreateLink(m_fps,Renderer::MenuLayer);
}

void WorldStats::HideFps()
{
   //Renderer::RemoveLink(m_fps);
}

void WorldStats::UpdateFps(int x,int y)
{
    //HideFps();
    //ShowFps(x,y);

    //std::stringstream ss;
    //ss << (float)(1/Renderer::GetRenderWindow()->GetFrameTime());

    //m_fps->SetText(ss.str());
}

void WorldStats::ShowWorldCount(int x,int y)
{
    std::stringstream ss;
    ss << m_managedWorldPtr->GetBodyCount();
    //std::cout<<m_managedWorldPtr->GetBodyCount()<<"\t"<<t<<"\n";
    m_wc = new sf::Text("Total Bodies: "+ss.str());
    m_wc->SetPosition(x,y);
    m_wc->SetColor(sf::Color(255,255,255));
    Renderer::CreateLink(m_wc,Renderer::MenuLayer);
}

void WorldStats::HideWorldCount()
{
    Renderer::RemoveLink(m_wc);
}

void WorldStats::UpdateWorldCount(int x,int y)
{
    //HideWorldCount();
    //ShowWorldCount(x,y);
    std::stringstream ss;
    ss << m_managedWorldPtr->GetBodyCount();
    m_wc->SetString("Total Bodies: "+ss.str());
}

*/
