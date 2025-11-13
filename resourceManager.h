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

typedef struct GameWorldTextures
{
    Texture2D defaultTile;

}GameWorldTextures;

typedef struct ResourceManager
{
    MenuTextures menu;
    PauseTextures pause;
    GameWorldTextures gw;

}ResourceManager;

extern ResourceManager rm;

void loadResources();

void unloadResouces();



#endif // RESOURCEMANAGER_H
