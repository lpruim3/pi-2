#ifndef READCSV_H
#define READCSV_H

#include "./produto.h"
#include "./hash.h"

int ler_csv(const char *caminho, VetorProdutos *vetor, TabelaHash *tabela);

#endif