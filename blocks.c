#include "raylib.h"
#include "blocks.h"

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
    DrawRectangleV(block->pos, block->dim,block->cor);
}
