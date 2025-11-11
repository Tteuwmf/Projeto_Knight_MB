#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include"gameLobby.h"
#include "gameWorld.h"

typedef enum GameStatus
{
    MENU,
    PAUSE,
    GAMELOBBY,
    GAMEWORLD,

} GameStatus;

typedef struct Game
{
    GameStatus status;

    Player *player;

    GameLobby gl;

    GameWorld *gw;
    bool gameWorldInitiate;
}Game;

Game createGame();

void initGame();


#endif // GAME_H
