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

    //if the left mouse is pressed then deselect all player units
    if (leftPressed) {
        vector<Entity*>::iterator q;
        for (q = entities[UNIT]->begin(); q != entities[UNIT]->end(); ++q) {
            (*q)->deselect();
        }
        leftPressed = false;
    }

    //if the right is pressed move the selected units to the destination*/
    if (rightPressed) {
        vector<Entity*>::iterator q;
        for (q = entities[UNIT]->begin(); q != entities[UNIT]->end(); ++q) {
            if ((*q)->selected) (*q)->setDest(mouseX, mouseY);
        }
        rightPressed = false;
    }

    //update everything passed on the number of frames passed
    for(int i = 0; i < framesPassed; ++i) {
        //Handle Collisons
        vector<Entity*>::iterator q;
        for (q = entities[UNIT]->begin(); q != entities[UNIT]->end(); ++q) {
            //iterate through all walls to see if they are colliding
            vector<Entity*>::iterator p;
            for (p = entities[BACKGROUND]->begin(); p != entities[BACKGROUND]->end(); ++p) {
                if ((*q)->collision((*p)->getX(), (*p)->getY(), (*p)->getW(), (*p)->getH()))
                    (*q)->stop();
            }
            //iterate through the walls to see if they are colliding
            for (p = entities[BUILDING]->begin(); p != entities[BUILDING]->end(); ++p) {
                if ((*q)->collision((*p)->getX(), (*p)->getY(), (*p)->getW(), (*p)->getH()))
                    (*q)->stop();
            }
            //iterate through the other units to see if they are colliding
            for (p = entities[UNIT]->begin(); p != entities[UNIT]->end(); ++p) {
                if ((*q) != (*p) && (*q)->collision((*p)->getX(), (*p)->getY(), (*p)->getW(), (*p)->getH())) {
                        (*q)->pushAway((*p));
                    }
            }
        }

        //update everything
        for (int j = 0; j < LEVEL_ENTITIES; ++j) {
            vector<Entity*>::iterator q;
            for (q = entities[j]->begin(); q != entities[j]->end(); ++q) {
                (*q)->update();
            }
        }
    }

    drawBackground();

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
        glBindTexture(GL_TEXTURE_2D, 0);
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

/*Draw the level background*/
void Engine::drawBackground() {
    for (int i = -200; i < NATURAL_RESO_X+200; i += 128) {
        for (int j = -200; j < NATURAL_RESO_Y+200; j += 128) {
            glBindTexture(GL_TEXTURE_2D, backgroundTex);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(i, j, -0.004);
            glTexCoord2f(0.0, 1.0); glVertex3f(i, j+128, -0.004);
            glTexCoord2f(1.0, 1.0); glVertex3f(i+128, j+128, -0.004);
            glTexCoord2f(1.0, 0.0); glVertex3f(i+128, j, -0.004);
            glEnd();
        }
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
            else if (line.substr(1, 4)  == "BUIL") currentLoad = BUILDING; //read units

            //create a new vector for the current load type
            entities.insert(pair<int, vector<Entity*>*>(currentLoad, new vector<Entity*>()));
        }
    }

    //FIXME: just for testing currently
    entities[UNIT]->push_back(new Unit(50, 50, true, softBodySmallTex));
    entities[UNIT]->push_back(new Unit(200, 200, true, softBodySmallTex));
    entities[UNIT]->push_back(new Unit(1000, 500, false, softBodySmallTex));
    entities[BUILDING]->push_back(new Nexus(500, 500, true, &nexusBodyTex, &nexusBlueTex));
    entities[BACKGROUND]->push_back(new Wall(400, 200, &rockTex));
}
