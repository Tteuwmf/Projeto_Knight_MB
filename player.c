#include "raylib.h"
#include "player.h"

//===============================================
//----------------CREATE-PLAYER------------------

Player createNewPlayer (Vector2 dim, Color cor)
{
    Player newPlayer = (Player)
        {
            .pos = {0},
            .speed = {0},
            .dim = dim,
            .cor = cor,

            .status = (PlayerStatus)
            {
                .life = 5,
                .dead = false,
                .defaultSpeed = 200.0,
                .onFloor = false,
                .lookingAtR = true,
                .lookingAtL = false,
            },

            .knockbackStatus = (KnockbackStatus)
            {
                .swordKnockbackR = false,
                .swordKnockbackL = false,
                .knockbackR = false,
                .knockbackL = false,
                .knockbackUp = false,
                .knockbackUn = false,
                .knockbackTime = 0.0f,
            },

            .jumpStatus = (JumpStatus)
            {
                .canJump = false,
                .defaultJumpForce = 400.0f,
                .jumpBoostForce = 20.0f,
                .isJumping = false,
                .jumpTime = 0.0f,
                .jumpTimeMax = 0.25f,
            },

            .attackStatus = (AttackStatus)
            {
                .attacking = false,
                .attackRight = false,
                .attackLeft = false,
                .attackUp = false,
                .attackDown = false,
                .timeToTheNextAttack = 1.0f,
                .contTimeToNextAttack = 0.0f,
            },

            .currentFrame = 0,
            .numberOfFrames = 0,
            .contTime = 0.0f,
            .timeToTheNextFrame = 0.5f,

        };

        return newPlayer;
}

//-----------------------------------------------
//===============================================
//---------------INPUT-AND-UPDATE----------------

void inputAndUpdatePlayer(Player *player, float delta)
{
    //============MOVESET============
    //----MOVIMENTAÇÃO-HORIZONTAL----

    if (player->knockbackStatus.knockbackTime<=0) // confere se não está sofrendo um knockback
    {
        if(IsKeyDown(KEY_D)) //indo para a direita
        {
            player->speed.x = player->status.defaultSpeed; //começa o movimento
            player->status.lookingAtR = true; //esta olhando para a direita
            player->status.lookingAtL = false; // não esta olhando para a esquerda
        }
        else if (IsKeyDown(KEY_A))// indo para a esquerda
        {
            player->speed.x = -player->status.defaultSpeed; //começa o movimento negativo
            player->status.lookingAtR = true; // não esta olhando para a direita
            player->status.lookingAtL = false; // esta olhando para a esquerda
        }
        else
            player->speed.x=0.0f; // se não esta se movendo velocidade é zero
    }
    else // caso esteja sofrendo um knockback
    {
        player->knockbackStatus.knockbackTime -= delta; // conta o tempo
        player->speed.x *= 0.9; // reduz a velocidade até o fim do tempo
    }

    //-----------ATTACKS-----------

    if (IsKeyPressed(KEY_X) && player->status.lookingAtR && player->attackStatus.attacking==false) // confere se a tecla do ataque foi acionada, a direção, e se ja esta atacando
    {
        player->attackStatus.attackRight = true;
        player->attackStatus.contTimeToNextAttack = 0.0f;
        player->attackStatus.attacking = true;
    }
    else
    {
        player->attackStatus.contTimeToNextAttack += delta;

        if( player->attackStatus.contTimeToNextAttack >= player->timeToTheNextFrame)
        {
            player->attackStatus.attackRight = false;
        }

        if(player->attackStatus.contTimeToNextAttack >= player->attackStatus.timeToTheNextAttack)
        {
            player->attackStatus.attacking = false;
            player->attackStatus.contTimeToNextAttack = 0.0f;
        }
    }
}
