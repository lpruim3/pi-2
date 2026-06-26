#include "./include/readcsv.h"
#include "./include/produto.h"
#include "./include/hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ler_csv(const char *caminho, VetorProdutos *vetor, TabelaHash *tabela) {
    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        printf("Erro: arquivo '%s' não encontrado.\n", caminho);
        return 0;
    }

    char linha[256];

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        // vai ignorar se tiver linha em branco
        if (linha[0] == '\n' || linha[0] == '\0') continue;

        Produto p;
        char valor_str[20];

        int campos = sscanf(linha, "%d,%99[^,],%49[^,],%19s",
                            &p.id, p.nome, p.categoria, valor_str);

        if (campos != 4) {
            printf("Aviso: linha com formato inválido ignorada: %s", linha);
            continue;
        }

        p.valor = atof(valor_str);

        // fase 1
        adicionar_produto(vetor, p);

        // fase 2
        inserir_tabela(tabela, p);
    }

    fclose(arquivo);
    return 1; 
}