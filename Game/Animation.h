#ifndef ANIMATION_H
#define ANIMATION_H

#include "../FileActions/Cfg/CfgInclude.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

//#include "../Magnet.h"
namespace animationglobals{static const bool debug = true; }
class Animation //! The class each animation gets wrapped in.
{
    public:


        Animation(std::string name,int eachVisibleFor,sf::Drawable& shape); //!< Create a new animation from a dir (ex:"poof/") and a frametime for each image to be shown.


        ~Animation(); //!< Deconstructor


        void Cycle(); //!< run the animation cycle another frame.

        void Reset(); //!< Reset m_curframe, allowing this animation to Cycle() once again.



        static void CycleAndKill(void* userdata);//!< cycles and RemoveLinks

        //------------------------------------------------------
        //REMEBER TO INIT IMAGES... BEFORE ANIMATOR USE    :/
        //------------------------------------------------------

    protected:
    private:

    int m_Fps; /*!< set by eachVisibleFor in the constructor. */


    int m_curframe; /*!< the currently shown frame */


    int m_cyclecounter; /*!< +1 each cycle */


    std::string m_mainPath; /*!< set by imageDir in constructor */


    sf::Sprite* Sprite; /*!< the image we Render-er. */



    bool m_unhooked; /*!< set to true when you dont need to run Cycle anymore. (until you can remove a hook) */


    std::vector<std::string> m_files; /*!< a vector that gets filled with all the image names */
};

#endif // Animation_h
