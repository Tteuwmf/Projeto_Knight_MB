#ifndef BLOCKS_H
#define BLOCKS_H

#include "raylib.h"

//====================================
//---------------STRUCTS--------------

typedef struct Block
{
    Vector2 pos;
    Vector2 dim;
    Color cor;

}Block;

typedef struct Grass
{
    Vector2 pos;
    Vector2 dim;
    Color cor;

}Grass;

//-------------------------------------
//=====================================
//--------------FUNCTIONS--------------

Block createBlock (Vector2 pos);

void drawBlock (Block *block);

Grass createGrass (Vector2 pos);

void drawGrass (Grass *grass);
#endif // BLOCKS_H
