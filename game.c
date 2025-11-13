#include "raylib.h"
#include "game.h"
#include "player.h"
#include "resourceManager.h"

Game createGame()
{
    Game newGame = (Game)
    {
        .status = GAMELOBBY,
        .player = createNewPlayer((Vector2){32,32}, BLUE),
        .gameWorldInitiate = false,
    };

    newGame.gl = createGameLobby(&newGame.player);

    newGame.playerLobbyFirstPos = newGame.player.pos;

    newGame.playerGameWorldFirstPos = (Vector2){0,0};

    loadResources();

    return newGame;

}


void initGame(Game *game, bool isFullScreen)
{

    switch(game->status)
    {
        case GAMELOBBY:

            if(IsKeyPressed(KEY_ENTER))
            {
                game->status = GAMEWORLD;

                if(game->gameWorldInitiate)
                {
                    game->gw->player->pos = game->playerGameWorldFirstPos;
                }
            }

            inputAndUpdateGameLobby(&game->gl, isFullScreen);

            drawGameLobby(&game->gl);
            break;

        case GAMEWORLD:

            if(IsKeyPressed(KEY_ENTER))
            {
                game->status = GAMELOBBY;

                game->gl.player->pos = game->playerLobbyFirstPos;
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

            inputAndUpdateGameWorld(game->gw, isFullScreen);

            drawGameWorld(game->gw);
            break;
            }
}
