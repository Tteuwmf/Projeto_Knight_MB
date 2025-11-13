#include "raylib.h"
#include "menu.h"
#include "resourceManager.h"

const int X_MENU_BUTTON = 20;
const int Y_START_BUTTON = 30;
const int Y_LOAD_BUTTON = 60;
const int Y_HELP_BUTTON = 90;
const int Y_CLOSE_BUTTON = 120;

void inputUpdateAndDrawMenu(Game *game)
{

    Vector2 mousePosition = GetMousePosition();

    Rectangle startArea = {X_MENU_BUTTON, Y_START_BUTTON, (int) rm.menu.normalStartButton.width, (int) rm.menu.normalStartButton.height};
    Rectangle loadArea = {X_MENU_BUTTON, Y_LOAD_BUTTON, (int) rm.menu.normalLoadButton.width, (int) rm.menu.normalLoadButton.height};
    Rectangle helpArea = {X_MENU_BUTTON, Y_HELP_BUTTON, (int) rm.menu.normalHelpButton.width, (int) rm.menu.normalHelpButton.height};
    Rectangle closeArea = {X_MENU_BUTTON, Y_CLOSE_BUTTON, (int) rm.menu.normalCloseButton.width, (int) rm.menu.normalCloseButton.height};

    bool mouseOnStartButton = CheckCollisionPointRec(mousePosition, startArea);
    bool mouseOnLoadButton = CheckCollisionPointRec(mousePosition, loadArea);
    bool mouseOnHelpButton = CheckCollisionPointRec(mousePosition, helpArea);
    bool mouseOnCloseButton = CheckCollisionPointRec(mousePosition, closeArea);

    if(mouseOnStartButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = GAMELOBBY;

    else if(mouseOnLoadButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = LOAD;

    else if(mouseOnHelpButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = HELP;

    else if(mouseOnCloseButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = LEAVE;

    //------------------------------------------------------------------

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    if (mouseOnStartButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.mouseStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.normalStartButton, X_MENU_BUTTON, Y_START_BUTTON, WHITE);
            // Botao de Carregar jogo
    if (mouseOnLoadButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.mouseLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.normalLoadButton, X_MENU_BUTTON, Y_LOAD_BUTTON, WHITE);
            // Botao de Ajuda
    if (mouseOnHelpButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DrawTexture(rm.menu.clickHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);
        else
            DrawTexture(rm.menu.mouseHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);
    }
    else
        DrawTexture(rm.menu.normalHelpButton, X_MENU_BUTTON, Y_HELP_BUTTON, WHITE);




    // Botao de Fechar jogo
    if (mouseOnCloseButton)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            DrawTexture(rm.menu.clickCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);
            //if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        }
        else
            DrawTexture(rm.menu.mouseCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);
    }

    else
        DrawTexture(rm.menu.normalCloseButton, X_MENU_BUTTON, Y_CLOSE_BUTTON, WHITE);

    EndDrawing();
}
