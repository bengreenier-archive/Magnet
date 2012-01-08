#ifndef RESOURCEPTR_H
#define RESOURCEPTR_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace Resource{

    class Pointer
    {
        public:
            enum Type{
                Invalid,
                Image,
                Sound,
                Text
            };

            Pointer(std::string file);
            virtual ~Pointer();

            void set(std::string file);
            Type getType(){ return m_type; };
            std::string file(){ return m_dir; }

            bool isValid(){ if(getType() == Invalid) return true; return false; }

            ////////////////////////////////////////////////////////////
            ///     Get a pointer to a resource of any type
            ///
            ///     throws NullPointer exception if the resource is
            ///     not valid;
            ////////////////////////////////////////////////////////////
            void* getGeneric();

            ////////////////////////////////////////////////////////////
            ///     Get a pointer to a resource of type image
            ///
            ///     throws NullPointer exception if the resource is
            ///     not of type image;
            ////////////////////////////////////////////////////////////
            sf::Image*  getImage();

            ////////////////////////////////////////////////////////////
            ///     Get a pointer to a resource of type font
            ///
            ///     throws NullPointer exception if the resource is
            ///     not of type font;
            ////////////////////////////////////////////////////////////
            sf::Font*   getFont();

            ////////////////////////////////////////////////////////////
            ///     Get a pointer to a resource of type text
            ///
            ///     throws NullPointer exception if the resource is
            ///     not of type Text;
            ////////////////////////////////////////////////////////////
            std::string* getText();

            ////////////////////////////////////////////////////////////
            ///     Get a pointer to a resource of type sound
            ///
            ///     throws NullPointer exception if the resource is
            ///     not of type Sound;
            ///     temporarily returns void*
            ////////////////////////////////////////////////////////////
            void* getSound();

        protected:
        private:
            std::string m_dir;
            Type m_type;

            void _settype();
            void parse(std::string str, std::string separator, std::vector<std::string>* results);

    };


}

#endif // RESOURCEPTR_H
