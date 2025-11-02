#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "raylib.h"
#include "player.h"
#include "enemies.h"
#include "blocks.h"
#include "collisions.h"

//============================================
//-----------------STRUCTS--------------------

typedef struct GameWorld
{
    Player player;

    Enemies *enemies;
    int numberOfEnemies;

    Block *blocks;
    int numberOfBlocks;

    Camera2D camera;

}GameWorld;


//============================================
//----------------FUNCTIONS-------------------

    //-------CREATE-DESTROYS------

GameWorld* createGameWorld();

void destroysGameWorld (GameWorld *gw);

void loadMap (GameWorld *gw, const char* arquivo);

    //---------MAIN-FUNCTION---------

void inputAndUpdateGameWorld (GameWorld *gw);

    //--------COLLISIONS---------

void makeCollisionPlayerBlock (GameWorld *gw);

void makeCollisionEnemiesBlock (GameWorld *gw);

void makeCollisionEnemiesPlayer (GameWorld *gw);

void makeCollisionEnemiesWeapons (GameWorld *gw);

    //-------DRAW-AND-CAMERA-------

void drawGameWorld (GameWorld *gw);

void updateCamera (Camera2D *camera, Player *player);

#endif // GAMEWORLD_H
