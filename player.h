#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

//===================================
//--------------STRUCTS--------------

typedef struct PlayerStatus
{
    int life;
    int maxLife;
    bool dead;
    int aura;
    bool healing;
    float healingTime;
    float contHealingTime;
    int ticketsRU;
    float defaultSpeed;
    bool onFloor;
    bool lookingAtR;
    bool lookingAtL;
    bool nextToCharm;
    bool nextToSkill;
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

typedef struct DashStatus
{
    bool canDash;
    float dashSpeed;
    float dashTime;

}DashStatus;

typedef struct JumpStatus
{
    bool canJump;
    bool wasOnFloor;
    bool canDoubleJump;
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
    bool goldTickets;

}PlayerCharms;

typedef struct PlayerInventory
{
    PlayerCharms equippedCharms;
    PlayerWeapons equippedWeapons;

    bool doubleJump;
    bool chiclete;
    bool teclaTab;

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

    DashStatus dashStatus;

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
