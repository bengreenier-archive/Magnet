#ifndef LINE_H
#define LINE_H

#include "PhysShape.h"

class Line : public PhysShape
{
    public:
        /** Default constructor */
        Line(int x,int y,int x2,int y2,int thickness = 1,Material* mat=new Material(MatType::Default));
        Line(int x,int y,int x2,int y2,bool staticc,int thickness = 1,Material* mat=new Material(MatType::Default));
        /** Default destructor */
        ~Line();

        /** Overide these virtual f(x)'s*/
        void Create();
        void Destroy();
        void Update();

        /** Getters/Setters */
        void Set_x1(int val){ m_x1 = val; }
        int Get_x1(){ return m_x1; }
        void Set_x2(int val){ m_x2 = val; }
        int Get_x2(){ return m_x2; }
        void Set_y1(int val){ m_y1 = val; }
        int Get_y1(){ return m_y1; }
        void Set_y2(int val){ m_y2 = val; }
        int Get_y2(){ return m_y2; }
        void Set_Width(int val){ m_Width = val; }
        int Get_Width(){ return m_Width; }
        void Set_Thickness(int val){ m_Thickness = val; }
        int Get_Thickness(){ return m_Thickness; }

    protected:
    private:
        int m_x1;
        int m_x2;
        int m_y1;
        int m_y2;
        int m_Width;
        int m_Thickness;
};

#endif // LINE_H
