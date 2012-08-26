#include "Wall.hpp"

//CONSTRUCTOR
Wall::Wall(int x, int y) {
    xPos = x;
    yPos = y;
    width = height = 50;
}

//DESTRUCTOR
Wall::~Wall() {}

//FUNCTIONS
/*update the wall*/
void Wall::update() {}

/*draw the wall*/
void Wall::draw(int offsetX, int offsetY) {
    glColor4d(1.0, 1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(xPos, yPos);
    glVertex2f(xPos+50, yPos);
    glVertex2f(xPos+50, yPos+50);
    glVertex2f(xPos, yPos+50);
    glEnd();
}
