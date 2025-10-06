#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct do produto
typedef struct
{
    char nome[30];
    int preco;
    int quant;
} estoque;

// --- Funções ---
void cadastrarProdutos(estoque *produto, int n);
void listarProdutos(estoque *produto, int n);
void comprarProduto(estoque *produto, int n);
void adicionarEstoque(estoque **produto, int *n);
void salvarArquivos(estoque *produto, int n);
void registrarTransacao(const char *mensagem);

// --- Menu ---
int menu(estoque **produto, int *n);

int main(void)
{
    estoque *produto;
    int n;

    printf("Qual sera o numero de produtos?\n");
    scanf("%i", &n);
    getchar();

    produto = malloc(n * sizeof(estoque));
    cadastrarProdutos(produto, n);

    menu(&produto, &n);

    free(produto);
    return 0;
}

// --- Implementação das funções ---
void cadastrarProdutos(estoque *produto, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Nome do %iº produto: ", i + 1);
        fgets(produto[i].nome, 30, stdin);
        produto[i].nome[strcspn(produto[i].nome, "\n")] = '\0';

        printf("Preco: ");
        scanf("%i", &produto[i].preco);
        getchar();

        printf("Quantidade: ");
        scanf("%i", &produto[i].quant);
        getchar();
    }
}

void listarProdutos(estoque *produto, int n)
{
    printf("=== Lista de Produtos ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("%iº produto: %s | Preco: %d | Quantidade: %d\n",
               i + 1, produto[i].nome, produto[i].preco, produto[i].quant);
    }
}

void comprarProduto(estoque *produto, int n)
{
    char nome[30];
    int compra;
    int encontrado = 0;

    printf("Produto a comprar: ");
    getchar();
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < n; i++)
    {
        if (strcmp(nome, produto[i].nome) == 0)
        {
            encontrado = 1;
            printf("Quantos deseja comprar? ");
            scanf("%i", &compra);
            getchar();

            if (produto[i].quant >= compra)
            {
                produto[i].quant -= compra;
                printf("Compra efetuada!\n");
                char log[100];
                sprintf(log, "Foram comprados %i de %s, restam %i", compra, produto[i].nome, produto[i].quant);
                registrarTransacao(log);
            }
            else
            {
                printf("Somente %i unidades disponiveis.\n", produto[i].quant);
            }
        }
    }

    if (!encontrado)
    {
        printf("Produto nao encontrado.\n");
    }
}

void adicionarEstoque(estoque **produto, int *n)
{
    int add;
    printf("Quantos produtos deseja adicionar? ");
    scanf("%i", &add);
    getchar();

    *produto = realloc(*produto, (*n + add) * sizeof(estoque));
    if (*produto == NULL)
    {
        printf("Erro ao alocar memoria\n");
        return;
    }

    for (int i = *n; i < *n + add; i++)
    {
        printf("Nome do %iº produto: ", i + 1);
        fgets((*produto)[i].nome, 30, stdin);
        (*produto)[i].nome[strcspn((*produto)[i].nome, "\n")] = '\0';

        printf("Preco: ");
        scanf("%i", &(*produto)[i].preco);
        getchar();

        printf("Quantidade: ");
        scanf("%i", &(*produto)[i].quant);
        getchar();

        char log[100];
        sprintf(log, "Produto adicionado: %s", (*produto)[i].nome);
        registrarTransacao(log);
    }

    *n += add;
}

void salvarArquivos(estoque *produto, int n)
{
    FILE *bin = fopen("estoque.bin", "wb+");
    FILE *txt = fopen("estoque.txt", "w");

    if (!bin || !txt)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fwrite(&produto[i], sizeof(estoque), 1, bin);
    }

    rewind(bin);
    estoque temp;
    while (fread(&temp, sizeof(estoque), 1, bin))
    {
        fprintf(txt, "NOME: %s | PRECO: %d | QTD: %d\n",
                temp.nome, temp.preco, temp.quant);
    }

    fclose(bin);
    fclose(txt);
}

// Função para registrar transações em log
void registrarTransacao(const char *mensagem)
{
    FILE *log = fopen("transacoes.log", "a");
    if (log)
    {
        fprintf(log, "%s\n", mensagem);
        fclose(log);
    }
}

// Menu principal
int menu(estoque **produto, int *n)
{
    int op;
    do
    {
        printf("\nMENU\n");
        printf("1 - Listar produtos\n");
        printf("2 - Comprar\n");
        printf("3 - Adicionar ao estoque\n");
        printf("4 - Salvar em arquivo\n");
        printf("5 - Sair\n");
        scanf("%i", &op);

        switch (op)
        {
        case 1:
            listarProdutos(*produto, *n);
            break;
        case 2:
            comprarProduto(*produto, *n);
            break;
        case 3:
            adicionarEstoque(produto, n);
            break;
        case 4:
            salvarArquivos(*produto, *n);
            break;
        case 5:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while (op != 5);

    return 0;
}
