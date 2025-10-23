/*
-----------------------------------------------
DESAFIO 2 - LISTA DUPLAMENTE ENCADEADA: EDITOR DE TEXTO
-----------------------------------------------

Enunciado:
Cada nó representa um "estado" do texto após uma edição.
Permitir:
 - Inserir novo estado (nova versão)
 - Voltar (Ctrl+Z)
 - Avançar (Ctrl+Y)

Exemplo de execução:
Entradas:
    Inserir: "Versão 1"
    Inserir: "Versão 2"
    Inserir: "Versão 3"
    Ctrl+Z -> voltar para "Versão 2"
    Ctrl+Y -> voltar para "Versão 3"
Saída esperada:
    Estado atual: Versão 3
-----------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTO 100

typedef struct No
{
    char texto[MAX_TEXTO];
    struct No *prox;
    struct No *ant;
} No;

No *criar_no(const char *texto)
{
    No *n = (No *)malloc(sizeof(No));
    strcpy(n->texto, texto);
    n->prox = n->ant = NULL;
    return n;
}

// Insere novo estado após o atual
No *inserir(No *atual, const char *texto)
{
    No *n = criar_no(texto);
    n->ant = atual;
    if (atual != NULL)
        atual->prox = n;
    return n;
}

// Voltar uma versão (Ctrl+Z)
No *desfazer(No *atual)
{
    if (atual && atual->ant)
        return atual->ant;
    printf("Não há versão anterior.\n");
    return atual;
}

// Avançar uma versão (Ctrl+Y)
No *refazer(No *atual)
{
    if (atual && atual->prox)
        return atual->prox;
    printf("Não há versão posterior.\n");
    return atual;
}

int main()
{
    No *inicio = criar_no("Versão 1");
    No *atual = inicio;

    atual = inserir(atual, "Versão 2");
    atual = inserir(atual, "Versão 3");

    atual = desfazer(atual); // volta p/ Versão 2
    atual = refazer(atual);  // volta p/ Versão 3

    printf("Estado atual: %s\n", atual->texto);
    return 0;
}
