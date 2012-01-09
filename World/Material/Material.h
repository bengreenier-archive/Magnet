#ifndef MATERIAL_H
#define MATERIAL_H


//the base material class, most materials should be able to be this.
//the only reason for a derived class would be a material like door that has a .click member function,etc.

//SHOULD HANDLE COLORS/TEXTURES/IMAGES EVENTUALLY TOO.


namespace MatType{

    enum Type{
        Default,
        Heavy,
        Light
    };

}

class Material
{
    public:
        Material(MatType::Type in=MatType::Default);
        ~Material();
        float GetDensity();
        float GetRestitution();
        float GetFriction();
    protected:
    private:
        float m_density;
        float m_restitution;
        float m_friction;

        //these set things up for each type. each type has a function here.
        void m_Default();
        void m_Heavy();
        void m_Light();

};



#endif // BASE_H
