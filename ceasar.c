#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXTO 256

void cifra_cesar(char texto[], int deslocamento, int decifrar) {
    int tamanho = strlen(texto);
    if (decifrar) deslocamento = 26 - (deslocamento % 26);

    for (int i = 0; i < tamanho; i++) {
        char c = texto[i];

        if (islower(c)) {
            c = ((c - 'a' + deslocamento) % 26) + 'a';
        } else if (isupper(c)) {
            c = ((c - 'A' + deslocamento) % 26) + 'A';
        }
        texto[i] = c;
    }
}

int validar_numero(char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2 || !validar_numero(argv[1])) {
        printf("Uso correto: %s <numero de casas>\n", argv[0]);
        return 1;
    }

    int deslocamento = atoi(argv[1]);
    char texto[MAX_TEXTO];
    int opcao;

    printf("Digite o texto que deseja criptografar/decifrar:\n");
    fgets(texto, MAX_TEXTO, stdin);
    texto[strcspn(texto, "\n")] = '\0';

    printf("Escolha a opção:\n1 - Criptografar\n2 - Decifrar\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        cifra_cesar(texto, deslocamento, 0);
        printf("Texto criptografado: %s\n", texto);
    } else if (opcao == 2) {
        cifra_cesar(texto, deslocamento, 1);
        printf("Texto decifrado: %s\n", texto);
    } else {
        printf("Opção inválida!\n");
    }

    return 0;
}
