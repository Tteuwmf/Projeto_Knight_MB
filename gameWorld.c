#include <stdlib.h>
#include "raylib.h"
#include "gameWorld.h"

#define GRAVIDADE 20.0
#define VEL_MAX_FALL 400.0

//================================================
//------------CREATE-DEFAULT-GAMEWORLD------------

GameWorld* createGameWorld()
{
    GameWorld *gw = (GameWorld*) calloc(1,sizeof (GameWorld));

    gw->player = createNewPlayer((Vector2){32,32},BLUE);

    gw->numberOfBlocks = 0;
    gw->numberOfEnemies = 0;

    //loadMap(gw,"maps/map1.txt");

    gw->camera = (Camera2D)
    {
        .target={GetScreenWidth()/2,GetScreenHeight()/2},
        .offset = {0,0},
        .rotation = 0.0f,
        .zoom = 1.0f
    };

    return gw;
}

//---------------------------------------------------
//===================================================
//--------------------LOADMAP------------------------

void loadMap(GameWorld *gw, const char* arquivo)
{
   char *dados = LoadFileText(arquivo); // leio o arquivo e coloco em um array chamado dados
   char *atual = dados; // um ponteiro para o dado da posição do arraty

   int contLines = 0;
   int contColumn = 0;
   int contBasicEnemies = 0;
   int contBlocks = 0;


   while(*atual != '\0')
   {
        if (*atual=='p'){
            gw->numberOfBlocks++;
        }

        if(*atual=='i'){
            gw->enemies->numberOfBasicEnemies++;
        }

        atual++;
   }

   gw->numberOfEnemies = gw->enemies->numberOfBasicEnemies;

   gw->blocks = (Block*) malloc(gw->numberOfBlocks * sizeof(Block));

   gw->enemies = (Enemies*) malloc (gw->numberOfEnemies * sizeof (Enemies));
        gw->enemies->enemy1 = (BasicEnemy*) malloc (gw->enemies->numberOfBasicEnemies * sizeof (BasicEnemy));



   atual = dados; //reset do contadorc
   while (*atual != '\0')
   {
       switch (*atual)
       {
        case '\n':
            contLines++;
            contColumn=0;
            break;

        case 'j':
            gw->player.pos = (Vector2) {contColumn*32,contLines*32};
            contColumn++;
            break;

        case 'i': //BASIC ENEMY
            gw->enemies->enemy1[contBasicEnemies] = createBasicEnemies(
                (Vector2){contColumn*32, contLines*32}
            );
            contColumn++;
            gw->enemies->enemy1->collisionRecs = createAndUpdateBasicEnemiesCollisionsRec(&gw->enemies->enemy1[contBasicEnemies]);
            contBasicEnemies++;
            break;

        case 'p': //PAREDES E CHÃO
            gw->blocks[contBlocks] = createBlock(
                (Vector2){contColumn*32, contLines*32}
            );
            contColumn++;
            contBlocks++;
            break;

        default:
            contColumn++;
            break;
       }
       atual++;
   }
}

//-------------------------------------------------------
//=======================================================
//---------------IMPUTS-AND-UPDATES----------------------

//--------------------------------//
//  float delta = GetFrameTime(); //  SET THE DELTA OF FRAME TIME
//--------------------------------//











