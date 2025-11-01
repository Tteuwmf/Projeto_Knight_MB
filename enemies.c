#include "raylib.h"
#include "enemies.h"

#define GRAVITY 20.0
#define MAX_SPEED_FALL 400.0

//===========================================
//----------------FUNCTIONS------------------

BasicEnemy createBasicEnemies(Vector2 pos)
{
    return (BasicEnemy)
    {
        .pos = pos,
        .speed = (Vector2) {0,0},
        .dim = (Vector2) {25,25},

        .cor = RED,

        .collisionRecs = {0},

        .life = 3,
        .dead = false,

        .defaultSpeed = 100.0,

        .onFloor =false
    };
}

void updateBasicEnemies(BasicEnemy *enemy1, float delta)
{
    //=============HORIZONTAL=MOVES===============

    if (enemy1->onFloor)
    {
        enemy1->speed.x = enemy1->defaultSpeed;
    }
    else if (enemy1->speed.x>0 && enemy1->onFloor==false)
    {
        enemy1->pos.x = enemy1->pos.x-(enemy1->dim.x/2);
        enemy1->defaultSpeed = -enemy1->defaultSpeed;
    }
    else if (enemy1->speed.x<0 && enemy1->onFloor==false)
    {
        enemy1->pos.x = enemy1->pos.x+(enemy1->dim.x/2);
        enemy1->defaultSpeed = -enemy1->defaultSpeed;
    }

    //=============VERTICAL=MOVES=================

    enemy1->speed.y += GRAVITY;

    if(enemy1->speed.y>MAX_SPEED_FALL)
        enemy1->speed.y = MAX_SPEED_FALL;

    //=============UPDATE=POSITION================

    enemy1->pos.x += enemy1->speed.x * delta;
    enemy1->pos.y += enemy1->speed.y * delta;
}

void updateEnemies (Enemies *enemies, float delta)
{
    //===========BASIC=ENEMIES==========

    for (int i=0; i<enemies->numberOfBasicEnemies;i++)
    {
        BasicEnemy *enemy1 = &enemies->enemy1[i];

        if (enemy1->dead==false)
        {
            updateBasicEnemies(enemy1, delta);
        }
    }

}

void drawBasicEnemies(BasicEnemy *enemy1)
{
    DrawRectangleV(enemy1->pos, enemy1->dim, enemy1->cor);
}

void drawEnemies(Enemies *enemies)
{
    //===========BASIC=ENEMIES==========

    for (int i=0; i<enemies->numberOfBasicEnemies;i++)
    {
        BasicEnemy *enemy1 = &enemies->enemy1[i];

        if (enemy1->dead==false)
        {
            drawBasicEnemies(enemy1);
        }
    }
}
