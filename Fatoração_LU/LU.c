#include <stdio.h>
#include <stdlib.h>

typedef struct ordem //LEMBRAR EM matriz[j].linha[i], i É COLUNA E j É LINHA
{
    int posi; //posi serve para rastrear as mudanças de linha, [1, 2, 3] -> [2, 3, 1]
    float * linha;
} ordem;

void imprimir(ordem * matriz, int n)
{
    int i, j;
    for (i=0; i<n; i++)
    {
        for (j=0;j<n;j++)
        {
            printf("%.10f ", matriz[i].linha[j]);
        }
        printf("\n");
    }
    return;
}

void encher_linha(float * matriz, int n) //preenche os elementos
{
    int i;
    for (i=0; i<n; i++)
    {
        scanf("%f", &matriz[i]);
    }
}

void encher_matriz(ordem * matriz, int n) //vai criar os array das linha e pedir pro encher_linha colocar os elementos
{
    int i;

    for (i=0; i<n; i++)
    {
        matriz[i].linha = malloc(n * sizeof(float));
        if (matriz[i].linha==NULL)
        {
            printf("Erro memoria");
            for (i=0;; i--)
                free(matriz[i].linha);
            free(matriz);
            exit(1);
        }

        printf("Digite os elementos da %d linha\n", i+1);
        encher_linha(matriz[i].linha, n);
    }    
    
}

ordem * iniciar_matriz (int n) //começando o array que aponta para as linhas
{
    int i;
    ordem * matriz = malloc(n * sizeof(ordem));
    if (matriz==NULL)
    {
        printf("Erro memoria");
        exit(1);
    }

    for (i=0; i<n; i++)
    {
        matriz[i].posi=(i+1);
        matriz[i].linha=NULL;
    }
    encher_matriz(matriz, n);
    return matriz;
}

void pivoparcial(ordem * matriz, int i, int n) //pega maior da coluna e troca as linha
{
    float * aux_pont;
    int j, aux_int, maior_int=0, k;
    float maior = ((matriz[0].linha)[i]);

    for (j=1; j<n; j++) //achar maior valor
    {
        if (maior <matriz[j].linha[i])
        {
            maior = matriz[j].linha[i];
            maior_int = matriz[j].posi;
            k = j;
        }
    }

    if (maior_int != 0) //caso nn esteja pivotado
    {
        //trocando os ponteiros
        aux_pont = matriz[i].linha; 
        matriz[i].linha = matriz[k].linha;
        matriz[k].linha = aux_pont;

        //trocando as posições
        matriz[k].posi = matriz[i].posi;
        matriz[i].posi = maior_int;
    }

    return;
}

void linhaLU(float * alto, float * menor, int n, float mult, int i) //muda o valor da linha de baixo
{
    for (;i<n;i++)
    {
        menor[i] = menor[i] - alto[i]*mult; 
    }
    return;
}
void fatorLU(ordem * matriz, int n) //organiza para as outras função trabalhar
{
    int i=0, j;
    float multiplicador;
    for (i; i<n; i++) // coluna
    {
        pivoparcial(matriz, i, n);

        for (j=(i+1); j<n; j++) // linha
        {
            if (matriz[i].linha[i]==0)
                {
                    printf("Matriz não tem posto %n", n); //ou seja, x/0
                    imprimir(matriz, n);
                    exit(1);
                }
            multiplicador = matriz[j].linha[i] / matriz[i].linha[i];
            matriz[j].linha[i] = multiplicador;
            linhaLU(matriz[i].linha, matriz[j].linha, n, multiplicador, j);
        }
    }
    return;
}

void criar_b(int n) //crio o b, depois so modifico o mesmo
{}

void ajeitar_b(int n, ordem * matriz) // PAx = LUx = Pb
{}

void resolver_b(ordem * matriz, int n, int b)
{
    int i;
    criar_b(n);
    for (i=0; i<b; i++)
    {
        
    }

    return;
}

void fre(ordem * matriz, int n) //desalocar memoria ne
{   
    int i;
    for (i=0; i<n; i++)
    {
        free(matriz[i].linha); //limpa memoria das linhas
    }
    free(matriz); //limpa resto

    return; //volta
}

int main()
{
    unsigned int n, b;
    ordem * matriz;

    {printf("Qual tamanho da matriz nxn? Se colocar n nao positivo o codigo quebra\n");
    scanf("%u", &n);

    if (n<=0)
    {
        printf("Codigo quebrou");
        exit(1);
    }
    }
    
    matriz = iniciar_matriz(n);
    fatorLU(matriz, n);

    {printf("Quantos b voce tem em Ax = b?\n"); //LU resolve varios b de "graça"
    scanf("%u", &b);

    if (b<=0)
    {
        printf("Codigo quebrou");
        exit(1);
    }
    }
    
    
    
    imprimir(matriz, n);
    free(matriz);
    return 0;
}
