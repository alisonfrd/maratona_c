/*
 * Beecrowd 2817 - Fila do Posto
 *
 * ENUNCIADO (Tradução):
 *
 * Uma das consequências da greve dos caminhoneiros foi a falta de gasolina em
 * todo o país. Em Santa Rita do Sapucaí, uma cidade no sul de Minas Gerais, não
 * foi diferente. Centenas de carros e motos se alinharam no último posto com
 * gasolina disponível para encher seus tanques antes que acabasse, parecia uma
 * cena de filme de apocalipse zumbi.
 *
 * O posto tem N bombas e em cada uma delas há uma fila em linha reta com M
 * veículos (carros ou motos). Abaixo, há uma ilustração de um posto com 4
 * bombas e uma fila de 2 veículos por bomba.
 *
 * Darlan, dono do posto, limitou a quantidade de gasolina que cada carro
 * poderia abastecer em 25 litros e cada moto em 12 litros. Como todos os
 * proprietários de veículos nas filas tinham medo de nunca conseguirem
 * reabastecer, eles certamente colocariam a gasolina máxima permitida por
 * Darlan.
 *
 * A equipe da TV local estava ao vivo com seu drone filmando as longas filas
 * de veículos ao redor do posto de Darlan quando um telespectador fez uma
 * pergunta um tanto aleatória: "Se levarmos em conta que as filas de carros
 * formam uma matriz de N linhas por M colunas, qual é a maior quantidade de
 * gasolina que os veículos em um quadrado de tamanho L colocarão? Dado que
 * neste quadrado deve haver pelo menos um veículo de cada tipo (carro e moto)."
 *
 * A equipe de TV não tem ideia de como responder essa pergunta e precisa da
 * sua ajuda!
 *
 * Entrada:
 * A primeira linha da entrada tem dois inteiros N, M (1 ≤ N, M ≤ 1000),
 * representando o número de bombas e o número de veículos enfileirados em cada
 * bomba. Seguem N linhas, cada uma contendo M caracteres 'C' ou 'M'
 * representando um carro ou uma moto, respectivamente. Depois disso haverá um
 * inteiro L (1 ≤ L ≤ 1000), representando o tamanho do lado do quadrado que o
 * telespectador deseja saber.
 *
 * Saída:
 * Exiba um único inteiro, a maior quantidade possível de gasolina que os
 * veículos em um quadrado L abastecerão, dado que deve haver pelo menos um
 * veículo de cada tipo. Se não houver quadrado que caracterize a dúvida do
 * telespectador, imprima -1.
 */

#include <stdio.h>
#include <string.h>

#define MAX_N 1001
#define CARRO 25 // Litros para carros
#define MOTO 12  // Litros para motos

// Matriz para armazenar a grade de veículos
char grade[MAX_N][MAX_N];

// Matrizes de soma de prefixos para calcular rapidamente a soma em qualquer retângulo
// prefixoGasolina[i][j] = soma total de gasolina do retângulo de (0,0) até (i-1,j-1)
// prefixoCarros[i][j] = quantidade de carros no retângulo de (0,0) até (i-1,j-1)
// prefixoMotos[i][j] = quantidade de motos no retângulo de (0,0) até (i-1,j-1)
int prefixoGasolina[MAX_N][MAX_N];
int prefixoCarros[MAX_N][MAX_N];
int prefixoMotos[MAX_N][MAX_N];

// Função para calcular a soma em um retângulo usando soma de prefixos 2D
// Retorna a soma no retângulo de (r1, c1) até (r2-1, c2-1)
int somaRetangulo(int prefixo[MAX_N][MAX_N], int r1, int c1, int r2, int c2)
{
    // Fórmula da soma de prefixos 2D:
    // soma = prefixo[r2][c2] - prefixo[r1][c2] - prefixo[r2][c1] + prefixo[r1][c1]
    return prefixo[r2][c2] - prefixo[r1][c2] - prefixo[r2][c1] + prefixo[r1][c1];
}

int main()
{
    int N, M, L;

    // Lê as dimensões da grade (N bombas x M veículos por bomba)
    scanf("%d %d", &N, &M);

    // Lê a grade de veículos
    for (int i = 1; i <= N; i++)
    {
        scanf("%s", &grade[i][1]);
    }

    // Constrói as matrizes de soma de prefixos
    // prefixo[i][j] representa a soma do retângulo de (1,1) até (i,j)
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            int gasolina = 0;
            int carro = 0;
            int moto = 0;

            if (grade[i][j] == 'C')
            {
                gasolina = CARRO;
                carro = 1;
            }
            else if (grade[i][j] == 'M')
            {
                gasolina = MOTO;
                moto = 1;
            }

            // Aplica a fórmula da soma de prefixos 2D
            // prefixo[i][j] = valor[i][j] + prefixo[i-1][j] + prefixo[i][j-1] - prefixo[i-1][j-1]
            prefixoGasolina[i][j] = gasolina + prefixoGasolina[i - 1][j] + prefixoGasolina[i][j - 1] - prefixoGasolina[i - 1][j - 1];
            prefixoCarros[i][j] = carro + prefixoCarros[i - 1][j] + prefixoCarros[i][j - 1] - prefixoCarros[i - 1][j - 1];
            prefixoMotos[i][j] = moto + prefixoMotos[i - 1][j] + prefixoMotos[i][j - 1] - prefixoMotos[i - 1][j - 1];
        }
    }

    // Lê o tamanho do quadrado desejado
    scanf("%d", &L);

    // Verifica se o quadrado cabe na grade
    if (L > N || L > M)
    {
        printf("-1\n");
        return 0;
    }

    int maxGasolina = -1;

    // Percorre todas as posições possíveis para um quadrado LxL
    // Agora em O(N*M) ao invés de O(N*M*L²)
    for (int i = 1; i <= N - L + 1; i++)
    {
        for (int j = 1; j <= M - L + 1; j++)
        {
            // Calcula quantos carros e motos existem no quadrado LxL
            // iniciando em (i, j) e terminando em (i+L-1, j+L-1)
            int carros = somaRetangulo(prefixoCarros, i - 1, j - 1, i + L - 1, j + L - 1);
            int motos = somaRetangulo(prefixoMotos, i - 1, j - 1, i + L - 1, j + L - 1);

            // Verifica se o quadrado tem pelo menos um carro E uma moto
            if (carros > 0 && motos > 0)
            {
                // Calcula a gasolina total no quadrado usando soma de prefixos
                int gasolina = somaRetangulo(prefixoGasolina, i - 1, j - 1, i + L - 1, j + L - 1);

                // Atualiza o máximo
                if (gasolina > maxGasolina)
                {
                    maxGasolina = gasolina;
                }
            }
        }
    }

    // Imprime o resultado
    printf("%d\n", maxGasolina);

    return 0;
}
