#include "Grunt.hpp"

//CONSTRUCTOR
Grunt::Grunt(int x, int y, bool p) {
    xPos = x;
    yPos = y;
    player = p;

    //initialise variables
    width = 25;
    height = 25;
    selected = false;
}

//DESTRUCTOR
Grunt::~Grunt() {}

//FUNCTIONS
/*updates the grunt*/
void Grunt::update() {
    
}

/*draws the grunt*/
void Grunt::draw(int offsetX, int offsetY) {
    glColor4d(0.5, 0.2, 0.1, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(xPos, yPos);
    glVertex2f(xPos+25, yPos);
    glVertex2f(xPos+25, yPos+25);
    glVertex2f(xPos, yPos+25);
    glEnd();

    if (selected) { //if the unit is selected draw the slected box
        glColor4d(1.0, 1.0, 0.0, 1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xPos-3, yPos-3);
        glVertex2f(xPos+width+4, yPos-3);
        glVertex2f(xPos+width+4, yPos+height+4);
        glVertex2f(xPos-3, yPos+height+4);
        glEnd();
    }
}

/*Selects the unit if the mouse is on*/
bool Grunt::mouseOn(int mouseStartX, int mouseStartY, int mouseX, int mouseY) {
    //set up the drag box coords
    int dbx1, dbx2, dby1, dby2 = 0;
    if (mouseStartX <= mouseX) {
        dbx1 = mouseStartX;
        dbx2 = mouseX;
    }
    else {
        dbx1 = mouseX;
        dbx2 = mouseStartX;
    }
    if (mouseStartY <= mouseY) {
        dby1 = mouseStartY;
        dby2 = mouseY;
    }
    else {
        dby1 = mouseY;
        dby2 = mouseStartY;
    }

    if (((xPos > dbx1 && xPos) && (xPos+width > dbx1 && xPos+width < dbx2)) &&
        ((yPos > dby1 && yPos < dby2) && (yPos+height > dby1 && yPos+height < dby2))
        && player) selected = true;
}

/*Deselects the unit*/
void Grunt::deselect() {
    selected = false;
}
