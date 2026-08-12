#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "game_atributes/gameWindow.h"


int main()
{
    GameWindow *gameWindow = createGameWindow (800, 450);

    initGameWindow(gameWindow);

    free(gameWindow);
    gameWindow=NULL;

    return 0;
}
