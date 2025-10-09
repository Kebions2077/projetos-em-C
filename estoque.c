#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char nome[30];
  int preço;
  int quant;  
} estoque;

void adicionar (int *n, int add, estoque **produto);
void compra (int n, int add, estoque *produto);
void listagem (int n, int add, estoque *produto);
void config_menu(estoque *produto, int n, int add);
int menu(estoque *produto, int n, int add);
int main (void)
{
    estoque *produto;
    int n;
    int add = 0;

    printf("qual sera o numero de produtos?\n");
    scanf("%i", &n);
    getchar();

    produto = malloc(n * sizeof(estoque));
    config_menu(produto, n, add);
}

void config_menu(estoque *produto, int n, int add)
{
    char nome[30];

    for(int i = 0; i < n; i++)
    {
        printf("qual sera o nome do %iº produto?\n", i+1);
        fgets(produto[i].nome, 30, stdin);
        produto[i].nome[strcspn(produto[i].nome, "\n")] = '\0';   

        printf("qual sera o preço?\n");
        scanf("%i", &produto[i].preço);
        getchar();

        printf("qual sera a quantidade do %iº produto?\n", i+1);
        scanf("%i", &produto[i].quant);
        getchar();
    }
    menu(produto, n, add);
}
void buscar(int n, estoque *produto)
{
    FILE *ptr_busca_bin;
    FILE *ptr_busca_txt;

    ptr_busca_bin = fopen("busca.bin", "wb+");
    if(ptr_busca_bin == NULL)
    {
        printf("erro ao abrir arquivo\n");
        exit (1);
    }

    char nome_pesq[30];
    printf("pesquisa_\n");
    scanf("%s", nome_pesq);
    getchar();

    for(int i = 0; i < n; i++)
    {
        fwrite(&produto[i].nome, sizeof(estoque), 1, ptr_busca_bin);
    }

    rewind(ptr_busca_bin);
    ptr_busca_txt = fopen("busca.txt", "w");

    estoque temp;
    while(fread(&temp, sizeof(estoque), 1, ptr_busca_bin))
    {
        if(strncmp(nome_pesq, temp.nome, 3) == 0)
        {
            fprintf(ptr_busca_txt, "NOME: %s PRECO: %d QTD: %d\n",
            temp.nome, temp.preço, temp.quant);
        }
        
    }
    fclose(ptr_busca_bin);
    fclose(ptr_busca_txt);
}
void adicionar_arq (int n, estoque *produto)
{
    FILE *ptr_ar_txt;
    FILE *ptr_ar_bin;
    ptr_ar_bin = fopen("estoque.bin", "wb+");

    if(ptr_ar_bin == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    int j;
    for(j = 0; j < n; j++)
    {
        fwrite(&produto[j], sizeof(estoque), 1, ptr_ar_bin);
    }
    rewind(ptr_ar_bin);
                
    ptr_ar_txt = fopen("estoque.txt", "w");
    if(ptr_ar_txt == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    estoque temp;
    rewind(ptr_ar_bin);
    while(fread(&temp, sizeof(estoque), 1, ptr_ar_bin))
    {
        fprintf(ptr_ar_txt, "NOME: %s PRECO: %d QTD: %d\n",
        temp.nome, temp.preço, temp.quant);
    }
    fclose(ptr_ar_txt);
    fclose(ptr_ar_bin); 
}
void adicionar (int *n, int add, estoque **produto)
{            
    printf("deseja adicionar quantos itens?\n");
    scanf("%i", &add);
    getchar();

    *produto = realloc(*produto, (*n + add) * sizeof(estoque));
    if(*produto == NULL)
    {
        printf("erro ao alocar memoria\n");
        exit (1);
    }
    int cont = *n;
    for(int i = *n; i < add + *n; i++)
    {
        printf("qual sera o nome do %iº produto?\n", i+1);
        fgets((*produto)[i].nome, 30, stdin);
        (*produto)[i].nome[strcspn((*produto)[i].nome, "\n")] = '\0';   

        printf("qual sera o preço?\n");
        scanf("%i", &(*produto)[i].preço);
        getchar();

        printf("qual sera a quantidade do %iº produto?\n", i+1);
        scanf("%i", &(*produto)[i].quant);
         getchar();
    }
    *n += add;
    FILE *ptr_trans;
    ptr_trans = fopen("transacoes.log", "a");
    if(ptr_trans == NULL)
    {
        printf("erro ao abrir ao arquivo");
        exit (1);
    }
    int ad = *n - add;
    for(int i = 0; i < add; i++) 
    {
        fprintf(ptr_trans, "ITEMS ADICIONADOS: %s\n", (*produto)[ad + i].nome);
    }
    fclose(ptr_trans);
}
void compra (int n, int add, estoque *produto)
{
    getchar();
    char nome[30];
    int compra;
    int encontrado = 0;
    int comp = 0;
    printf("deseja comprar qual produto?\n");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(int i = 0; i < n; i++)
    {
        if(strcmp(nome, produto[i].nome) == 0)
        {
            encontrado = 1;
            printf("quantos %s deseja comprar?\n", produto [i].nome);
            scanf("%i", &compra);
            getchar();

            if(produto[i].quant >= compra)
            {
                produto[i].quant -= compra;
                printf("compra efetuada com sucesso\n");
                comp++;
                            

                FILE *ptr_comp;
                ptr_comp = fopen("transacoes.log", "a");
                if(ptr_comp == NULL)
                {
                    printf("erro ao abrir arquivo");
                    exit (1);
                }
                for(int o = 0; o < n; o++)
                {
                    if(strcmp(nome, produto[o].nome) == 0)
                    {
                        fprintf(ptr_comp, "foram comprados %i de %s restao %i itens\n", compra, produto[o].nome, produto[o].quant);   
                    }
                }
                fclose(ptr_comp);

            }
            else
            {
                printf("vc pd comprar apenas %i unidades desse produto\n", produto[i].quant);
            }
        }
               
    }
    if(encontrado == 0)
    {
        printf("produto invalido\n");
    }
                        
}
void listagem (int n, int add, estoque *produto)
{
    for(int i = 0; i < n; i++)
    {
        printf("%iº produto == %s\n", i+1, produto[i].nome);
    }
}
int menu(estoque *produto, int n, int add)
{
    int op;
    
    do{
        
        printf("MENU--------\n");
        printf("1 - listar produtos\n");
        printf("2 - comprar\n");
        printf("3 - adicionar ao estoque\n");
        printf("4 - adicionar ao arquivo\n");
        printf("5 - buscar produto\n");
        printf("6 - sair\n");
        scanf("%i", &op);
    
        

        switch(op)
        {
            case 1:
                listagem(n, add, produto);
                break;
            
            case 2:
                compra(n, add, produto);
                break;          
            case 3:
                adicionar(&n, add, &produto);
                break;
            case 4:
                adicionar_arq(n, produto);
                break;
            case 5:
                buscar(n, produto);
                break;
            case 6:
                printf("saindo...\n");
                free(produto);
                return 0;
            break;
        }       


    }while (op != 7);   
    free(produto);
}