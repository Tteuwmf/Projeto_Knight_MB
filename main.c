#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "gameWindow.h"


int main()
{
    GameWindow *gameWindow = createGameWindow (800, 450);

    initGameWindow(gameWindow);

    free(gameWindow);

    return 0;
}
