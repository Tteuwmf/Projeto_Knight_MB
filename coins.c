#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "coins.h"




Coins summonCoins(BasicEnemy *enemy, int number)
{

    return (Coins)
    {
        .pos = (Vector2){enemy->pos.x+(enemy->dim.x/2),enemy->pos.y+(enemy->dim.y/2)},
        .dim = (Vector2){8,8},
        .speed = (Vector2){100*number,-500},
        .friction = 0.95f,
        .cor = YELLOW,
        .available = true,
    };
}


void drawCoins(Coins *coin)
{
    if(coin->available)
        DrawRectangleV(coin->pos, coin->dim,coin->cor);
}
