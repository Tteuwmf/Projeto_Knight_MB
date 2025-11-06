#include "raylib.h"
#include "player.h"
#include "weapons.h"
#include "collisions.h"

#define GRAVITY 20.0
#define MAX_SPEED_FALL 400.0

//===============================================
//----------------CREATE-PLAYER------------------

Player createNewPlayer (Vector2 dim, Color cor)
{
    Player newPlayer = (Player)
        {
            .pos = {{0}},
            .speed = {{0}},
            .dim = dim,
            .cor = cor,

            .collisionRecs = {0},

            .status = (PlayerStatus)
            {
                .life = 5,
                .dead = false,
                .aura = 0,
                .ticketsRU = 0,
                .defaultSpeed = 200.0,
                .onFloor = false,
                .lookingAtR = true,
                .lookingAtL = false,
                .invulnerable = false,
                .invulnerableTime = 2.0f,
                .contInvulnerableTime = 0.0f,

            },

            .powers = (SpecialAttacks)
            {
                .horizontalPowerActive = true,
                .usingHorizontalPower = false,
                .horizontalPower = (HorizontalPower)
                {
                    .pos = {0},
                    .dim = {0},
                    .speed = (Vector2){0,0},
                    .cor = WHITE,
                    .currentFrame = 0,
                    .numberOfFrames=0,
                    .contTime=0,
                    .attackTime = 4.0,
                    .timeToTheNextFrame=0,
                },
            },

            .inventory = (PlayerInventory)
            {
                .equippedCharms = 0,
                .equippedWeapons = (PlayerWeapons)
                {
                    .defaultSword = true,
                },
            },



            .sword = createPlayerSword(),


            .knockbackStatus = (KnockbackStatus)
            {
                .swordKnockbackR = false,
                .swordKnockbackL = false,
                .swordKnockbackUp = false,
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
                .attackTime = 0.35f,
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
    //-------HORIZONTAL-MOVES--------

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
            player->status.lookingAtR = false; // não esta olhando para a direita
            player->status.lookingAtL = true; // esta olhando para a esquerda
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

    if (IsKeyPressed(KEY_X) && player->status.lookingAtR && player->status.lookingUp==false && player->status.lookingDown==false && player->attackStatus.attacking==false) // confere se a tecla do ataque foi acionada, a direção, e se ja esta atacando
    {
        player->attackStatus.attackRight = true; //inicia o ataque
        player->attackStatus.contTimeToNextAttack = 0.0f; //recomeça o timer
        player->attackStatus.attacking = true; // esta atacando

        player->sword.activated =true;
    }
    else
    {
        player->attackStatus.contTimeToNextAttack += delta; //conta tempo

        if( player->attackStatus.contTimeToNextAttack >= player->attackStatus.attackTime) //confere se ja passou o tempo da animação
        {
            player->attackStatus.attackRight = false; //encerra o ataque
            player->sword.activated =false;
        }

        if(player->attackStatus.contTimeToNextAttack >= player->attackStatus.timeToTheNextAttack) // ja pode dar o proximo ataque?
        {
            player->attackStatus.attacking = false; //encerra por completo a ação
            player->attackStatus.contTimeToNextAttack = 0.0f; // zera o contador
        }

    }

    if (IsKeyPressed(KEY_X) && player->status.lookingAtL && player->status.lookingUp==false && player->status.lookingDown==false && player->attackStatus.attacking==false) // confere se a tecla do ataque foi acionada, a direção, e se ja esta atacando
    {
        player->attackStatus.attackLeft = true;
        player->attackStatus.contTimeToNextAttack = 0.0f;
        player->attackStatus.attacking = true;

        player->sword.activated =true;
    }
    else
    {
        player->attackStatus.contTimeToNextAttack += delta;

        if( player->attackStatus.contTimeToNextAttack >= player->attackStatus.attackTime)
        {
            player->attackStatus.attackLeft = false;
            player->sword.activated =false;
        }

        if(player->attackStatus.contTimeToNextAttack >= player->attackStatus.timeToTheNextAttack)
        {
            player->attackStatus.attacking = false;
            player->attackStatus.contTimeToNextAttack = 0.0f;
        }

    }

            //-----ESPECIAL-ATTACKS-----

    if (IsKeyPressed(KEY_C)&& player->powers.horizontalPowerActive && player->powers.usingHorizontalPower==false && player->status.aura>=3)
    {
        player->powers.usingHorizontalPower=true;

        player->status.aura-=3;

        player->powers.horizontalPower.dim = (Vector2){32,32};

        player->powers.horizontalPower.pos = (Vector2){player->pos.x+player->dim.x, player->pos.y-player->powers.horizontalPower.dim.y/2};

        if (player->status.lookingAtL)
        {
            player->powers.horizontalPower.speed.x = -400;
            player->powers.horizontalPower.pos = (Vector2){player->pos.x, player->pos.y-player->powers.horizontalPower.dim.y/2};

        }
        else
        {
            player->powers.horizontalPower.speed.x = 400;
            player->powers.horizontalPower.pos = (Vector2){player->pos.x+player->dim.x, player->pos.y-player->powers.horizontalPower.dim.y/2};
        }

    }
    else
    {
        if(player->powers.usingHorizontalPower)
        {
            player->powers.horizontalPower.contTime += delta;
        }
        if(player->powers.horizontalPower.contTime>=player->powers.horizontalPower.attackTime)
        {
            player->powers.usingHorizontalPower= false;
            player->powers.horizontalPower.contTime = 0.0f;
        }
    }

    //----------VERTICAL-MOVES----------

    if(IsKeyDown(KEY_S))
    {
        player->status.lookingDown=true;
    }
    else if(IsKeyDown(KEY_W))
    {
        player->status.lookingUp=true;
    }

    if(IsKeyReleased(KEY_S))
    {
        player->status.lookingDown=false;
    }
    else if(IsKeyReleased(KEY_W))
    {
        player->status.lookingUp=false;
    }

    //---------ATTACKS---------

    if (IsKeyPressed(KEY_X) && player->status.lookingUp && player->attackStatus.attacking==false) // confere se a tecla do ataque foi acionada, a direção, e se ja esta atacando
    {
        player->attackStatus.attackUp = true; //inicia o ataque
        player->attackStatus.contTimeToNextAttack = 0.0f; //recomeça o timer
        player->attackStatus.attacking = true; // esta atacando

        player->sword.activated =true;
    }
    else
    {
        player->attackStatus.contTimeToNextAttack += delta; //conta tempo

        if( player->attackStatus.contTimeToNextAttack >= player->attackStatus.attackTime) //confere se ja passou o tempo da animação
        {
            player->attackStatus.attackUp = false; //encerra o ataque
            player->sword.activated =false;
        }

        if(player->attackStatus.contTimeToNextAttack >= player->attackStatus.timeToTheNextAttack) // ja pode dar o proximo ataque?
        {
            player->attackStatus.attacking = false; //encerra por completo a ação
            player->attackStatus.contTimeToNextAttack = 0.0f; // zera o contador
        }
    }

    if (IsKeyPressed(KEY_X) && player->status.lookingDown && player->status.onFloor==false && player->attackStatus.attacking==false) // confere se a tecla do ataque foi acionada, a direção, e se ja esta atacando
    {
        player->attackStatus.attackDown = true; //inicia o ataque
        player->attackStatus.contTimeToNextAttack = 0.0f; //recomeça o timer
        player->attackStatus.attacking = true; // esta atacando

        player->sword.activated =true;
    }
    else
    {
        player->attackStatus.contTimeToNextAttack += delta; //conta tempo

        if( player->attackStatus.contTimeToNextAttack >= player->attackStatus.attackTime) //confere se ja passou o tempo da animação
        {
            player->attackStatus.attackDown = false; //encerra o ataque
            player->sword.activated =false;
        }

        if(player->attackStatus.contTimeToNextAttack >= player->attackStatus.timeToTheNextAttack) // ja pode dar o proximo ataque?
        {
            player->attackStatus.attacking = false; //encerra por completo a ação
            player->attackStatus.contTimeToNextAttack = 0.0f; // zera o contador
        }
    }


    //---------GRAVITY---------

    player->speed.y+=GRAVITY; //soma sempre a gravidade na velocidade

    if (player->speed.y>MAX_SPEED_FALL) // define uma velocidade max para o player n passar pelo chão
        player->speed.y = MAX_SPEED_FALL;

    //---------JUUMPSET--------

    if (player->knockbackStatus.knockbackTime<=0)
    {
        if(player->status.onFloor) // se o jogador esta no chão
        {
            player->jumpStatus.canJump=true; // pode pular
            player->jumpStatus.isJumping = false; // nao esta pulando
        }
        else
            player->jumpStatus.canJump=false; //se não, não pode pular

        if (IsKeyPressed(KEY_SPACE)&&player->jumpStatus.canJump) //se pode pular e a tecla for acionada
        {
            player->speed.y += -player->jumpStatus.defaultJumpForce; // realiza o pulo
            player->jumpStatus.isJumping = true; //  pulando
            player->jumpStatus.canJump = false; // e não pode pular enquanto esta pulando
            player->status.onFloor = false;
        }

        if(IsKeyDown(KEY_SPACE)&& player->jumpStatus.isJumping) //se esta pulamndo e atecla continua pressionada
        {
            player->jumpStatus.jumpTime += delta; // conta um tempo max do bonus

            if(player->jumpStatus.jumpTime<player->jumpStatus.jumpTimeMax) //se esta dentro do tempo
            {
                player->speed.y += -player->jumpStatus.jumpBoostForce; //soma o bonus ao pulo
            }
        }

        if(IsKeyReleased(KEY_SPACE))// Se a tecla for solta
        {
            player->jumpStatus.isJumping=false;  //não esta mais pulando
            player->jumpStatus.jumpTime =  0.0f; //zera o timer
        }
    }


//------------------------------------------------------------
//============================================================
//---------------------UPDATE-POSITION------------------------

    player->pos.x += player->speed.x * delta; // atualiza a posição de acordo com a velocidade (usa o delta para normalizar de acordo com o FPS)

    player->pos.y += player->speed.y * delta;

//-------------------------------------------------------------
//=============================================================
//---------------------UPDATE-FUNCTIONS------------------------

    player->collisionRecs =  updatePlayerCollisionRecs(player);

    updatePlayerSword(player);

    if(player->sword.activated)
    {
        player->sword.swordCollisionRec = createAndUpdatePlayerSwordCollisionRec(player);
    }
    else
        player->sword.swordCollisionRec = deletePlayerSwordCollisionRec(player);

    if(player->status.invulnerable)
    {
        player->status.contInvulnerableTime +=delta;

        if(player->status.contInvulnerableTime>=player->status.invulnerableTime)
        {
            player->status.invulnerable = false;
            player->status.contInvulnerableTime = 0.0f;
        }
    }

    if(player->powers.usingHorizontalPower==true)
    {
        player->powers.horizontalPower.pos.x += player->powers.horizontalPower.speed.x * delta;
    }
    else
    {
        player->powers.horizontalPower.dim = (Vector2){0,0};
        player->powers.horizontalPower.pos = (Vector2){0,0};
    }


}

//------------------------------------------------------------
//============================================================
//-----------------------KNOCKBACK----------------------------

void applyKnockbackToPlayer(Player *player)
{
    if (player->knockbackStatus.knockbackL) //confere o tipo e direção
    {
        player->speed.x = -500.0; //aplica as forças
        player->speed.y = -200.0;
        player->knockbackStatus.knockbackTime = 0.5; // inicia o contador
    }
    else if (player->knockbackStatus.knockbackR)
    {
        player->speed.x = 500.0;
        player->speed.y = -200.0;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.knockbackUn)
    {
        if(player->status.lookingAtL)
        {
            player->speed.x = 200.0;
        }
        if(player->status.lookingAtR)
        {
            player->speed.x = -200.0;
        }
        player->speed.y = 300.0;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.knockbackUp)
    {
        if(player->status.lookingAtL)
        {
            player->speed.x = 200.0;
        }
        if(player->status.lookingAtR)
        {
            player->speed.x = -200.0;
        }
        player->speed.y = -300.0;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.swordKnockbackL)
    {
        player->speed.x = 300.0;
        player->speed.y = -200.0;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.swordKnockbackR)
    {
        player->speed.x = -300.0;
        player->speed.y = -200.0;
        player->knockbackStatus.knockbackTime = 0.5;
    }
    else if (player->knockbackStatus.swordKnockbackUp)
    {
        player->speed.y = -300.0;
        player->knockbackStatus.knockbackTime = 0.5;
    }

    //após aplicar qualquer knockback zera os status
    player->knockbackStatus.knockbackL = false;
    player->knockbackStatus.knockbackR = false;
    player->knockbackStatus.knockbackUn = false;
    player->knockbackStatus.knockbackUp = false;
    player->knockbackStatus.swordKnockbackL = false;
    player->knockbackStatus.swordKnockbackR = false;
    player->knockbackStatus.swordKnockbackUp = false;

}

//-------------------------------------------------------
//=======================================================
//---------------------DRAW-PLAYER-----------------------
void drawPlayer(Player *player)
{
    if(player->powers.usingHorizontalPower)
        DrawRectangleV(player->powers.horizontalPower.pos, player->powers.horizontalPower.dim, player->powers.horizontalPower.cor);

    DrawRectangleV(player->pos,player->dim,player->cor);

    drawPlayerSword(player);

}


void drawHud (Player *player)
{
    DrawText(TextFormat("Lives: %02i", player->status.life), 20,20,20, GREEN);
    DrawText(TextFormat("Aura: %02i", player->status.aura), 20,50,20, GREEN);
    DrawText(TextFormat("Amuletos: "), 20,80,20, GREEN);
    DrawText(TextFormat("TicketsRU: %02i", player->status.ticketsRU), 20,110,20, GREEN);
}
