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

typedef struct PlayerTextures
{
    Texture2D fiveHearts;
    Texture2D fourHearts;
    Texture2D treeHearts;
    Texture2D twoHearts;
    Texture2D oneHearts;

    Texture2D zeroAura;
    Texture2D oneAura;
    Texture2D twoAura;
    Texture2D treeAura;
    Texture2D fourAura;
    Texture2D fiveAura;
    Texture2D sixAura;

    Texture2D zeroAuraG;
    Texture2D oneAuraG;
    Texture2D twoAuraG;
    Texture2D treeAuraG;
    Texture2D fourAuraG;
    Texture2D fiveAuraG;
    Texture2D sixAuraG;

}PlayerTextures;

typedef struct ResourceManager
{
    MenuTextures menu;
    PauseTextures pause;
    GameLobbyTextures gl;
    GameWorldTextures gw;
    PlayerTextures player;

}ResourceManager;

extern ResourceManager rm;

void loadResources();

void unloadResouces();



#endif // RESOURCEMANAGER_H
