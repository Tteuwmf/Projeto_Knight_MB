#include "raylib.h"
#include "resourceManager.h"

ResourceManager rm = {0};

void loadResources()
{
    rm.menu.normalStartButton = LoadTexture("Assets/Textures/BotaoIniciarNormal.png");
    rm.menu.mouseStartButton = LoadTexture("Assets/Textures/BotaoIniciarMouse.png");
    rm.menu.clickStartButton = LoadTexture("Assets/Textures/BotaoIniciarClicado.png");

    rm.menu.normalLoadButton = LoadTexture("Assets/Textures/BotaoCarregarNormal.png");
    rm.menu.mouseLoadButton = LoadTexture("Assets/Textures/BotaoCarregarMouse.png");
    rm.menu.clickLoadButton = LoadTexture("Assets/Textures/BotaoCarregarClicado.png");

    rm.menu.normalHelpButton = LoadTexture("Assets/Textures/BotaoAjudaNormal.png");
    rm.menu.mouseHelpButton = LoadTexture("Assets/Textures/BotaoAjudaMouse.png");
    rm.menu.clickHelpButton = LoadTexture("Assets/Textures/BotaoAjudaClick.png");

    rm.menu.normalCloseButton = LoadTexture("Assets/Textures/BotaoFecharNormal.png");
    rm.menu.mouseCloseButton = LoadTexture("Assets/Textures/BotaoFecharMouse.png");
    rm.menu.clickCloseButton = LoadTexture("Assets/Textures/BotaoFecharClick.png");


    rm.pause.normalReturnButton = LoadTexture("Assets/Textures/BotaoRetomarNormal.png");
    rm.pause.mouseReturnButton = LoadTexture("Assets/Textures/BotaoRetomarMouse.png");

    rm.pause.normalSaveButton = LoadTexture("Assets/Textures/BotaoSalvarNormal.png");
    rm.pause.mouseSaveButton = LoadTexture("Assets/Textures/BotaoSalvarMouse.png");

    rm.pause.normalLeaveButton = LoadTexture("Assets/Textures/BotaoSairNormal.png");
    rm.pause.mouseLeaveButton = LoadTexture("Assets/Textures/BotaoSairMouse.png");


    rm.gw.defaultTile = LoadTexture("Assets/Textures/DefaultTile.png");

    rm.gw.horizontalPowerA = LoadTexture("Assets/Textures/HorizontalPowerA.png");
    rm.gw.horizontalPowerB = LoadTexture("Assets/Textures/HorizontalPowerB.png");

    rm.gw.ticketRU= LoadTexture("Assets/Textures/TicketRU.png");
}

void unloadResouces()
{
    UnloadTexture(rm.menu.normalStartButton);
    UnloadTexture(rm.menu.mouseStartButton);
    UnloadTexture(rm.menu.clickStartButton );

    UnloadTexture(rm.menu.normalLoadButton);
    UnloadTexture(rm.menu.mouseLoadButton);
    UnloadTexture(rm.menu.clickLoadButton);

    UnloadTexture(rm.menu.normalHelpButton);
    UnloadTexture(rm.menu.mouseHelpButton);
    UnloadTexture(rm.menu.clickHelpButton);

    UnloadTexture(rm.menu.normalCloseButton);
    UnloadTexture(rm.menu.mouseCloseButton);
    UnloadTexture(rm.menu.clickCloseButton);


    UnloadTexture(rm.pause.normalReturnButton);
    UnloadTexture(rm.pause.mouseReturnButton);

    UnloadTexture(rm.pause.normalSaveButton);
    UnloadTexture(rm.pause.mouseSaveButton);

    UnloadTexture(rm.pause.normalLeaveButton);
    UnloadTexture(rm.pause.mouseLeaveButton);


    UnloadTexture(rm.gw.defaultTile);

    UnloadTexture(rm.gw.horizontalPowerA);
    UnloadTexture(rm.gw.horizontalPowerB);

    UnloadTexture(rm.gw.ticketRU);

}
