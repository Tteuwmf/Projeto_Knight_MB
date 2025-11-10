#include "raylib.h"
#include "gameLobby.h"
#include "blocks.h"
#include "collisions.h"
#include "gameWindow.h"

GameLobby createGameLobby()
{
    GameLobby gl = (GameLobby)
    {
        .player = createNewPlayer((Vector2){32,32},BLUE),
        .numberOfBlocks= 0,
        .camera = (Camera2D)
        {
            .target={GetScreenWidth()/2, GetScreenHeight()/2},
            .offset = {0,0},
            .rotation = 0.0f,
            .zoom = 1.0f,
        },
    };

    loadLobby(&gl,"maps/map1.txt");

    return gl;

}

void loadLobby(GameLobby *gl, const char* arquivo)
{
    char *dados = LoadFileText(arquivo);
    if(!dados){return;}

    char *atual = dados;

    int contLines = 0;
    int contColumn = 0;
    int contBlocks = 0;

    while(*atual != '\0')
    {
        switch(*atual)
        {
            case '\n':
                contLines++;
                contColumn=0;
                break;

            case 'J':
            case 'j':
                gl->player.pos = (Vector2){contColumn*32,contLines*32};
                contColumn++;
                break;

            case 'p':
            case 'P':
                gl->blocks[contBlocks] = createBlock(
                    (Vector2){contColumn*32,contLines*32}
                );
                contColumn++;
                contBlocks++;
                gl->numberOfBlocks++;
                break;

            default:
                contColumn++;
                break;
        }

        atual++;
    }

    UnloadFileText(dados);

}

void inputAndUpdateGameLobby(GameLobby *gl, bool isFullscreen)
{
    //-------------------------//
    float delta = GetFrameTime();
    //-------------------------//

    inputAndUpdatePlayer(&gl->player, delta);

    makeLobbyCollisionPlayerBlock(gl);

    updateCamera(&gl->camera, &gl->player, isFullscreen);
}

void makeLobbyCollisionPlayerBlock(GameLobby *gl)
{
    Player *player = &gl->player;
    PlayerCollisionRec *collisionRec = &gl->player.collisionRecs;

    for(int i =0; i<gl->numberOfBlocks; i++)
    {
        Block *block = &gl->blocks[i];

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
            }

            if(checkPlayerBlockCollision_Left(collisionRec ,block))
            {
                player->pos.x=block->pos.x+block->dim.x;
            }
    }

}

void makeLobbyCollisionBlocksPowersAndWeapons(GameLobby *gl)
{
    Player *player = &gl->player;


    for(int i =0; i<gl->numberOfBlocks; i++)
    {
        Block *blocks = &gl->blocks[i];

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






void drawGameLobby (GameLobby *gl)
{

    BeginDrawing();

    ClearBackground (GRAY);

    BeginMode2D(gl->camera);

    drawPlayer(&gl->player);

    for (int i =0; i<gl->numberOfBlocks; i++)
    {
        drawBlock(&gl->blocks[i]);
    }

    EndMode2D();

    drawHud(&gl->player);

    EndDrawing();
}





