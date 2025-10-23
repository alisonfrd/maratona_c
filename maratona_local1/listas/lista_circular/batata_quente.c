/*
-----------------------------------------------
DESAFIO 3 - LISTA CIRCULAR: JOGO DA BATATA QUENTE
-----------------------------------------------

Enunciado:
Cada nó é um jogador. A batata passa N vezes, e o jogador que a recebe é eliminado.
O jogo segue até restar apenas um.

Exemplo de execução:
Jogadores: Ana, Bob, Carlos, Duda
Passes: 3
Saída esperada:
    Carlos eliminado
    Duda eliminado
    Ana eliminado
    Bob vence o jogo!
-----------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30

typedef struct No
{
    char nome[MAX_NOME];
    struct No *prox;
} No;

// Cria novo jogador
No *novo_jogador(const char *nome)
{
    No *n = (No *)malloc(sizeof(No));
    strcpy(n->nome, nome);
    n->prox = NULL;
    return n;
}

// Insere no fim da lista circular
void inserir(No **inicio, const char *nome)
{
    No *n = novo_jogador(nome);
    if (*inicio == NULL)
    {
        *inicio = n;
        n->prox = n; // aponta para si mesmo
        return;
    }

    No *p = *inicio;
    while (p->prox != *inicio)
        p = p->prox;
    p->prox = n;
    n->prox = *inicio;
}

// Remove jogador após N passes
void eliminar(No **inicio, int N)
{
    if (*inicio == NULL)
        return;

    No *p = *inicio;
    No *ant = NULL;

    while (p->prox != p)
    { // até sobrar 1
        for (int i = 0; i < N - 1; i++)
        {
            ant = p;
            p = p->prox;
        }

        printf("%s eliminado!\n", p->nome);
        ant->prox = p->prox;

        if (p == *inicio)
            *inicio = p->prox;

        free(p);
        p = ant->prox;
    }

    printf("%s vence o jogo!\n", p->nome);
    free(p);
    *inicio = NULL;
}

int main()
{
    No *jogadores = NULL;

    inserir(&jogadores, "Ana");
    inserir(&jogadores, "Bob");
    inserir(&jogadores, "Carlos");
    inserir(&jogadores, "Duda");

    int N = 3;
    eliminar(&jogadores, N);
    return 0;
}
