#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    char nome[100];
    char categoria[50];
    float valor;
} Produto;

typedef struct {
    Produto *dados;
    int tamanho;
    int capacidade;
} VetorProdutos;

void inicializador_vetor(VetorProdutos *v);
int adicionar_produto(VetorProdutos *v, Produto p);
void liberar_vetor(VetorProdutos *v);
int busca_sequencial(VetorProdutos *v, int id_buscado);

#endif
