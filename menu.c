#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "resourceManager.h"
#include "save.h"

const int X_MENU_BUTTON = 200;
const int Y_START_BUTTON = 100;
const int Y_LOAD_BUTTON = 160;
const int Y_HELP_BUTTON = 220;
const int Y_CLOSE_BUTTON = 280;

void inputUpdateAndDrawMenu(Game *game)
{

    Vector2 mousePosition = GetMousePosition();

    Rectangle startArea = {X_MENU_BUTTON, Y_START_BUTTON, (int) rm.menu.bigNormalStartButton.width, (int) rm.menu.bigNormalStartButton.height};
    Rectangle loadArea = {X_MENU_BUTTON, Y_LOAD_BUTTON, (int) rm.menu.bigNormalLoadButton.width, (int) rm.menu.bigNormalLoadButton.height};
    Rectangle helpArea = {X_MENU_BUTTON, Y_HELP_BUTTON, (int) rm.menu.bigNormalHelpButton.width, (int) rm.menu.bigNormalHelpButton.height};
    Rectangle closeArea = {X_MENU_BUTTON, Y_CLOSE_BUTTON, (int) rm.menu.bigNormalCloseButton.width, (int) rm.menu.bigNormalCloseButton.height};

    bool mouseOnStartButton = CheckCollisionPointRec(mousePosition, startArea);
    bool mouseOnLoadButton = CheckCollisionPointRec(mousePosition, loadArea);
    bool mouseOnHelpButton = CheckCollisionPointRec(mousePosition, helpArea);
    bool mouseOnCloseButton = CheckCollisionPointRec(mousePosition, closeArea);

    if(mouseOnStartButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        game->status = GAMELOBBY;

        game->gl = createGameLobby(&game->player);

        game->playerLobbyFirstPos = game->player.pos;

        game->playerLobbyReturnPos = game->gl.posComputer;

        printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
               game->playerLobbyReturnPos.x,
               game->playerLobbyReturnPos.y);

        game->gl.player->pos = game->playerLobbyFirstPos;

        if(checkEmptySaveSlot("save1"))
            game->saveSlot1 = true;
        else if (checkEmptySaveSlot("save2"))
            game->saveSlot2 = true;
        else if (checkEmptySaveSlot("save3"))
            game->saveSlot3 = true;
    }

    else if(mouseOnLoadButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = LOAD;

    else if(mouseOnHelpButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = HELP;

    else if(mouseOnCloseButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = LEAVE;

    //------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(BLACK);

    if (mouseOnStartButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.bigMouseStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.bigNormalStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
            // Botao de Carregar jogo
    if (mouseOnLoadButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.bigMouseLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.bigNormalLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
            // Botao de Ajuda
    if (mouseOnHelpButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.bigMouseHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.bigNormalHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);




    // Botao de Fechar jogo
    if (mouseOnCloseButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawTexture(rm.menu.clickCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);
            //if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        }
        else
            DrawTexture(rm.menu.bigMouseCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);
    }

    else
        DrawTexture(rm.menu.bigNormalCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);

    EndDrawing();
}



const int X_SLOTS_BUTTON = 200;
const int Y_SLOT1_BUTTON = 100;
const int Y_SLOT2_BUTTON = 160;
const int Y_SLOT3_BUTTON = 220;
const int Y_GOTOMENU_BUTTON = 280;

void inputUpdateAndDrawLoad(Game *game)
{

    Vector2 mousePosition = GetMousePosition();

    Rectangle startArea = {X_SLOTS_BUTTON, Y_SLOT1_BUTTON, (int) rm.menu.bigNormalStartButton.width, (int) rm.menu.bigNormalStartButton.height};
    Rectangle loadArea = {X_SLOTS_BUTTON, Y_SLOT2_BUTTON, (int) rm.menu.bigNormalLoadButton.width, (int) rm.menu.bigNormalLoadButton.height};
    Rectangle helpArea = {X_SLOTS_BUTTON, Y_SLOT3_BUTTON, (int) rm.menu.bigNormalHelpButton.width, (int) rm.menu.bigNormalHelpButton.height};
    Rectangle closeArea = {X_SLOTS_BUTTON, Y_GOTOMENU_BUTTON, (int) rm.menu.bigNormalCloseButton.width, (int) rm.menu.bigNormalCloseButton.height};

    bool mouseOnStartButton = CheckCollisionPointRec(mousePosition, startArea);
    bool mouseOnLoadButton = CheckCollisionPointRec(mousePosition, loadArea);
    bool mouseOnHelpButton = CheckCollisionPointRec(mousePosition, helpArea);
    bool mouseOnCloseButton = CheckCollisionPointRec(mousePosition, closeArea);

    if(mouseOnStartButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(checkEmptySaveSlot("save1")==false)
        {
            game->status = GAMELOBBY;
            game->saveSlot1 =true;
            game->player = loadGame("save1");

                game->playerLobbyFirstPos = game->player.pos;

                game->gl = createGameLobby(&game->player);

                game->playerLobbyReturnPos = game->gl.posComputer;

                printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
                       game->playerLobbyReturnPos.x,
                       game->playerLobbyReturnPos.y);

                game->gl.player->pos = game->playerLobbyFirstPos;
        }
    }

    else if(mouseOnLoadButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(checkEmptySaveSlot("save2")==false)
        {
            game->status = GAMELOBBY;
            game->saveSlot2 =true;
            game->player = loadGame("save2");

                game->playerLobbyFirstPos = game->player.pos;

                game->gl = createGameLobby(&game->player);

                game->playerLobbyReturnPos = game->gl.posComputer;

                printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
                       game->playerLobbyReturnPos.x,
                       game->playerLobbyReturnPos.y);

                game->gl.player->pos = game->playerLobbyFirstPos;
        }
    }

    else if(mouseOnHelpButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(checkEmptySaveSlot("save3")==false)
        {
            game->status = GAMELOBBY;
            game->saveSlot3 =true;
            game->player = loadGame("save3");

                game->playerLobbyFirstPos = game->player.pos;

                game->gl = createGameLobby(&game->player);

                game->playerLobbyReturnPos = game->gl.posComputer;

                printf("Posicao Retorno (M) -> X: %.2f, Y: %.2f\n",
                       game->playerLobbyReturnPos.x,
                       game->playerLobbyReturnPos.y);

                game->gl.player->pos = game->playerLobbyFirstPos;
        }
    }

    else if(mouseOnCloseButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = MENU;

    //------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(BLACK);

    if (mouseOnStartButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickStartButton, X_SLOTS_BUTTON, Y_SLOT1_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.bigMouseStartButton, X_SLOTS_BUTTON, Y_SLOT1_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.bigNormalStartButton, X_SLOTS_BUTTON, Y_SLOT1_BUTTON, WHITE);
            // Botao de Carregar jogo
    if (mouseOnLoadButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickLoadButton, X_SLOTS_BUTTON, Y_SLOT2_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.bigMouseLoadButton, X_SLOTS_BUTTON, Y_SLOT2_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.bigNormalLoadButton, X_SLOTS_BUTTON, Y_SLOT2_BUTTON, WHITE);
            // Botao de Ajuda
    if (mouseOnHelpButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickHelpButton, X_SLOTS_BUTTON, Y_SLOT3_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.bigMouseHelpButton, X_SLOTS_BUTTON, Y_SLOT3_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.bigNormalHelpButton, X_SLOTS_BUTTON, Y_SLOT3_BUTTON, WHITE);




    // Botao de Fechar jogo
    if (mouseOnCloseButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawTexture(rm.menu.clickCloseButton, X_SLOTS_BUTTON, Y_GOTOMENU_BUTTON, WHITE);
            //if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        }
        else
            DrawTexture(rm.menu.bigMouseCloseButton, X_SLOTS_BUTTON, Y_GOTOMENU_BUTTON, WHITE);
    }

    else
        DrawTexture(rm.menu.bigNormalCloseButton, X_SLOTS_BUTTON, Y_GOTOMENU_BUTTON, WHITE);

    EndDrawing();
}
