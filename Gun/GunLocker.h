#ifndef GUNLOCKER_H
#define GUNLOCKER_H
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "GunMaker.h"
#include "GunComponent.h"
#include "GunEnum.h"


class GunLocker //!< A static class that contains lists of all guns in the game currently, as well as what they do.
{
    public:
        GunLocker(); //!< Default Constructor
        static GunLocker* Get(); //!< Static singleton class, so this gets the instance

        void         AddFrontComponent(GunComponent* Component);                //!< Add a front component to the list of available fronts
        void         AddMiddleComponent(GunComponent* Component);               //!< Add a middle component to the list of available fronts
        void         AddRearComponent(GunComponent* Component);                 //!< Add a rear component to the list of available fronts

        GunComponent GetFrontComponent(int Index);                              //!< Return a front component from vector[Index]
        GunComponent GetMiddleComponent(int Index);                             //!< Return a middle component from vector[Index]
        GunComponent GetRearComponent(int Index);                               //!< Return a rear component from vector[Index]
        GunComponent GetRandomComponent(GunEnum::Component comp, GunEnum::Type type);//!< Get Random Component, and return it.

        GunComponent GetRandomFrontComponent(GunEnum::Type type); //!< Get random front component (Depreciated)
        GunComponent GetRandomMiddleComponent(GunEnum::Type type);//!< Get random middle component (Depreciated)
        GunComponent GetRandomRearComponent(GunEnum::Type type);//!< Get random rear component (Depreciated)

        std::string GetRandomName(); //!< Get a random name
        int Random(int range); //!< generate a random number from 0-range

        int          FrontSize();                                   //!< Get the front vector's size
        int          MiddleSize();                                  //!< Get the middle vector's size
        int          RearSize();                                    //!< Get the rear vector's size


        static void  StaticGunsAdd(GunMaker in); //!< Add a static gun
        static void  StaticGunsLoad(); //!< load all static guns (non changing/survies reload/saves/etc)
        static GunMaker StaticGunsGet(std::string name); //!< Get a static gun based on name.

    protected:
    private:
        std::vector <GunComponent*> Front;                        // Store front components that are useable
        std::vector <GunComponent*> Middle;                       // Store middle components that are useable
        std::vector <GunComponent*> Rear;                         // Stire rear components that are useable

        std::vector<std::string>   nouns;
        std::vector<std::string>   adjectives;
        std::vector<std::string>   verbs;
        void ParseList(std::string ListPath,std::vector<std::string>& List);         //To parse naming scheme.

        sf::Image   ImageFromPath(std::string Path);                            // Return a sf::Image from a resource path

        std::vector <GunMaker> staticGuns;                                      //holds non random guns. survies game exit/relaunch

        static GunLocker* GunLockerPtr;                                         // A helper pointer for the Get method of this class.

};

#endif // GUNLOCKER_H
