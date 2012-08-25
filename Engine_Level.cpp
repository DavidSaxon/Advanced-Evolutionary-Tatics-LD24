#include "Engine.hpp"

//FUNCTIONS
/*updates the current level*/
void Engine::levelUpdate(int framesPassed) {
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
}
