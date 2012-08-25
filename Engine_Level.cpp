#include "Engine.hpp"

//FUNCTIONS
/*updates the current level*/
void Engine::levelUpdate(int framesPassed) {
    //if the mouse is released find the entities in the dragbox
    if(leftReleased) {
        vector<Entity*>::iterator q;
        for (q = entities[UNIT]->begin(); q != entities[UNIT]->end(); ++q) {
            (*q)->mouseOn(mouseStartX, mouseStartY, mouseX, mouseY);
        }
        leftReleased = false;
    }

    //if the right or left mouse is pressed then deselect all player units
    if (leftPressed) {
        vector<Entity*>::iterator q;
        for (q = entities[UNIT]->begin(); q != entities[UNIT]->end(); ++q) {
            (*q)->deselect();
        }
        leftPressed = false;
    }

    //update everything passed on the number of frames passed
    for(int i = 0; i < framesPassed; ++i) {
        for (int j = 0; j < LEVEL_ENTITIES; ++j) {
            vector<Entity*>::iterator q;
            for (q = entities[j]->begin(); q != entities[j]->end(); ++q) {
                (*q)->update();
            }
        }
    }

    //now draw everything
    for (int j = 0; j < LEVEL_ENTITIES; ++j) {
        vector<Entity*>::iterator q;
        for (q = entities[j]->begin(); q != entities[j]->end(); ++q) {
            (*q)->draw(0, 0); //TODO: use proper offset
        }
    }

    //draw the drag box
    if (leftMouseDown) {
        //set up the drag box coords
        int dbx1, dbx2, dby1, dby2 = 0;
        if (mouseStartX <= mouseX) {
            dbx1 = mouseStartX;
            dbx2 = mouseX-dbx1;
        }
        else {
            dbx1 = mouseX;
            dbx2 = mouseStartX-dbx1;
        }
        if (mouseStartY <= mouseY) {
            dby1 = mouseStartY;
            dby2 = mouseY-dby1;
        }
        else {
            dby1 = mouseY;
            dby2 = mouseStartY-dby1;
        }
        glColor4d(0.0, 0.0, 1.0, 0.3);
        //draw the centre part
        glBegin(GL_QUADS);
        glVertex2f(dbx1, dby1);
        glVertex2f(dbx1+dbx2, dby1);
        glVertex2f(dbx1+dbx2, dby1+dby2);
        glVertex2f(dbx1, dby1+dby2);
        glEnd();
        //draw the outline
        glBegin(GL_LINE_LOOP);
        glVertex2f(dbx1, dby1);
        glVertex2f(dbx1+dbx2, dby1);
        glVertex2f(dbx1+dbx2, dby1+dby2);
        glVertex2f(dbx1, dby1+dby2);
        glEnd();
    }
}

/*loads the level from a file*/
void Engine::loadLevel() {
    const char* file = levelName.c_str();
    FILE* fileHandle = fopen(file, "r");
    int currentLoad = 0; //the current entity type to load

    while (!feof(fileHandle)) {
        char charLine[1000];
        fgets(charLine, 1000, fileHandle); //gets the current line of the file
        string line = charLine;

        if (line.at(0) == '#') { //the line is an entity tag
            if (line.substr(1, 4)  == "BACK") currentLoad = BACKGROUND; //read the background
            else if (line.substr(1, 4)  == "UNIT") currentLoad = UNIT; //read units

            //create a new vector for the current load type
            entities.insert(pair<int, vector<Entity*>*>(currentLoad, new vector<Entity*>()));
        }
    }

    //FIXME: just for testing currently
    entities[UNIT]->push_back(new Grunt(50, 50, true));
    entities[UNIT]->push_back(new Grunt(200, 200, true));
    entities[UNIT]->push_back(new Grunt(150, 400, false));
}
