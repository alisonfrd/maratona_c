/*
 * Beecrowd 1340 - Eu Posso Adivinhar a Estrutura de Dados!
 *
 * ENUNCIADO (Tradução):
 *
 * Há uma estrutura de dados tipo "bolsa" que suporta duas operações:
 *
 * 1 x
 * Joga um elemento x na bolsa.
 *
 * 2
 * Retira um elemento da bolsa.
 *
 * Dada uma sequência de operações com valores de retorno, você deve adivinhar
 * a estrutura de dados. É uma pilha (LIFO - Last-In, First-Out), uma fila
 * (FIFO - First-In, First-Out), uma fila de prioridade (sempre retira elementos
 * maiores primeiro) ou algo mais que você dificilmente pode imaginar!
 *
 * Entrada:
 * Há vários casos de teste. Cada caso começa com uma linha contendo um único
 * inteiro n (1 <= n <= 1000). Cada uma das próximas n linhas é ou um comando
 * tipo-1, ou um inteiro 2 seguido de um inteiro x. Isso significa que após
 * executar um comando tipo-2, obtemos um elemento x sem erro. O valor de x é
 * sempre um inteiro positivo não maior que 100. A entrada termina com EOF.
 * O tamanho do arquivo de entrada não excede 1MB.
 *
 * Saída:
 * Para cada caso de teste, imprima uma das seguintes opções:
 *
 * stack - É definitivamente uma pilha.
 * queue - É definitivamente uma fila.
 * priority queue - É definitivamente uma fila de prioridade.
 * impossible - Não pode ser pilha, fila ou fila de prioridade.
 * not sure - Pode ser mais de uma das três estruturas mencionadas.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

// Estrutura para armazenar as operações
typedef struct
{
    int type;  // 1 para inserir, 2 para remover
    int value; // valor a ser inserido ou valor esperado ao remover
} Operation;

// Função para verificar se as operações correspondem a uma pilha (LIFO)
int isStack(Operation ops[], int n)
{
    int stack[MAX_N];
    int top = -1; // Topo da pilha (-1 indica pilha vazia)

    for (int i = 0; i < n; i++)
    {
        if (ops[i].type == 1)
        {
            // Operação de inserção: empilha o valor
            top++;
            stack[top] = ops[i].value;
        }
        else
        {
            // Operação de remoção: desempilha e verifica
            if (top == -1)
            {
                // Pilha vazia, não pode remover
                return 0;
            }
            if (stack[top] != ops[i].value)
            {
                // Valor removido não corresponde ao esperado
                return 0;
            }
            top--;
        }
    }
    return 1; // Todas as operações correspondem a uma pilha
}

// Função para verificar se as operações correspondem a uma fila (FIFO)
int isQueue(Operation ops[], int n)
{
    int queue[MAX_N];
    int front = 0; // Início da fila
    int rear = 0;  // Fim da fila

    for (int i = 0; i < n; i++)
    {
        if (ops[i].type == 1)
        {
            // Operação de inserção: enfileira o valor
            queue[rear] = ops[i].value;
            rear++;
        }
        else
        {
            // Operação de remoção: desenfileira e verifica
            if (front == rear)
            {
                // Fila vazia, não pode remover
                return 0;
            }
            if (queue[front] != ops[i].value)
            {
                // Valor removido não corresponde ao esperado
                return 0;
            }
            front++;
        }
    }
    return 1; // Todas as operações correspondem a uma fila
}

// Função para verificar se as operações correspondem a uma fila de prioridade (max heap)
int isPriorityQueue(Operation ops[], int n)
{
    int pq[MAX_N];
    int size = 0; // Tamanho atual da fila de prioridade

    for (int i = 0; i < n; i++)
    {
        if (ops[i].type == 1)
        {
            // Operação de inserção: adiciona o valor na fila de prioridade
            pq[size] = ops[i].value;
            size++;
        }
        else
        {
            // Operação de remoção: encontra e remove o maior elemento
            if (size == 0)
            {
                // Fila vazia, não pode remover
                return 0;
            }

            // Encontra o índice do maior elemento
            int maxIdx = 0;
            for (int j = 1; j < size; j++)
            {
                if (pq[j] > pq[maxIdx])
                {
                    maxIdx = j;
                }
            }

            // Verifica se o maior elemento corresponde ao esperado
            if (pq[maxIdx] != ops[i].value)
            {
                return 0;
            }

            // Remove o maior elemento deslocando os elementos seguintes
            for (int j = maxIdx; j < size - 1; j++)
            {
                pq[j] = pq[j + 1];
            }
            size--;
        }
    }
    return 1; // Todas as operações correspondem a uma fila de prioridade
}

int main()
{
    int n;

    // Lê casos de teste até EOF
    while (scanf("%d", &n) != EOF)
    {
        Operation ops[MAX_N];

        // Lê as n operações
        for (int i = 0; i < n; i++)
        {
            int type, value;
            scanf("%d %d", &type, &value);
            ops[i].type = type;
            ops[i].value = value;
        }

        // Verifica qual(is) estrutura(s) de dados correspondem às operações
        int stack = isStack(ops, n);
        int queue = isQueue(ops, n);
        int priorityQueue = isPriorityQueue(ops, n);

        // Conta quantas estruturas correspondem
        int count = stack + queue + priorityQueue;

        // Determina a saída baseada no número de correspondências
        if (count == 0)
        {
            printf("impossible\n");
        }
        else if (count > 1)
        {
            printf("not sure\n");
        }
        else if (stack)
        {
            printf("stack\n");
        }
        else if (queue)
        {
            printf("queue\n");
        }
        else
        {
            printf("priority queue\n");
        }
    }

    return 0;
}
