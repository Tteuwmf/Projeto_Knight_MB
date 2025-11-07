#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"

//========================================
//-----------------STRUCTS----------------

typedef struct BasicEnemyCollisionRec
{
    Rectangle upper;
    Rectangle under;
    Rectangle left;
    Rectangle right;

}BasicEnemyCollisionRec;

typedef struct BasicEnemyKnockbackStatus
{
    bool knockbackR;
    bool knockbackL;
    bool knockbackUp;
    bool knockbackUn;
    float knockbackTime;

}BasicEnemyKnockbackStatus;


typedef struct BasicEnemy
{
    Vector2 pos;
    Vector2 speed;
    Vector2 dim;

    BasicEnemyCollisionRec collisionRecs;

    BasicEnemyKnockbackStatus knockbackStatus;

    int life;
    bool dead;
    bool haveCoins;

    Color cor;

    float defaultSpeed; //velocidade padrão de movimetno

    bool onFloor;

}BasicEnemy;

typedef struct Enemies
{
    BasicEnemy *enemy1;
    int numberOfBasicEnemies;

}Enemies;

//------------------------------------------
//==========================================
//----------------FUNCTIONS-----------------

BasicEnemy createBasicEnemies (Vector2 pos);

void updateEnemies (Enemies *enemies, float delta);

void updateBasicEnemies(BasicEnemy *enemy1, float delta);

void applyKnockbackToEnemies (Enemies *enemies);

void applyKnockbackToBasicEnemies (BasicEnemy *enemy);

void drawEnemies (Enemies *enemies);

void drawBasicEnemies (BasicEnemy *enemy1);



#endif // ENEMIES_H
