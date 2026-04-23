#include "produto.h"
#include <stdlib.h>
#include <stdio.h>

void inicializador_vetor(VetorProdutos *v) {
    v->capacidade = 10;
    v->tamanho = 0;
    v->dados = malloc(v->capacidade * sizeof(Produto));

    if (v->dados == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
}

int adicionar_produto(VetorProdutos *v, Produto p) {
    if (v->tamanho == v->capacidade) {
        v->capacidade *= 2;
        v->dados = realloc(v->dados, v->capacidade * sizeof(Produto));

        if (v->dados == NULL) {
            printf("Erro ao realocar memória.\n");
            return 0; // falhou
        }
    }

    v->dados[v->tamanho] = p;
    v->tamanho++;
    return 1; // sucesso
}

void liberar_vetor(VetorProdutos *v) {
    free(v->dados);
    v->dados = NULL;
    v->tamanho = 0;
    v->capacidade = 0;
}