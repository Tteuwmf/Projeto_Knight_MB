#ifndef SAVE_H
#define SAVE_H

#include "raylib.h"
#include "entities/player.h"

void saveGame(const char *saveName, Player player);

Player loadGame(const char *saveName);

bool checkEmptySaveSlot(const char *saveName);

#endif // SAVE_H
