#include "Engine.hpp"

//CONSTRUCTOR
Engine::Engine() {}

//DESTRUCTOR
Engine::~Engine() {}

//FUNCTIONS
/*Initialise the game*/
bool Engine::init() {
    //initialise variables
    running = true;
    gameState = LEVEL; //TODO: change to MENU in final
    levelName = "data/levels/test.lvl";
    mouseX = 0;
    mouseY = 0;
    leftMouseDown = false;
    rightMouseDown = false;
    leftPressed = false;
    leftReleased = false;
    rightPressed = false;
    rightReleased = false;
    mouseStartX = 0;
    mouseStartY = 0;
    frameRate = 60;
    framesPassed = 0;

    //initialise sdl
    initSDL();

    //open the window
    const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo(); //get the video info
    int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_FULLSCREEN; //sets the window flags
    if(videoInfo->hw_available) flags |= SDL_HWSURFACE; //check to see if hardware surfaces are enabled
    else flags |= SDL_SWSURFACE;
    if(videoInfo->blit_hw) flags |= SDL_HWACCEL; //check to see if hardware supports blitting
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if ((display = SDL_SetVideoMode(0, 0, 32, flags)) == NULL) return false; //sets up the video mode

    //initialise opengl
    initGL();

    //get the width and height
    width = display->w;
    height = display->h;
    
    //find the scale
    scaleX = NATURAL_RESO_X/(float) width;
    scaleY = NATURAL_RESO_Y/(float) height;

    loadLevel(); //TODO: remove this from here

    return true; //everything is initialised
}

/*Initialises SDL*/
bool Engine::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    return true; //sdl has been initialised
}

/*Initialise openGL*/
bool Engine::initGL() {
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1920, 1080, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();

    return true; //openGL has been initialised
}

/*Run the main game loop*/
bool Engine::execute() {
    SDL_Event event; //creates a new event
    int startTime = getMilliCount();
    int lastTime = startTime;

    //start the main game loop
    while (running) {
        //handle fps
        framesPassed = 0;
        if (getMilliSpan(lastTime) > 16) { //if a frame has passed
            framesPassed = getMilliSpan(lastTime)/16; //gets the number of frames passed
            lastTime += framesPassed*(16);
        }

        while (SDL_PollEvent(&event)) onEvent(&event); //polls the events

        //clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //checks to see what state the game is in
        switch (gameState) {
            case MENU:
                break;
            case LEVEL: //update the level
                levelUpdate(framesPassed);
                break;
        }

        //Swap the buffers
        SDL_GL_SwapBuffers();
    }

    return true; //the game has finished running
}

/*Cleanup the game*/
bool Engine::cleanup() {
    SDL_FreeSurface(display); //Remove the display window

    return true; //cleanup has compeleted
}

//get the current time in milliseconds
int Engine::getMilliCount() {
	timeb tb;
	ftime(&tb);
	int count = tb.millitm+(tb.time & 0xfffff)*1000;
    return count;
}

//get the span of time since millicount
int Engine::getMilliSpan(int timeStart) {
	int span = getMilliCount()-timeStart;
	//if(span < 0) span += 0x100000*1000;
	return span;
}
