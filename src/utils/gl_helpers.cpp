#include "gl_helpers.h"

void GLHELPERS::grid(float groundLevel) {
	GLfloat extent      = 19.0f; // How far on the Z-Axis and X-Axis the ground extends
    GLfloat stepSize    = 1.0f;  // The size of the separation between points
    
    // Set grid lines color
    glColor3ub(40, 40, 40);
    
    // Draw our ground grid
    glBegin(GL_LINES);
    for (GLfloat loop = -extent; loop < extent; loop += stepSize)
    {
        // first loop is the first lines
        if(loop == 0) {
            // Y-Axis is green
            glColor3ub(0, 125, 0);
            glVertex3f(0, extent, 0);
            glVertex3f(0, -extent, 0);
            // X-Axis is red
            glColor3ub(125, 0, 0);
            glVertex3f(extent, groundLevel,  0);
            glVertex3f(-extent, groundLevel, 0);
            // Z-Axis is blue
            glColor3ub(0, 0, 125);
            glVertex3f(0, groundLevel,  extent);
            glVertex3f(0, groundLevel, -extent);
        } else {
            glColor3ub(40, 40, 40);
            // Draw lines along Z-Axis
            glVertex3f(loop, groundLevel,  extent);
            glVertex3f(loop, groundLevel, -extent);
            // Draw lines across X-Axis
            glVertex3f(-extent, groundLevel, loop);
            glVertex3f( extent, groundLevel, loop);
        }
    }
    glEnd();
}

void GLHELPERS::axis(float fScale)
{
    // Draw axis
  glEnableClientState(GL_VERTEX_ARRAY);

  GLfloat axis[] = {
    0.0, 0.0, 0.0,
    fScale , 0, 0 };
    glColor4f(1, 0, 0, 1);
    glVertexPointer(3, GL_FLOAT, 0, axis);
    glDrawArrays(GL_LINE_STRIP, 0, 2);

    axis[3] = 0.0;
    axis[4] = fScale;
    glColor4f(0, 1, 0, 1);
    glVertexPointer(3, GL_FLOAT, 0, axis);
    glDrawArrays(GL_LINE_STRIP, 0, 2);

    axis[4] = 0.0;
    axis[5] = fScale;
    glColor4f(0, 0, 1, 1);
    glVertexPointer(3, GL_FLOAT, 0, axis);
    glDrawArrays(GL_LINE_STRIP, 0, 2);

    glDisableClientState(GL_VERTEX_ARRAY);
}