#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "game_atributes/gameWindow.h"
#include "resources/global.h"


int main()
{
    GameWindow *gameWindow = createGameWindow (INITWINDOW_WIDTH, INITWINDOW_HEIGHT);

    initGameWindow(gameWindow);

    free(gameWindow);
    gameWindow=NULL;

    return 0;
}
