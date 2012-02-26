#include "Entity.h"

Entity::Entity(EntityInfo::Type type,EntityDimensions* dims,Material* mat,EntityInfo::Context context)
{
    //ctor
    Context = context;
    switch(type)
    {
        case EntityInfo::Bullet:{CraftBullet(context,dims,mat);}break;
        case EntityInfo::Circle:{CraftCircle(context,dims,mat);}break;
        case EntityInfo::Rect:{CraftRect(context,dims,mat);}break;
        case EntityInfo::Triangle:{CraftTriangle(context,dims,mat);}break;
    }
}

Entity::Entity(ShapeTransform* trans,ShapeDraw* draw,ShapeData* data)
{
    Transform = trans;
    Data = data;
    Draw = draw;
}

Entity::~Entity()
{
    //dtor
    delete Transform;
    delete Draw;
    delete Data;
}

void Entity::CraftBullet(EntityInfo::Context context,EntityDimensions* dims,Material* mat)
{

    b2BodyDef bodyDef;
    if (context == EntityInfo::Dynamic)
        bodyDef.type = b2_dynamicBody;

    bodyDef.allowSleep = true;
    bodyDef.awake = true;
    bodyDef.bullet = true;

    //check if material is using an image, correct things if this is the case
    if (mat->UsesImage())
    {
        dims->height = mat->GetImage()->GetHeight();
        dims->width = mat->GetImage()->GetWidth();
    }

    //check if material is using text, correct if needed
    if (mat->UsesText())
    {
        dims->height = mat->GetText()->GetLocalBounds().Height;
        dims->width =  mat->GetText()->GetLocalBounds().Width;
    }

    //set the bodydef's position in box2d coords
    bodyDef.position.Set(dims->posx*WorldStandards::ppm,dims->posy*WorldStandards::ppm);

    //set incoming angle
    bodyDef.angle = (((-1)*dims->angle)*WorldStandards::degtorad);

    //make a an actual box
    b2PolygonShape* dynamicBox = new b2PolygonShape;
    dynamicBox->SetAsBox((dims->width/2)*WorldStandards::ppm, (dims->height/2)*WorldStandards::ppm);

    //make fixture
    b2FixtureDef fixtureDef;

    //fixtureize the box
    fixtureDef.shape = dynamicBox;

    //apply material info to the fixture
    fixtureDef.density = mat->GetDensity();
    fixtureDef.friction = mat->GetFriction();
    fixtureDef.restitution = mat->GetRestitution();

    //set the data to be all set to be Created
    Data = new ShapeData(fixtureDef,bodyDef);

    //create a rectangleshape with given width and height


    if (mat->UsesImage())
    {
        sf::Sprite* rectangle = new sf::Sprite(*mat->GetImage());
            //adjust rectangle properties
    rectangle->SetPosition(dims->posx,dims->posy);
    rectangle->SetOrigin(dims->width/2,dims->height/2);
    rectangle->Rotate(dims->angle);

        //set the stuff for Draw and Transform
    Draw = new ShapeDraw(rectangle);
    Transform = new ShapeTransform(rectangle);
    }

    //check if material is using text, correct if needed
    else if (mat->UsesText())
    {
        sf::Text* rectangle = mat->GetText();
            //adjust rectangle properties
    rectangle->SetPosition(dims->posx,dims->posy);
    rectangle->SetOrigin(dims->width/2,dims->height/2);
    rectangle->Rotate(dims->angle);

        //set the stuff for Draw and Transform
    Draw = new ShapeDraw(rectangle);
    Transform = new ShapeTransform(rectangle);
    }
    else
    {
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(dims->width,dims->height));
            //adjust rectangle properties
    rectangle->SetPosition(dims->posx,dims->posy);
    rectangle->SetOrigin(dims->width/2,dims->height/2);
    rectangle->Rotate(dims->angle);
        rectangle->SetFillColor(mat->GetColor());

            //set the stuff for Draw and Transform
    Draw = new ShapeDraw(rectangle);
    Transform = new ShapeTransform(rectangle);
    }






}


void Entity::CraftRect(EntityInfo::Context context,EntityDimensions* dims,Material* mat)
{

    b2BodyDef bodyDef;
    if (context == EntityInfo::Dynamic)
        bodyDef.type = b2_dynamicBody;

    bodyDef.allowSleep = true;
    bodyDef.awake = true;
    bodyDef.bullet = false;


    //check if material is using text, correct if needed
    if (mat->UsesText())
    {
        dims->height = mat->GetText()->GetLocalBounds().Height;
        dims->width =  mat->GetText()->GetLocalBounds().Width;
    }

    //set the bodydef's position in box2d coords
    bodyDef.position.Set(dims->posx*WorldStandards::ppm,dims->posy*WorldStandards::ppm);

    //set incoming angle
    bodyDef.angle = (((-1)*dims->angle)*WorldStandards::degtorad);

    //make a an actual box
    b2PolygonShape* dynamicBox = new b2PolygonShape;
    dynamicBox->SetAsBox((dims->width/2)*WorldStandards::ppm, (dims->height/2)*WorldStandards::ppm);

    //make fixture
    b2FixtureDef fixtureDef;

    //fixtureize the box
    fixtureDef.shape = dynamicBox;

    //apply material info to the fixture
    fixtureDef.density = mat->GetDensity();
    fixtureDef.friction = mat->GetFriction();
    fixtureDef.restitution = mat->GetRestitution();

    //set the data to be all set to be Created
    Data = new ShapeData(fixtureDef,bodyDef);

    //create a rectangleshape with given width and height
    if (mat->UsesImage())
    {
        sf::Sprite* rectangle = new sf::Sprite(*mat->GetImage());
        //adjust rectangle properties

    rectangle->SetPosition(dims->posx,dims->posy);
    rectangle->SetOrigin(dims->width/2,dims->height/2);
    rectangle->Rotate(dims->angle);

        //if (mat->UsesOffset())//is thisright?
            //rectangle->Scale((1/(dims->width+mat->GetOffset()->xa+mat->GetOffset()->xb)),(1/(dims->height++mat->GetOffset()->ya+mat->GetOffset()->yb)));
        //else
            rectangle->Scale((1/dims->width),(1/dims->height));

        //set the stuff for Draw and Transform
    Draw = new ShapeDraw(rectangle);
    Transform = new ShapeTransform(rectangle);
    }

    //check if material is using text, correct if needed
    else if (mat->UsesText())
    {
        sf::Text* rectangle = mat->GetText();
        //adjust rectangle properties
    rectangle->SetPosition(dims->posx,dims->posy);
    rectangle->SetOrigin(dims->width/2,dims->height/2);
    rectangle->Rotate(dims->angle);

        //set the stuff for Draw and Transform
    Draw = new ShapeDraw(rectangle);
    Transform = new ShapeTransform(rectangle);
    }
    else
    {
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(dims->width,dims->height));
        //adjust rectangle properties
    rectangle->SetPosition(dims->posx,dims->posy);
    rectangle->SetOrigin(dims->width/2,dims->height/2);
    rectangle->Rotate(dims->angle);
        rectangle->SetFillColor(mat->GetColor());

            //set the stuff for Draw and Transform
    Draw = new ShapeDraw(rectangle);
    Transform = new ShapeTransform(rectangle);
    }





}


void Entity::CraftCircle(EntityInfo::Context context,EntityDimensions* dims,Material* mat)
{

    b2BodyDef bodyDef;
    if (context == EntityInfo::Dynamic)
        bodyDef.type = b2_dynamicBody;

    bodyDef.allowSleep = true;
    bodyDef.awake = true;
    bodyDef.bullet = true;

    //check if material is using an image, correct things if this is the case
        //was no need

    //check if material is using text, correct if needed
    if (mat->UsesText())
    {
        std::cout<<"[Entity][CraftCircle] Circle Using Text = dumb || Not supported.\n";
    }

    //set the bodydef's position in box2d coords
    bodyDef.position.Set(dims->posx*WorldStandards::ppm, dims->posy*WorldStandards::ppm);

    //set incoming angle
    bodyDef.angle = (((-1)*dims->angle)*WorldStandards::degtorad);

    //make a an actual circle
    b2CircleShape* circle = new b2CircleShape;

    circle->m_radius = dims->radius * WorldStandards::ppm;

    //make fixture
    b2FixtureDef fixtureDef;

    //fixtureize the box
    fixtureDef.shape = circle;

    //apply material info to the fixture
    fixtureDef.density = mat->GetDensity();
    fixtureDef.friction = mat->GetFriction();
    fixtureDef.restitution = mat->GetRestitution();

    //set the data to be all set to be Created
    Data = new ShapeData(fixtureDef,bodyDef);

    //create a rectangleshape with given width and height
    if (mat->UsesImage())
    {
        sf::Sprite* rectangle = new sf::Sprite(*mat->GetImage());
        //adjust rectangle properties
    rectangle->SetPosition(dims->posx,dims->posy);
    rectangle->Rotate(dims->angle);

        //if (mat->UsesOffset())//is thisright?
        //    rectangle->Scale((1/(dims->radius+mat->GetOffset()->xa++mat->GetOffset()->xb)),(1/(dims->radius++mat->GetOffset()->ya++mat->GetOffset()->yb)));
        //else
            rectangle->Scale((1/dims->radius),(1/dims->radius));

        //set the stuff for Draw and Transform
    Draw = new ShapeDraw(rectangle);
    Transform = new ShapeTransform(rectangle);
    }

    //check if material is using text, correct if needed
    else if (mat->UsesText())
    {
        sf::Text* rectangle = mat->GetText();
        //adjust rectangle properties
    rectangle->SetPosition(dims->posx,dims->posy);
    rectangle->Rotate(dims->angle);

        //set the stuff for Draw and Transform
    Draw = new ShapeDraw(rectangle);
    Transform = new ShapeTransform(rectangle);
    }
    else
    {
        sf::CircleShape* rectangle = new sf::CircleShape(dims->radius);
        //adjust rectangle properties
    rectangle->SetPosition(dims->posx,dims->posy);
    rectangle->Rotate(dims->angle);
    rectangle->SetFillColor(mat->GetColor());
        rectangle->SetFillColor(mat->GetColor());

            //set the stuff for Draw and Transform
    Draw = new ShapeDraw(rectangle);
    Transform = new ShapeTransform(rectangle);
    }




}

void Entity::CraftTriangle(EntityInfo::Context context,EntityDimensions* dims,Material* mat)
{
    std::cout<<"[Entity][CraftTriangle] Triangles are disabled for now.\n";
}
