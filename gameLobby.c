#include "raylib.h"
#include "gameLobby.h"
#include "blocks.h"
#include "collisions.h"
#include "gameWindow.h"
#include "resourceManager.h"

GameLobby createGameLobby(Player *player)
{
    GameLobby gl = (GameLobby)
    {
        .player = player,
        .numberOfBlocks= 0,
        .camera = (Camera2D)
        {
            .target={GetScreenWidth()/2, GetScreenHeight()/2},
            .offset = {0,0},
            .rotation = 0.0f,
            .zoom = 1.0f,
        },

        .nearBanch = false,
        .nearRoom = false,
        //.nearStore = false,
        .roomCamera = false,

        .fadeScreenGL = 1.0f,
    };

    loadLobby(&gl,"maps/mapLobby.txt");

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
                gl->player->pos = (Vector2){contColumn*32,contLines*32};
                contColumn++;
                break;

            case 'O':
            case 'C':
            case 'p':
            case 'P':
                gl->blocks[contBlocks] = createBlock(
                    (Vector2){contColumn*32,contLines*32}
                );
                contColumn++;
                contBlocks++;
                gl->numberOfBlocks++;
                break;

            case 'B':
                gl->Banch = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
                break;

            case 'L':
                gl->Store = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
                break;

            case 'S':
                gl->Room = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
                break;

            case 'M':
                gl->Computer = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
                break;

             case 'D':
                gl->DoorR = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
                break;

            case 'd':
                gl->DoorS = (Rectangle)
                {
                    .x = contColumn*32,
                    .y = contLines*32,
                    .width = 32,
                    .height = 32,
                };
                contColumn++;
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

    if(gl->player->status.resting==false)
        inputAndUpdatePlayer(gl->player, delta);


    if(CheckCollisionRecs((Rectangle){.x = gl->player->pos.x,  .y = gl->player->pos.y, .width = gl->player->dim.x, .height = gl->player->dim.y}, gl->Banch))
        {
            if(IsKeyPressed(KEY_W) && gl->player->status.resting==false)
            {
                gl->player->status.resting = true;
                gl->player->pos.x = gl->Banch.x+16;
                gl->player->pos.y += 10;
            }

            gl->nearBanch = true;

        }
        else gl->nearBanch = false;

    if(gl->player->status.resting && (IsKeyPressed(KEY_A)||IsKeyPressed(KEY_D)))
         gl->player->status.resting = false;


    if(CheckCollisionRecs((Rectangle){.x = gl->player->pos.x,  .y = gl->player->pos.y, .width = gl->player->dim.x, .height = gl->player->dim.y}, gl->Room))
        {
            if(IsKeyPressed(KEY_W))
            {
                gl->player->speed.y = 0.0;
                gl->player->pos.x = gl->DoorR.x;
                gl->player->pos.y = gl->DoorR.y;
                gl->roomCamera = true;
            }

            gl->nearRoom = true;

        }
        else gl->nearRoom = false;

    makeLobbyCollisionPlayerBlock(gl);

    updateLobbyCamera(&gl->camera, gl->player, isFullscreen, gl->roomCamera, gl->storeCamera);
}

void makeLobbyCollisionPlayerBlock(GameLobby *gl)
{
    Player *player = gl->player;
    PlayerCollisionRec *collisionRec = &gl->player->collisionRecs;

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
                player->chiclete.rightWall = true;
            }

            if(checkPlayerBlockCollision_Left(collisionRec ,block))
            {
                player->pos.x=block->pos.x+block->dim.x;
                player->chiclete.leftWall = true;
            }
    }

}

void makeLobbyCollisionBlocksPowersAndWeapons(GameLobby *gl)
{
    Player *player = gl->player;


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

void updateLobbyCamera(Camera2D *camera, Player *player, bool isFullscreen, bool roomCamera, bool storeCamera)
{
    if(isFullscreen==false)
    {
        if(roomCamera==false && storeCamera==false)
        {
            if (player->pos.x <= 704 && player->pos.y <= 372)
            {
                camera->target= (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->rotation = 0.0f;
                camera->zoom = 1.0f;
            }
            else if (player->pos.x >= 448 && player->pos.x < 896 && player->pos.y > 384 && player->pos.y <= 800)
            {
                camera->target= (Vector2) {592,player->pos.y+(player->dim.y/2)-100};
                camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->rotation = 0.0f;
                camera->zoom = 1.5f;
            }
            else
            {
                if(player->pos.x <= 1152)
                {
                    camera->target= (Vector2) {1152,player->pos.y+(player->dim.y/2)-128};
                    camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                    camera->rotation = 0.0f;
                    camera->zoom = 1.3f;
                }
                else if(player->pos.x >= 2624-32)
                {
                    camera->target= (Vector2) {2624-32,player->pos.y+(player->dim.y/2)-128};
                    camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                    camera->rotation = 0.0f;
                    camera->zoom = 1.3f;
                }
                else
                {
                    camera->target= (Vector2) {player->pos.x+(player->dim.x/2),player->pos.y+(player->dim.y/2)-128};
                    camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                    camera->rotation = 0.0f;
                    camera->zoom = 1.3f;
                }
            }
        }
        else if(roomCamera)
        {
            camera->target= (Vector2) {player->pos.x+(player->dim.x/2),player->pos.y+(player->dim.y/2)-64};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 1.3f;
        }
        else if(storeCamera)
        {
            camera->target= (Vector2) {player->pos.x+(player->dim.x/2),player->pos.y+(player->dim.y/2)-64};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 1.3f;
        }
    }
    else
    {
       if (player->pos.x <= 704 && player->pos.y <= 372)
        {
            camera->target= (Vector2) {435,250};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 2.2f;
        }
        else if (player->pos.x >= 448 && player->pos.x < 896 && player->pos.y > 384 && player->pos.y <= 800)
        {
            camera->target= (Vector2) {592,player->pos.y+(player->dim.y/2)-100};
            camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
            camera->rotation = 0.0f;
            camera->zoom = 3.5f;
        }
        else
        {
            if(player->pos.x <= 1152)
            {
                camera->target= (Vector2) {1152,600};
                camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->rotation = 0.0f;
                camera->zoom = 2.3f;
            }
            else if(player->pos.x >= 2500)
            {
                camera->target= (Vector2) {2500,600};
                camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->rotation = 0.0f;
                camera->zoom = 2.3f;
            }
            else
            {
                camera->target= (Vector2) {player->pos.x+(player->dim.x/2),600};
                camera->offset = (Vector2) {GetScreenWidth()/2,GetScreenHeight()/2};
                camera->rotation = 0.0f;
                camera->zoom = 2.3f;
            }
        }

    }
}




void drawGameLobby (GameLobby *gl)
{

    BeginDrawing();

    ClearBackground (DARKGRAY);

    BeginMode2D(gl->camera);

    DrawTexture(rm.gl.bench,gl->Banch.x,gl->Banch.y, WHITE);
    //DrawRectangleRec(gl->Banch, WHITE);
    DrawRectangleRec(gl->Store, WHITE);
    DrawRectangleRec(gl->Room, WHITE);
    DrawRectangleRec(gl->DoorR, WHITE);
    DrawRectangleRec(gl->DoorS, WHITE);

    drawPlayer(gl->player);

    if(gl->nearBanch)
        DrawText(TextFormat("DESCANSAR: W"), gl->Banch.x,gl->Banch.y-16,15, WHITE);

    if(gl->nearRoom)
        DrawText(TextFormat("ENTRAR NA SALA: W"), gl->Room.x,gl->Room.y-16,15, WHITE);

    if(gl->nearStore)
        DrawText(TextFormat("ENTRAR NA LOJA: W"), gl->Store.x,gl->Store.y-16,15, WHITE);

    for (int i =0; i<gl->numberOfBlocks; i++)
    {
        drawBlock(&gl->blocks[i]);
    }

    EndMode2D();

    drawHud(gl->player);

        gl->fadeScreenGL -= 0.2f*GetFrameTime();
        if(gl->fadeScreenGL<0.0f) gl->fadeScreenGL = 0.0f;

        DrawRectangle(0,0,1920, 1080, (Color){0,0,0,(unsigned char)(gl->fadeScreenGL*255)});

        if(gl->fadeScreenGL>0.0f)
            DrawText("NOME DO JOGO", ((GetScreenWidth()/2) - 240), ((GetScreenHeight()/2) - 34), 64, GREEN);

    EndDrawing();
}





