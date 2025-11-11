#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "gameWindow.h"

GameWindow* createGameWindow(int width, int height)
{
    GameWindow *gameWindow = (GameWindow*) malloc(sizeof(GameWindow));
    if (!gameWindow){return NULL;}

    gameWindow->width = width;
    gameWindow->height = height;
    gameWindow->gw = NULL;
    gameWindow->gameWorldInitiate = false;
    gameWindow->initiate = false;

    return gameWindow;
}

void initGameWindow(GameWindow *gameWindow)
{
    if(!gameWindow){return;} //checa para não dar crashs

    if(!gameWindow->initiate)
    {
        gameWindow->initiate = true;

        //======FULL-SCREEN-CONFIG======

        bool isFullScreen = false;

        //-------------------------------

        InitWindow (gameWindow->width, gameWindow->height, "JOGO2.0");

        gameWindow->gl = createGameLobby();

        Vector2 playerLobbyfirstPos = gameWindow->gl.player.pos;

        Vector2 playerGameWorldfirstPos;

        SetTargetFPS(60);

        int lobbyOrWorld = 0;

        while (!WindowShouldClose())
        {
            //----FULL-SCREEN-CONFIG----

            if(IsKeyPressed(KEY_F))
            {
                isFullScreen = !isFullScreen;

                if(isFullScreen)
                {
                    SetWindowSize(1920,1080);
                    SetWindowPosition(0,0);
                }
                else
                {
                    SetWindowSize(gameWindow->width, gameWindow->height);
                    SetWindowPosition(
                        (1920-gameWindow->width)/2,
                        (1080-gameWindow->height)/2
                    );
                }
            }

            //-----------------------------

            switch(lobbyOrWorld)
            {

                case 0:

                    if(IsKeyPressed(KEY_ENTER))
                    {
                        lobbyOrWorld++;

                        if(gameWindow->gameWorldInitiate)
                        {
                            gameWindow->gw->player->pos = playerGameWorldfirstPos;
                        }
                    }

                    inputAndUpdateGameLobby(&gameWindow->gl, isFullScreen);

                    drawGameLobby(&gameWindow->gl);
                    break;

                case 1:

                    if(IsKeyPressed(KEY_ENTER))
                    {
                        lobbyOrWorld--;
                        gameWindow->gl.player.pos = playerLobbyfirstPos;
                    }

                    if(gameWindow->gameWorldInitiate==false)
                    {
                        gameWindow->gw = createGameWorld(&gameWindow->gl.player);

                        gameWindow->gameWorldInitiate = true;
                    }

                    if (playerGameWorldfirstPos.x==0 && playerGameWorldfirstPos.y ==0)
                        {
                            playerGameWorldfirstPos = gameWindow->gw->player->pos;
                        }

                    inputAndUpdateGameWorld(gameWindow->gw, isFullScreen);

                    drawGameWorld(gameWindow->gw);
                    break;
            }

        }


        CloseWindow();
        destroysGameWorld(gameWindow->gw);

    }
}
