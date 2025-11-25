#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "gameWindow.h"
#include "resourceManager.h"

GameWindow* createGameWindow(int width, int height)
{
    GameWindow *gameWindow = (GameWindow*) malloc(sizeof(GameWindow));
    if (!gameWindow){return NULL;}

    gameWindow->width = width;
    gameWindow->height = height;
    gameWindow->initiate = false;
    //gameWindow->shouldClose = false;

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

        SetExitKey(KEY_NULL);

        gameWindow->game = createGame();

        gameWindow->game.gl = createGameLobby(&gameWindow->game.player);

        gameWindow->game.playerLobbyFirstPos = gameWindow->game.player.pos;

        gameWindow->game.playerLobbyReturnPos = gameWindow->game.gl.posComputer;

        printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
               gameWindow->game.playerLobbyReturnPos.x,
               gameWindow->game.playerLobbyReturnPos.y);

        SetTargetFPS(60);

        while (!WindowShouldClose() && gameWindow->game.shouldClose==false)
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

            initGame(&gameWindow->game, isFullScreen);

        }

        CloseWindow();
        unloadResouces();
        if(gameWindow->game.gameWorldInitiate)
            destroysGameWorld(gameWindow->game.gw);

    }
}
