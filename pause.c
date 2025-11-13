#include "raylib.h"
#include "pause.h"

const int X_PAUSE_BUTTON = 354;
const int Y_RETURN_BUTTON = 175;
const int Y_SAVE_BUTTON = 230;
const int Y_LEAVE_BUTTON = 285;

void inputUpdateAndDrawPause(Game *game, GameStatus lastStatus)
{

    Vector2 mousePosition = GetMousePosition();

    Rectangle returnArea = {X_PAUSE_BUTTON, Y_RETURN_BUTTON, (int) rm.pause.normalReturnButton.width, (int) rm.pause.normalReturnButton.height};
    Rectangle saveArea = {X_PAUSE_BUTTON, Y_SAVE_BUTTON, (int) rm.pause.normalSaveButton.width, (int) rm.pause.normalSaveButton.height};
    Rectangle leaveArea = {X_PAUSE_BUTTON, Y_LEAVE_BUTTON, (int) rm.pause.normalLeaveButton.width, (int) rm.pause.normalLeaveButton.height};

    bool mouseOnReturnButton = CheckCollisionPointRec(mousePosition, returnArea);
    bool mouseOnSaveButton = CheckCollisionPointRec(mousePosition, saveArea);
    bool mouseOnLeaveButton = CheckCollisionPointRec(mousePosition, leaveArea);

    if(mouseOnReturnButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = lastStatus;

    if(mouseOnLeaveButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = CONFIRM;

    //---------------------------------------------------

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
    DrawRectangle(266, 0, 266, 450, BLACK);
    DrawText("JOGO PAUSADO!!", 300, 40, 25, WHITE);

    if (mouseOnReturnButton)
        DrawTexture(rm.pause.mouseReturnButton, X_PAUSE_BUTTON, Y_RETURN_BUTTON, WHITE);
    else
        DrawTexture(rm.pause.normalReturnButton, X_PAUSE_BUTTON, Y_RETURN_BUTTON, WHITE);


    if (mouseOnSaveButton)
        DrawTexture(rm.pause.mouseSaveButton, X_PAUSE_BUTTON, Y_SAVE_BUTTON, WHITE);
    else
        DrawTexture(rm.pause.normalSaveButton, X_PAUSE_BUTTON, Y_SAVE_BUTTON, WHITE);


    if (mouseOnLeaveButton)
        DrawTexture(rm.pause.mouseLeaveButton, X_PAUSE_BUTTON, Y_LEAVE_BUTTON, WHITE);
    else
        DrawTexture(rm.pause.normalLeaveButton, X_PAUSE_BUTTON, Y_LEAVE_BUTTON, WHITE);

    EndDrawing();
}

void inputUpdateAndDrawConfirm(Game *game)
{
    Vector2 mousePosition = GetMousePosition();

    Rectangle yesArea = {((GetScreenWidth()/2)-73), ((GetScreenHeight()/2)+15),32,15};
    Rectangle noArea = {((GetScreenWidth()/2)+41), ((GetScreenHeight()/2)+15),32,15};

    bool mouseOnYesButton = CheckCollisionPointRec(mousePosition, yesArea);
    bool mouseOnNoButton = CheckCollisionPointRec(mousePosition, noArea);

    if ( mouseOnNoButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = PAUSE;

    if (mouseOnYesButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        game->status = MENU;

    //-----------------------------------------------

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    DrawRectangle(((GetScreenWidth()/2) - 200), ((GetScreenHeight()/2) - 50), 400, 100, BLACK);
    DrawText("Voce deseja mesmo sair?", ((GetScreenWidth()/2) - 62), ((GetScreenHeight()/2) - 34), 5, WHITE);
    DrawText("Todo o progresso nao salvo sera perdido!", ((GetScreenWidth()/2) - 150), ((GetScreenHeight()/2) - 16), 15, RED);
    DrawText("SIM", ((GetScreenWidth()/2) - 71), ((GetScreenHeight()/2) + 15), 15, WHITE);
    DrawText("NAO", ((GetScreenWidth()/2) + 43), ((GetScreenHeight()/2) + 15), 15, WHITE);

    EndDrawing();
}

