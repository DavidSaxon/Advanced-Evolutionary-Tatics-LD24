#include "Wall.hpp"

//CONSTRUCTOR
Wall::Wall(int x, int y, GLuint* t) {
    xPos = x;
    yPos = y;
    width = height = 50;
    tex = t;
}

//DESTRUCTOR
Wall::~Wall() {}

//FUNCTIONS
/*update the wall*/
void Wall::update() {}

/*draw the wall*/
void Wall::draw(int offsetX, int offsetY) {
    glBindTexture(GL_TEXTURE_2D, *tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(xPos+offsetX, yPos+offsetY, -0.0039);
    glTexCoord2f(0.0, 1.0); glVertex3f(xPos+offsetX, yPos+height+offsetY, -0.0039);
    glTexCoord2f(1.0, 1.0); glVertex3f(xPos+width+offsetX, yPos+height+offsetY, -0.0039);
    glTexCoord2f(1.0, 0.0); glVertex3f(xPos+width+offsetX, yPos+offsetY, -0.0039);
    glEnd();
}
