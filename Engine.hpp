/*****************************************************************************\
| The Engine of AET, opens the window handles events and contains all objects |
| Also handles fps and loading of resources                                   |
\*****************************************************************************/
#ifndef _ENGINE_H_
    #define _ENGINE_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <sys/timeb.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_opengl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <png.h>

#include "Define.hpp"
#include "Event.hpp"
#include "Body.hpp"
#include "Leg.hpp"
#include "Fang.hpp"
#include "Eye.hpp"
#include "Entity.hpp"
#include "entities/Unit.hpp"
#include "entities/Nexus.hpp"
#include "entities/Wall.hpp"
#include "entities/Attack.hpp"
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
    double scaleX; //the x scale
    double scaleY; //the y scale
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
    int frameRate; //the max frame rate of the game
    int framesPassed; //the number of frames passed since the last loop
    Mix_Chunk* sound;
    int upDown;
    int leftRight;
    int introChannel;
    
    //FUNCTIONS
    //get the current time in milliseconds
    int getMilliCount();

    //get the span of time since millicount
    int getMilliSpan(int timeStart);

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
    
    void menu();

//LEVEL
private:

    //VARIABLES
    string levelName; //the name of the current level    /*loads the level from a file*/
    vector<Entity*> units;
    vector<Entity*> backgrounds;
    vector<Entity*> buildings;
    vector<Entity*> attacks;
    int playerSpawnX;
    int playerSpawnY;
    int comSpawnX;
    int comSpawnY;
    int money;
    int lowChance;
    int medChance;
    int highChance;
    int comLow;
    int comMed;
    int comHigh;
    int moneyWait;
    int moneyCounter;
    int offsetX;
    int offsetY;

    //body parts
    Body* squishyBodySmall;
    Body* exoBodySmall;
    Body* armoredBodySmall;
    Leg* leg4;
    Leg* leg6;
    Leg* wheel;
    Leg* rocket;
    Fang* light;
    Fang* med;
    Fang* heavy;
    Eye* squint;
    Eye* norm;
    Eye* ant;
    Eye* allSee;


public:

    //FUNCTIONS
    /*updates the current level*/
    void levelUpdate(int framesPassed);

    /*Draw the level background*/
    void drawBackground();

    /*loads the level from a file*/
    void loadLevel();
    
    void buildUnit(bool pl);

//EVENT
public:

    //FUNCTIONS
    /*Handles events*/
    void onEvent(SDL_Event* event);

    /*When the exit button is pressed*/
    void onExit();

    /*When a key is pressed down*/
    void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    
    void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

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

//RESOURCES
private:

    //VARIABLES
    //images
    GLubyte *backgroundImg;
    GLubyte *rockImg;
    GLubyte *attackSmallImg;
    GLubyte *attackMedImg;
    GLubyte *attackLargeImg;
    GLubyte *nexusBodyImg;
    GLubyte *nexusBlueImg;
    GLubyte *nexusRedImg;
    GLubyte *softBodySmallImg;
    GLubyte *exoBodySmallImg;
    GLubyte *armoredBodySmallImg;
    GLubyte *leg4Img;
    GLubyte *leg6Img;
    GLubyte *wheelImg;
    GLubyte *rocketImg;
    GLubyte *lightImg;
    GLubyte *medImg;
    GLubyte *heavyImg;
    GLubyte *squintImg;
    GLubyte *normImg;
    GLubyte *antImg;
    GLubyte *allSeeImg;
    GLubyte *blueImg;
    GLubyte *redImg;
    GLubyte *barImg;
    GLubyte *menuImg;
    //textures
    GLuint backgroundTex;
    GLuint rockTex;
    GLuint attackSmallTex;
    GLuint attackMedTex;
    GLuint attackLargeTex;
    GLuint nexusBodyTex;
    GLuint nexusBlueTex;
    GLuint nexusRedTex;
    GLuint softBodySmallTex;
    GLuint exoBodySmallTex;
    GLuint armoredBodySmallTex;
    GLuint leg4Tex;
    GLuint leg6Tex;
    GLuint wheelTex;
    GLuint rocketTex;
    GLuint lightTex;
    GLuint medTex;
    GLuint heavyTex;
    GLuint squintTex;
    GLuint normTex;
    GLuint antTex;
    GLuint allSeeTex;
    GLuint blueTex;
    GLuint redTex;
    GLuint barTex;
    GLuint menuTex;

public:

    //FUNCTIONS
    /*Loads all the textures into memory*/
    void loadTextures();

    /*Loads a png image*/
    bool loadImage(char* name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

};

#endif
