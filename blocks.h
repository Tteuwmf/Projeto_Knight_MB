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

//-------------------------------------
//=====================================
//--------------FUNCTIONS--------------

Block createBlock (Vector2 pos);

void drawBlock (Block *block);


#endif // BLOCKS_H
