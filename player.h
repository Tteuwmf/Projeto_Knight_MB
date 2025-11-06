#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

//===================================
//--------------STRUCTS--------------

typedef struct PlayerStatus
{
    int life;
    bool dead;
    int aura;
    float defaultSpeed;
    bool onFloor;
    bool lookingAtR;
    bool lookingAtL;
    bool lookingDown;
    bool lookingUp;
    bool invulnerable;
    float invulnerableTime;
    float contInvulnerableTime;

}PlayerStatus;

typedef struct KnockbackStatus
{
    bool swordKnockbackR;
    bool swordKnockbackL;
    bool swordKnockbackUp;
    bool knockbackR;
    bool knockbackL;
    bool knockbackUp;
    bool knockbackUn;
    float knockbackTime;

}KnockbackStatus;

typedef struct JumpStatus
{
    bool canJump;
    float defaultJumpForce;
    float jumpBoostForce;
    bool isJumping;
    float jumpTime;
    float jumpTimeMax;

}JumpStatus;

typedef struct HorizontalPower
{
    Vector2 pos;
    Vector2 dim;
    Vector2 speed;
    Color cor;

    int currentFrame;
    int numberOfFrames;
    float contTime;
    float attackTime;
    float timeToTheNextFrame;

}HorizontalPower;

typedef struct SpecialAttacks
{
    bool horizontalPowerActive;
    bool usingHorizontalPower;
    HorizontalPower horizontalPower;

}SpecialAttacks;

typedef struct AttackStatus
{
    bool attacking;
    float attackTime;
    float timeToTheNextAttack;
    float contTimeToNextAttack;
    bool attackRight;
    bool attackLeft;
    bool attackUp;
    bool attackDown;

}AttackStatus;

typedef struct PlayerWeapons
{
    bool defaultSword;

}PlayerWeapons;

typedef struct PlayerCharms
{


}PlayerCharms;

typedef struct PlayerInventory
{
    PlayerCharms equippedCharms;
    PlayerWeapons equippedWeapons;

}PlayerInventory;

//-----------COLLISION-STRUCT----------

typedef struct PlayerCollisionRec
{
    Rectangle upper;
    Rectangle under;
    Rectangle left;
    Rectangle right;

} PlayerCollisionRec;

//-------------------------------------

typedef struct PlayerSword
{
    Vector2 pos;
    Vector2 dim;
    Color cor;

    Rectangle swordCollisionRec;

    bool up;
    bool down;
    bool left;
    bool right;

    bool activated;

    int currentFrame;
    int numberOfFrames;
    float contTime;
    float timeToTheNextFrame;

}PlayerSword;


typedef struct Player
{
    Vector2 pos;
    Vector2 dim;
    Vector2 speed;
    Color cor;

    PlayerCollisionRec collisionRecs;

    PlayerStatus status;

    PlayerInventory inventory;

    PlayerSword sword;

    KnockbackStatus knockbackStatus;

    JumpStatus jumpStatus;

    AttackStatus attackStatus;

    SpecialAttacks powers;

    int currentFrame;
    int numberOfFrames;
    float contTime;
    float timeToTheNextFrame;

}Player;

//-----------------------------------
//===================================
//------------FUNCTIONS--------------

Player createNewPlayer (Vector2 dim, Color cor);

void inputAndUpdatePlayer (Player *player, float delta);

void applyKnockbackToPlayer (Player *player);

void drawPlayer (Player *player);

void drawHud (Player *player);

#endif // PLAYER_H
