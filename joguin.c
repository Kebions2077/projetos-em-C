#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int vida;
    int passos;
    int x, y;
    char nickname[10];
} status;

void exibirMapa3D(status *player);
void moverJogador(status *player, char direcao);

void apaga() {
    fflush(stdout);
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(void)
{
    status player;
    player.vida = 100;
    player.passos = 0;
    player.x = 2;
    player.y = 5;

    printf("Digite seu nome player: ");
    fgets(player.nickname, sizeof(player.nickname), stdin);
    player.nickname[strcspn(player.nickname, "\n")] = '\0';

    char comando;

    printf("\nBem-vindo, %s! Use W, A, S, D para se mover. (Q para sair)\n", player.nickname);

    while (1)
    {
        apaga();  // Limpa a tela antes de mostrar o mapa
        exibirMapa3D(&player);
        printf("\nVida: %d | Passos: %d\n", player.vida, player.passos);
        printf("Digite seu movimento: ");
        scanf(" %c", &comando);

        if (comando == 'q' || comando == 'Q')
        {
            printf("\nSaindo do jogo... valeu, %s!\n", player.nickname);
            printf("...\n..\n.\n");
            break;
        }

        switch (comando)
        {
            case 'w': case 'W':
            case 'a': case 'A':
            case 's': case 'S':
            case 'd': case 'D':
                moverJogador(&player, comando);
                break;
            default:
                printf("\nComando inválido! Use W, A, S, D ou Q.\n");
                #ifdef _WIN32
                    system("pause");  // Windows
                #else
                    printf("Pressione Enter para continuar...");
                    getchar();  // consome o '\n' do scanf
                    getchar();  // espera o Enter
                #endif
                break;
        }
    }

    return 0;
}

void exibirMapa3D(status *player)
{
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        // deslocamento lateral pra dar a sensação de profundidade
        for (int k = 0; k < 5 - i; k++)
            printf(" ");

        for (int j = 0; j < 10; j++)
        {
            if (i == player->x && j == player->y)
                printf("/&\\ ");  // jogador
            else
                printf("/_\\ ");  // chão com relevo
        }
        printf("\n");
    }
    printf("\n");
}

void moverJogador(status *player, char direcao)
{
    switch (direcao)
    {
        case 'w': case 'W':
            if (player->x > 0) player->x--;
            break;
        case 's': case 'S':
            if (player->x < 4) player->x++;
            break;
        case 'a': case 'A':
            if (player->y > 0) player->y--;
            break;
        case 'd': case 'D':
            if (player->y < 9) player->y++;
            break;
    }

    player->passos++;
}
