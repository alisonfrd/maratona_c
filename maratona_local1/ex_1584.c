/*
 * Beecrowd 1584 - Padrão de Desbloqueio do Espertofone
 *
 * ENUNCIADO (Tradução):
 *
 * A UFFS (União Federal dos Fabricantes de Selulares), uma empresa 100%
 * brasileira do grupo MEC (Mercado da Espanção Comercial), acaba de lançar o
 * Espertofone para competir com smartphones importados. Espertofones executam
 * um sistema operacional próprio chamado Androido.
 *
 * Quando um usuário liga um Espertofone com Androido, aparece uma tela de
 * desbloqueio com uma grade de N × N botões. O usuário deve então, sem tirar
 * o dedo da tela, deslizá-lo pelos botões para desenhar seu padrão de
 * desbloqueio previamente gravado e, assim, desbloquear o telefone para uso.
 *
 * O sistema sempre mantém na tela um segmento de linha com uma extremidade no
 * último botão tocado e a outra sob o dedo do usuário, e considera que o
 * usuário toca um botão B se e somente se este segmento de linha intercepta o
 * centro de B.
 *
 * Diferentemente do que acontece com a empresa rival, no Androido o usuário
 * pode repetir botões, desde que seja possível. A figura ilustra um padrão de
 * desbloqueio com K = 8 segmentos em uma grade 4 × 4, enumerando os segmentos.
 *
 * Observe que, em uma grade 4 × 4, não é possível que o botão (3, 3) siga o
 * botão (1, 1) em um padrão de desbloqueio, porque o segmento passaria
 * obrigatoriamente pelo centro do botão (2, 2). Obviamente, nunca é possível
 * que um botão siga a si mesmo.
 *
 * Neste problema, considere que o dedo do usuário é tão fino quanto necessário
 * para conectar botões que teoricamente podem seguir um ao outro.
 *
 * A UFFS quer agora provar que seu sistema é melhor que o da rival, calculando
 * o número de padrões de desbloqueio com K segmentos.
 *
 * Entrada:
 * A entrada consiste em vários casos de teste, cada um em uma linha e por sua
 * vez consistindo de dois inteiros: N e K (2 ≤ N ≤ 5, 0 ≤ K ≤ 10^15).
 *
 * Saída:
 * Imprima para cada caso de teste o número de padrões de desbloqueio possíveis
 * com exatamente K segmentos de linha, considerando uma grade N × N. Como este
 * número pode ser muito grande, imprima o resto que este número deixa quando
 * dividido por 10^9 + 7.
 *
 * ANÁLISE CORRIGIDA:
 * - K segmentos = K+1 botões tocados (não K botões!)
 * - Para K=1: 1 segmento = 2 botões tocados
 * - O enunciado diz que pode repetir botões, mas pela saída esperada,
 *   parece que estamos considerando classes de equivalência por simetria
 */

#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 25

typedef long long ll;

int N, total_botoes;
int adj[MAX_N][MAX_N];

typedef struct
{
    ll mat[MAX_N][MAX_N];
    int size;
} Matrix;

int mdc(int a, int b)
{
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

int podeConectar(int r1, int c1, int r2, int c2)
{
    if (r1 == r2 && c1 == c2)
        return 0;

    int dr = r2 - r1;
    int dc = c2 - c1;
    int g = mdc(dr < 0 ? -dr : dr, dc < 0 ? -dc : dc);
    if (g == 0)
        g = 1;

    int step_r = dr / g;
    int step_c = dc / g;

    for (int k = 1; k < g; k++)
    {
        int mid_r = r1 + k * step_r;
        int mid_c = c1 + k * step_c;
        if (mid_r >= 0 && mid_r < N && mid_c >= 0 && mid_c < N)
        {
            return 0;
        }
    }
    return 1;
}

Matrix multiplicarMatrizes(Matrix A, Matrix B)
{
    Matrix C;
    C.size = A.size;
    for (int i = 0; i < C.size; i++)
    {
        for (int j = 0; j < C.size; j++)
        {
            C.mat[i][j] = 0;
            for (int k = 0; k < C.size; k++)
            {
                C.mat[i][j] = (C.mat[i][j] + (A.mat[i][k] * B.mat[k][j]) % MOD) % MOD;
            }
        }
    }
    return C;
}

Matrix potenciaMatriz(Matrix base, ll exp)
{
    Matrix resultado;
    resultado.size = base.size;

    for (int i = 0; i < resultado.size; i++)
    {
        for (int j = 0; j < resultado.size; j++)
        {
            resultado.mat[i][j] = (i == j) ? 1 : 0;
        }
    }

    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            resultado = multiplicarMatrizes(resultado, base);
        }
        base = multiplicarMatrizes(base, base);
        exp /= 2;
    }
    return resultado;
}

int main()
{
    ll K;

    while (scanf("%d %lld", &N, &K) != EOF)
    {
        total_botoes = N * N;

        if (K == 0)
        {
            // K=0 significa nenhum movimento, mas talvez conte os botões iniciais?
            // Baseado na saída esperada, parece ser 0
            printf("0\n");
            continue;
        }

        memset(adj, 0, sizeof(adj));

        for (int i = 0; i < total_botoes; i++)
        {
            int r1 = i / N;
            int c1 = i % N;
            for (int j = 0; j < total_botoes; j++)
            {
                int r2 = j / N;
                int c2 = j % N;
                if (podeConectar(r1, c1, r2, c2))
                {
                    adj[i][j] = 1;
                }
            }
        }

        Matrix A;
        A.size = total_botoes;
        for (int i = 0; i < total_botoes; i++)
        {
            for (int j = 0; j < total_botoes; j++)
            {
                A.mat[i][j] = adj[i][j];
            }
        }

        // Calcula A^K
        Matrix resultado = potenciaMatriz(A, K);

        // Soma todos os elementos - cada um representa caminhos de K arestas
        ll total = 0;
        for (int i = 0; i < total_botoes; i++)
        {
            for (int j = 0; j < total_botoes; j++)
            {
                total = (total + resultado.mat[i][j]) % MOD;
            }
        }

        printf("%lld\n", total);
    }

    return 0;
}
