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


    rm.menu.bigNormalStartButton = LoadTexture("Assets/Textures/BotaoIniciarNormalGrande.png");
    rm.menu.bigMouseStartButton = LoadTexture("Assets/Textures/BotaoIniciarMouseGrande.png");

    rm.menu.bigNormalLoadButton = LoadTexture("Assets/Textures/BotaoCarregarNormalGrande.png");
    rm.menu.bigMouseLoadButton = LoadTexture("Assets/Textures/BotaoCarregarMouseGrande.png");

    rm.menu.bigNormalHelpButton = LoadTexture("Assets/Textures/BotaoAjudaNormalGrande.png");
    rm.menu.bigMouseHelpButton = LoadTexture("Assets/Textures/BotaoAjudaMouseGrande.png");

    rm.menu.bigNormalCloseButton = LoadTexture("Assets/Textures/BotaoFecharNormalGrande.png");
    rm.menu.bigMouseCloseButton = LoadTexture("Assets/Textures/BotaoFecharMouseGrande.png");


    rm.pause.normalReturnButton = LoadTexture("Assets/Textures/BotaoRetomarNormal.png");
    rm.pause.mouseReturnButton = LoadTexture("Assets/Textures/BotaoRetomarMouse.png");

    rm.pause.normalSaveButton = LoadTexture("Assets/Textures/BotaoSalvarNormal.png");
    rm.pause.mouseSaveButton = LoadTexture("Assets/Textures/BotaoSalvarMouse.png");

    rm.pause.normalLeaveButton = LoadTexture("Assets/Textures/BotaoSairNormal.png");
    rm.pause.mouseLeaveButton = LoadTexture("Assets/Textures/BotaoSairMouse.png");


    rm.gl.bench = LoadTexture("Assets/Textures/Banch.png");


    rm.gw.defaultTile = LoadTexture("Assets/Textures/DefaultTile.png");

    rm.gw.horizontalPowerA = LoadTexture("Assets/Textures/HorizontalPowerA.png");
    rm.gw.horizontalPowerB = LoadTexture("Assets/Textures/HorizontalPowerB.png");

    rm.gw.ticketRU= LoadTexture("Assets/Textures/TicketRU.png");



    rm.player.fiveHearts = LoadTexture("Assets/Textures/5corações.png");
    rm.player.fourHearts = LoadTexture("Assets/Textures/4corações.png");
    rm.player.treeHearts = LoadTexture("Assets/Textures/3corações.png");
    rm.player.twoHearts = LoadTexture("Assets/Textures/2corações.png");
    rm.player.oneHearts = LoadTexture("Assets/Textures/1corações.png");

    rm.player.hit5Heart = LoadTexture("Assets/Textures/hit5heart.png");


    rm.player.fiveHeartsG = LoadTexture("Assets/Textures/5coraçõesG.png");
    rm.player.fourHeartsG = LoadTexture("Assets/Textures/4coraçõesG.png");
    rm.player.treeHeartsG = LoadTexture("Assets/Textures/3coraçõesG.png");
    rm.player.twoHeartsG = LoadTexture("Assets/Textures/2coraçõesG.png");
    rm.player.oneHeartsG = LoadTexture("Assets/Textures/1coraçõesG.png");

    rm.player.zeroAura = LoadTexture("Assets/Textures/0aura.png");
    rm.player.oneAura = LoadTexture("Assets/Textures/1aura.png");
    rm.player.twoAura = LoadTexture("Assets/Textures/2aura.png");
    rm.player.treeAura = LoadTexture("Assets/Textures/3aura.png");
    rm.player.fourAura = LoadTexture("Assets/Textures/4aura.png");
    rm.player.fiveAura = LoadTexture("Assets/Textures/5aura.png");
    rm.player.sixAura = LoadTexture("Assets/Textures/6aura.png");

    rm.player.zeroAuraG = LoadTexture("Assets/Textures/0auraGrande.png");
    rm.player.oneAuraG = LoadTexture("Assets/Textures/1auraGrande.png");
    rm.player.twoAuraG = LoadTexture("Assets/Textures/2auraGrande.png");
    rm.player.treeAuraG = LoadTexture("Assets/Textures/3auraGrande.png");
    rm.player.fourAuraG = LoadTexture("Assets/Textures/4auraGrande.png");
    rm.player.fiveAuraG = LoadTexture("Assets/Textures/5auraGrande.png");
    rm.player.sixAuraG = LoadTexture("Assets/Textures/6auraGrande.png");

    rm.player.auraLeek = LoadTexture("Assets/Textures/auraLeek.png");
    rm.player.auraLeekG = LoadTexture("Assets/Textures/auraLeekG.png");

    rm.player.ticketsRU1 = LoadTexture("Assets/Textures/ticketRU1.png");
    rm.player.ticketsRU2 = LoadTexture("Assets/Textures/ticketRU2.png");
    rm.player.ticketsRU1G = LoadTexture("Assets/Textures/ticketRU1G.png");
    rm.player.ticketsRU2G = LoadTexture("Assets/Textures/ticketRU2G.png");

    rm.player.restingPlayer[0] = LoadTexture("Assets/Textures/restingPlayer.png");
    rm.player.restingPlayer[1] = LoadTexture("Assets/Textures/restingPlayer2.png");
    rm.player.normalPlayer = LoadTexture("Assets/Textures/normalPlayer.png");
    rm.player.playerRunning[0] = LoadTexture("Assets/Textures/playerRunning.png");
    rm.player.playerRunning[1] = LoadTexture("Assets/Textures/playerRunning2.png");
    rm.player.playerJumping[0] = LoadTexture("Assets/Textures/playerJumping.png");
    rm.player.playerJumping[1] = LoadTexture("Assets/Textures/playerJumping2.png");
    rm.player.playerFalling[0] = LoadTexture("Assets/Textures/playerFalling.png");
    rm.player.playerFalling[1] = LoadTexture("Assets/Textures/playerFalling2.png");
    rm.player.playerDash = LoadTexture("Assets/Textures/playerDash.png");
    rm.player.playerDoubleJump = LoadTexture("Assets/Textures/playerDoubleJump.png");
    rm.player.playerChiclete = LoadTexture("Assets/Textures/playerChiclete.png");
    rm.player.playerAttack = LoadTexture("Assets/Textures/playerAttacks.png");

    rm.player.swordAttack = LoadTexture("Assets/Textures/swordAttack.png");


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


    UnloadTexture(rm.menu.bigNormalStartButton);
    UnloadTexture(rm.menu.bigMouseStartButton );

    UnloadTexture(rm.menu.bigNormalLoadButton);
    UnloadTexture(rm.menu.bigMouseLoadButton);

    UnloadTexture(rm.menu.bigNormalHelpButton);
    UnloadTexture(rm.menu.bigMouseHelpButton);

    UnloadTexture(rm.menu.bigNormalCloseButton);
    UnloadTexture(rm.menu.bigMouseCloseButton);

    UnloadTexture(rm.pause.normalReturnButton);
    UnloadTexture(rm.pause.mouseReturnButton);

    UnloadTexture(rm.pause.normalSaveButton);
    UnloadTexture(rm.pause.mouseSaveButton);

    UnloadTexture(rm.pause.normalLeaveButton);
    UnloadTexture(rm.pause.mouseLeaveButton);


    UnloadTexture(rm.gl.bench);


    UnloadTexture(rm.gw.defaultTile);

    UnloadTexture(rm.gw.horizontalPowerA);
    UnloadTexture(rm.gw.horizontalPowerB);

    UnloadTexture(rm.gw.ticketRU);



    UnloadTexture(rm.player.fiveHearts );
    UnloadTexture(rm.player.fourHearts );
    UnloadTexture(rm.player.treeHearts );
    UnloadTexture(rm.player.twoHearts );
    UnloadTexture(rm.player.oneHearts );

    UnloadTexture(rm.player.hit5Heart);

    UnloadTexture(rm.player.fiveHeartsG );
    UnloadTexture(rm.player.fourHeartsG );
    UnloadTexture(rm.player.treeHeartsG );
    UnloadTexture(rm.player.twoHeartsG );
    UnloadTexture(rm.player.oneHeartsG );

    UnloadTexture(rm.player.zeroAura);
    UnloadTexture(rm.player.oneAura);
    UnloadTexture(rm.player.twoAura);
    UnloadTexture(rm.player.treeAura);
    UnloadTexture(rm.player.fourAura);
    UnloadTexture(rm.player.fiveAura);
    UnloadTexture(rm.player.sixAura);

    UnloadTexture(rm.player.zeroAuraG);
    UnloadTexture(rm.player.oneAuraG);
    UnloadTexture(rm.player.twoAuraG);
    UnloadTexture(rm.player.treeAuraG);
    UnloadTexture(rm.player.fourAuraG);
    UnloadTexture(rm.player.fiveAuraG);
    UnloadTexture(rm.player.sixAuraG);

    UnloadTexture(rm.player.auraLeek);
    UnloadTexture(rm.player.auraLeekG);

    UnloadTexture(rm.player.ticketsRU1);
    UnloadTexture(rm.player.ticketsRU2);

    UnloadTexture(rm.player.ticketsRU1G);
    UnloadTexture(rm.player.ticketsRU2G);

    UnloadTexture(rm.player.restingPlayer[0]);
    UnloadTexture(rm.player.restingPlayer[1]);
    UnloadTexture(rm.player.normalPlayer);
    UnloadTexture(rm.player.playerRunning[0]);
    UnloadTexture(rm.player.playerRunning[1]);
    UnloadTexture(rm.player.playerJumping[0]);
    UnloadTexture(rm.player.playerJumping[1]);
    UnloadTexture(rm.player.playerFalling[0]);
    UnloadTexture(rm.player.playerFalling[1]);
    UnloadTexture(rm.player.playerDash);
    UnloadTexture(rm.player.playerDoubleJump );
    UnloadTexture(rm.player.playerChiclete);
    UnloadTexture(rm.player.playerAttack);

    UnloadTexture(rm.player.swordAttack);
}
