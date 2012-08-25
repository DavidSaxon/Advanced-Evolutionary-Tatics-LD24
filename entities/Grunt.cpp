#include "Grunt.hpp"

//CONSTRUCTOR
Grunt::Grunt(int x, int y, bool p) {
    xPos = x;
    yPos = y;
    player = p;
}

//DESTRUCTOR
Grunt::~Grunt() {}

//FUNCTIONS
/*updates the grunt*/
void Grunt::update() {
    ++xPos;
}

/*draws the grunt*/
void Grunt::draw(int offsetX, int offsetY) {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(xPos, yPos);
    glVertex2f(xPos+50, yPos);
    glVertex2f(xPos+50, yPos+50);
    glVertex2f(xPos, yPos+50);
    glEnd();
}
