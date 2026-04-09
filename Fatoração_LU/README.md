# analise_numerica
Dado A uma matriz dos reais nxn e b um vetor dos reais n.

Fatoração LU é uma decomposição de matriz na forma A = LU, sendo L uma matriz triangular inferior (lower) e U uma superior (upper), meu codigo apresenta com pivotamento parcial, ou seja, PA = LU, assim, PAx = LUx, porém chamando Ux = y, temos um sistema

Ly = Pb

Ux = y

Ou seja, podemos achar o valores de varios b e trivialmente o determinante de A também.

Como o processo de pivoteamento precisa em cada redução trocar de lugar duas linhas, notei que isso geraria um gasto de 2n (praticamente), para diminuir o custo, fiz uma array que aponta para as linhas, assim fazendo o processo de pivoteamento ser de 2 (praticamente), ja que so trocamos apenas dois ponteiros de lugar.
