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
        /*
        int monitor = GetCurrentMonitor();
        int monitorWidth = GetMonitorWidth(monitor);
        int monitorHeight = GetMonitorHeight(monitor);*/

        bool isFullScreen = false;

        //-------------------------------

        InitWindow (gameWindow->width, gameWindow->height, "JOGO2.0");

        gameWindow->gl = createGameLobby();

        //gameWindow->gw = createGameWorld();

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
                int salvaPosX=0;
                int salvaPosY=0;

                case 0:

                if(IsKeyPressed(KEY_ENTER))
                {
                    lobbyOrWorld++;

                    if(salvaPosX!=0 || salvaPosY!=0)
                    {
                        gameWindow->gw->player.pos.x = salvaPosX;
                        gameWindow->gw->player.pos.y = salvaPosY;
                    }
                }


                inputAndUpdateGameLobby(&gameWindow->gl, isFullScreen);

                drawGameLobby(&gameWindow->gl);
                break;

                case 1:

                if(IsKeyPressed(KEY_ENTER))
                    lobbyOrWorld--;

                if(gameWindow->gameWorldInitiate==false)
                {
                    gameWindow->gw = createGameWorld();

                            salvaPosX = gameWindow->gw->player.pos.x;
                            salvaPosY = gameWindow->gw->player.pos.y;

                    gameWindow->gameWorldInitiate = true;
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
