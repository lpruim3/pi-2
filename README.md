# Sistema de Análise de Desempenho — Busca Sequencial

Projeto desenvolvido em grupo para a **Fase I da disciplina de Estrutura de Dados**, com foco na construção de uma base experimental para análise de desempenho de algoritmos de busca.

Esta etapa estabelece um **baseline de comparação**, que será utilizado futuramente na implementação da **Tabela Hash (Fase II)**.

---

## Objetivo Geral

Desenvolver uma base experimental para análise de desempenho de algoritmos de busca por meio da:

* Leitura e estruturação de dados reais;
* Implementação da busca sequencial;
* Medição do tempo de execução;
* Construção de relatório técnico inicial com análise dos resultados.

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

O volume de dados pode variar conforme a versão do dataset disponibilizada.

---

## Requisitos Implementados

O sistema atende aos seguintes requisitos propostos:

* Leitura do arquivo CSV com validação de erros;
* Armazenamento dos registros em vetor dinâmico;
* Implementação da busca sequencial por `id`;
* Medição de tempo de execução;
* Execução de múltiplos testes com cálculo de média.

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

1. Vetor completamente carregado antes das medições;
2. Mínimo de **1.000 buscas consecutivas** por cenário;
3. Testes realizados com:

   * Elemento no início;
   * Elemento no meio;
   * Elemento no final;
   * Elemento inexistente;
4. Tempo total dividido pelo número de execuções;
5. Repetição de cada teste **3 vezes**, utilizando média final.

---

## Quantidade de Registros

**300.007 registros** carregados em memória dinâmica.

---

## Resultados Oficiais

| Cenário     | Repetição 1 (ms) | Repetição 2 (ms) | Repetição 3 (ms) | Tempo Médio por Busca (ms) |
| ----------- | ---------------: | ---------------: | ---------------: | -------------------------: |
| Início      |           0.0000 |           0.0000 |           0.0000 |                   0.000000 |
| Meio        |        1583.0000 |        1625.0000 |        1372.0000 |                   1.526667 |
| Final       |        3122.0000 |        3160.0000 |        3242.0000 |                   3.174667 |
| Inexistente |        2302.0000 |        2325.0000 |        2273.0000 |                   2.300000 |

---

## Análise Interpretativa

### Comportamento Observado

Os resultados demonstram que o tempo de busca aumenta conforme a posição do elemento no vetor.

* Elementos no início são encontrados imediatamente;
* Elementos no meio exigem percorrer parte do vetor;
* Elementos no final ou inexistentes exigem percorrer quase todos os registros.

---

### Relação entre Tamanho do Vetor e Tempo de Busca

A busca sequencial possui comportamento linear, ou seja:

```text id="m1z1ra"
O(n)
```

Quanto maior a quantidade de registros, maior tende a ser o tempo necessário para localizar um item.

---

### Limitações da Busca Sequencial

Apesar de simples implementação, a busca sequencial apresenta limitações em bases extensas:

* Crescimento linear do tempo de resposta;
* Baixa escalabilidade;
* Ineficiência para consultas frequentes;

---

## Conclusão

Os resultados obtidos confirmam, na prática, o comportamento teórico da busca sequencial, evidenciando que seu tempo de execução cresce conforme a posição do elemento procurado e o tamanho do conjunto de dados.

Embora seja um algoritmo simples e de fácil implementação, seu desempenho torna-se limitado em bases extensas. Dessa forma, esta etapa fornece uma referência inicial importante para comparações futuras com estruturas mais eficientes.

---

## Integrantes do Grupo

* Ana Luiza Gomes de Lima - Matrícula: 2512130059
* Lucas Pessoa Ranieri - Matrícula: 2512130092
* Pedro Augusto Machado Cardoso - Matrícula: 2612130005

