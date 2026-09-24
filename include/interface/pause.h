#ifndef PAUSE_H
#define PAUSE_H

#include "raylib.h"
#include "resources/resourceManager.h"

// Forward declarations para desacoplamento de includes circulares
typedef struct Game Game;
typedef struct GameWorld GameWorld;

void inputUpdateAndDrawPause(Game *game, bool* isFullscreen);

void inputUpdateAndDrawConfirm(Game *game);

void inputUpdateDeathScreen(Game *game);

void drawDeathScreen(GameWorld *gw);

#endif // PAUSE_H
