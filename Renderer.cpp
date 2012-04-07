#include "Renderer.h"
#include "Magnet.h"

RenderObject* Renderer::CreateSquare( Point pos, Vector size )
{
    point_t size_x = size.x() /2;
    point_t size_y = size.y() /2;

    //This should be managed by some sort of garbage collecting memory allocator
    VertexArray* shape_data = new VertexArray(4);
    shape_data->point(0, Point(-size_x, -size_y));
    shape_data->point(1, Point(-size_x, size_y));
    shape_data->point(2, Point(size_x, size_y));
    shape_data->point(3, Point(size_x, -size_y));

    RenderObject* ob = new RenderObject(shape_data, pos);
    ob->shape_type(GL_QUADS);
    /*
    ob->addPoint(new Point(-size_x, -size_y));
    ob->addPoint(new Point(-size_x, size_y));
    ob->addPoint(new Point(size_x, size_y));
    ob->addPoint(new Point(size_x, -size_y));
    */


    return ob;
}
//RenderObject* Renderer::CreateCircle( Point pos = Point(), point_t radius = 5, unsigned int level = 6 );
RenderObject* Renderer::CreateCube( Point pos, Vector size )
{
    point_t size_x = size.x() /2;
    point_t size_y = size.y() /2;
    point_t size_z = size.z() /2;

    VertexArray* shape_data = new VertexArray(16);
    //Front
    shape_data->point(0, Point(-size_x, -size_y, size_z));
    shape_data->point(1, Point(-size_x, size_y, size_z));
    shape_data->point(2, Point(size_x, size_y, size_z));
    shape_data->point(3, Point(size_x, -size_y, size_z));

    //Back
    shape_data->point(4, Point(-size_x, -size_y, -size_z));
    shape_data->point(5, Point(-size_x, size_y, -size_z));
    shape_data->point(6, Point(size_x, size_y, -size_z));
    shape_data->point(7, Point(size_x, -size_y, -size_z));

    //Left
    shape_data->point(8, Point(-size_x, -size_y, size_z));
    shape_data->point(9, Point(-size_x, size_y, size_z));
    shape_data->point(10, Point(-size_x, size_y, -size_z));
    shape_data->point(11, Point(-size_x, -size_y, -size_z));

    //Left
    shape_data->point(12, Point(size_x, -size_y, size_z));
    shape_data->point(13, Point(size_x, size_y, size_z));
    shape_data->point(14, Point(size_x, size_y, -size_z));
    shape_data->point(15, Point(size_x, -size_y, -size_z));

    RenderObject* ob = new RenderObject(shape_data, pos);
    ob->shape_type(GL_QUADS);



    return ob;
}
Renderer::Renderer(sf::Window* window)
:     util::Service("renderer"),
      m_state(State::Ready),
      m_drawThread(&Renderer::onDrawFrame, this),
      m_hooks("RendererHooks")
{
    m_window = window;

    m_state.reset();
}

bool Renderer::onInitialize()
{
    std::cout << "[Renderer] Intializing\n";
    m_window->setActive(true);


    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);


    setViewport();

    try{
        ob = Renderer::CreateCube();
        addRenderObject(ob);
    }catch(util::Exception e){
        std::cout << "Exception caught\n";
        e.log();
    }

    m_window->setActive(false);
    m_drawThread.launch();

    return true;
}

void Renderer::onDrawFrame(){
    m_state.set(State::Drawing);
    m_window->setActive(true);
    sf::Context glContext;

    Vector all(1, 1, 1);
    all.normalize();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_CW);
    glEnable(GL_CULL_FACE);

    while(m_window->isOpen()){
        //ob->rotate(1, all);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW_MATRIX);
        glLoadIdentity();
        srand(time(0));

        for(int i = 0; i < m_renderobjects.size(); i++){
            glPushMatrix();
            glLoadIdentity();

            m_renderobjects[i]->draw();

            glPopMatrix();
        }

        hooks()->Call(Hook::onDraw);
       // glFlush();
        m_window->display();
    }


    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CW);
    glDisable(GL_CULL_FACE);
    glDisableClientState(GL_VERTEX_ARRAY);
}

//Should likely be inlined
HookRegistry* Renderer::hooks()
{
    return &m_hooks;
}

State* Renderer::getState() {
    return &m_state;
}
void Renderer::onThink()
{

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*switch(getState()->get()){
        case State::Null:
            m_drawThread.launch();
            break;
        case State::Drawing:

            break;
    }*/
}

void Renderer::event_resized(sf::Event& evt)
{
    setViewport();
}

void Renderer::setViewport()
{
    int width  =   m_window->getSize().x;
    int height =   m_window->getSize().y;

    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 0, 50); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
    glMatrixMode(GL_MODELVIEW);

}

void Renderer::addRenderObject(RenderObject* newob){
    std::cout << "![Renderer] addRenderObject\n";
    m_renderobjects.push_back(newob);
}
