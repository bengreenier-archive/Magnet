#include "Rect.h"
#include "../WorldManager.h"

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
        Set_Radial_Gravity_Distance(0);
    Set_Radial_Gravity(b2Vec2(0,0));
    startanim(false);
    Set_CreateWithForce(false);
}

Rect::Rect(int width,int height,b2Vec2 tForce,sf::Vector2f pos,Material* mat,float degangle)
{
    //ctor
    Set_Width(width);
    Set_Height(height);
    Set_Position(pos);
    Set_Mat(mat);
    Set_Static(false);//default staticicity
    Set_Angle(degangle);
    Set_ShapeType(WorldShapes::Rect);

        Set_Radial_Gravity_Distance(0);
    Set_Radial_Gravity(b2Vec2(0,0));
    Set_CreateWithForce(true);
    startanim(false);
    Set_CreateWithForce_Force(tForce);
}

Rect::Rect(int width,int height,bool staticc,sf::Vector2f pos,Material* mat,float degangle)
{
    //ctor
    Set_Width(width);
    Set_Height(height);
    Set_Static(staticc);
    Set_Position(pos);
    Set_Mat(mat);
    startanim(false);
    Set_Angle(degangle);
    Set_ShapeType(WorldShapes::StaticRect);
        Set_Radial_Gravity_Distance(0);

    Set_Radial_Gravity(b2Vec2(0,0));
    Set_CreateWithForce(false);
}

Rect::Rect(int width,int height,b2Vec2 radialgrav,int radialdist,bool staticc,sf::Vector2f pos,Material* mat,float degangle)
{
    //ctor
    Set_Width(width);
    Set_Height(height);
    Set_Static(staticc);
    Set_Position(pos);
    Set_Mat(mat);
    Set_Angle(degangle);
    Set_ShapeType(WorldShapes::StaticRect);
    Set_Radial_Gravity_Distance(radialdist);
    Set_Radial_Gravity(radialgrav);
    startanim(false);
    Set_CreateWithForce(false);
            pullorpush_val_set(radialgrav.y);
}


Rect::~Rect()
{
    //dtor
    Destroy(Get_C_World());
}

void Rect::Create(b2World* p_world)
{
    Set_C_World(p_world);
    //do box2d first..
    b2BodyDef bodyDef;
	if (!Get_Static()){
	bodyDef.type = b2_dynamicBody;
	}
    bodyDef.allowSleep = true;
	bodyDef.awake = true;

    //NO FUCKING CLUE...THIS IS DUMB. but it works...
    if (!Get_Static())
        bodyDef.position.Set(/*(*/(Get_Position().x+Get_Width())/*/2)*/*WorldStandards::ppm, /*(*/(Get_Position().y+Get_Height())/*/2)*/*WorldStandards::ppm);
    else
        bodyDef.position.Set(((Get_Position().x+Get_Width())/2)*WorldStandards::ppm, ((Get_Position().y+Get_Height())/2)*WorldStandards::ppm);

    bodyDef.angle = (((-1)*Get_Angle())*WorldStandards::degtorad);

	Set_Body(p_world->CreateBody(&bodyDef));

	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox((Get_Width()/2)*WorldStandards::ppm, (Get_Height()/2)*WorldStandards::ppm);

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

    if (Get_CreateWithForce())
        ApplyForce(Get_CreateWithForce_Force());

    if (WorldStandards::debug)
        std::cout << "[Box2D] Added Box.\n";


    float b2posx = Get_Body()->GetPosition().x;
    float b2posy = Get_Body()->GetPosition().y;
    float b2rot  = Get_Body()->GetAngle();

    float sfposx = b2posx*WorldStandards::mpp;
    float sfposy = b2posy*WorldStandards::mpp;

    //do sfml
    if (!Get_Mat()->UsesImage())
    {
        Set_Shape(new sf::Shape(sf::Shape::Rectangle(0, 0,Get_Width(),Get_Height(),Get_Mat()->GetColor())));
        Get_Shape()->SetPosition(sf::Vector2f(sfposx, sfposy)); //Get_Position()
        Get_Shape()->SetCenter(sf::Vector2f((Get_Width()/2), (Get_Height()/2)));
        Get_Shape()->Rotate(Get_Angle());
    }
    else
    {
        sf::Sprite* temp = new sf::Sprite();
        temp->SetImage(*Get_Mat()->GetImage());

        float img_width   = Get_Mat()->GetImage()->GetWidth();
        float img_height  = Get_Mat()->GetImage()->GetHeight();

        temp->SetPosition(sf::Vector2f(sfposx, sfposy)); //Get_Position()
        temp->Rotate(Get_Angle());
        temp->Resize(Get_Width(), Get_Height());
        temp->SetCenter((Get_Width()*(1/temp->GetScale().x))/2,(Get_Height()*(1/temp->GetScale().y))/2);

        Set_Shape(temp);
    }

    Renderer::CreateLink(Get_Shape());

    if (WorldStandards::debug)
        std::cout << "[SFML] Added Box.\n";


}
