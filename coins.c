#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "coins.h"


Skill createSkill(Vector2 pos, int number)
{
    return (Skill)
    {
        .pos = pos,
        .dim = (Vector2){16,16},
        .cor = PINK,
        .skilNumber = number,
        .available = true,
    };
}

Charm createCharm(Vector2 pos, int number)
{
    return (Charm)
    {
        .pos = pos,
        .dim = (Vector2){10,10},
        .cor = VIOLET,
        .charmNumber = number,
        .available = true,
    };
}

void drawSkills(Skill *skill)
{
    if(skill->available)
        DrawRectangleV(skill->pos, skill->dim,skill->cor);
}

void drawCharms(Charm *charm)
{
    if(charm->available)
        DrawRectangleV(charm->pos, charm->dim,charm->cor);
}

//=====================================
//-------------TICKETSRU---------------

Coins summonCoinsForBasicEnemies(BasicEnemy *enemy, int number)
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

Coins summonCoinsForAirBasicEnemies(AirBasicEnemy *enemy, int number)
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
