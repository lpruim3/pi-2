# Sistema de Análise de Desempenho — Busca Sequencial

Projeto desenvolvido em grupo para a **disciplina de Projeto Integrador do Centro Universitário IESB**. O objetivo do projeto foi realizar a reengenharia e evolução arquitetural de um sistema de recuperação de dados em memória, saindo de um modelo linear (Fase I) para uma estrutura indexada de alta performance via Tabela Hash (Fase II).

O sistema processa um conjunto de dados real contendo **300.006 registros** de produtos e utiliza um protocolo experimental rigoroso para avaliar o tempo de resposta em cenários críticos.

---

## Objetivo Geral

### FASE 1

Desenvolver uma base experimental para análise de desempenho de algoritmos de busca por meio da:

* Leitura e estruturação de dados reais;
* Implementação da busca sequencial;
* Medição do tempo de execução;
* Construção de relatório técnico inicial com análise dos resultados.

### FASE 2

Desenvolver uma estrutura de busca otimizada para análise de desempenho de algoritmos, por meio da:

* Leitura e estruturação de dados reais;
* Implementação da Tabela Hash com tratamento de colisões;
* Medição controlada do tempo de execução;
* Análise comparativa entre busca sequencial (Fase I) e Tabela Hash;
* Produção de artigo científico com análise experimental completa.

---

## Dataset

O projeto utiliza um arquivo `.csv` contendo registros de produtos com a seguinte estrutura lógica:

```c id="3r64fa"
typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;
```

O volume de dados atribuído ao grupo é de 300.006 registros.

---

## Requisitos Implementados

O sistema atende aos seguintes requisitos propostos:

### FASE 1

* Leitura do arquivo CSV com validação de erros;
* Armazenamento dos registros em vetor dinâmico;
* Implementação da busca sequencial por `id`;
* Medição de tempo de execução;
* Execução de múltiplos testes com cálculo de média.

### FASE 2

* Implementação da Tabela Hash com encadeamento;
* Utilização da função hash definida para o grupo;
* Tamanho da tabela hash deverá ser igual ao volume de dados do dataset testado;
* Implementação de mecanismo para contabilizar colisões;
* Execução automatizada de múltiplos testes para cálculo do tempo médio de busca.

---

## Estrutura do Projeto

```bash id="vntiyx"
├── src/                # Código-fonte (.c)
├── src/include/        # Arquivos de cabeçalho (.h)
├── data/               # Dataset CSV
│   └── dataset3.csv
├── docs/               # Relatório técnico
├── .gitignore
└── README.md
```

---

## Como Executar

### Compilação

```bash id="3vk1y4"
gcc src/*.c -o experimento
```

### Execução

```bash id="ezpwk2"
./experimento.exe
```

---

## Protocolo Experimental

Os testes seguiram o protocolo exigido:

### FASE 1
1. Vetor completamente carregado antes das medições;
2. Mínimo de **1.000 buscas consecutivas** por cenário;
3. Testes realizados com:

   * Elemento no início;
   * Elemento no meio;
   * Elemento no final;
   * Elemento inexistente;
4. Tempo total dividido pelo número de execuções;
5. Repetição de cada teste **3 vezes**, utilizando média final.

### FASE 2

1. A Tabela Hash deve estar completamente carregada antes do início das medições.
2. Devem ser realizadas no mínimo 1.000 buscas consecutivas para cálculo do tempo médio.
3. As buscas devem contemplar:
    * Elementos existentes (no início, no meio e no final do dataset);
    * Elementos inexistentes.
4. O tempo total deve ser medido e dividido pelo número de execuções para obtenção do tempo médio.
5. Os testes devem ser repetidos ao menos 3 vezes, apresentando-se a média final.
6. Deve ser contabilizado o número total de colisões.

---

## Quantidade de Registros

**300.006 registros** carregados em memória dinâmica.

---

## Resultados Oficiais

| Cenário de Busca | ID Alvo | Busca Sequencial (ms) | Tabela Hash (ms) | Fator de Aceleração (Speedup) |
| :--- | :---: | :---: | :---: | :---: |
| **INÍCIO** | 43614 | 0,000004 | 0,000005 | ~1,00x (Equivalente) |
| **MEIO** | 3341 | 1,572596 | 0,000007 | **224.656x mais rápida** |
| **FINAL** | 189553 | 3,551487 | 0,000005 | **710.297x mais rápida** |
| **INEXISTENTE** | -9999 | 3,412290 | 0,000006 | **568.715x mais rápida** |
---

## Análise Interpretativa dos Resultados

A comparação entre os testes práticos e os modelos teóricos da Ciência da Computação valida com precisão cirúrgica o impacto da evolução arquitetural feita da Fase I para a Fase II.

###  1. O Gargalo Linear da Busca Sequencial O(n)
Os dados coletados na Fase I comprovam como a busca linear é extremamente dependente da **posição física** do registro na memória:
* **Cenário INÍCIO (0,000004 ms):** Representa o melhor caso teórico. O laço `for` encontrou o produto na primeira tentativa e foi interrompido instantaneamente.
* **Cenário MEIO (1,572596 ms):** O caso médio. O processador precisou inspecionar sequencialmente cerca de 150.000 registros, escalando o tempo de resposta proporcionalmente.
* **Cenários FINAL e INEXISTENTE (~3,50 ms):** O pior caso absoluto. O algoritmo é obrigado a realizar todas as **300.006 iterações** em memória antes de dar uma resposta, provando que a estrutura linear não possui escalabilidade.

###  2. A Imunidade Locacional da Tabela Hash O(1)
A Fase II erradicou completamente o problema de localização. Os tempos médios mantiveram-se estáveis na casa dos microssegundos (**entre 0,000005 ms e 0,000007 ms**) em todos os cenários. 

Não importa se o ID está no início, no fim ou se nem existe: o custo computacional é fixo. Isso ocorre porque o tempo para calcular a função matemática de hash e acessar o índice direto (*bucket*) na memória RAM é sempre o mesmo.

###  3. Eficiência da Dispersão (Apenas 1 Colisão)
O dimensionamento perfeito da tabela ($m = 300.006$) garantiu o fator de carga ideal de projeto α  = 1,0 

O método da divisão obteve uma dispersão quase perfeita, gerando **apenas 1 colisão em todo o universo de 300.006 produtos**. Isso evitou que o sistema precisasse varrer listas encadeadas longas dentro dos buckets, mantendo a estrutura operando em tempo constante puro. Se houvesse muitas colisões, o desempenho da tabela se degradaria de volta para o modelo linear O(n).

###  4. Impacto Prático (Speedup)
O cálculo do fator de aceleração traduz o sucesso da reengenharia:
* Para buscar o elemento do **meio**, a Tabela Hash foi **224.656 vezes mais rápida**.
* No pior cenário (**final**), a aceleração atingiu a marca extraordinária de **710.297 vezes mais rapidez**.

Em sistemas reais, essa otimização transforma um software que travaria a CPU sob intensa carga em uma aplicação de altíssima performance com tempo de resposta imperceptível para o usuário.

##  Conclusão

A evolução arquitetural promovida entre a Fase I e a Fase II deste projeto foi concluída com sucesso absoluto. A substituição do modelo de vetor dinâmico por uma infraestrutura baseada em Tabela Hash com encadeamento externo provou ser a estratégia definitiva para eliminar os problemas de latência e garantir a escalabilidade do sistema frente a grandes volumes de dados.

Os testes práticos ratificaram de forma incontestável os conceitos teóricos da Ciência da Computação:
1. **A busca linear O(n)** mostrou-se inviável para sistemas de larga escala, pois o tempo de resposta cresce junto com a base de dados, gerando gargalos severos no pior cenário.
2. **A indexação por hash O(1)** estabilizou o sistema no patamar ideal de tempo constante, oferecendo respostas na casa dos microssegundos independentemente do cenário de busca.
3. **A eficiência matemática** da função por método da divisão foi comprovada pelo número quase nulo de colisões (apenas 1 em 300.006 registros), operando com o fator de carga perfeito α  = 1,0.

Em suma, esta base experimental não apenas consolidou na prática os conceitos avançados de Estruturas de Dados na linguagem C, mas também simulou os desafios reais de otimização de software enfrentados no mercado de tecnologia, comprovando que a engenharia de algoritmos correta é a chave para a construção de aplicações de alta performance.

---

## Integrantes do Grupo

* Ana Luiza Gomes de Lima - Matrícula: 2512130059
* Lucas Pessoa Ranieri - Matrícula: 2512130092
* Pedro Augusto Machado Cardoso - Matrícula: 2612130005


