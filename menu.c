#include "raylib.h"
#include "menu.h"
#include "resourceManager.h"

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
        game->gl.player->pos = game->playerLobbyFirstPos;
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
