#include <TreeVisualizer.h>
#include <cmath> 

void Tree_Vizualizer::drawCircle(float x, float y, float radius)
{
    int triangleAmount = 40;  
    float twicePi = 2.0f * M_PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(238, 139, 21); 
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void Tree_Vizualizer::drawDiagonalLine(float x1, float y1, float x2, float y2) {
    GLfloat vertices[] = { x1, y1, x2, y2 };


    glEnableClientState(GL_VERTEX_ARRAY);


    glVertexPointer(2, GL_FLOAT, 0, vertices);


    glDrawArrays(GL_LINES, 0, 2);


    glDisableClientState(GL_VERTEX_ARRAY);
}
