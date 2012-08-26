#include "Nexus.hpp"

//CONSTRUCTOR
Nexus::Nexus(int x, int y, bool p) {
    xPos = x;
    yPos = y;
    player = p;
    width = height = 200;
}

//DESTRUCTOR
Nexus::~Nexus() {}

//FUNCTIONS
/*update the nexus*/
void Nexus::update() {
    
}

/*draw the nexus*/
void Nexus::draw(int offsetX, int offsetY) {
    glColor4d(0.0, 0.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(xPos, yPos);
    glVertex2f(xPos+200, yPos);
    glVertex2f(xPos+200, yPos+200);
    glVertex2f(xPos, yPos+200);
    glEnd();
}


