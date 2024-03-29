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
    gameState = MENU;
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
    money = 0;
    comLow = lowChance = 25;
    comMed = medChance = 40;
    highChance = 48;
    comHigh = 100000; //computer gets no chance for high evolutions because he is a total dick with them
    moneyCounter = moneyWait = 5;
    offsetX = offsetY = 0;
    upDown = leftRight = 0;
    

    //initialise sdl
    initSDL();

    //open the window
    const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo(); //get the video info
    int flags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE| SDL_FULLSCREEN; //sets the window flags
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

    //LoadTextures
    loadTextures();

    sound = Mix_LoadWAV("data/music/Intro-Menu.wav");
    if(sound == NULL) {
        fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
    }
     
    introChannel = Mix_PlayChannel(-1, sound, -1);
    if(introChannel == -1) {
	    fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
    }

    return true; //everything is initialised
}

/*Initialises SDL*/
bool Engine::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) < 0) return false;
    
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
        exit(1);
    }
    
    return true; //sdl has been initialised
    
}

/*Initialise openGL*/
bool Engine::initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 960, 540, 0, 0, 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_TEXTURE_2D);

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
                menu();
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

void Engine::menu() {
    glBindTexture(GL_TEXTURE_2D, menuTex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex3f(0, 0, -0.0005);
    glTexCoord2f(0.0, 0.0); glVertex3f(0, 540, -0.0005);
    glTexCoord2f(1.0, 0.0); glVertex3f(960, 540, -0.0005);
    glTexCoord2f(1.0, 1.0); glVertex3f(960, 0, -0.0005);
    glEnd();
}

/*Cleanup the game*/
bool Engine::cleanup() {
    SDL_FreeSurface(display); //Remove the display window
    Mix_FreeChunk(sound);
    Mix_CloseAudio();
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
