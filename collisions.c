#include "raylib.h"
#include "collisions.h"

//===============================================
//-----------PLAYER-COLLISION-FUNCTIONS----------

//-----------------------------------------------
//                    CREATE
//-----------------------------------------------

PlayerCollisionRec updatePlayerCollisionRecs(Player *player)
{
    return (PlayerCollisionRec){
                .upper = (Rectangle){
                        .x = player->pos.x+(player->dim.x/2)-8,
                        .y = player->pos.y,
                        .width = 16,
                        .height = 6
                        },
                .under = (Rectangle){
                        .x = player->pos.x+(player->dim.x/2)-8,
                        .y = player->pos.y+player->dim.y-6,
                        .width = 16,
                        .height = 6
                        },
                .left = (Rectangle){
                        .x = player->pos.x,
                        .y = player->pos.y+(player->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        },
                .right = (Rectangle){
                        .x = player->pos.x+player->dim.x-6,
                        .y = player->pos.y+(player->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        }
    };
}

void DrawPlayerRecCollisionUnder(PlayerCollisionRec *recCollision)
{
    DrawRectangleRec(recCollision->under, WHITE);
}


    //============PLAYER-SWORD===============
PlayerSwordCollisionRec createAndUpdatePlayerSwordCollisionRecs(Player *player)
{
    PlayerSwordCollisionRec updatedPlayersSwordRecsCollision = (PlayerSwordCollisionRec){
                .upper = (Rectangle){
                        .x = player->sword.pos.x+(player->sword.dim.x/2)-3,
                        .y = player->sword.pos.y,
                        .width = 6,
                        .height = 6
                        },
                .under = (Rectangle){
                        .x = player->sword.pos.x+(player->sword.dim.x/2)-3,
                        .y = player->sword.pos.y+player->sword.dim.y-6,
                        .width = 6,
                        .height = 6
                        },
                .left = (Rectangle){
                        .x = player->sword.pos.x,
                        .y = player->sword.pos.y+(player->sword.dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        },
                .right = (Rectangle){
                        .x = player->sword.pos.x+player->sword.dim.x-6,
                        .y = player->sword.pos.y+(player->sword.dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        }

    };
    return updatedPlayersSwordRecsCollision;
}

//--------------------------------------------//
//                    MAKE                    //
//--------------------------------------------//

    //============PLAYER-BLOCK==============

//------------UPPERplayer-COLLISION-------------
bool checkPlayerBlockCollision_Upper(PlayerCollisionRec *collisionRecs, Block *block)
{
    return CheckCollisionRecs(collisionRecs->upper,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//------------UNDERplayer-COLLISION-------------
bool checkPlayerBlockCollision_Under(PlayerCollisionRec *collisionRecs, Block *block)
{
    return CheckCollisionRecs(collisionRecs->under,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//-----------LEFTplayer-COLLISION---------------
bool  checkPlayerBlockCollision_Left(PlayerCollisionRec *collisionRecs, Block *block)
{
    return CheckCollisionRecs(collisionRecs->left,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//-----------RIGHTplayer-COLLISION--------------
bool  checkPlayerBlockCollision_Right(PlayerCollisionRec *collisionRecs, Block *block)
{
    return CheckCollisionRecs(collisionRecs->right,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

    //=============PLAYER-ENEMIES=============

        //----------BASIC-ENEMIES----------

bool checkPlayerBasicEnemiesCollision_Upper(PlayerCollisionRec *collisionRec, BasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->upper,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}
//------------COLISÃO POR BAIXO-------------
bool checkPlayerBasicEnemiesCollision_Under(PlayerCollisionRec *collisionRec, BasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->under,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}

bool checkPlayerBasicEnemiesCollision_Left(PlayerCollisionRec *collisionRec, BasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->left,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}

bool checkPlayerBasicEnemiesCollision_Right(PlayerCollisionRec *collisionRec, BasicEnemy *enemy)
{
    return CheckCollisionRecs(collisionRec->right,(Rectangle){.x = enemy->pos.x, .y = enemy->pos.y, .width = enemy->dim.x, .height = enemy->dim.y});
}


    //=============PLAYER-SWORD===============

bool checkBasicEnemiesPlayerSwordCollision_Left(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword)
{
    return CheckCollisionRecs(collisionRec->left,(Rectangle){.x = playerSword->pos.x, .y = playerSword->pos.y, .width = playerSword->dim.x, .height = playerSword->dim.y});
}

bool checkBasicEnemiesPlayerSwordCollision_Right(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword)
{
    return CheckCollisionRecs(collisionRec->right,(Rectangle){.x = playerSword->pos.x, .y = playerSword->pos.y, .width = playerSword->dim.x, .height = playerSword->dim.y});
}


//----------------------------------------------------
//====================================================
//-----------ENEMIES-COLLISIONS-FUNCTIONS-------------

//----------------------------------------------------
//                      CREATE
//----------------------------------------------------

    //------BASIC-ENEMIES-----

BasicEnemyCollisionRec createAndUpdateBasicEnemiesCollisionsRec(BasicEnemy *enemy)
{
    return (BasicEnemyCollisionRec){
                .upper = (Rectangle){
                        .x = enemy->pos.x+(enemy->dim.x/2)-3,
                        .y = enemy->pos.y,
                        .width = 6,
                        .height = 6
                        },
                .under = (Rectangle){
                        .x = enemy->pos.x+(enemy->dim.x/2)-3,
                        .y = enemy->pos.y+enemy->dim.y-6,
                        .width = 6,
                        .height = 6
                        },
                .left = (Rectangle){
                        .x = enemy->pos.x,
                        .y = enemy->pos.y+(enemy->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        },
                .right = (Rectangle){
                        .x = enemy->pos.x+enemy->dim.x-6,
                        .y = enemy->pos.y+(enemy->dim.y/2)-3,
                        .width = 6,
                        .height = 6
                        }
    };
}

    //------MAIN-FUNCTION-FOR-ENEMIES------

void createAndUpdateEnemiesCollisionRecs(Enemies *enemies)
{
    for (int i=0; i<enemies->numberOfBasicEnemies;i++)
    {
        BasicEnemy *enemy1 = &enemies->enemy1[i];

        if (enemy1->dead==false)
        {
            createAndUpdateBasicEnemiesCollisionsRec(enemy1);
        }
    }
}

//---------------------------------------------//
//                    MAKE                     //
//---------------------------------------------//

    //-----BASIC-ENEMIES-BLOCK-COLLISION-----

//------------COLISÃO POR CIMA-------------
bool checkBasicEnemiesBlockCollision_Upper(BasicEnemyCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->upper,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}
//------------COLISÃO POR BAIXO-------------
bool checkBasicEnemiesBlockCollision_Under(BasicEnemyCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->under,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

bool checkBasicEnemiesBlockCollision_Left(BasicEnemyCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->left,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}

bool checkBasicEnemiesBlockCollision_Right(BasicEnemyCollisionRec *collisionRec, Block *block)
{
    return CheckCollisionRecs(collisionRec->right,(Rectangle){.x = block->pos.x, .y = block->pos.y, .width = block->dim.x, .height = block->dim.y});
}



