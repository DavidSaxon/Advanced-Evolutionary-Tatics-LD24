/*****************************************************************************\
| The Engine of AET, opens the window handles events and contains all objects |
| Also handles fps and loading of resources                                   |
\*****************************************************************************/
#ifndef _ENGINE_H_
    #define _ENGINE_H_

#include <iostream>
#include <vector>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Define.hpp"
#include "Event.hpp"
#include "Entity.hpp"
#include "entities/Grunt.hpp"
using namespace std;

class Engine : public Event {
//MAIN
private:

    //VARIABLES
    bool running; //is true while the game is running
    int gameState; //holds the game state
    SDL_Surface* display; //the game window
    int width; //the width of the window
    int height; //the height of the window
    int mouseX; //the x position of  the mouse
    int mouseY; //the y position of the mouse
    bool leftMouseDown; //is true when the left mouse is down
    bool rightMouseDown; //is true when the right mouse is down
    bool leftPressed; //is true when the left is first pressed
    bool leftReleased; //is true just after the left is released
    bool rightPressed; //is true when the right is first pressed
    bool rightReleased; //is true just after the right is released
    int mouseStartX; //where the mouse is first pressed
    int mouseStartY;

public:

    //CONSTRUCTOR
    Engine();

    //DESTRUCTOR
    ~Engine();

    //FUNCTIONS
    /*Initialises the game*/
    bool init();

    /*Initialises SDL*/
    bool initSDL();

    /*Initialises openGL*/
    bool initGL();

    /*Run the main game loop*/
    bool execute();

    /*Cleanup the game*/
    bool cleanup();
    
//LEVEL
private:

    //VARIABLES
    string levelName; //the name of the current level    /*loads the level from a file*/
    map <int, vector<Entity*>*> entities; //a map that holds all the entites in the game in their respective groups
    
    
public:
    
    //FUNCTIONS
    /*updates the current level*/
    void levelUpdate(int framesPassed);
    
    /*loads the level from a file*/
    void loadLevel();

//EVENT
public:

    //FUNCTIONS
    /*Handles events*/
    void onEvent(SDL_Event* event);

    /*When the exit button is pressed*/
    void onExit();

    /*When a key is pressed down*/
    void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    
    /*When the mouse is moved*/
    void onMouseMove(int mX, int mY, int relX, int relY, bool left,bool right,bool middle);
    
    /*When the left mouse button is pressed*/
    void onLButtonDown(int mX, int mY);

    /*When the left mouse button is released*/
    void onLButtonUp(int mX, int mY);
    
    /*When the right mouse button is pressed*/
    void onRButtonDown(int mX, int mY);
    
    /*When the right button is released*/
    void onRButtonUp(int mX, int mY);

};

#endif
