#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include <Box2D/Box2D.h>

class ShapeData
{
    public:
        /** Default constructor */
        ShapeData(b2FixtureDef bodyFixture,b2BodyDef engineBodyDef,b2World* engineWorld);
        /** Default destructor */
        ~ShapeData();

        void Create();
		void Remove();

    protected:
    private:
        b2FixtureDef fdef;
        b2BodyDef bdef;
        b2Body* body;
		b2World* world;
};

#endif // SHAPEDATA_H
