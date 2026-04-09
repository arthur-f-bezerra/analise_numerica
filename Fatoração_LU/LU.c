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
        matriz[i].linha = calloc(n, sizeof(float));
        if (matriz[i].linha==NULL)
        {
            printf("Erro memoria");
            exit(1);
        }

        printf("Digite os elementos da %d linha\n", i+1);
        encher_linha(matriz[i].linha, n);
    }    
    
}

ordem * iniciar_matriz (int n) //começando o array que aponta para as linhas
{
    int i;
    ordem * matriz = calloc(n, sizeof(ordem));
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

void determinante(ordem * matriz, int n)//det(A)=det(L)det(U)=1det(U)
{
    float det=1;
    int i;
    for (i=0; i<n; i++)
    {
        det=matriz[i].linha[i]*det;
    }
    printf("det(A) = %.10f");
    return;
}

float * criar_vetor(int n) //crio o x/b, depois so modifico o mesmo
{
    float * vetor;
    vetor = calloc(n, sizeof(float));
    if (vetor==NULL)
        {
            printf("Erro memoria");
            exit(1);
        }
    return vetor;
}

void Ux(ordem * matriz, int n, float * x, float * y)
{
    int i, j;
    float soma;
    y[n-1] = x[n-1];
    for (i=n-2; i<0; i--)
    {
        soma=0;
        for (j=i; j>0;j--)
        {
            soma += matriz[i].linha[j]*y[j];
        }
        y[i] = x[i]/soma;
    }
}

void Ly(ordem * matriz, int n, float * b, float * y)
{
    int i, j;
    float soma;
    y[0] = b[0];
    for (i=1; i<n; i++)
    {
        soma=0;
        for (j=0; j<i;j++)
        {
            soma += matriz[i].linha[j]*y[j];
        }
        y[i] = b[i]/soma;
    }
    return;
}

void preencher_b(int n, float * vetor, ordem * matriz)
{
    int i, j;
    for (i=0;i<n;i++)
    {
        for (j=i;i<n;i++)
        {
            if ((matriz[j].posi-1)==i)
                {
                    printf("Digite o valor de b");
                    scanf("%f", &vetor[i]);
                }
        }
    }
    printf("Caso tenha mais b outra mensagem aparecerá");
    return;
}

void resolver_b(ordem * matriz, int n, int m)
{
    int i;
    float * b;
    float * y;
    float * x;
    b = criar_vetor(n);
    y = criar_vetor(n);
    x = criar_vetor(n);
    for (i=0; i<m; i++)
    {
        preencher_b(n,b,matriz);

    }
    free(b);
    free(x);
    free(y);
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
    unsigned int n, m;
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
    scanf("%u", &m);

    if (m<=0)
    {
        printf("Codigo quebrou");
        exit(1);
    }
    }
    

    imprimir(matriz, n);
    determinante(matriz,n);
    free(matriz);
    return 0;
}
