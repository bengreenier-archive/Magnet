#include "WorldStorage.h"

WorldStorage::WorldStorage()
{
    //ctor
        m_radius=-1;
        m_width=-1;
        m_height=-1;
        m_angle=-1;
        m_mat = new Material();
        m_pos=sf::Vector2f(-1,-1);
        m_isstatic=false;

}

WorldStorage::~WorldStorage()
{
    //dtor
}

void WorldStorage::SetParams(int radius,sf::Vector2f pos,Material* mat, float degangle)//circle params
{
    m_radius = radius; m_pos = pos; m_mat = mat; m_angle = degangle;
}

void WorldStorage::SetParams(int width,int height,sf::Vector2f pos,Material* mat, float degangle)//box params
{
    m_width = width; m_height = height; m_pos = pos; m_mat = mat; m_angle = degangle;
}

int WorldStorage::GetRadius()
{
    return m_radius;
}

sf::Vector2f WorldStorage::GetPos()
{
    return m_pos;
}

Material* WorldStorage::GetMat()
{
    return m_mat;
}

float WorldStorage::GetAngle()
{
    return m_angle;
}

int WorldStorage::GetWidth()
{
    return m_width;
}

int WorldStorage::GetHeight()
{
    return m_height;
}

bool WorldStorage::IsType(WorldShape::Type in)
{
    if ((in == WorldShape::Box)&&(m_width!=-1)&&(!m_isstatic))
        return true;

    if ((in == WorldShape::Circle)&&(m_radius!=-1)&&(!m_isstatic))
        return true;

    if ((in == WorldShape::StaticBox)&&(m_width!=-1)&&(m_isstatic))
        return true;

    if ((in == WorldShape::StaticCircle)&&(m_radius!=-1)&&(m_isstatic))
        return true;

    return false;


}

void WorldStorage::MakeStatic()
{
    m_isstatic=true;
}
