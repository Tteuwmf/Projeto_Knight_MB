#ifndef COINS_H
#define COINS_H

#include "raylib.h"
#include "enemies.h"

typedef struct Skill
{
    Vector2 pos;
    Vector2 dim;
    Color cor;
    int skilNumber;
    bool available;
    bool playerNext;

}Skill;

Skill createSkill(Vector2 pos, int number);

typedef struct Charm
{
    Vector2 pos;
    Vector2 dim;
    Color cor;
    int charmNumber;
    bool available;
    bool playerNext;

}Charm;

Charm createCharm(Vector2 pos, int number);

void drawSkills(Skill *skill);

void drawCharms(Charm *charm);

//=====================================
//-------------TICKETSRU---------------

typedef struct Coins
{
    Vector2 pos;
    Vector2 dim;
    Vector2 speed;
    float friction;
    Color cor;
    bool available;
}Coins;

Coins summonCoinsForBasicEnemies(BasicEnemy *enemy, int number);

Coins summonCoinsForAirBasicEnemies(AirBasicEnemy *enemy, int number);

void drawCoins(Coins *coin);

#endif // COINS_H
