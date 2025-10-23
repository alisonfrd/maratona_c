/*
 * Beecrowd 2818 - Comparação de Substring
 *
 * ENUNCIADO (Tradução):
 *
 * Bino e Cino estão brincando de remover dígitos de um número para torná-lo
 * múltiplo de 6. Para realizar este jogo, eles sorteiam um número, então tentam
 * remover o menor número de dígitos desse número para que ele se torne um
 * múltiplo de 6 sem zeros à esquerda.
 *
 * Bino e Cino são muito bons neste jogo, e eles sempre conseguem transformar
 * o número em um múltiplo de 6 usando o menor número possível de remoções.
 *
 * Por exemplo:
 * • 132: Não é necessário remover dígitos porque 132 é um múltiplo de 6.
 * • 106: É necessário remover o 1 e o 0 do número para que o resto seja
 *   múltiplo de 6. Não é possível remover apenas o 1, porque o resultado
 *   teria zeros à esquerda.
 *
 * Entrada:
 * A entrada consiste em múltiplas linhas. A primeira linha contém um inteiro
 * X (1 ≤ X ≤ 100) indicando o número de casos de teste. Cada uma das próximas
 * X linhas contém um inteiro Y (0 ≤ Y ≤ 10^100000) indicando um número
 * sorteado por Bino e Cino.
 *
 * Saída:
 * Para cada número sorteado por Bino e Cino, imprima a menor quantidade de
 * remoções de dígitos necessária para que o número seja um múltiplo de 6.
 * Se o número não puder ser um múltiplo de 6, imprima a mensagem: "Cilada".
 *
 * ANÁLISE:
 * Um número é múltiplo de 6 se e somente se:
 * 1. É divisível por 2 (último dígito par)
 * 2. É divisível por 3 (soma dos dígitos divisível por 3)
 * 3. Não tem zeros à esquerda (exceto se for apenas "0")
 */
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100005
#define INF 1000000000

static int dp_next[18], dp_cur[18];
static char num[MAX_LEN];

static inline int min_int(int a, int b) { return a < b ? a : b; }

int main(void)
{
    int T;
    if (scanf("%d", &T) != 1)
        return 0;

    while (T--)
    {
        if (scanf("%s", num) != 1)
            return 0;
        int n = (int)strlen(num);

        // Base: pos == n
        // estado: soma(0..2), modo(0..2), ultimo_par(0..1) => id = soma*6 + modo*2 + up
        for (int soma = 0; soma < 3; ++soma)
        {
            for (int modo = 0; modo < 3; ++modo)
            {
                for (int up = 0; up < 2; ++up)
                {
                    int id = soma * 6 + modo * 2 + up;
                    int val = INF;
                    // válido se:
                    //  - modo==2 (número "0")
                    //  - ou (modo==1 && soma==0 && up==1)
                    if (modo == 2)
                        val = 0;
                    else if (modo == 1 && soma == 0 && up == 1)
                        val = 0;
                    dp_next[id] = val;
                }
            }
        }

        // DP bottom-up: do fim para o início
        for (int pos = n - 1; pos >= 0; --pos)
        {
            int d = num[pos] - '0';
            int d_par = (d % 2 == 0);
            int d_mod3 = d % 3;

            for (int soma = 0; soma < 3; ++soma)
            {
                for (int modo = 0; modo < 3; ++modo)
                {
                    for (int up = 0; up < 2; ++up)
                    {
                        int id = soma * 6 + modo * 2 + up;

                        // opção 1: remover (custo 1)
                        int best = (dp_next[id] >= INF) ? INF : (dp_next[id] + 1);

                        // opção 2: manter
                        if (modo == 0)
                        {
                            if (d == 0)
                            {
                                // escolher "0" como número inteiro (modo=2), último par = 1
                                int nsoma = soma;                // +0
                                int nid = nsoma * 6 + 2 * 2 + 1; // modo=2, up=1
                                best = min_int(best, dp_next[nid]);
                            }
                            else
                            {
                                int nsoma = (soma + d_mod3) % 3;
                                int nid = nsoma * 6 + 1 * 2 + (d_par ? 1 : 0); // modo=1
                                best = min_int(best, dp_next[nid]);
                            }
                        }
                        else if (modo == 1)
                        {
                            int nsoma = (soma + d_mod3) % 3;
                            int nid = nsoma * 6 + 1 * 2 + (d_par ? 1 : 0);
                            best = min_int(best, dp_next[nid]);
                        }
                        else
                        { // modo == 2
                            // não pode manter nada (evita zeros à esquerda)
                        }

                        dp_cur[id] = best;
                    }
                }
            }
            // passa a linha atual para a próxima iteração
            for (int i = 0; i < 18; ++i)
                dp_next[i] = dp_cur[i];
        }

        // estado inicial: soma=0, modo=0 (ainda não escolhi), ultimo_par=0 (irrelevante)
        int ans = dp_next[0 * 6 + 0 * 2 + 0];
        if (ans >= INF)
            puts("Cilada");
        else
            printf("%d\n", ans);
    }
    return 0;
}
