#ifndef WORLDSTORAGE_H
#define WORLDSTORAGE_H

#include <SFML/Graphics.hpp>
#include "../Material/Material.h"

namespace WorldShape
{
    enum Type{
        Box,
        Circle,
        StaticBox,
        StaticCircle
    };
}

class WorldStorage //! outdated class that should be removed.
{
    public:
        WorldStorage();
        ~WorldStorage();

        void SetParams(int radius,sf::Vector2f pos,Material* mat, float degangle);//circle params
        void SetParams(int width,int height,sf::Vector2f pos,Material* mat, float degangle);//box params

        void MakeStatic();

        int GetRadius();
        sf::Vector2f GetPos();
        Material* GetMat();
        float GetAngle();

        int GetWidth();
        int GetHeight();

        bool IsType(WorldShape::Type in);

    protected:
    private:
        int m_radius;
        int m_width;
        int m_height;
        float m_angle;
        Material* m_mat;
        sf::Vector2f m_pos;
        bool m_isstatic;
};

#endif // WORLDSTORAGE_H
