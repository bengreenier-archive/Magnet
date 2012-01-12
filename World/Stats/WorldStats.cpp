#include "WorldStats.h"
#include "../../Magnet.h"


WorldStats::WorldStats(b2World* in)
{
    //ctor
    m_managedWorldPtr = in;
}

WorldStats::~WorldStats()
{
    //dtor
}

void WorldStats::ShowAll()
{
    ShowFps();
    ShowWorldCount();
}

void WorldStats::HideAll()
{
    HideFps();
    HideWorldCount();
}


void WorldStats::ShowFps()
{

}

void WorldStats::HideFps()
{

}


void WorldStats::ShowWorldCount()
{

    sf::Uint32 t = m_managedWorldPtr->GetBodyCount();
    //std::cout<<m_managedWorldPtr->GetBodyCount()<<"\t"<<t<<"\n";
    m_wc = new sf::String(&t);
    m_wc->SetPosition(10,10);
    m_wc->SetColor(sf::Color(255,255,255));
    Renderer::CreateLink(m_wc);
}

void WorldStats::HideWorldCount()
{
    Renderer::RemoveLink(m_wc);
}

void WorldStats::UpdateWorldCount()
{
    HideWorldCount();
    ShowWorldCount();
}
