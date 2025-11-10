#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "raylib.h"
#include "gameWorld.h"
#include "gameLobby.h"

typedef struct GameWindow
{
    int width;
    int height;

    GameLobby gl;

    GameWorld *gw;
    bool gameWorldInitiate;

    bool initiate;

}GameWindow;

GameWindow* createGameWindow(int width, int height);

void initGameWindow (GameWindow *gameWindow);

#endif // GAMEWINDOW_H
