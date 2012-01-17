#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>

class Animation
{
    public:
        /** Default constructor */

        //each time you want to animate, associate a new Animator, with the path to imageDir (not full path), and time each img is visable for
        Animation(std::string imageDir,int eachVisibleFor);
        /** Default destructor */
        ~Animation();

        //run the animation cycle another frame.
        void Cycle();

        //------------------------------------------------------
        //REMEBER TO INIT IMAGES... BEFORE ANIMATOR USE    :/
        //------------------------------------------------------

    protected:
    private:
    //set by eachVisibleFor in the constructor.
    int m_Fps;

    //set by imageDir in constructor
    std::string m_mainPath;

    //the image we Render-er.
    sf::Image* Sprite;

    //set to true when you dont need to run Cycle anymore.
    bool unhooked;
};

#endif // ANIMATion_H
