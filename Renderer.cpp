#include "Renderer.h"
#include "Magnet.h"

RenderObject* Renderer::CreateSquare( Point pos, Vector size )
{
    point_t size_x = size.x() /2;
    point_t size_y = size.y() /2;

    RenderObject* ob = new RenderObject(pos);
    ob->shape_type(GL_QUADS);
    ob->addPoint(new Point(-size_x, -size_y));
    ob->addPoint(new Point(-size_x, size_y));
    ob->addPoint(new Point(size_x, size_y));
    ob->addPoint(new Point(size_x, -size_y));

    return ob;
}
//RenderObject* Renderer::CreateCircle( Point pos = Point(), point_t radius = 5, unsigned int level = 6 );
Renderer::Renderer(sf::Window* window)
:     util::Service("renderer"),
      m_state(State::Ready),
      m_drawThread(&Renderer::onDrawFrame, this)
{
    m_window = window;

    m_state.reset();
}

void Renderer::onInitialize()
{
    std::cout << "[Renderer] Intializing\n";
    m_window->setActive(true);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    setViewport();

    ob = Renderer::CreateSquare();
    addRenderObject(ob);

    m_window->setActive(false);
    m_drawThread.launch();
}

void Renderer::onDrawFrame(){
    m_state.set(State::Drawing);
    m_window->setActive(true);
    sf::Context glContext;

    Vector all(1, 1, 1);
    all.normalize();
    while(m_window->isOpen()){
        ob->rotate(1, all);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW_MATRIX);
        glLoadIdentity();
        srand(time(0));

        for(int i = 0; i < m_renderobjects.size(); i++){
            glPushMatrix();
            glLoadIdentity();

            glTranslatef(0.0f, 0.0f, -5.0f);
            glTranslatef(m_renderobjects[i]->position().x(), m_renderobjects[i]->position().y(), m_renderobjects[i]->position().z());

            glRotatef(m_renderobjects[i]->rotation().x(), 1, 0, 0);
            glRotatef(m_renderobjects[i]->rotation().y(), 0, 1, 0);
            glRotatef(m_renderobjects[i]->rotation().z(), 0, 0, 1);

            glBegin(m_renderobjects[i]->shape_type());
                for(int j = 0; j < m_renderobjects[i]->points(); j++){
                    const Point& pt = m_renderobjects[i]->getPoint(j);

                    glColor3f( ((float)(rand()%100))/100
                              ,((float)(rand()%100))/100
                              ,((float)(rand()%100))/100 );
                    glVertex3f(pt.x(), pt.y(), pt.z());
                }
            glEnd();
            glPopMatrix();
        }


        hooks()->Call(Hook::onDraw);
        glFlush();
        m_window->display();
    }
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

    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
    glMatrixMode(GL_MODELVIEW);

}

void Renderer::addRenderObject(RenderObject* newob){
    std::cout << "Here\n";
    m_renderobjects.push_back(newob);
}
