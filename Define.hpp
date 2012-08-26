/**********************************************\
| Defines overall fields and enums of the game |
\**********************************************/
#ifndef _DEFINE_H_
    #define _DEFINE_H_

//DEFINES
#define NATURAL_RESO_X 1920
#define NATURAL_RESO_Y 1080

#define LEVEL_ENTITIES 3 //the number of entity types in the level state

//ENUMARTORS
//Game States
enum {
    MENU = 0,
    LEVEL
};

//Level entity types
enum {
    BACKGROUND = 0,
    UNIT,
    BUILDING
};

#endif
