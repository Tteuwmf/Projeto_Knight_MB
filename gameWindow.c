#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "gameWindow.h"

GameWindow* createGameWindow(int width, int height)
{
    GameWindow *gameWindow = (GameWindow*) malloc(sizeof(GameWindow));

    gameWindow->width = width;
    gameWindow->height = height;
    gameWindow->gw = NULL;
    gameWindow->initiate = false;

    return gameWindow;
}

void initGameWindow(GameWindow *gameWindow)
{
    if(!gameWindow->initiate)
    {
        gameWindow->initiate = true;

        InitWindow (gameWindow->width, gameWindow->height, "JOGO2.0");

        gameWindow->gw = createGameWorld();

        SetTargetFPS(60);

        while (!WindowShouldClose())
        {
            inputAndUpdateGameWorld(gameWindow->gw);

            drawGameWorld(gameWindow->gw);
        }


        CloseWindow();
        destroysGameWorld(gameWindow->gw);


    }
}
