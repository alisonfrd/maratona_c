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
 *
 * ============================================================================
 * ANÁLISE DA COMPLEXIDADE E DECISÃO DE USAR SOMA DE PREFIXOS 2D
 * ============================================================================
 *
 * RACIOCÍNIO EM MARATONA:
 *
 * 1. IDENTIFICANDO O PROBLEMA:
 *    - Precisamos testar TODOS os quadrados LxL possíveis na matriz NxM
 *    - Para cada quadrado, precisamos:
 *      a) Somar a gasolina total
 *      b) Contar quantos carros existem
 *      c) Contar quantas motos existem
 *    - Depois escolher o quadrado com maior soma que tenha pelo menos 1 carro E 1 moto
 *
 * 2. ABORDAGEM INGÊNUA (primeira ideia):
 *    - Para cada posição (i,j) possível do canto superior esquerdo do quadrado:
 *      - Percorrer todas as L linhas e L colunas do quadrado
 *      - Somar os valores célula por célula
 *    - Número de quadrados possíveis: O((N-L+1) * (M-L+1)) ≈ O(N*M)
 *    - Para cada quadrado: O(L²) para percorrer todas as células
 *    - COMPLEXIDADE TOTAL: O(N * M * L²)
 *    - Com N=M=L=1000: 1000 * 1000 * 1000² = 10^12 operações → MUITO LENTO! TLE!
 *
 * 3. OTIMIZAÇÃO NECESSÁRIA:
 *    - Precisamos calcular a soma de um retângulo em O(1) ao invés de O(L²)
 *    - Isso reduzirá a complexidade para O(N*M), que com N=M=1000 é 10^6 → ACEITÁVEL!
 *
 * 4. SOLUÇÃO: SOMA DE PREFIXOS 2D (Prefix Sum 2D / Summed Area Table)
 *    - É uma técnica clássica de maratona para problemas de soma em submatrizes
 *    - Ideia: pré-computar as somas acumuladas para responder queries em O(1)
 *
 * ============================================================================
 * DEDUÇÃO DA FÓRMULA DE SOMA DE PREFIXOS 2D
 * ============================================================================
 *
 * DEFINIÇÃO:
 * prefixo[i][j] = soma de todos os elementos no retângulo de (0,0) até (i-1, j-1)
 *
 * CONSTRUÇÃO (como preencher a matriz de prefixos):
 *
 * Pense visualmente:
 *     0   1   2   3   (colunas)
 *   +---+---+---+---+
 * 0 | A | B | ? | ? |
 *   +---+---+---+---+
 * 1 | C | X | ? | ? |    Queremos calcular prefixo[1][1] (soma até X)
 *   +---+---+---+---+
 * 2 | ? | ? | ? | ? |
 *   +---+---+---+---+
 *
 * Para calcular prefixo[i][j] (soma do retângulo de (0,0) até (i-1,j-1)):
 *
 * prefixo[i][j] = valor[i][j]              // o valor da célula atual
 *               + prefixo[i-1][j]          // soma do retângulo acima
 *               + prefixo[i][j-1]          // soma do retângulo à esquerda
 *               - prefixo[i-1][j-1]        // subtrai a interseção que foi contada 2x
 *
 * Por que subtrair prefixo[i-1][j-1]?
 * - Ao somar prefixo[i-1][j] e prefixo[i][j-1], a região diagonal superior
 *   esquerda é contada DUAS VEZES, então precisamos subtrair uma vez.
 *
 * CONSULTA (como calcular soma de um retângulo arbitrário):
 *
 * Queremos a soma do retângulo de (r1,c1) até (r2-1,c2-1):
 *
 *     c1      c2
 *      ↓       ↓
 *   +--+-------+--+
 * r1→| A|   B  | C|
 *   +--+-------+--+
 *   | D|  ALVO | E|  ← Queremos somar apenas a região ALVO
 *   +--+-------+--+
 * r2→| F|   G  | H|
 *   +--+-------+--+
 *
 * FÓRMULA DA CONSULTA:
 * soma = prefixo[r2][c2]           // toda a região de (0,0) até (r2-1,c2-1)
 *      - prefixo[r1][c2]           // subtrai a parte de cima (antes de r1)
 *      - prefixo[r2][c1]           // subtrai a parte da esquerda (antes de c1)
 *      + prefixo[r1][c1]           // adiciona o canto que foi subtraído 2x
 *
 * ANALOGIA PARA MARATONA:
 * Imagine que prefixo[i][j] é a "área total pintada" de (0,0) até (i,j).
 * Para descobrir a área de um retângulo menor:
 * 1. Pegue a área total até o canto inferior direito
 * 2. Remova a faixa de cima (acima de r1)
 * 3. Remova a faixa da esquerda (à esquerda de c1)
 * 4. Mas agora removemos o cantinho superior esquerdo 2 vezes, então devolvemos 1x
 *
 * ============================================================================
 * COMO CHEGAR NESSA SOLUÇÃO EM UMA PROVA:
 * ============================================================================
 *
 * PASSO 1: Identificar que a solução ingênua é muito lenta
 * - Calcular a complexidade: O(N*M*L²) = 10^12 → TLE
 *
 * PASSO 2: Reconhecer o padrão do problema
 * - "Soma de elementos em múltiplos subretângulos" → Soma de Prefixos 2D
 * - É uma técnica standard que todo competidor de maratona deve conhecer
 *
 * PASSO 3: Aplicar a técnica
 * - Pré-processar: O(N*M) para construir as matrizes de prefixo
 * - Query: O(1) para cada quadrado
 * - Total: O(N*M) → Passa no tempo limite!
 *
 * PASSO 4: Implementar com cuidado nos índices
 * - Usar indexação 1-based ou 0-based consistentemente
 * - Testar com exemplo pequeno (matriz 3x3, L=2) para validar
 *
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX_N 1001

// DECISÃO: Por que 25 e 12?
// - Enunciado especifica que carros podem abastecer no máximo 25 litros
// - Motos podem abastecer no máximo 12 litros
// - Usamos constantes para facilitar manutenção e legibilidade do código
#define CARRO 25 // Litros para carros
#define MOTO 12  // Litros para motos

// DECISÃO: Por que char e não int para armazenar a grade?
// - Cada célula contém apenas 'C' ou 'M' (1 byte cada)
// - char usa 1 byte, int usa 4 bytes
// - Com N=M=1000, economizamos 3MB de memória (importante em juízes online)
// - Leitura com scanf("%s") é mais conveniente linha por linha
char grade[MAX_N][MAX_N];

// DECISÃO: Por que precisamos de 3 matrizes de prefixos?
// - Precisamos responder 3 perguntas para cada quadrado:
//   1. Qual a gasolina total? (para maximizar)
//   2. Quantos carros existem? (precisa ter >= 1)
//   3. Quantas motos existem? (precisa ter >= 1)
// - Cada matriz de prefixos permite responder uma dessas perguntas em O(1)
//
// CONVENÇÃO DE INDEXAÇÃO:
// - Usamos indexação 1-based (começando em 1) para simplificar a fórmula
// - prefixo[0][j] e prefixo[i][0] são sempre 0 (bordas para evitar if's)
// - prefixo[i][j] = soma do retângulo de (1,1) até (i,j) INCLUSIVE
//
// DEFINIÇÃO FORMAL:
// prefixoGasolina[i][j] = soma de litros de gasolina no retângulo de (1,1) até (i,j)
// prefixoCarros[i][j] = quantidade de carros no retângulo de (1,1) até (i,j)
// prefixoMotos[i][j] = quantidade de motos no retângulo de (1,1) até (i,j)
int prefixoGasolina[MAX_N][MAX_N];
int prefixoCarros[MAX_N][MAX_N];
int prefixoMotos[MAX_N][MAX_N];

/*
 * Função para calcular a soma em um retângulo usando soma de prefixos 2D
 *
 * PARÂMETROS:
 * - prefixo: a matriz de prefixos já construída
 * - r1, c1: coordenadas do canto SUPERIOR ESQUERDO do retângulo (EXCLUSIVE)
 * - r2, c2: coordenadas do canto INFERIOR DIREITO do retângulo (INCLUSIVE)
 *
 * RETORNA: soma dos valores no retângulo de (r1+1, c1+1) até (r2, c2)
 *
 * DEDUÇÃO DA FÓRMULA (passo a passo):
 *
 * Queremos somar o retângulo de (r1+1, c1+1) até (r2, c2).
 *
 * Visualização:
 *
 *      0   c1  ...  c2  ... M
 *    +----+----+----+----+----+
 *  0 | A  | A  | A  | A  |    |  ← prefixo[r1][c1] = soma de toda região A
 *    +----+----+----+----+----+
 * r1 | A  | A  | B  | B  |    |  ← prefixo[r1][c2] = soma de A + B
 *    +----+----+----+----+----+
 *    | A  | A  | ALVO|    |    |  ← Este é o retângulo que queremos!
 *    +----+----+----+----+----+
 * r2 | A  | A  | ALVO|    |    |  ← prefixo[r2][c2] = soma de A + D + ALVO + B
 *    +----+----+----+----+----+
 *    | D  | D  |    |    |    |  ← prefixo[r2][c1] = soma de A + D
 *    +----+----+----+----+----+
 *
 * PASSO 1: Pegamos prefixo[r2][c2]
 *    = soma de toda a região de (0,0) até (r2,c2)
 *    = A + B + D + ALVO
 *
 * PASSO 2: Subtraímos prefixo[r1][c2] (remove a parte de cima)
 *    Agora temos: (A + B + D + ALVO) - (A + B) = D + ALVO
 *
 * PASSO 3: Subtraímos prefixo[r2][c1] (remove a parte da esquerda)
 *    Agora temos: (D + ALVO) - (A + D) = ALVO - A
 *    Ops! Subtraímos A uma vez a mais!
 *
 * PASSO 4: Adicionamos prefixo[r1][c1] (devolve o canto que foi subtraído 2x)
 *    Resultado final: (ALVO - A) + A = ALVO ✓
 *
 * FÓRMULA FINAL:
 * soma = prefixo[r2][c2] - prefixo[r1][c2] - prefixo[r2][c1] + prefixo[r1][c1]
 *
 * TRUQUE DE MARATONA:
 * - Os parâmetros r1 e c1 representam a linha/coluna ANTES do retângulo desejado
 * - Isso simplifica a fórmula e evita condições especiais nos limites
 * - Para calcular um quadrado de (i,j) até (i+L-1, j+L-1), usamos:
 *   somaRetangulo(prefixo, i-1, j-1, i+L-1, j+L-1)
 */
int somaRetangulo(int prefixo[MAX_N][MAX_N], int r1, int c1, int r2, int c2)
{
    // Aplicação direta da fórmula deduzida acima
    // Esta operação é O(1) - apenas 3 subtrações e 1 adição!
    return prefixo[r2][c2] - prefixo[r1][c2] - prefixo[r2][c1] + prefixo[r1][c1];
}

int main()
{
    int N, M, L;

    // Lê as dimensões da grade (N bombas x M veículos por bomba)
    // N = número de linhas (bombas)
    // M = número de colunas (veículos por bomba)
    scanf("%d %d", &N, &M);

    // DECISÃO: Por que ler com &grade[i][1] e não &grade[i][0]?
    // - Estamos usando indexação 1-based para facilitar a lógica dos prefixos
    // - grade[i][1] até grade[i][M] contém os caracteres da linha i
    // - grade[i][0] fica sem uso (poderia ser usado para 0-based, mas seria mais confuso)
    // - scanf("%s") lê uma string completa, então automaticamente preenche
    //   grade[i][1], grade[i][2], ..., grade[i][M]
    //
    // IMPORTANTE: scanf("%s") adiciona '\0' ao final, por isso MAX_N precisa ter espaço extra
    for (int i = 1; i <= N; i++)
    {
        scanf("%s", &grade[i][1]);
    }

    // ========================================================================
    // CONSTRUÇÃO DAS MATRIZES DE SOMA DE PREFIXOS - O CORAÇÃO DA SOLUÇÃO
    // ========================================================================
    //
    // OBJETIVO: Pré-computar as somas acumuladas para responder queries em O(1)
    //
    // INVARIANTE: prefixo[i][j] = soma de todos os valores de (1,1) até (i,j)
    //
    // COMPLEXIDADE: O(N*M) - percorremos cada célula uma única vez
    //
    // DECISÃO: Por que computar 3 matrizes separadas?
    // - Cada matriz rastreia uma métrica diferente (gasolina, carros, motos)
    // - Poderíamos usar apenas 1 matriz e recalcular as outras, mas seria menos eficiente
    // - Espaço extra: 3 * N * M * 4 bytes ≈ 12MB com N=M=1000 (aceitável)
    //
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            // PASSO 1: Determinar o valor da célula atual
            // Convertemos 'C' → 25 litros, 'M' → 12 litros
            int gasolina = 0;
            int carro = 0; // Booleano: 1 se é carro, 0 caso contrário
            int moto = 0;  // Booleano: 1 se é moto, 0 caso contrário

            if (grade[i][j] == 'C')
            {
                gasolina = CARRO; // 25 litros
                carro = 1;
            }
            else if (grade[i][j] == 'M')
            {
                gasolina = MOTO; // 12 litros
                moto = 1;
            }
            // Nota: se grade[i][j] não for 'C' nem 'M', mantemos tudo 0 (célula vazia)
            // Mas pelo enunciado, isso nunca acontece

            // PASSO 2: Aplicar a fórmula de construção do prefixo 2D
            //
            // DEDUÇÃO DA FÓRMULA DE CONSTRUÇÃO:
            //
            // Queremos: prefixo[i][j] = soma de (1,1) até (i,j)
            //
            // Podemos dividir em 4 partes:
            //     j-1  j
            //    +----+--+
            // i-1| A  |B |  A = prefixo[i-1][j-1]
            //    +----+--+  B = prefixo[i-1][j] - prefixo[i-1][j-1]
            // i  | C  |X |  C = prefixo[i][j-1] - prefixo[i-1][j-1]
            //    +----+--+  X = valor[i][j] (célula atual)
            //
            // Então: prefixo[i][j] = A + B + C + X
            //                       = prefixo[i-1][j-1] + (prefixo[i-1][j] - prefixo[i-1][j-1])
            //                         + (prefixo[i][j-1] - prefixo[i-1][j-1]) + valor[i][j]
            //                       = valor[i][j] + prefixo[i-1][j] + prefixo[i][j-1]
            //                         - prefixo[i-1][j-1]
            //
            // INTERPRETAÇÃO:
            // - valor[i][j]: adiciona o valor da célula atual
            // - prefixo[i-1][j]: adiciona toda a soma acima (linhas 1 até i-1, colunas 1 até j)
            // - prefixo[i][j-1]: adiciona toda a soma à esquerda (linhas 1 até i, colunas 1 até j-1)
            // - -prefixo[i-1][j-1]: subtrai a interseção que foi contada duas vezes
            //
            // CONDIÇÃO DE BORDA:
            // - Quando i=1 ou j=1, os termos com [i-1] ou [j-1] acessam [0], que foi
            //   inicializado como 0 (globals em C são zerados automaticamente)
            // - Isso elimina a necessidade de if's para casos especiais!
            //
            prefixoGasolina[i][j] = gasolina + prefixoGasolina[i - 1][j] // soma de cima
                                    + prefixoGasolina[i][j - 1]          // soma da esquerda
                                    - prefixoGasolina[i - 1][j - 1];     // remove interseção

            prefixoCarros[i][j] = carro + prefixoCarros[i - 1][j] + prefixoCarros[i][j - 1] - prefixoCarros[i - 1][j - 1];

            prefixoMotos[i][j] = moto + prefixoMotos[i - 1][j] + prefixoMotos[i][j - 1] - prefixoMotos[i - 1][j - 1];
        }
    }
    // Após este loop, as 3 matrizes de prefixos estão completamente construídas
    // e prontas para responder queries em O(1)!

    // Lê o tamanho do quadrado desejado
    scanf("%d", &L);

    // ========================================================================
    // VALIDAÇÃO: Verifica se é possível ter um quadrado LxL na grade NxM
    // ========================================================================
    //
    // DECISÃO: Por que verificar L > N ou L > M?
    // - Se L > N, não há L linhas suficientes para formar o quadrado
    // - Se L > M, não há L colunas suficientes para formar o quadrado
    // - Exemplo: matriz 3x5 (3 linhas, 5 colunas) com L=4
    //   → Não dá para ter 4 linhas, então retorna -1
    //
    // DECISÃO: Por que retornar -1?
    // - O enunciado especifica: "Se não houver quadrado [...], imprima -1"
    // - Este é um caso impossível (não há nem espaço físico para o quadrado)
    //
    if (L > N || L > M)
    {
        printf("-1\n");
        return 0;
    }

    // DECISÃO: Por que inicializar maxGasolina com -1?
    // - Se nenhum quadrado válido for encontrado (com >= 1 carro E >= 1 moto),
    //   queremos imprimir -1
    // - Inicializar com -1 permite detectar esse caso ao final
    // - Qualquer quadrado válido terá gasolina >= 12+25 = 37, então -1 nunca
    //   será confundido com um valor real
    int maxGasolina = -1;

    // ========================================================================
    // BUSCA EXAUSTIVA: Testar todos os quadrados LxL possíveis
    // ========================================================================
    //
    // DECISÃO: Por que iterar de 1 até N-L+1 (e não até N)?
    // - O quadrado começa em (i,j) e ocupa L linhas e L colunas
    // - Se começar em linha i, o quadrado vai até linha i+L-1
    // - Para caber na grade: i+L-1 ≤ N  →  i ≤ N-L+1
    // - Mesma lógica para colunas
    //
    // EXEMPLO: N=5, L=3
    // - Posições válidas para i: 1, 2, 3
    //   i=1 → quadrado ocupa linhas 1,2,3 ✓
    //   i=2 → quadrado ocupa linhas 2,3,4 ✓
    //   i=3 → quadrado ocupa linhas 3,4,5 ✓
    //   i=4 → quadrado ocuparia linhas 4,5,6 ✗ (não existe linha 6)
    //
    // COMPLEXIDADE: O((N-L+1) * (M-L+1)) = O(N*M)
    // - Para cada posição, fazemos apenas O(1) operações (graças aos prefixos!)
    //
    for (int i = 1; i <= N - L + 1; i++)
    {
        for (int j = 1; j <= M - L + 1; j++)
        {
            // ================================================================
            // QUERY: Calcular estatísticas do quadrado em O(1)
            // ================================================================
            //
            // O quadrado atual:
            // - Canto superior esquerdo: (i, j)
            // - Canto inferior direito: (i+L-1, j+L-1)
            //
            // DECISÃO: Por que passar (i-1, j-1) como primeiros parâmetros?
            // - A função somaRetangulo espera os índices ANTES do retângulo
            // - Queremos somar de (i,j) até (i+L-1, j+L-1)
            // - Então passamos a linha/coluna anterior: (i-1, j-1)
            //
            // CÁLCULO DOS CARROS: Quantos carros existem neste quadrado?
            int carros = somaRetangulo(prefixoCarros, i - 1, j - 1, i + L - 1, j + L - 1);

            // CÁLCULO DAS MOTOS: Quantas motos existem neste quadrado?
            int motos = somaRetangulo(prefixoMotos, i - 1, j - 1, i + L - 1, j + L - 1);

            // ================================================================
            // VALIDAÇÃO: O quadrado satisfaz as condições do problema?
            // ================================================================
            //
            // CONDIÇÃO DO ENUNCIADO: "deve haver pelo menos um veículo de cada tipo"
            // - Precisa ter >= 1 carro E >= 1 moto
            // - Se tiver só carros ou só motos, não é válido
            //
            // DECISÃO: Por que verificar carros > 0 && motos > 0?
            // - Se carros == 0, o quadrado tem apenas motos → inválido
            // - Se motos == 0, o quadrado tem apenas carros → inválido
            // - Só processamos o quadrado se ambos forem > 0
            //
            if (carros > 0 && motos > 0)
            {
                // QUERY DE GASOLINA: Agora sim, calcula a gasolina total
                // (só calculamos se o quadrado for válido, para não desperdiçar operações)
                int gasolina = somaRetangulo(prefixoGasolina, i - 1, j - 1, i + L - 1, j + L - 1);

                // ATUALIZAÇÃO DO MÁXIMO
                // - Se este quadrado tem mais gasolina que o melhor encontrado até agora,
                //   atualizamos o máximo
                // - Na primeira iteração válida, maxGasolina era -1, então qualquer valor
                //   positivo será maior e atualizará maxGasolina
                if (gasolina > maxGasolina)
                {
                    maxGasolina = gasolina;
                }
            }
            // Se carros == 0 ou motos == 0, simplesmente ignoramos este quadrado
            // e continuamos testando os próximos
        }
    }

    // ========================================================================
    // SAÍDA DO RESULTADO
    // ========================================================================
    //
    // DECISÃO: Por que apenas um printf?
    // - Se maxGasolina ainda for -1, nenhum quadrado válido foi encontrado
    // - Se maxGasolina > -1, foi encontrado pelo menos um quadrado válido
    // - Em ambos os casos, o valor correto já está em maxGasolina!
    //
    printf("%d\n", maxGasolina);

    return 0;
}

/*
 * ============================================================================
 * RESUMO DA SOLUÇÃO PARA MARATONA
 * ============================================================================
 *
 * 1. IDENTIFICAÇÃO DO PROBLEMA:
 *    - Soma em submatrizes múltiplas → Soma de Prefixos 2D
 *
 * 2. PRÉ-PROCESSAMENTO: O(N*M)
 *    - Construir 3 matrizes de prefixos (gasolina, carros, motos)
 *    - Fórmula: prefixo[i][j] = valor + prefixo[i-1][j] + prefixo[i][j-1] - prefixo[i-1][j-1]
 *
 * 3. BUSCA: O(N*M)
 *    - Para cada posição (i,j) possível do quadrado LxL:
 *      a) Calcular quantidade de carros e motos em O(1)
 *      b) Se tem >= 1 de cada tipo, calcular gasolina total em O(1)
 *      c) Atualizar o máximo
 *
 * 4. COMPLEXIDADE TOTAL: O(N*M)
 *    - Com N=M=1000: ~10^6 operações → Passa tranquilamente!
 *
 * 5. PONTOS DE ATENÇÃO:
 *    - Indexação 1-based consistente
 *    - Inicialização correta das bordas (linha/coluna 0 = 0)
 *    - Cuidado com os limites do loop (N-L+1, não N)
 *    - Tratamento do caso impossível (maxGasolina = -1)
 *
 * 6. TÉCNICAS UTILIZADAS:
 *    - Soma de Prefixos 2D (Prefix Sum 2D / Summed Area Table)
 *    - Busca exaustiva otimizada
 *    - Pré-computação para queries rápidas
 *
 * ============================================================================
 */
