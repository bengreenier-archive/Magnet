#include "ShapeData.h"


ShapeData::ShapeData(b2FixtureDef bodyFixture,b2BodyDef engineBodyDef,b2World* engineWorld)
{
    //ctor
    fdef = bodyFixture;
    bdef = engineBodyDef;
    world = engineWorld;
}

ShapeData::~ShapeData()
{
    //dtor
}

void ShapeData::Create()
{
    body = world->CreateBody(&bdef);
    body->CreateFixture(&fdef);
    //now its in the world simulation
}

void ShapeData::Remove()
{
    world->DestroyBody(body);
    //now this body won't be simulated
}