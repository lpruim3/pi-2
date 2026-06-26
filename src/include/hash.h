#ifndef HASH_H
#define HASH_H

#include "produto.h"

typedef struct Node {
    Produto produto;
    struct Node *proximo;
} Node;

typedef struct {
    Node **buckets;     
    int tamanho;        
    int total_colisoes; 
} TabelaHash;

void inicializar_tabela(TabelaHash *tabela, int tamanho);
int funcao_hash(int id, int tamanho);
void inserir_tabela(TabelaHash *tabela, Produto prod);
int busca_tabela(TabelaHash *tabela, int id);
void liberar_tabela(TabelaHash *tabela);

#endif
