#include <string.h>
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
    };

    newGame.gl = createGameLobby(&newGame.player);

    newGame.playerLobbyFirstPos = newGame.player.pos;

    newGame.playerLobbyReturnPos = (Vector2) {newGame.gl.Computer.x,newGame.gl.Computer.y };

    newGame.playerGameWorldFirstPos = (Vector2){0,0};

    loadResources();

    return newGame;

}


void initGame(Game *game, bool isFullScreen)
{



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
            inputUpdateAndDrawPause(game);
            break;

        case CONFIRM:
            inputUpdateAndDrawConfirm(game);
            break;

        case GAMELOBBY:

            if(IsKeyPressed(KEY_ENTER))
            {
                game->status = GAMEWORLD;

                if(game->gameWorldInitiate)
                {
                    game->gw->player->pos = game->playerGameWorldFirstPos;
                }
            }

            if(IsKeyPressed(KEY_I))
            {
                game->lastStatus = game->status;
                game->status = PAUSE;
            }


            inputAndUpdateGameLobby(&game->gl, isFullScreen);

            drawGameLobby(&game->gl);
            break;

        case GAMEWORLD:

            if(IsKeyPressed(KEY_ENTER))
            {
                game->status = GAMELOBBY;

                game->gl.player->pos = game->playerLobbyFirstPos;

                //destroysGameWorld(game->gw);

                game->gameWorldInitiate = false;
            }

            if(game->gameWorldInitiate==false)
            {
                game->gw = createGameWorld(game->gl.player);

                game->gameWorldInitiate = true;
            }

            if (game->playerGameWorldFirstPos.x==0 && game->playerGameWorldFirstPos.y ==0 && game->gameWorldInitiate)
            {
                game->playerGameWorldFirstPos = game->gw->player->pos;
            }

            if(IsKeyPressed(KEY_I))
            {
                game->lastStatus = game->status;
                game->status = PAUSE;
            }

            if(game->gw->player->status.dead && GetKeyPressed() && game->gw->fadeScreenGW>=1)
            {
                game->status = MENU;
                resetPlayer(game->gw->player);
                //CRIAR AINDA UMA FUNÇÃO PARA RESETAR O LOBBY
                destroysGameWorld(game->gw);
                game->gameWorldInitiate = false;
            }
            else
            inputAndUpdateGameWorld(game->gw, isFullScreen);

            drawGameWorld(game->gw);
            break;


        case LEAVE:
            break;
    }
}
