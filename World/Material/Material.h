#ifndef MATERIAL_H
#define MATERIAL_H


//the base material class, most materials should be able to be this.
//the only reason for a derived class would be a material like door that has a .click member function,etc.

//SHOULD HANDLE COLORS/TEXTURES/IMAGES EVENTUALLY TOO.

#include <SFML/Graphics.hpp>
#include <string>

namespace MatType{ //! The List of all materials any PhysShape can have.

    enum Type{
        Default,
        Heavy,
        Light,
        Floor,
        Rubber,
        Wood,
        Ground
    };

}

class Material //! The material class, defining a material that a PhysShape can be.
{
    public:
        struct MatOffset{int xa,xb,ya,yb;};//the pixel offset that can be applied to an image

        Material(MatType::Type in=MatType::Default); //!< Default Constructor
        Material(float density,float rest,float fric,sf::Color col,std::string name);//!< Long Contructor
        Material(float density,float rest,float fric,std::string imagepath);//!< Long Contructor, for image use
        Material(float density,float rest,float fric,std::string imagepath,MatOffset* offset);//!< Long Contructor, for image use (with offset)
        Material(float density,float rest,float fric,std::string text,std::string fontpath);//!< Long text constructor, for text use

        ~Material(); //!< Default Deconstructor
        float GetDensity(); //!< Get material instance's density
        float GetRestitution(); //!< Get material instance's restitution
        float GetFriction(); //!< Get material instance's friction
        sf::Color GetColor(); //!< Get material instance's color
        std::string GetName();//!< Get materials name (not always defined)
        sf::Texture* GetImage();//!< REturns image , only call if UsesImage
        sf::Text* GetText();//!< return std::string text.
        sf::Font* GetFont();//!< Returns font
        MatOffset* GetOffset();//!< Returns offset

        bool UsesText(){return m_useText;}
        bool UsesImage(){return m_useImage;}
        bool UsesOffset(){return m_useOffset;}



    protected:
    private:
        float m_density;
        float m_restitution;
        float m_friction;
        sf::Color m_color;
        std::string m_name;//!< Not always needed/used.
        sf::Texture* m_image;
        sf::Text m_text;
        sf::Font m_font;
        MatOffset* m_offset;
        bool m_useImage,m_useText,m_useOffset;

        //these set things up for each type. each type has a function here.
        void m_Default();
        void m_Heavy();
        void m_Light();
        void m_Floor();
        void m_Rubber();
        void m_Wood();
        void m_Ground_Img();

};



#endif // BASE_H
