#include <stdio.h>
#include <stdlib.h>
#include "./include/produto.h"
#include "./include/readcsv.h"
#include "./include/timer.h"

#define QTD_BUSCAS 1000
#define QTD_REPETICOES 3

void executar_busca(VetorProdutos *v, int id_alvo, const char *posicao)
{
    double soma_tempos = 0;

    printf("\n--- Testando: %s (ID: %d) ---\n", posicao, id_alvo);

    // quantidade de repetições
    for (int r = 1; r <= QTD_REPETICOES; r++)
    {

        // inicio da medição do tempo
        double inicio = pegar_tempo();

        // quantidade de buscas
        for (int i = 0; i < QTD_BUSCAS; i++)
        {
            busca_sequencial(v, id_alvo);
        }

        // fim tempo
        double fim = pegar_tempo();

        // tempo em ms
        double tempo_total_ms = calcular_diferenca_ms(inicio, fim);
        soma_tempos += tempo_total_ms;

        printf("  Repeticao %d: %.4f ms (Total para %d buscas)\n", r, tempo_total_ms, QTD_BUSCAS);
    }

    // media por busca
    double media_total = soma_tempos / QTD_REPETICOES;
    double media_por_busca = media_total / QTD_BUSCAS;

    printf("  >> Resultado Final: Media de %.6f ms por busca.\n", media_por_busca);
}

int main()
{
    VetorProdutos vetor;
    inicializador_vetor(&vetor);

    printf("Carregando CSV...\n");
    if (!ler_csv("data/dataset3.csv", &vetor))
    {
        return 1;
    }
    printf("Carregamento do CSV Concluido!\n");

    int id_inicio = vetor.dados[0].id;
    int id_meio = vetor.dados[vetor.tamanho / 2].id;
    int id_fim = vetor.dados[vetor.tamanho - 1].id;
    int id_inexistente = -9999;

    int alvos[] = {id_inicio, id_meio, id_fim};
    const char *labels[] = {"INICIO", "MEIO", "FIM"};

    // verificar se esta encontrando nos lugares certos
    printf("\n=== VALIDACAO DE BUSCA ===\n");
    for (int i = 0; i < 4; i++) {
        int indice = busca_sequencial(&vetor, alvos[i]);
        
        if (indice != -1) {
            // se encontrou (inicio, meio, fim)
            Produto p = vetor.dados[indice];
            printf("[%s] ID %d encontrado no indice %d: %s | R$ %.2f\n", 
                    labels[i], alvos[i], indice, p.nome, p.valor);
        } else {
            // inexistente
            printf("[%s] ID %d: Nao encontrado (Comportamento esperado)\n", 
                    labels[i], alvos[i]);
        }
    }
    printf("====================================================\n");

    // buscas sem imprimir na tela
    executar_busca(&vetor, id_inicio, "INICIO");
    executar_busca(&vetor, id_meio, "MEIO");
    executar_busca(&vetor, id_fim, "FINAL");
    executar_busca(&vetor, id_inexistente, "INEXISTENTE");

    liberar_vetor(&vetor);
    printf("\nTodas as buscas finalizadas!\n");

    return 0;
}