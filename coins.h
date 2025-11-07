#ifndef COINS_H
#define COINS_H

#include "raylib.h"
#include "enemies.h"

typedef struct Coins
{
    Vector2 pos;
    Vector2 dim;
    Vector2 speed;
    float friction;
    Color cor;
    bool available;
}Coins;

Coins summonCoins(BasicEnemy *enemy, int number);

void drawCoins(Coins *coin);

#endif // COINS_H
