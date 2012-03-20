#include "Renderer.h"

Renderer::Renderer(sf::Window* window)
{
    m_window = window;
}


void Renderer::frame()
{
    m_window->setActive();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW_MATRIX);

    srand(time(0));

    for(int i = 0; i < m_renderobjects.size(); i++){
        glPushMatrix();
        glLoadIdentity();

        glTranslatef(0.0f, 0.0f, -5.0f);

        glTranslatef(m_renderobjects[i]->position().x(), m_renderobjects[i]->position().y(), m_renderobjects[i]->position().z());

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


    glPopMatrix();
    glFlush();

    m_window->display();
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

void Renderer::hook_initialized()
{
    std::cout << "Initialized\n";
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    setViewport();
}

void Renderer::addRenderObject(RenderObject* newob){
    std::cout << "Here\n";
    m_renderobjects.push_back(newob);
}
