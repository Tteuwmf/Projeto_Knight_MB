#include <stdio.h>
#include "raylib.h"
#include "entities/player.h"
#include "resources/save.h"

void saveGame(const char *saveName, Player player)
{
    if (!saveName) return;

    FILE *arq = fopen(TextFormat("saves/%s.bin", saveName), "wb");
    if (!arq)
    {
        printf("Erro de abertura no save.\n");
        return;
    }

    if (fwrite(&player, sizeof(Player), 1, arq) != 1)
    {
        printf("Erro no save.\n");
    }

    fclose(arq);
}

Player loadGame(const char *saveName)
{
    Player player = {0};
    if (!saveName) return player;

    FILE *arq = fopen(TextFormat("saves/%s.bin", saveName), "rb");
    if (!arq)
    {
        printf("Erro de abertura no save.\n");
        return player;
    }

    if (fread(&player, sizeof(Player), 1, arq) != 1)
    {
        printf("Erro no save.\n");
    }

    fclose(arq);
    return player;
}

bool checkEmptySaveSlot(const char *saveName)
{
    if (!saveName) return true;

    FILE *arq = fopen(TextFormat("saves/%s.bin", saveName), "rb");
    if (!arq)
    {
        return true;
    }

    fseek(arq, 0L, SEEK_END);
    long int size = ftell(arq);
    fclose(arq);

    return (size <= 0);
}
