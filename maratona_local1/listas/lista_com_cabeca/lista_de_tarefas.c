/*
-----------------------------------------------
DESAFIO 4 - LISTA COM CABEÇA: LISTA DE TAREFAS
-----------------------------------------------

Enunciado:
Implemente uma lista encadeada com nó cabeça (sem dados úteis no primeiro nó)
Cada tarefa tem uma descrição.
Permitir:
 - Inserir no início
 - Remover tarefa pelo nome
 - Imprimir todas as tarefas

Exemplo de execução:
Inserções: "Estudar C", "Revisar Ponteiros", "Fazer Exercícios"
Remover: "Revisar Ponteiros"
Saída esperada:
    [Fazer Exercícios] -> [Estudar C] -> NULL
-----------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFA 80

typedef struct No
{
    char tarefa[MAX_TAREFA];
    struct No *prox;
} No;

// Cria nó cabeça
No *criar_lista()
{
    No *cabeca = (No *)malloc(sizeof(No));
    cabeca->prox = NULL;
    return cabeca;
}

// Insere logo após o nó cabeça
void inserir(No *cabeca, const char *tarefa)
{
    No *novo = (No *)malloc(sizeof(No));
    strcpy(novo->tarefa, tarefa);
    novo->prox = cabeca->prox;
    cabeca->prox = novo;
}

// Remove tarefa pelo nome
void remover(No *cabeca, const char *tarefa)
{
    No *ant = cabeca;
    No *p = cabeca->prox;

    while (p != NULL && strcmp(p->tarefa, tarefa) != 0)
    {
        ant = p;
        p = p->prox;
    }

    if (p != NULL)
    {
        ant->prox = p->prox;
        free(p);
    }
}

// Imprime todas as tarefas
void imprimir(No *cabeca)
{
    No *p = cabeca->prox;
    while (p != NULL)
    {
        printf("[%s] -> ", p->tarefa);
        p = p->prox;
    }
    printf("NULL\n");
}

int main()
{
    No *lista = criar_lista();

    inserir(lista, "Estudar C");
    inserir(lista, "Revisar Ponteiros");
    inserir(lista, "Fazer Exercícios");

    remover(lista, "Revisar Ponteiros");
    imprimir(lista);

    return 0;
}
