#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "raylib.h"

typedef struct MenuTextures
{
    Texture2D normalStartButton;
    Texture2D mouseStartButton;
    Texture2D clickStartButton;

    Texture2D normalLoadButton;
    Texture2D mouseLoadButton;
    Texture2D clickLoadButton;

    Texture2D normalHelpButton;
    Texture2D mouseHelpButton;
    Texture2D clickHelpButton;

    Texture2D normalCloseButton;
    Texture2D mouseCloseButton;
    Texture2D clickCloseButton;


    Texture2D bigNormalStartButton;
    Texture2D bigMouseStartButton;

    Texture2D bigNormalLoadButton;
    Texture2D bigMouseLoadButton;

    Texture2D bigNormalHelpButton;
    Texture2D bigMouseHelpButton;

    Texture2D bigNormalCloseButton;
    Texture2D bigMouseCloseButton;

}MenuTextures;

typedef struct PauseTextures
{
    Texture2D normalReturnButton;
    Texture2D mouseReturnButton;

    Texture2D normalSaveButton;
    Texture2D mouseSaveButton;

    Texture2D normalLeaveButton;
    Texture2D mouseLeaveButton;

}PauseTextures;

typedef struct GameLobbyTextures
{
    Texture2D bench;

}GameLobbyTextures;

typedef struct GameWorldTextures
{
    Texture2D defaultTile;

    Texture2D horizontalPowerA;
    Texture2D horizontalPowerB;

    Texture2D ticketRU;

}GameWorldTextures;

typedef struct ResourceManager
{
    MenuTextures menu;
    PauseTextures pause;
    GameLobbyTextures gl;
    GameWorldTextures gw;

}ResourceManager;

extern ResourceManager rm;

void loadResources();

void unloadResouces();



#endif // RESOURCEMANAGER_H
