#include "raylib.h"
#include "entities/blocks.h"
#include "resources/resourceManager.h"
#include "resources/global.h"

Block createBlock (Vector2 pos)
{
    return (Block){
        .pos = pos,
        .dim = (Vector2){BLOCK_SIZE,BLOCK_SIZE},
        .cor = BLACK,
    };
}

void drawBlock(Block *block)
{
    DrawTextureV(rm.gw.defaultTile,block->pos,WHITE);
}

Grass createGrass (Vector2 pos)
{
    return (Grass){
        .pos = pos,
        .dim = (Vector2){BLOCK_SIZE, BLOCK_SIZE},
        .cor = BLACK,
    };
}

void drawGrass(Grass *grass)
{
    DrawTextureV(rm.gl.grass,grass->pos,WHITE);
}

StoreBlock createStoreBlock (Vector2 pos)
{
    return (StoreBlock){
        .pos = pos,
        .dim = (Vector2){BLOCK_SIZE,BLOCK_SIZE},
        .cor = BLACK,
    };
}

void drawStoreBlock(StoreBlock *storeBlock)
{
    DrawTextureV(rm.gl.storeBlock,storeBlock->pos,WHITE);
}
