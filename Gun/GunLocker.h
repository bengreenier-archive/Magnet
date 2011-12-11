#ifndef GUNLOCKER_H
#define GUNLOCKER_H
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "GunComponent.h"
#include "GunEnum.h"


/*******************************
This contains all the gun/weapon choices
allows easy access to the gun peices mostly.


-Needs a getter, as we shouldn't want more then one instance.
********************************/
class GunLocker
{
    public:
        GunLocker();
        static GunLocker* Get();

        void         AddFrontComponent(GunComponent* Component);                // Add a front component to the list of available fronts
        void         AddMiddleComponent(GunComponent* Component);               // Add a middle component to the list of available fronts
        void         AddRearComponent(GunComponent* Component);                 // Add a rear component to the list of available fronts

        GunComponent GetFrontComponent(int Index);                              // Return a front component from vector[Index]
        GunComponent GetMiddleComponent(int Index);                             // Return a middle component from vector[Index]
        GunComponent GetRearComponent(int Index);                               // Return a rear component from vector[Index]
        GunComponent GetRandomComponent(GunEnum::Component comp, GunEnum::Type type);

        GunComponent GetRandomFrontComponent(GunEnum::Type type);
        GunComponent GetRandomMiddleComponent(GunEnum::Type type);
        GunComponent GetRandomRearComponent(GunEnum::Type type);

        std::string GetRandomName();
        int Random(int range);

        int          FrontSize();                                   // Get the front vector's size
        int          MiddleSize();                                  // Get the middle vector's size
        int          RearSize();                                    // Get the rear vector's size
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

        static GunLocker* GunLockerPtr;                                         // A helper pointer for the Get method of this class.

};

#endif // GUNLOCKER_H
