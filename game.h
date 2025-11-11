#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include"gameLobby.h"
#include "gameWorld.h"

typedef enum GameStatus
{
    MENU = 0,
    PAUSE,
    GAMELOBBY,
    GAMEWORLD,

} GameStatus;

typedef struct Game
{
    GameStatus status;

    Player player;

    GameLobby gl;
    Vector2 playerLobbyFirstPos;

    GameWorld *gw;
    Vector2 playerGameWorldFirstPos;

    bool gameWorldInitiate;

}Game;

Game createGame();

void initGame(Game *game, bool isFullScreen);


#endif // GAME_H
