#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "raylib.h"
#include "player.h"
#include "blocks.h"
#include "weapons.h"
#include "enemies.h"

//=======================================
//------COLLISIONS-PLAYER-FUNCITONS------

PlayerCollisionRec updatePlayerCollisionRecs(Player *player);

//------CHECK-COLLISION-TYPES-----

bool checkPlayerBlockCollision_Upper(PlayerCollisionRec *collisionRec, Block *block);
bool checkPlayerBlockCollision_Under(PlayerCollisionRec *collisionRec, Block *block);
bool checkPlayerBlockCollision_Left(PlayerCollisionRec *collisionRec, Block *block);
bool checkPlayerBlockCollision_Right(PlayerCollisionRec *collisionRec, Block *block);

bool checkPlayerBasicEnemiesCollision_Upper(PlayerCollisionRec *collisionRec, BasicEnemy *enemy);
bool checkPlayerBasicEnemiesCollision_Under(PlayerCollisionRec *collisionRec, BasicEnemy *enemy);
bool checkPlayerBasicEnemiesCollision_Left(PlayerCollisionRec *collisionRec, BasicEnemy *enemy);
bool checkPlayerBasicEnemiesCollision_Right(PlayerCollisionRec *collisionRec, BasicEnemy *enemy);

//========================================
//------COLLISIONS-WEAPONS-FUNCTIONS------

PlayerSwordCollisionRec createAndUpdatePlayerSwordCollisionRecs(Player *player);

bool checkBasicEnemiesPlayerSwordCollision_Left(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword);
bool checkBasicEnemiesPlayerSwordCollision_Right(BasicEnemyCollisionRec *collisionRec, PlayerSword *playerSword);


//----------------------------------------
//========================================
//------COLLISIONS-ENEMIES-FUNCTIONS------

void createAndUpdateEnemiesCollisionRecs(Enemies *enemies);

BasicEnemyCollisionRec createAndUpdateBasicEnemiesCollisionsRec(BasicEnemy *enemy);

bool checkBasicEnemiesBlockCollision_Upper(BasicEnemyCollisionRec *collisionRecs, Block *block);
bool checkBasicEnemiesBlockCollision_Under(BasicEnemyCollisionRec *collisionRecs, Block *block);
bool checkBasicEnemiesBlockCollision_Left(BasicEnemyCollisionRec *collisionRecs, Block *block);
bool checkBasicEnemiesBlockCollision_Right(BasicEnemyCollisionRec *collisionRecs, Block *block);


#endif // COLLISIONS_H
