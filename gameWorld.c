#include <stdlib.h>
#include "raylib.h"
#include "gameWorld.h"



#define GRAVIDADE 20.0
#define MAX_SPEED_FALL 400.0

//================================================
//------------CREATE-DEFAULT-GAMEWORLD------------

GameWorld* createGameWorld(Player *player)
{
    GameWorld *gw = (GameWorld*) calloc(1,sizeof (GameWorld));
    if (!gw){return NULL;}

    //gw->player = createNewPlayer((Vector2){32,32},BLUE);
    gw->player = player;

    gw->numberOfBlocks = 0;
    gw->numberOfEnemies = 0;
    gw->numberOfCoins = 0;
    gw->numberOfCharms = 0;
    gw->numberOfSkills = 0;

    loadMap(gw,"maps/mapEx.txt");

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
    if(!dados){return;}

    char *atual = dados; // um ponteiro para o dado da posição do arraty

    int contLines = 0;
    int contColumn = 0;
    int contBasicEnemies = 0;
    int contAirBasicEnemies = 0;
    int basicEnemySelector = 0;
    int contBlocks = 0;
    int contCharms = 0;
    int contSkills = 0;

    gw->enemies = (Enemies*) calloc(1, sizeof(Enemies));
    if (!gw->enemies){free(gw->enemies); return;}

   while(*atual != '\0')
   {
        if (*atual=='p'||*atual=='P'){
            gw->numberOfBlocks++;
        }

        if(*atual=='i'||*atual=='M'){

            if(basicEnemySelector==0)
            {
                gw->enemies->numberOfBasicEnemies++;
                basicEnemySelector++;
            }
            else
            {
                gw->enemies->numberOfAirBasicEnemies++;
                basicEnemySelector--;
            }
        }

        if(*atual=='A'|| *atual=='c'){
            gw->numberOfCharms++;
        }

        if(*atual=='H'|| *atual=='s'){
            gw->numberOfSkills++;
        }

        atual++;
   }

    gw->numberOfEnemies = gw->enemies->numberOfBasicEnemies;

    if(gw->numberOfBlocks>0)
    {
        gw->blocks = (Block*) malloc(gw->numberOfBlocks * sizeof(Block));
        if(!gw->blocks){free(gw->blocks); return;}
    }
    else
        gw->blocks=NULL;

    if(gw->enemies->numberOfBasicEnemies>0)
    {
        gw->enemies->enemy1 = (BasicEnemy*) malloc (gw->enemies->numberOfBasicEnemies * sizeof (BasicEnemy));
        if(!gw->enemies->enemy1){free(gw->enemies->enemy1); return;};
    }
    else
        gw->enemies->enemy1 = NULL;


    atual = dados; //reset do contadorc

    basicEnemySelector=0; //reset do seletor

    while (*atual != '\0')
    {
        switch (*atual)
        {
            case '\n':
                contLines++;
                contColumn=0;
                break;

            case 'J':
            case 'j':
                gw->player->pos = (Vector2) {contColumn*32,contLines*32};
                contColumn++;
                break;

            case 'M':
            case 'i': //BASIC ENEMY
                if(basicEnemySelector==0)
                {
                    gw->enemies->enemy1[contBasicEnemies] = createBasicEnemies(
                        (Vector2){contColumn*32, contLines*32}
                    );
                    contColumn++;
                    gw->enemies->enemy1[contBasicEnemies].collisionRecs = createAndUpdateBasicEnemiesCollisionsRec(&gw->enemies->enemy1[contBasicEnemies]);
                    contBasicEnemies++;
                    basicEnemySelector++;

                }
                else
                {
                     gw->enemies->enemy2[contAirBasicEnemies] = createAirBasicEnemies(
                        (Vector2){contColumn*32, contLines*32}, contAirBasicEnemies
                    );
                    contColumn++;
                    gw->enemies->enemy2[contAirBasicEnemies].collisionRecs = createAndUpdateAirBasicEnemiesCollisionsRec(&gw->enemies->enemy2[contAirBasicEnemies]);
                    contAirBasicEnemies++;
                    basicEnemySelector--;
                }
                break;

            case 'P':
            case 'p': //PAREDES E CHÃO
                gw->blocks[contBlocks] = createBlock(
                    (Vector2){contColumn*32, contLines*32}
                );
                contColumn++;
                contBlocks++;
                break;

            case 'A':
            case 'c': //charms
                gw->charms[contCharms] = createCharm(
                    (Vector2){contColumn*32, contLines*32+22}, contCharms
                );
                contColumn++;
                contCharms++;
                break;

            case 'H':
            case 's': //skills
                gw->skills[contSkills] = createSkill(
                    (Vector2){contColumn*32+8, contLines*32+8}, contSkills
                );
                contColumn++;
                contSkills++;
                break;

            default:
                contColumn++;
                break;
        }
        atual++;
    }

    UnloadFileText(dados);
}

//-------------------------------------------------------
//=======================================================
//----------------IMPUTS-AND-UPDATES---------------------

void inputAndUpdateGameWorld(GameWorld *gw, bool isFullscreen)
{

//--------------------------------//
  float delta = GetFrameTime();   //  SET THE DELTA OF FRAME TIME
//--------------------------------//

    applyKnockbackToPlayer(gw->player);

    applyKnockbackToEnemies(gw->enemies);

//---------------MAIN-FUNCTION-----------------
    inputAndUpdatePlayer(gw->player, delta);

    updateEnemies (gw->enemies,delta);
//---------------------------------------------

    makeCollisionPlayerBlock (gw);

    makeCllisionBlockWeaponsAndPowers(gw);

    makeCollisionEnemiesBlock (gw);

    makeCollisionEnemiesPlayerPowers (gw);

    makeCollisionEnemiesWeapons(gw);

    updateCoins(gw, delta);

    makeCollisionPlayerCoinsSkillsAndCharms(gw);

    if (gw->player->knockbackStatus.knockbackTime<=0 && gw->player->status.invulnerable==false)
        makeCollisionEnemiesPlayer(gw);

    updateCamera(&gw->camera, gw->player, isFullscreen);

}

//-------------------------------------------------------
//=======================================================
//-----------------MAKE-COLLISION-IN-GW------------------

void makeCollisionPlayerBlock (GameWorld *gw)
{
    Player *player = gw->player;
    PlayerCollisionRec *collisionRec = &gw->player->collisionRecs;

    for(int i =0; i<gw->numberOfBlocks; i++)
    {
        Block *block = &gw->blocks[i];

            //colisão por cima

            if(checkPlayerBlockCollision_Under(collisionRec ,block))
            {
                player->pos.y = block->pos.y-player->dim.y;
                player->status.onFloor = true;
                player->speed.y = 0.0f;
            }
            else if ( player->speed.y>0.0f)
                player->status.onFloor = false;


            if(checkPlayerBlockCollision_Upper(collisionRec ,block))
            {
                player->pos.y = block->pos.y + block->dim.y;
                player->speed.y = 0.0f;
            }

            if(checkPlayerBlockCollision_Right(collisionRec ,block))
            {
                player->pos.x = block->pos.x-player->dim.x;
                if(player->status.onFloor==false)
                    player->chiclete.rightWall = true;
            }
           // else
                //player->chiclete.rightWall = false;

            if(checkPlayerBlockCollision_Left(collisionRec ,block))
            {
                player->pos.x=block->pos.x+block->dim.x;
                if(player->status.onFloor==false)
                    player->chiclete.leftWall =true;
            }
            //else
               //player->chiclete.leftWall =false;
    }

}

void makeCollisionPlayerCoinsSkillsAndCharms(GameWorld *gw)
{
    Player *player = gw->player;

    for(int i =0;i<gw->numberOfCoins;i++)
    {
        Coins *coin = &gw->ticketsRU[i];

        if(coin->available)
        {
            if(checkCoinsPlayerCollision(coin, player))
            {
                coin->available=false;

                if(player->inventory.equippedCharms.goldTickets==false)
                    player->status.ticketsRU++;
                else
                    player->status.ticketsRU+=3;
            }
        }
    }

    for(int s=0;s<gw->numberOfSkills;s++)
    {
        Skill *skill = &gw->skills[s];

        if(skill->available)
        {
            int number = skill->skilNumber;

            if(checkSkillsPlayerClose(skill, player))
                skill->playerNext = true;
            else skill->playerNext = false;

            if(checkSkillsPlayer(skill, player)&& IsKeyPressed(KEY_W))
            {
                switch(number)
                {
                    case 0:
                        player->powers.horizontalPowerActive = true;
                        break;
                }

                skill->available=false;
            }
        }
    }


    for(int h=0;h<gw->numberOfSkills;h++)
    {
        Charm *charm = &gw->charms[h];

        if(charm->available)
        {
            int number = charm->charmNumber;

            if(checkCharmsPlayerClose(charm, player))
                charm->playerNext = true;
            else charm->playerNext = false;

            if(checkCharmsPlayer(charm, player)&& IsKeyPressed(KEY_W))
            {
                switch(number)
                {
                    case 0:
                        player->inventory.equippedCharms.goldTickets = true;
                        break;
                }

                charm->available=false;
            }
        }
    }

}


void makeCllisionBlockWeaponsAndPowers(GameWorld *gw)
{
    Player *player = gw->player;


    for(int i =0; i<gw->numberOfBlocks; i++)
    {
        Block *blocks = &gw->blocks[i];

        Rectangle block = (Rectangle)
        {
            .x = blocks->pos.x,
            .y = blocks->pos.y,
            .width = blocks->dim.x,
            .height = blocks->dim.y,
        };

        //------DEFAULT-SWORD-------

        if(player->inventory.equippedWeapons.defaultSword && (player->attackStatus.attackLeft || player->attackStatus.attackRight) && player->sword.activated)
        {

            Rectangle swordCollisionRec = player->sword.swordCollisionRec;

            if (checkPlayerSwordBlocksCollision(swordCollisionRec,block)&& player->status.lookingAtL)
            {
                 player->knockbackStatus.swordKnockbackL = true;
                 player->sword.activated = false;
            }

            if (checkPlayerSwordBlocksCollision(swordCollisionRec,block)&& player->status.lookingAtR)
            {
                 player->knockbackStatus.swordKnockbackR = true;
                 player->sword.activated = false;
            }
        }

        //-------HORIZONTAL-POWER-------

        if(player->powers.usingHorizontalPower)
        {
            HorizontalPower *power = &player->powers.horizontalPower;

            if(checkBlocksHorizontalPowerCollision(block, power))
            {
                power->contTime+=5.0;
            }
        }
    }

}

void makeCollisionEnemiesBlock (GameWorld *gw)
{
    //============BASIC=ENIMIES============

    for (int i =0 ; i<gw->enemies->numberOfBasicEnemies; i++)
    {
        BasicEnemy *enemy = &gw->enemies->enemy1[i];
        BasicEnemyCollisionRec *collisionRec = &enemy->collisionRecs;

        for(int i =0; i<gw->numberOfBlocks; i++)
        {
            Block *block = &gw->blocks[i];

                if(checkBasicEnemiesBlockCollision_Under(collisionRec ,block))
                {
                    enemy->pos.y = block->pos.y-enemy->dim.y;
                    enemy->onFloor = true;
                    enemy->speed.y = 0.0f;
                }
                else if ( enemy->speed.y>0.0f)
                    enemy->onFloor = false;


                if(checkBasicEnemiesBlockCollision_Upper(collisionRec ,block))
                {
                    enemy->pos.y = block->pos.y + block->dim.y;
                    enemy->speed.y = 0.0f;
                }

                if(checkBasicEnemiesBlockCollision_Right(collisionRec ,block))
                {
                    enemy->pos.x = block->pos.x-enemy->dim.x;
                    enemy->defaultSpeed = -enemy->defaultSpeed;
                }

                if(checkBasicEnemiesBlockCollision_Left(collisionRec ,block))
                {
                    enemy->pos.x=block->pos.x+block->dim.x;
                    enemy->defaultSpeed = -enemy->defaultSpeed;
                }
        }
    }

    //=============AIR-BASIC-ENEMIES=============

    for (int a =0 ; a<gw->enemies->numberOfAirBasicEnemies; a++)
    {
        AirBasicEnemy *enemy = &gw->enemies->enemy2[a];
        BasicEnemyCollisionRec *collisionRec = &enemy->collisionRecs;

        for(int b =0; b<gw->numberOfBlocks; b++)
        {
            Block *block = &gw->blocks[b];

                if(checkBasicEnemiesBlockCollision_Under(collisionRec ,block))
                {
                    enemy->pos.y = block->pos.y-enemy->dim.y;
                    enemy->speed.y = -enemy->speed.y;
                }
                if(checkBasicEnemiesBlockCollision_Upper(collisionRec ,block))
                {
                    enemy->pos.y = block->pos.y + block->dim.y;
                    enemy->speed.y = -enemy->speed.y;
                }

                if(checkBasicEnemiesBlockCollision_Right(collisionRec ,block))
                {
                    enemy->pos.x = block->pos.x-enemy->dim.x;
                    enemy->speed.x = -enemy->speed.x;
                }

                if(checkBasicEnemiesBlockCollision_Left(collisionRec ,block))
                {
                    enemy->pos.x=block->pos.x+block->dim.x;
                    enemy->speed.x = -enemy->speed.x;
                }
        }
    }

}

void makeCollisionEnemiesWeapons(GameWorld *gw)
{
    if(gw->player->inventory.equippedWeapons.defaultSword)
    {
        PlayerSword *defaultSword = &gw->player->sword;
        Player *player = gw->player;

        //----------BASIC-ENEMIES---------

        for(int i = 0; i<gw->enemies->numberOfBasicEnemies;i++)
        {
            BasicEnemy *enemy = &gw->enemies->enemy1[i];
            BasicEnemyCollisionRec *collisionRec = &enemy->collisionRecs;


            if(enemy->dead==false && (player->attackStatus.attackLeft || player->attackStatus.attackRight || player->attackStatus.attackDown || player->attackStatus.attackUp)&& player->sword.activated)
            {
                if(player->pos.x-enemy->pos.x>50 )
                {
                    if (checkBasicEnemiesPlayerSwordCollision_Right(collisionRec, defaultSword) && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackR=true;
                        player->knockbackStatus.swordKnockbackL = true;
                        player->sword.activated = false;
                    }
                    else if (checkBasicEnemiesPlayerSwordCollision_Left(collisionRec, defaultSword) && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackL=true;
                        player->knockbackStatus.swordKnockbackR = true;
                        player->sword.activated = false;
                    }
                    else if(checkBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.y+player->dim.y<enemy->pos.y)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        player->knockbackStatus.swordKnockbackUp = true;
                        player->sword.activated = false;
                    }
                }
                else if (enemy->pos.x-player->pos.x>50)
                {
                     if (checkBasicEnemiesPlayerSwordCollision_Right(collisionRec, defaultSword) && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackR=true;
                        player->knockbackStatus.swordKnockbackL = true;
                        player->sword.activated = false;
                    }
                    else if (checkBasicEnemiesPlayerSwordCollision_Left(collisionRec, defaultSword) && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackL=true;
                        player->knockbackStatus.swordKnockbackR = true;
                        player->sword.activated = false;
                    }
                    else if(checkBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.y+player->dim.y<enemy->pos.y)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        player->knockbackStatus.swordKnockbackUp = true;
                        player->sword.activated = false;
                    }
                }
                else if(enemy->pos.x-player->pos.x<50 || player->pos.x-enemy->pos.x<50 )
                {
                    if (checkBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.x<=enemy->pos.x  && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackL=true;
                        player->knockbackStatus.swordKnockbackR = true;
                        player->sword.activated = false;
                    }
                    else if (checkBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.x>enemy->pos.x && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackR=true;
                        player->knockbackStatus.swordKnockbackL = true;
                        player->sword.activated = false;
                    }
                    else if(checkBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.y+player->dim.y<enemy->pos.y)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        player->knockbackStatus.swordKnockbackUp = true;
                        player->sword.activated = false;
                    }
                }

            }
        }

        //------AIR-BASIC-ENEMIES-----

        for(int a = 0; a<gw->enemies->numberOfAirBasicEnemies;a++)
        {
            AirBasicEnemy *enemy = &gw->enemies->enemy2[a];
            BasicEnemyCollisionRec *collisionRec = &enemy->collisionRecs;


            if(enemy->dead==false && (player->attackStatus.attackLeft || player->attackStatus.attackRight || player->attackStatus.attackDown || player->attackStatus.attackUp)&& player->sword.activated)
            {
                if(player->pos.x-enemy->pos.x>50 )
                {
                    if (checkBasicEnemiesPlayerSwordCollision_Right(collisionRec, defaultSword) && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackR=true;
                        player->knockbackStatus.swordKnockbackL = true;
                        player->sword.activated = false;
                    }
                    else if (checkBasicEnemiesPlayerSwordCollision_Left(collisionRec, defaultSword) && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackL=true;
                        player->knockbackStatus.swordKnockbackR = true;
                        player->sword.activated = false;
                    }
                    else if(checkAirBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.y+player->dim.y<enemy->pos.y)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        player->knockbackStatus.swordKnockbackUp = true;
                        player->sword.activated = false;
                    }
                }
                else if (enemy->pos.x-player->pos.x>50)
                {
                     if (checkBasicEnemiesPlayerSwordCollision_Right(collisionRec, defaultSword) && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackR=true;
                        player->knockbackStatus.swordKnockbackL = true;
                        player->sword.activated = false;
                    }
                    else if (checkBasicEnemiesPlayerSwordCollision_Left(collisionRec, defaultSword) && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackL=true;
                        player->knockbackStatus.swordKnockbackR = true;
                        player->sword.activated = false;
                    }
                    else if(checkAirBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.y+player->dim.y<enemy->pos.y)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        player->knockbackStatus.swordKnockbackUp = true;
                        player->sword.activated = false;
                    }
                }
                else if(enemy->pos.x-player->pos.x<50 || player->pos.x-enemy->pos.x<50 )
                {
                    if (checkAirBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.x<=enemy->pos.x  && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackL=true;
                        player->knockbackStatus.swordKnockbackR = true;
                        player->sword.activated = false;
                    }
                    else if (checkAirBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.x>enemy->pos.x && (player->pos.y+player->dim.y<enemy->pos.y)==false)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        enemy->knockbackStatus.knockbackR=true;
                        player->knockbackStatus.swordKnockbackL = true;
                        player->sword.activated = false;
                    }
                    else if(checkAirBasicEnemiesPlayerSwordCollision_default(enemy,defaultSword)&& player->pos.y+player->dim.y<enemy->pos.y)
                    {
                        enemy->life-= 1;
                        player->status.aura++;
                        player->knockbackStatus.swordKnockbackUp = true;
                        player->sword.activated = false;
                    }
                }

            }
        }

    }
}

void makeCollisionEnemiesPlayerPowers (GameWorld *gw)
{
    if(gw->player->powers.horizontalPowerActive)
    {
        HorizontalPower *power1 = &gw->player->powers.horizontalPower;

        //----------BASIC-ENEMIES---------

        for(int i = 0; i<gw->enemies->numberOfBasicEnemies;i++)
        {
            BasicEnemy *enemy = &gw->enemies->enemy1[i];

            if(enemy->dead==false && power1->contTime<=power1->attackTime)
            {
                if(checkBasicEnemiesHorizontalPowerCollision(enemy,power1))
                {
                    enemy->life+= -3;
                }
            }
        }

        //---------AIR-BASIC-ENEMIES--------

        for(int a = 0; a<gw->enemies->numberOfAirBasicEnemies;a++)
        {
            AirBasicEnemy *enemy = &gw->enemies->enemy2[a];

            if(enemy->dead==false && power1->contTime<=power1->attackTime)
            {
                if(checkAirBasicEnemiesHorizontalPowerCollision(enemy,power1))
                {
                    enemy->life+= -3;
                }
            }
        }


    }
}

void makeCollisionEnemiesPlayer(GameWorld *gw)
{
    Player *player = gw->player;
    PlayerCollisionRec *collisionRec = &gw->player->collisionRecs;

    //-----------BASIC-ENEMY-----------

    for(int i = 0; i<gw->enemies->numberOfBasicEnemies;i++)
    {
        BasicEnemy *enemy = &gw->enemies->enemy1[i];

        if(enemy->dead==false)
        {
            if (checkPlayerBasicEnemiesCollision_Right(collisionRec, enemy))
            {
                player->knockbackStatus.knockbackL = true;
                player->status.invulnerable=true;
                player->status.life--;
            }
            else if (checkPlayerBasicEnemiesCollision_Left(collisionRec, enemy))
            {
                player->knockbackStatus.knockbackR = true;
                player->status.invulnerable=true;
                player->status.life--;
            }
            else if (checkPlayerBasicEnemiesCollision_Upper(collisionRec, enemy))
            {
                player->knockbackStatus.knockbackUp= true;
                player->status.invulnerable=true;
                player->status.life--;
            }
            else if (checkPlayerBasicEnemiesCollision_Under(collisionRec, enemy))
            {
                player->knockbackStatus.knockbackUn = true;
                player->status.invulnerable=true;
                player->status.life--;
            }
        }
    }

    //------AIR-BASIC-ENEMIES------

    for(int a = 0; a<gw->enemies->numberOfAirBasicEnemies;a++)
    {
        AirBasicEnemy *enemy = &gw->enemies->enemy2[a];

        if(enemy->dead==false)
        {
            if (checkPlayerAirBasicEnemiesCollision_Right(collisionRec, enemy))
            {
                player->knockbackStatus.knockbackL = true;
                player->status.invulnerable=true;
                player->status.life--;
            }
            else if (checkPlayerAirBasicEnemiesCollision_Left(collisionRec, enemy))
            {
                player->knockbackStatus.knockbackR = true;
                player->status.invulnerable=true;
                player->status.life--;
            }
            else if (checkPlayerAirBasicEnemiesCollision_Upper(collisionRec, enemy))
            {
                player->knockbackStatus.knockbackUp= true;
                player->status.invulnerable=true;
                player->status.life--;
            }
            else if (checkPlayerAirBasicEnemiesCollision_Under(collisionRec, enemy))
            {
                player->knockbackStatus.knockbackUn = true;
                player->status.invulnerable=true;
                player->status.life--;
            }
        }
    }
}

//--------------------------------------------
//============================================
//--------------------COINS-------------------

void updateCoins(GameWorld *gw, float delta)
{
        //---BASIC-ENEMIES---

    for(int e = 0; e<gw->enemies->numberOfBasicEnemies;e++)
    {
        BasicEnemy *enemy = &gw->enemies->enemy1[e];

        if(enemy->dead && enemy->haveCoins)
        {
            enemy->haveCoins=false;

            gw->ticketsRU[gw->numberOfCoins]=summonCoinsForBasicEnemies(enemy, -3);
            gw->numberOfCoins++;

            gw->ticketsRU[gw->numberOfCoins]=summonCoinsForBasicEnemies(enemy, 0);
            gw->numberOfCoins++;

            gw->ticketsRU[gw->numberOfCoins]=summonCoinsForBasicEnemies(enemy, 2);
            gw->numberOfCoins++;

        }
    }

        //---AIR-BASIC-ENEMIES---

    for(int a = 0; a<gw->enemies->numberOfAirBasicEnemies;a++)
    {
        AirBasicEnemy *enemy = &gw->enemies->enemy2[a];

        if(enemy->dead && enemy->haveCoins)
        {
            enemy->haveCoins=false;

            gw->ticketsRU[gw->numberOfCoins]=summonCoinsForAirBasicEnemies(enemy, -1);
            gw->numberOfCoins++;

            gw->ticketsRU[gw->numberOfCoins]=summonCoinsForAirBasicEnemies(enemy, 0);
            gw->numberOfCoins++;

            gw->ticketsRU[gw->numberOfCoins]=summonCoinsForAirBasicEnemies(enemy, 1);
            gw->numberOfCoins++;

        }
    }


    //--------------------------------------------

    for(int i =0;i<gw->numberOfCoins;i++)
    {
        Coins *coin = &gw->ticketsRU[i];

        if(coin->available)
        {

            coin->speed.y = (coin->speed.y*coin->friction)+GRAVIDADE;
            coin->speed.x = coin->speed.x*coin->friction;

            coin->pos.x += coin->speed.x * delta;
            coin->pos.y += coin->speed.y * delta;

            for(int k=0;k<gw->numberOfBlocks;k++)
            {
                Block *block = &gw->blocks[k];

                if(checkCoinsBlocksCollision(coin,block))
                {

                    if(coin->pos.y<block->pos.y)
                    {
                        coin->speed.y = -coin->speed.y;
                        coin->pos.y = block->pos.y-coin->dim.y;
                    }
                    if(coin->pos.y>=block->pos.y)
                    {
                        coin->speed.y = 0.0f;
                        coin->pos.y = block->pos.y+block->dim.y;
                    }
                    if(coin->pos.x<block->pos.x)
                    {
                        coin->speed.x = -coin->speed.x;
                        coin->pos.x = block->pos.x-coin->dim.x;
                    }
                    if(coin->pos.x>=block->pos.x+block->dim.x)
                    {
                        coin->speed.x = -coin->speed.x;
                        coin->pos.x = block->pos.x+block->dim.x;
                    }
                }
            }
        }
    }
}


//--------------------------------------------
//============================================
//-------------CAMERA2D-AND-DRAW--------------

void updateCamera(Camera2D *camera, Player *player, bool isFullscreen)
{

    if(isFullscreen==false)
    {
        if (player->pos.x <= 390 && player->pos.y >= 200)
        {
            camera->target= (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 1.0f;
        }
        else if(player->pos.y >= 200)
        {
            camera->target= (Vector2) {player->pos.x+(player->dim.x/2),GetScreenHeight()/2};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 1.0f;
        }
        else if (player->pos.x <= 390)
        {
            camera->target= (Vector2) {GetScreenWidth()/2,player->pos.y+(player->dim.y/2)};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 1.0f;
        }
        else
        {
            camera->target= (Vector2) {player->pos.x+(player->dim.x/2),player->pos.y+(player->dim.y/2)};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 1.0f;
        }
    }
    else
    {
        camera->target= (Vector2) {player->pos.x+(player->dim.x/2),player->pos.y+(player->dim.y/2)-64};
        camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
        camera->rotation = 0.0f;
        camera->zoom = 2.5f;
    }

}

void drawGameWorld (GameWorld *gw)
{


    BeginDrawing();

    ClearBackground (BLACK);

    BeginMode2D(gw->camera);

    drawPlayer(gw->player);

    drawEnemies(gw->enemies);

    for (int i =0; i<gw->numberOfBlocks; i++)
    {
        drawBlock(&gw->blocks[i]);
    }

    for(int c=0;c<gw->numberOfCoins;c++)
    {
        drawCoins(&gw->ticketsRU[c]);
    }

    for(int h=0;h<gw->numberOfCharms;h++)
    {
        drawCharms(&gw->charms[h]);
    }

    for(int s=0;s<gw->numberOfSkills;s++)
    {
        drawSkills(&gw->skills[s]);
    }

    EndMode2D();

    drawHud(gw->player);


    EndDrawing();
}

//------------------------------------------------
//================================================
//-------------------DESTROYS---------------------

void destroysGameWorld(GameWorld *gw)
{
    if(!gw) return;

    if(gw->enemies)
    {
        free(gw->enemies->enemy1);
        gw->enemies->enemy1=NULL;
        free(gw->enemies);
        gw->enemies=NULL;
    }

    free(gw->blocks);
    gw->blocks=NULL;

    free(gw);
    gw=NULL;
}
