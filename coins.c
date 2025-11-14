#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "coins.h"
#include "resourceManager.h"


Skill createSkill(Vector2 pos, int number)
{
    return (Skill)
    {
        .pos = pos,
        .dim = (Vector2){16,16},
        .cor = PINK,
        .skilNumber = number,
        .available = true,
        .playerNext = false,
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
        .playerNext = false,
    };
}

void drawSkills(Skill *skill)
{
    if(skill->available)
    {
        DrawRectangleV(skill->pos, skill->dim,skill->cor);
        if (skill->playerNext)
        {
            DrawText(TextFormat("PEGAR: W"), skill->pos.x-16,skill->pos.y-16,5, GREEN);
        }
    }
}

void drawCharms(Charm *charm)
{
    if(charm->available)
    {
        DrawRectangleV(charm->pos, charm->dim,charm->cor);
        if (charm->playerNext)
        {
            DrawText(TextFormat("PEGAR: W"), charm->pos.x-16,charm->pos.y-16,5, GREEN);
        }
    }
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
        DrawTextureV(rm.gw.ticketRU,coin->pos,coin->cor);
}
