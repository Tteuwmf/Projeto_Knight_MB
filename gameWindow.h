#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "raylib.h"
#include "gameWorld.h"

typedef struct GameWindow
{
    int width;
    int height;
    GameWorld *gw;
    bool initiate;

}GameWindow;

GameWindow* createGameWindow(int width, int height);

void initGameWindow (GameWindow *gameWindow);

#endif // GAMEWINDOW_H
