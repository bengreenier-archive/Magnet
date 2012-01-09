#ifndef BASE_H
#define BASE_H


//the base material class, most materials should be able to be this.
//the only reason for a derived class would be a material like door that has a .click member function,etc.

//SHOULD HANDLE COLORS/TEXTURES/IMAGES EVENTUALLY TOO.

/*
namespace Material{

    enum Type{
        Default,
        Heavy,
        Light
    };


class Base
{
    public:
        Base(Type in=Material::Type::Default);
        ~Base();
    protected:
    private:
        float m_density;
        float m_restitution;
        float m_friction;

        //these set things up for each type. each type has a function here.
        void Default();
        void Heavy();
        void Light();

};

}//namespace material
*/
#endif // BASE_H
