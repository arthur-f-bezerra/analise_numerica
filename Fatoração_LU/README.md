# analise_numerica
Dado A uma matriz dos reais nxn e b um vetor dos reais n.

Fatoração LU é uma decomposição de matriz na forma A = LU, sendo L uma matriz triangular inferior (lower) e U uma superior (upper), meu codigo apresenta com pivotamento parcial, ou seja, PA = LU, assim, PAx = LUx, com P sendo a mateiz de permutação, porém chamando Ux = y, temos um sistema

Ly = Pb

Ux = y

Ou seja, podemos achar o valores de varios b e trivialmente o determinante de A também.
Pois

det(A) = det(L) det (U) (-1)^s, sendo s o numero de permutações.
mas sabemos que det(L)=1 e det(U) é a multiplicação da diagonal.

Como o processo de pivoteamento precisa em cada redução trocar de lugar duas linhas, notei que isso geraria um custo computacional de O(n), para diminuir o custo, fiz um array que aponta para as linhas, assim fazendo o processo de pivoteamento ser de O(1), ja que so trocamos apenas dois ponteiros de lugar.
