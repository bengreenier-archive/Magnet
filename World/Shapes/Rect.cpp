#include "Rect.h"
#include "../World.h"

Rect::Rect(int width,int height,sf::Vector2f pos,Material* mat,float degangle)
{
    //ctor
    Set_Width(width);
    Set_Height(height);
    Set_Position(pos);
    Set_Mat(mat);
    Set_Static(false);//default staticicity
    Set_Angle(degangle);
    Set_ShapeType(WorldShapes::Rect);
}

Rect::Rect(int width,int height,bool staticc,sf::Vector2f pos,Material* mat,float degangle)
{
    //ctor
    Set_Width(width);
    Set_Height(height);
    Set_Static(staticc);
    Set_Position(pos);
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_ShapeType(WorldShapes::StaticRect);
}

Rect::~Rect()
{
    //dtor
    Destroy();
}

void Rect::Create()
{
    //do box2d first..
    b2BodyDef bodyDef;
	if (!Get_Static()){
	bodyDef.type = b2_dynamicBody;
	}
    bodyDef.allowSleep = true;
	bodyDef.awake = true;

    //see if this hlps..

	bodyDef.position.Set(((Get_Position().x+Get_Width())/2)*WorldStandards::ppm, ((Get_Position().y+Get_Height())/2)*WorldStandards::ppm);

    bodyDef.angle = (((-1)*Get_Angle())*WorldStandards::degtorad);

	Set_Body(World::Access()->CurrentWorld()->CreateBody(&bodyDef));

	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(((Get_Width())/2)*WorldStandards::ppm, ((Get_Height())/2)*WorldStandards::ppm);

	//fixture stuff
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &dynamicBox;

    if (!Get_Static()){
    /////add material class in the futurec.
    fixtureDef.density = Get_Mat()->GetDensity();
    fixtureDef.friction = Get_Mat()->GetFriction();
    fixtureDef.restitution = Get_Mat()->GetRestitution();
	//////
	}

	Get_Body()->CreateFixture(&fixtureDef);

    //add the body to the list
    //Access()->b2PhysicsObjects.push_back(bodyBox);

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added Box.\n";

    //do sfml
    Set_Shape(new sf::Shape(sf::Shape::Rectangle(0,0,Get_Width(),Get_Height(),Get_Mat()->GetColor())));
    Get_Shape()->SetPosition(Get_Position());
    Get_Shape()->SetCenter(sf::Vector2f(Get_Width()/2, Get_Height()/2));
    Get_Shape()->Rotate(Get_Angle());

    Renderer::CreateLink(Get_Shape());


    //add body to the list
    //Access()->sfPhysicsObjects.push_back(visibox);

    if (WorldStandards::debug)
        std::cout << "[SFML] Added Box.\n";


}

void Rect::Destroy()
{
    //
    Renderer::RemoveLink(Get_Shape());
    World::Access()->CurrentWorld()->DestroyBody(Get_Body());
    if (WorldStandards::debug)
        std::cout << "[SFML/Box2D] Removed Box.\n";

}