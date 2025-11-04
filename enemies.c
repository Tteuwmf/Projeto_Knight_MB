#include "raylib.h"
#include "enemies.h"
#include "collisions.h"

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

        .knockbackStatus = (BasicEnemyKnockbackStatus)
        {
            .knockbackR = false,
            .knockbackL = false,
            .knockbackUp = false,
            .knockbackUn = false,
            .knockbackTime = 0.0f,
        },

        .life = 3,
        .dead = false,

        .defaultSpeed = 100.0,

        .onFloor =false
    };
}

void updateBasicEnemies(BasicEnemy *enemy1, float delta)
{
    //=============HORIZONTAL=MOVES===============
    if (enemy1->knockbackStatus.knockbackTime<=0)
    {
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
    }
    else
    {
        enemy1->knockbackStatus.knockbackTime -= delta; // conta o tempo
        enemy1->speed.x *= 0.9; // reduz a velocidade até o fim do tempo
    }


    //=============VERTICAL=MOVES=================

    enemy1->speed.y += GRAVITY;

    if(enemy1->speed.y>MAX_SPEED_FALL)
        enemy1->speed.y = MAX_SPEED_FALL;

    //=============UPDATE=POSITION================

    enemy1->pos.x += enemy1->speed.x * delta;
    enemy1->pos.y += enemy1->speed.y * delta;

    //=============UPDATE=HEAT=BOX================

    enemy1->collisionRecs  = createAndUpdateBasicEnemiesCollisionsRec(enemy1);

    //===============UPDATE=STATS=================

    if(enemy1->life<=0){enemy1->dead=true;}

}

//---------------------------------------------------
//===================================================
//----------------KNOCKBACK-FUNCTIOS-----------------

void applyKnockbackToBasicEnemies(BasicEnemy *enemy)
{
    if (enemy->knockbackStatus.knockbackR) //confere o tipo e direção
    {
        enemy->speed.x = -500.0; //aplica as forças
        enemy->speed.y = -200.0;
        enemy->knockbackStatus.knockbackTime = 0.5; // inicia o contador
    }
    if (enemy->knockbackStatus.knockbackL)
    {
        enemy->speed.x = 500.0;
        enemy->speed.y = -200.0;
        enemy->knockbackStatus.knockbackTime = 0.5;
    }
    if (enemy->knockbackStatus.knockbackUn)
    {
        if(enemy->speed.x<0)
        {
            enemy->speed.x = 200.0;
        }
        if(enemy->speed.x>0)
        {
            enemy->speed.x = -200.0;
        }
        enemy->speed.y = 300.0;
        enemy->knockbackStatus.knockbackTime = 0.5;
    }
     if (enemy->knockbackStatus.knockbackUp)
    {
        if(enemy->speed.x<0)
        {
            enemy->speed.x = 200.0;
        }
        if(enemy->speed.x>0)
        {
            enemy->speed.x = -200.0;
        }
        enemy->speed.y = -300.0;
        enemy->knockbackStatus.knockbackTime = 0.5;
    }

    enemy->knockbackStatus.knockbackL = false;
    enemy->knockbackStatus.knockbackR = false;
    enemy->knockbackStatus.knockbackUn = false;
    enemy->knockbackStatus.knockbackUp = false;
}

void applyKnockbackToEnemies(Enemies *enemies)
{
    //===========BASIC=ENEMIES==========

    for (int i=0; i<enemies->numberOfBasicEnemies;i++)
    {
        BasicEnemy *enemy1 = &enemies->enemy1[i];

        if (enemy1->dead==false)
        {
            applyKnockbackToBasicEnemies(enemy1);
        }
    }
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
