#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "game_atributes/gameWindow.h"
#include "resources/resourceManager.h"
#include "resources/global.h"

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

        bool isFullScreen = true;
        bool lastFullScreen = !isFullScreen; // Garante aplicacao inicial de tamanho

        //-------------------------------

        InitWindow (gameWindow->width, gameWindow->height, "JOGO2.0");

        SetExitKey(KEY_NULL);

        InitAudioDevice();

        gameWindow->game = createGame();

        SetTextureFilter(rm.gl.storeWall, TEXTURE_FILTER_POINT);

        printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
               gameWindow->game.playerLobbyReturnPos.x,
               gameWindow->game.playerLobbyReturnPos.y);

        SetTargetFPS(TARGET_FPS);

        while (!WindowShouldClose() && gameWindow->game.shouldClose==false)
        {
            //----FULL-SCREEN-CONFIG (Otimizado: atualiza somente ao alterar estado)----

            if(isFullScreen != lastFullScreen)
            {
                if(isFullScreen)
                {
                    SetWindowSize(FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT);
                    SetWindowPosition(0, 0);
                }
                else
                {
                    SetWindowSize(gameWindow->width, gameWindow->height);
                    SetWindowPosition(
                        (FULLSCREEN_WIDTH - gameWindow->width) / 2,
                        (FULLSCREEN_HEIGHT - gameWindow->height) / 2
                    );
                }
                lastFullScreen = isFullScreen;
            }

            //-----------------------------

            initGame(&gameWindow->game, &isFullScreen);

        }
        CloseWindow();
        unloadResources();
        CloseAudioDevice();
        if(gameWindow->game.gameWorldInitiate)
            destroysGameWorld(gameWindow->game.gw);

    }
}
