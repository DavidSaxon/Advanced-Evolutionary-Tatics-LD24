#include "Engine.hpp"

//FUNCTIONS
/*updates the current level*/
void Engine::levelUpdate(int framesPassed) {
    vector<Entity*> newAttacks; //the new attacks
    vector<Entity*> remove; //entities to remove
    //if the mouse is released find the entities in the dragbox
    if(leftReleased) {
        vector<Entity*>::iterator q;
        for (q = units.begin(); q != units.end(); ++q) {
            (*q)->mouseOn(mouseStartX, mouseStartY, mouseX, mouseY);
        }
        leftReleased = false;
    }

    //if the left mouse is pressed then deselect all player units
    if (leftPressed) {
        vector<Entity*>::iterator q;
        for (q = units.begin(); q != units.end(); ++q) {
            if ((*q)->mouseOn(mouseX, mouseY)) (*q)->selected = true;
            else (*q)->deselect();
        }
        leftPressed = false;
    }

    //if the right is pressed move the selected units to the destination*/
    if (rightPressed) {
        //first check if the destination is a enemy unit
        vector<Entity*>::iterator q;
        Entity* target = NULL;
        for (q = units.begin(); q != units.end(); ++q) {
            if ((*q)->mouseOn(mouseX, mouseY) && !(*q)->player) target = (*q);
        }

        for (q = units.begin(); q != units.end(); ++q) {
            if ((*q)->selected) {
                if (target == NULL) (*q)->setDest(mouseX, mouseY);
                else (*q)->target = target;
            }
        }
        rightPressed = false;
    }

    //update everything passed on the number of frames passed
    for(int i = 0; i < framesPassed; ++i) {
        //Handle Collisons
        vector<Entity*>::iterator q;
        for (q = units.begin(); q != units.end();) {
            //iterate through all walls to see if they are colliding
            vector<Entity*>::iterator p;
            for (p = backgrounds.begin(); p != backgrounds.end(); ++p) {
                if ((*q)->collision((*p)->getX(), (*p)->getY(), (*p)->getW(), (*p)->getH()))
                    (*q)->stop();
            }
            //iterate through the walls to see if they are colliding
            for (p = buildings.begin(); p != buildings.end(); ++p) {
                if ((*q)->collision((*p)->getX(), (*p)->getY(), (*p)->getW(), (*p)->getH()))
                    (*q)->stop();
            }
            //iterate through the other units to see if they are colliding
            for (p = units.begin(); p != units.end(); ++p) {
                if ((*q) != (*p) && (*q)->collision((*p)->getX(), (*p)->getY(), (*p)->getW(), (*p)->getH())) {
                        (*q)->pushAway((*p));
                    }
            }
            //iterate through attacks to see if they are colliding
            for (p = attacks.begin(); p != attacks.end();) {
                if ((*q)->player != (*p)->player && (*q)->collision((*p)->getX()-12, (*p)->getY()-12, (*p)->getW()+24, (*p)->getH()+24)) {
                    (*q)->health = (*q)->health-(*p)->damage;
                    p = attacks.erase(p);
                    if ((*q)->health < 1) q = units.erase(q);
                }
                else ++p;
            }
        
            if (q != units.end()) ++q;
        }

        //update everything
        for (q = units.begin(); q != units.end(); ++q) {
            if ((*q)->attackFlag) { //if attacking create attack
                int x1 = (*q)->getX();
                int y1 = (*q)->getY();
                int x2 = (*q)->target->getX();
                int y2 = (*q)->target->getY();
                if ((*q)->attackType == 0) newAttacks.push_back(new Attack(x1, y1, x2, y2, 0, (*q)->player, &attackSmallTex));
                (*q)->attackFlag = false;
            }
            (*q)->update();
        }
        for (q = attacks.begin(); q != attacks.end();) {
            (*q)->update();
            if ((*q)->dead) q = attacks.erase(q);
            else ++q;
        }
    }

    drawBackground();

    //now draw everything else
    vector<Entity*>::iterator q;
    for (q = backgrounds.begin(); q != backgrounds.end(); ++q) {
        (*q)->draw(0, 0); //TODO: use proper offset
    }
    for (q = buildings.begin(); q != buildings.end(); ++q) {
        (*q)->draw(0, 0); //TODO: use proper offset
    }
    for (q = units.begin(); q != units.end(); ++q) {
        (*q)->draw(0, 0); //TODO: use proper offset
    }
    for (q = attacks.begin(); q != attacks.end(); ++q) {
        (*q)->draw(0, 0); //TODO: use proper offset
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

    //add the new attacks
    if (newAttacks.size() > 0) {
       vector<Entity*>::iterator v;
        for (v = newAttacks.begin(); v != newAttacks.end(); ++v) {
            attacks.push_back(*v);
        }
    }

    //remove dead entities
    /*vector<Entity*>::iterator r;
    for (r = remove.begin(); r != remove.end(); ++r) {
        attacks.erase(r);
    }*/
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

/*loads the level*/
void Engine::loadLevel() {
    for (int i = 0; i < LEVEL_ENTITIES; ++i) { //create each vector
        entities.insert(pair<int, vector<Entity*>*>(i, new vector<Entity*>()));
    }

    //add the entities
    //add units
    units.push_back(new Unit(50, 50, true, softBodySmallTex));
    units.push_back(new Unit(200, 200, true, softBodySmallTex));
    units.push_back(new Unit(1000, 500, false, softBodySmallTex));
    //add buildings
    buildings.push_back(new Nexus(500, 500, true, &nexusBodyTex, &nexusBlueTex));
    //add backgrounds
    backgrounds.push_back(new Wall(400, 200, &rockTex));
}
