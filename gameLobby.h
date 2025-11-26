#ifndef GAMELOBBY_H
#define GAMELOBBY_H

#include "raylib.h"
#include "player.h"
#include "blocks.h"

typedef struct GameLobby
{
    Player *player;

    Block blocks[3000];
    int numberOfBlocks;

    Rectangle Banch;
    bool nearBanch;

    Rectangle Room;
    bool nearRoom;
    bool roomCamera;

    Rectangle Computer;
    bool nearComputer;
    Vector2 posComputer;

    Rectangle DoorR;
    bool nearRoomDoor;

    Rectangle Store;
    bool nearStore;

    Camera2D camera;

    float fadeScreenGL;

}GameLobby;

GameLobby createGameLobby(Player *player);

void loadLobby (GameLobby *gl, const char* arquivo);

void inputAndUpdateGameLobby(GameLobby *gl, bool isFullscreen);

void makeLobbyCollisionPlayerBlock (GameLobby *gl);

void makeLobbyCollisionBlocksPowersAndWeapons (GameLobby *gl);

void drawGameLobby (GameLobby *gl, bool isFullscreen);

void updateLobbyCamera(Camera2D *camera, Player *player, bool isFullscreen, bool roomCamera);

void resetGameLobby(GameLobby *gl, Vector2 startPos);


#endif // GAMELOBBY_H
