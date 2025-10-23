/*
-----------------------------------------------
DESAFIO 1 - LISTA ENCADEADA SIMPLES: FILA DE IMPRESSÃO
-----------------------------------------------

Enunciado:
Implemente uma lista encadeada simples que simule uma fila de impressão.
Cada nó representa um documento com:
 - nome do arquivo (string)
 - número de páginas (int)

Operações:
 1. Inserir documento no fim da fila
 2. Imprimir a fila completa
 3. Remover (imprimir) o primeiro documento

Exemplo de execução:
Entrada simulada:
    Inserir: Relatorio.pdf (12)
    Inserir: Apresentacao.pptx (25)
    Inserir: Contrato.docx (7)
    Remover (imprime o primeiro)
Saída esperada:
    [Relatorio.pdf | 12] -> [Apresentacao.pptx | 25] -> [Contrato.docx | 7] -> NULL
    [Apresentacao.pptx | 25] -> [Contrato.docx | 7] -> NULL
-----------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 64

// Estrutura do nó da lista simples
typedef struct No
{
    char doc[MAX_NOME];
    int paginas;
    struct No *prox;
} No;

// Cria um novo nó
No *novo_no(const char *nome, int pags)
{
    No *n = (No *)malloc(sizeof(No));
    strcpy(n->doc, nome);
    n->paginas = pags;
    n->prox = NULL;
    return n;
}

// Insere no fim da fila
void enfileirar(No **ini, const char *nome, int pags)
{
    No *n = novo_no(nome, pags);

    if (*ini == NULL)
    { // caso fila vazia
        *ini = n;
        return;
    }

    No *p = *ini;
    while (p->prox != NULL) // percorre até o último
        p = p->prox;
    p->prox = n; // liga o último ao novo nó
}

// Remove do início da fila
void desenfileirar(No **ini)
{
    if (*ini == NULL)
        return;

    No *temp = *ini; // guarda o primeiro
    printf("Imprimindo: %s (%d páginas)\n", temp->doc, temp->paginas);
    *ini = temp->prox; // move o início
    free(temp);        // libera memória
}

// Imprime toda a fila
void imprimir(No *ini)
{
    while (ini != NULL)
    {
        printf("[%s | %d] -> ", ini->doc, ini->paginas);
        ini = ini->prox;
    }
    printf("NULL\n");
}

int main()
{
    No *fila = NULL;

    enfileirar(&fila, "Relatorio.pdf", 12);
    enfileirar(&fila, "Apresentacao.pptx", 25);
    enfileirar(&fila, "Contrato.docx", 7);

    imprimir(fila);
    desenfileirar(&fila);
    imprimir(fila);

    return 0;
}
