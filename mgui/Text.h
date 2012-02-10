/*
#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>
#include "Component.h"

namespace mgui{
    class Text : virtual public Component
    {
        public:
            enum AlignType{
                AlignLeft,
                AlignRight,
                AlignCenter
            };

            Text();
            Text(const char* name);
            Text(const char* name, const char* string);
            Text(const char* name, const char* string, AlignType align);

            virtual void SetText(const char* text);

            virtual void SetPosition(sf::Vector2f pos);

            /////////////////////////////////////
            /// Set the font size
            /////////////////////////////////////
            virtual void SetFontSize(int size);
            /////////////////////////////////////
            /// Get font size
            /////////////////////////////////////
            //virtual float GetFontSize();

            virtual void Update();
            /////////////////////////////////////
            /// Set text alignment
            /////////////////////////////////////
            //virtual void SetAlignment(AlignType type);

            /////////////////////////////////////
            /// Overrides to make sure Text acts
            /// as we expect
            void EnableFill(bool toggle){}
            void EnableOutline(bool toggle){}
            /////////////////////////////////////


            virtual bool onMouseRelease(sf::Event evt){}
            virtual bool onMousePress(sf::Event evt){}
            virtual bool onMouseMove(sf::Vector2f mouse_pos){}


            virtual ~Text();
        protected:
        private:
            sf::String  m_string;
            AlignType   m_align;
            Renderer::Link* m_text_link;

            void init(const char* string, AlignType type);
    };
}

#endif // TEXT_H
*/
