#include "Engine.hpp"

//FUNCTIONS
/*updates the current level*/
void Engine::levelUpdate(int framesPassed) {
    vector<Entity*> newAttacks; //the new attacks
    vector<Entity*> remove; //entities to remove

    if (upDown == 1) {
        if (offsetY < 0) offsetY += 5;
    }
    else if (upDown == 2) {
        if (offsetY > -515) offsetY -= 5;
    }
    if (leftRight == 1) {
        if (offsetX < 0) offsetX += 5;
    }
    else if (leftRight == 2) {
        if (offsetX > -1040) offsetX -= 5;
    }

    //if the mouse is released find the entities in the dragbox
    if(leftReleased) {
        vector<Entity*>::iterator q;
        for (q = units.begin(); q != units.end(); ++q) {
            (*q)->mouseOn(mouseStartX-offsetX, mouseStartY-offsetY, mouseX-offsetX, mouseY-offsetY);
        }
        leftReleased = false;
    }

    //if the left mouse is pressed then deselect all player units
    if (leftPressed) {
        vector<Entity*>::iterator q;
        for (q = units.begin(); q != units.end(); ++q) {
            if ((*q)->player && (*q)->mouseOn(mouseX-offsetX, mouseY-offsetY)) (*q)->selected = true;
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
            if ((*q)->mouseOn(mouseX-offsetX, mouseY-offsetY) && !(*q)->player) target = (*q);
        }

        for (q = units.begin(); q != units.end(); ++q) {
            if ((*q)->selected) {
                if (target == NULL) (*q)->setDest(mouseX-offsetX, mouseY-offsetY);
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
                else if ((*q)->attackType == 1) newAttacks.push_back(new Attack(x1, y1, x2, y2, 1, (*q)->player, &attackMedTex));
                else if ((*q)->attackType == 2) newAttacks.push_back(new Attack(x1, y1, x2, y2, 2, (*q)->player, &attackLargeTex));
                (*q)->attackFlag = false;
            }
            if (!(*q)->player) {
                int attackC = rand()%20;
                vector<Entity*>::iterator z;
                for (z = units.begin(); z != units.end(); ++z) {
                    if (rand()%20 == attackC && (*z)->player) (*q)->target = (*z);
                }
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
        (*q)->draw(offsetX, offsetY);
    }
    for (q = buildings.begin(); q != buildings.end(); ++q) {
        (*q)->draw(offsetX, offsetY);
    }
    for (q = units.begin(); q != units.end(); ++q) {
        (*q)->draw(offsetX, offsetY);
    }
    for (q = attacks.begin(); q != attacks.end(); ++q) {
        (*q)->draw(offsetX, offsetY);
    }


    //draw the ui bar
    glBindTexture(GL_TEXTURE_2D, barTex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(0, 465, -0.0005);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 540, -0.0005);
    glTexCoord2f(1.0, 0.0); glVertex3f(960, 540, -0.0005);
    glTexCoord2f(1.0, 1.0); glVertex3f(960, 465, -0.0005);
    glEnd();

    //draw player money
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glRasterPos2i(900, 25); //set the raster position
    void* font = GLUT_BITMAP_TIMES_ROMAN_24;
    stringstream ss;
    ss << "$" << money;
    string text = ss.str();
    for (string::iterator i = text.begin(); i != text.end(); ++i) { //iterate through each letter and draw it
        char c = *i;
        glutBitmapCharacter(font, c);
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

    int csp = rand()%2000;
    if (csp == 1 && comLow > 10) {
        comLow -= 3;
        comMed -= 2;
        --comHigh;
    }
    else if (csp >= 1996) {
        buildUnit(false);
    }

    //addmoney
    if (moneyCounter == 0) {
        ++money;
        moneyCounter = moneyWait;
    }
    else --moneyCounter;
}

/*Draw the level background*/
void Engine::drawBackground() {
    for (int i = -200; i < NATURAL_RESO_X*2+600; i += 128) {
        for (int j = -200; j < NATURAL_RESO_Y*2+600; j += 128) {
            glBindTexture(GL_TEXTURE_2D, backgroundTex);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(i+offsetX, j+offsetY, -0.004);
            glTexCoord2f(0.0, 1.0); glVertex3f(i+offsetX, j+128+offsetY, -0.004);
            glTexCoord2f(1.0, 1.0); glVertex3f(i+128+offsetX, j+128+offsetY, -0.004);
            glTexCoord2f(1.0, 0.0); glVertex3f(i+128+offsetX, j+offsetY, -0.004);
            glEnd();
        }
    }
}

void Engine::buildUnit(bool pl) {
    if (pl) {
        if (money >= 50) {
            Body* b;
            Leg* l;
            Fang* f;
            Eye* e;
            int chance = (rand()%50)+1;
            if (chance >= medChance) b = armoredBodySmall;
            else if (chance >= lowChance) b = exoBodySmall;
            else b = squishyBodySmall;
            chance = (rand()%50)+1;
            if (chance >= highChance) l = rocket;
            else if (chance >= medChance) l = wheel;
            else if (chance >= lowChance) l = leg6;
            else l = leg4;
            chance = (rand()%50)+1;
            if (chance >= medChance) f = heavy;
            else if (chance >= lowChance) f = med;
            else f = light;
            chance = (rand()%50)+1;
            if (chance >= highChance) e = allSee;
            else if (chance >= medChance) e = ant;
            else if (chance >= lowChance) e = norm;
            else e = squint;

            units.push_back(new Unit(playerSpawnX, playerSpawnY, true, b, l, f, e, &blueTex));

            money -= 50;
        }
    }
    else {
        Body* b;
        Leg* l;
        Fang* f;
        Eye* e;
        int chance = (rand()%50)+1;
        if (chance >= comMed) b = armoredBodySmall;
        else if (chance >= comLow) b = exoBodySmall;
        else b = squishyBodySmall;
        chance = (rand()%50)+1;
        if (chance >= comHigh) l = rocket;
        else if (chance >= comMed) l = wheel;
        else if (chance >= comLow) l = leg6;
        else l = leg4;
        chance = (rand()%50)+1;
        if (chance >= comMed) f = heavy;
        else if (chance >= comLow) f = med;
        else f = light;
        chance = (rand()%50)+1;
        if (chance >= comHigh) e = allSee;
        else if (chance >= comMed) e = ant;
        else if (chance >= comLow) e = norm;
        else e = squint;

        units.push_back(new Unit(comSpawnX, comSpawnY, false, b, l, f, e, &redTex));
    }
}

/*loads the level*/
void Engine::loadLevel() {
    //create body parts
    squishyBodySmall = new Body(25, 20, &softBodySmallTex);
    exoBodySmall = new Body(25, 50, &exoBodySmallTex);
    armoredBodySmall = new Body(25, 100, &armoredBodySmallTex);
    leg4 = new Leg(2, &leg4Tex);
    leg6 = new Leg(4, &leg6Tex);
    wheel = new Leg(6, &wheelTex);
    rocket = new Leg(25, &rocketTex);
    light = new Fang(0, &lightTex);
    med = new Fang(1, &medTex);
    heavy = new Fang(2, &heavyTex);
    squint = new Eye(100, &squintTex);
    norm = new Eye(200, &normTex);
    ant = new Eye(300, &antTex);
    allSee = new Eye(1000, &allSeeTex);

    //create entities
    //add units
    units.push_back(new Unit(300, 50, true, squishyBodySmall, leg6, light, squint, &blueTex));
    units.push_back(new Unit(300, 300, true, squishyBodySmall, leg4, med, squint, &blueTex));
    units.push_back(new Unit(50, 300, true, exoBodySmall, leg4, light, norm, &blueTex));

    units.push_back(new Unit(1700, 950, false, squishyBodySmall, leg6, light, squint, &redTex));
    units.push_back(new Unit(1700, 700, false, squishyBodySmall, leg4, med, squint, &redTex));
    units.push_back(new Unit(1950, 650, false, exoBodySmall, leg4, light, norm, &redTex));
    //add buildings
    buildings.push_back(new Nexus(0, 0, true, &nexusBodyTex, &nexusBlueTex));
    playerSpawnX = playerSpawnY = 210;
    buildings.push_back(new Nexus(1800, 800, false, &nexusBodyTex, &nexusRedTex));
    comSpawnX = 1790;
    comSpawnY = 790;
    //add backgrounds
    backgrounds.push_back(new Wall(400, 0, &rockTex));
    backgrounds.push_back(new Wall(400, 50, &rockTex));
    backgrounds.push_back(new Wall(400, 100, &rockTex));
    backgrounds.push_back(new Wall(400, 150, &rockTex));
    backgrounds.push_back(new Wall(400, 200, &rockTex));
    backgrounds.push_back(new Wall(400, 250, &rockTex));

    backgrounds.push_back(new Wall(0, 400, &rockTex));
    backgrounds.push_back(new Wall(50, 400, &rockTex));
    backgrounds.push_back(new Wall(100, 400, &rockTex));
    backgrounds.push_back(new Wall(150, 400, &rockTex));
    backgrounds.push_back(new Wall(200, 400, &rockTex));
    backgrounds.push_back(new Wall(250, 400, &rockTex));

    backgrounds.push_back(new Wall(1600, 950, &rockTex));
    backgrounds.push_back(new Wall(1600, 900, &rockTex));
    backgrounds.push_back(new Wall(1600, 850, &rockTex));
    backgrounds.push_back(new Wall(1600, 800, &rockTex));
    backgrounds.push_back(new Wall(1600, 750, &rockTex));
    backgrounds.push_back(new Wall(1600, 700, &rockTex));

    backgrounds.push_back(new Wall(1950, 600, &rockTex));
    backgrounds.push_back(new Wall(1900, 600, &rockTex));
    backgrounds.push_back(new Wall(1850, 600, &rockTex));
    backgrounds.push_back(new Wall(1800, 600, &rockTex));
    backgrounds.push_back(new Wall(1750, 600, &rockTex));
    backgrounds.push_back(new Wall(1700, 600, &rockTex));

    backgrounds.push_back(new Wall(950, 450, &rockTex));
    backgrounds.push_back(new Wall(1000, 450, &rockTex));
    backgrounds.push_back(new Wall(1000, 500, &rockTex));
    backgrounds.push_back(new Wall(950, 500, &rockTex));

    backgrounds.push_back(new Wall(543, 234, &rockTex));
    backgrounds.push_back(new Wall(845, 52, &rockTex));
    backgrounds.push_back(new Wall(234, 800, &rockTex));
    backgrounds.push_back(new Wall(460, 900, &rockTex));
    backgrounds.push_back(new Wall(357, 742, &rockTex));
    backgrounds.push_back(new Wall(0, 641, &rockTex));
    backgrounds.push_back(new Wall(160, 769, &rockTex));
    backgrounds.push_back(new Wall(504, 543, &rockTex));
    backgrounds.push_back(new Wall(1600, 0, &rockTex));
    backgrounds.push_back(new Wall(500, 150, &rockTex));
    backgrounds.push_back(new Wall(1800, 450, &rockTex));
    backgrounds.push_back(new Wall(800, 500, &rockTex));
    backgrounds.push_back(new Wall(453, 240, &rockTex));
    backgrounds.push_back(new Wall(1400, 12, &rockTex));
    backgrounds.push_back(new Wall(600, 342, &rockTex));
    backgrounds.push_back(new Wall(1700, 298, &rockTex));
    backgrounds.push_back(new Wall(1200, 292, &rockTex));
    //backgrounds.push_back(new Wall(500, 431, &rockTex));
    backgrounds.push_back(new Wall(1500, 500, &rockTex));
    backgrounds.push_back(new Wall(1500, 900, &rockTex));
    backgrounds.push_back(new Wall(950, 850, &rockTex));
    backgrounds.push_back(new Wall(800, 650, &rockTex));
    backgrounds.push_back(new Wall(1000, 800, &rockTex));
    backgrounds.push_back(new Wall(1500, 750, &rockTex));
    backgrounds.push_back(new Wall(1100, 950, &rockTex));
}
