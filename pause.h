#ifndef PAUSE_H
#define PAUSE_H

#include "raylib.h"
#include "resourceManager.h"
#include "game.h"

void inputUpdateAndDrawPause(Game *game, GameStatus lastStatus);

void inputUpdateAndDrawConfirm(Game *game);


#endif // PAUSE_H
