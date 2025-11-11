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

        gameWindow->game = createGame();

        SetTargetFPS(60);

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

            initGame(&gameWindow->game, isFullScreen);

        }

        CloseWindow();
        destroysGameWorld(gameWindow->game.gw);

    }
}
