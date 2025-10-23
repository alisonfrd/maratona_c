#include <stdio.h>
#include <stdlib.h>

/*
 * Problema: Fila da Copa do Mundo (Beecrowd 2460)
 *
 * Descrição: Dado uma fila inicial de N pessoas com identificadores únicos
 * e uma lista de M pessoas que saíram da fila, determinar quem permaneceu.
 *
 * Estratégia:
 * 1. Ler a fila inicial com N pessoas
 * 2. Ler os M identificadores das pessoas que saíram
 * 3. Marcar quais pessoas saíram usando um array auxiliar
 * 4. Imprimir apenas as pessoas que não saíram, mantendo a ordem original
 *
 * Complexidade: O(N + M)
 */

int main()
{
    int n, m;

    // Lê o número de pessoas inicialmente na fila
    scanf("%d", &n);

    // Array para armazenar os identificadores da fila inicial
    int fila[n];

    // Lê os identificadores das pessoas na fila (em ordem)
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &fila[i]);
    }

    // Lê o número de pessoas que saíram da fila
    scanf("%d", &m);

    // Array para marcar quais pessoas saíram
    // Como os identificadores podem ser até 100000, criamos um array desse tamanho
    // Inicializamos tudo com 0 (não saiu)
    int saiu[100001] = {0};

    // Lê os identificadores das pessoas que saíram e marca no array
    for (int i = 0; i < m; i++)
    {
        int id;
        scanf("%d", &id);
        saiu[id] = 1; // Marca que esta pessoa saiu da fila
    }

    // Variável para controlar a impressão de espaços
    int primeiro = 1;

    // Percorre a fila original e imprime apenas quem permaneceu
    for (int i = 0; i < n; i++)
    {
        // Se a pessoa não saiu da fila (saiu[fila[i]] == 0)
        if (!saiu[fila[i]])
        {
            // Imprime espaço antes dos elementos (exceto o primeiro)
            if (!primeiro)
            {
                printf(" ");
            }
            printf("%d", fila[i]);
            primeiro = 0;
        }
    }

    // Imprime quebra de linha ao final
    printf("\n");

    return 0;
}
