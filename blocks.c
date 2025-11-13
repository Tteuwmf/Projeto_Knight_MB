#include "raylib.h"
#include "blocks.h"
#include "resourceManager.h"

Block createBlock (Vector2 pos)
{
    return (Block){
        .pos = pos,
        .dim = (Vector2){32,32},
        .cor = BLACK,
    };
}

void drawBlock(Block *block)
{
    DrawTextureV(rm.gw.defaultTile,block->pos,WHITE);
}
