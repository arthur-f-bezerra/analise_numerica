#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float * criar_vetor(int n) //iniciar vetor
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

void norma_p(float * vetor, int n, int p)
{
    float soma=0;
    int i;

    for (i=0; i<n; i++)
    {
        soma+=pow( fabs( vetor[i] ),p );
    }

    soma = pow( soma, (float)1/p );
    printf("%.10f", soma);
    return;
}

void norma_inf(float * vetor, int n)
{
    float maior;
    int i;

    maior = fabs(vetor[0]);
    for (i=1; i<n; i++)
    {
        if (maior < vetor[i])
            maior = vetor[i];
    }

    printf("%.10f", maior);
    return;
}

int main ()  
{
    unsigned int n, p;
    float * vetor;

    {printf("Qual tamanho do vetor?\n"); //LU resolve varios b de "graça"
    scanf("%u", &n);

    if (n<=0)
    {
        printf("n tem que ser positivo");
        exit(1);
    }
    }

    {printf("Qual normal? 0 será infinito\n"); //LU resolve varios b de "graça"
    scanf("%u", &p);

    if (p<0)
    {
        printf("p tem que ser positivo");
        exit(1);
    }
    }

    vetor = criar_vetor(n);

    if (p>0)
    {
        norma_p(vetor, n, p);
        return 0;
    }
    if (p=0)
    {
        norma_inf(vetor, n);
        return 0;
    }
}
