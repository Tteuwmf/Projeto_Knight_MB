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

typedef struct BasicEnemy
{
    Vector2 pos;
    Vector2 speed;
    Vector2 dim;

    BasicEnemyCollisionRec collisionRecs;

    int life;
    bool dead;

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

void updadeEnemies (Enemies *enemies, float delta);

void updateBasicEnemies(BasicEnemy *enemy1, float delta);

void drawEnemies (Enemies *enemies);

void drawBasicEnemies (BasicEnemy *enemy1);



#endif // ENEMIES_H
