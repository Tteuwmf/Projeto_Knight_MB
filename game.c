#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "game.h"
#include "player.h"
#include "resourceManager.h"
#include "menu.h"
#include "pause.h"

Game createGame()
{
    Game newGame = (Game)
    {
        .status = MENU,
        .lastStatus = MENU,
        .player = createNewPlayer((Vector2){32,32}, BLUE),
        .gameWorldInitiate = false,
        .fadeScreenMenus = 0.0,
        .timeToCode = 0.0,

        .playerLobbyFirstPos = (Vector2){0,0},
        .playerLobbyReturnPos = (Vector2){0,0},
        .playerGameWorldFirstPos = (Vector2){0,0}
    };

    loadResources();

    return newGame;

}


void initGame(Game *game, bool isFullScreen)
{

    game->gl.player = &game->player;

    switch(game->status)
    {
        case MENU:
            inputUpdateAndDrawMenu(game);
            break;

        case LOAD:
            break;

        case HELP:
            break;

        case PAUSE:
            inputUpdateAndDrawPause(game, isFullScreen);
            break;

        case CONFIRM:
            inputUpdateAndDrawConfirm(game);
            break;

        case GAMELOBBY:

            game->timeToCode -= GetFrameTime();
            if(game->timeToCode<=0)
                game->timeToCode = 0.0;

            if(IsKeyPressed(KEY_ENTER) && game->gl.nearComputer && game->timeToCode==0.0)
            {
                game->status = GAMEWORLD;

                if(game->gameWorldInitiate)
                {
                    game->gw->player->pos = game->playerGameWorldFirstPos;
                }
            }

            if(IsKeyPressed(KEY_ESCAPE))
            {
                game->lastStatus = game->status;
                game->status = PAUSE;
            }


            inputAndUpdateGameLobby(&game->gl, isFullScreen);

            drawGameLobby(&game->gl);
            break;

        case GAMEWORLD:

            //---------CRIA MUNDO--------

            if(game->gameWorldInitiate==false)
            {
                game->gw = createGameWorld(&game->player);

                game->gameWorldInitiate = true;
            }

            //---SALVA POSIÇÃO INICIAL---

            if (game->playerGameWorldFirstPos.x==0 && game->playerGameWorldFirstPos.y ==0 && game->gameWorldInitiate)
            {
                game->playerGameWorldFirstPos = game->gw->player->pos;
            }

            //---------PAUSE---------

            if(IsKeyPressed(KEY_ESCAPE))
            {
                game->lastStatus = game->status;
                game->status = PAUSE;
            }

            //---------FIM DE JOGO----------

            if(game->gw->player->status.dead && GetKeyPressed() && game->gw->fadeScreenGW>=1)
            {
                game->status = MENU;
                resetPlayer(game->gw->player);
                resetGameLobby(&game->gl, game->playerLobbyFirstPos);
                destroysGameWorld(game->gw);
                game->gameWorldInitiate = false;
            }
            else

            //-----------UPDATE MUNDO--------

            inputAndUpdateGameWorld(game->gw, isFullScreen);

            //---------DESENHA MUNDO--------

            drawGameWorld(game->gw);

            //--------TROCA MUNDO--------

            if(IsKeyPressed(KEY_ENTER)&& game->gw->canLeaveFase)
            {
                game->status = GAMELOBBY;

                if(game->playerLobbyReturnPos.x != 0 || game->playerLobbyReturnPos.y != 0) {
                    game->gl.player->pos = game->playerLobbyReturnPos;
                } else {
                    game->gl.player->pos = game->playerLobbyFirstPos;
                }

                game->gl.player->speed.y = -200;
                game->gl.player->speed.x = -100;
                game->player.progress++;

                game->timeToCode = 2.0;

                destroysGameWorld(game->gw);

                game->gameWorldInitiate = false;

            }

            break;


        case LEAVE:
            game->shouldClose = true;
            break;
    }
}
