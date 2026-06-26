#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

void inicializar_tabela(TabelaHash *tabela, int tamanho) {
    tabela->tamanho = tamanho;
    tabela->total_colisoes = 0;
    tabela->buckets = (Node **)malloc(tamanho * sizeof(Node *));
    
    for (int i = 0; i < tamanho; i++) {
        tabela->buckets[i] = NULL; 
    }
}

// funcao hash: resto da divisao simples
int funcao_hash(int id, int tamanho) {
    if (id < 0) {
        return (-id) % tamanho;
    }
    return id % tamanho;
}

// inserção com encadeamento
void inserir_tabela(TabelaHash *tabela, Produto prod) {
    int indice = funcao_hash(prod.id, tabela->tamanho);
    
    Node *novo_no = (Node *)malloc(sizeof(Node));
    novo_no->produto = prod;
    novo_no->proximo = NULL;

    // detecção de colisão 
    if (tabela->buckets[indice] != NULL) {
        tabela->total_colisoes++;
        
        novo_no->proximo = tabela->buckets[indice];
        tabela->buckets[indice] = novo_no;
    } else {
        tabela->buckets[indice] = novo_no;
    }
}

// busca O(1), caso medio
int busca_tabela(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id, tabela->tamanho);
    Node *atual = tabela->buckets[indice];
    
    while (atual != NULL) {
        if (atual->produto.id == id) {
            return indice; // sucesso
        }
        atual = atual->proximo;
    }
    return -1; // nao encontrado
}

// libera memoria
void liberar_tabela(TabelaHash *tabela) {
    for (int i = 0; i < tabela->tamanho; i++) {
        Node *atual = tabela->buckets[i];
        while (atual != NULL) {
            Node *aux = atual;
            atual = atual->proximo;
            free(aux);
        }
    }
    free(tabela->buckets);
    tabela->buckets = NULL;
}
