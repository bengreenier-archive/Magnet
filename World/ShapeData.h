#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include <Box2D/Box2D.h>
#include <iostream>

namespace RadialGravity
{
    enum Type{
        Pull,
        Push
    };
}

#include "WorldStandards.h"

class ShapeData
{
    public:
        /** Default constructor */
        ShapeData(b2FixtureDef bodyFixture,b2BodyDef engineBodyDef);
        /** Default destructor */
        ~ShapeData();

        b2Body* EngineBody;

        void Create(b2World* engineWorld);
		void Remove();

        //construct radial gravity on this element
        void EnableRadialGravity(RadialGravity::Type type,float multiplier,int distance);

		bool HasRadialGravity(){return r_grav;}
		int RadialDirection() { return r_grav_direction;}
		float RadialMultiplier(){return r_grav_multiplier;}
		int RadialDistance(){return r_grav_distance;}

    protected:
    private:
        b2FixtureDef fdef;
        b2BodyDef bdef;

		b2World* world;

		bool r_grav;
		int r_grav_direction;
		int r_grav_distance;
		float r_grav_multiplier;
};

#endif // SHAPEDATA_H
