/*
 * Beecrowd 1858 - A Resposta de Theon
 *
 * ENUNCIADO (Tradução):
 *
 * Ramsay: "(...) você vence o jogo se descobrir quem eu sou e por que estou te torturando."
 *
 * Theon precisa pensar rápido e adivinhar quem é o seu torturador!
 * Porém, Ramsay já decidiu o que fará após Theon dar sua resposta.
 *
 * Há N pessoas que Theon pode dizer ser o torturador.
 * Considere que as pessoas são numeradas de 1 a N.
 * Se Theon disser que o torturador é a pessoa i, Ramsay o baterá Ti vezes.
 *
 * Sua tarefa é ajudar Theon a determinar qual resposta ele deve dar
 * para minimizar o número de vezes que será atingido.
 *
 * Entrada:
 *  - A primeira linha contém um inteiro N (1 ≤ N ≤ 100)
 *  - A segunda linha contém N inteiros T1, T2, ..., TN (0 ≤ Ti ≤ 20)
 *
 * Saída:
 *  - Imprima uma única linha contendo o número da pessoa
 *    que Theon deve dizer ser o torturador.
 *  - Se houver mais de uma resposta possível, imprima a menor.
 */

#include <stdio.h>

int main(void)
{
    int N;
    scanf("%d", &N);

    int menor_valor = 1000000;
    int resposta = -1;

    for (int i = 1; i <= N; i++)
    {
        int Ti;
        scanf("%d", &Ti);
        if (Ti < menor_valor)
        {
            menor_valor = Ti;
            resposta = i;
        }
    }

    printf("%d\n", resposta);
    return 0;
}
