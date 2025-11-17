#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // (Necessário para o tipo 'bool')

// --- Constantes Globais ---
#define MAX_ITENS 10    // Capacidade da mochila
#define TAM_NOME 50
#define TAM_TIPO 30

// --- Estrutura de Dados ---
// (Struct atualizada com 'prioridade')
struct Item {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade; // (Valores de 1 a 5)
};

// Enum para critérios de ordenação
enum CriterioOrdenacao {
    NOME,
    TIPO,
    PRIORIDADE
};

// --- Protótipos das Funções ---
void limparTela();
void pausar();
void limparBufferEntrada();
void exibirMenu(int numItens, bool ordenadaPorNome);
void inserirItem(struct Item mochila[], int *numItens, bool *ordenadaPorNome);
void removerItem(struct Item mochila[], int *numItens, bool *ordenadaPorNome);
void listarItens(struct Item mochila[], int numItens);
void menuDeOrdenacao(struct Item mochila[], int numItens, int *comparacoes, bool *ordenadaPorNome);
void insertionSort(struct Item mochila[], int numItens, enum CriterioOrdenacao criterio, int *comparacoes);
void buscarItemPorNome(struct Item mochila[], int numItens, bool ordenadaPorNome);

// --- Função Principal (main) ---
int main() {
    struct Item mochila[MAX_ITENS];
    int numItens = 0;
    int opcao;
    
    // Variáveis de controle do Nível Mestre
    int comparacoes = 0; // (Para análise de desempenho)
    bool ordenadaPorNome = false; // (Controle para busca binária)

    // Laço principal do menu interativo
    do {
        limparTela();
        exibirMenu(numItens, ordenadaPorNome); // (Menu agora exibe status)
        
        printf("Escolha sua acao: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1; 
        }
        limparBufferEntrada();

        // Switch atualizado para Nível Mestre
        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens, &ordenadaPorNome);
                break;
            case 2:
                removerItem(mochila, &numItens, &ordenadaPorNome);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                menuDeOrdenacao(mochila, numItens, &comparacoes, &ordenadaPorNome); //
                break;
            case 5:
                buscarItemPorNome(mochila, numItens, ordenadaPorNome); //
                break;
            case 0:
                printf("\nSaindo da ilha... Boa sorte, sobrevivente!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
        
        if (opcao != 0) {
            pausar();
        }

    } while (opcao != 0);

    return 0;
}

// --- Funções de Interface ---

void limparTela() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Menu atualizado para Nível Mestre
void exibirMenu(int numItens, bool ordenadaPorNome) {
    printf("===================================\n");
    printf("  MOCHILA DE SOBREVIVENCIA (FF)\n");
    printf("===================================\n");
    printf("Itens na Mochila: %d / %d\n", numItens, MAX_ITENS);
    // (Exibe o status da ordenação)
    printf("Status da Mochila: %s\n", ordenadaPorNome ? "Ordenada por NOME" : "Nao ordenada");
    printf("-----------------------------------\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens por criterio\n"); //
    printf("5. Buscar item por nome (Binaria)\n"); //
    printf("0. Sair\n");
    printf("-----------------------------------\n");
}

// --- Funções de Gerenciamento de Itens ---

// (Atualizada para prioridade e status de ordenação)
void inserirItem(struct Item mochila[], int *numItens, bool *ordenadaPorNome) {
    if (*numItens >= MAX_ITENS) {
        printf("\nERRO: A mochila esta cheia!\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    
    struct Item novoItem;

    printf("Nome do item: ");
    fgets(novoItem.nome, TAM_NOME, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Tipo do item (ex: Arma, Municao, Medkit): ");
    fgets(novoItem.tipo, TAM_TIPO, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    // (Solicita prioridade)
    printf("Prioridade (1 a 5): "); 
    scanf("%d", &novoItem.prioridade);
    limparBufferEntrada();
    
    // Validação da prioridade
    if (novoItem.prioridade < 1) novoItem.prioridade = 1;
    if (novoItem.prioridade > 5) novoItem.prioridade = 5;

    mochila[*numItens] = novoItem;
    (*numItens)++;
    
    // (Qualquer inserção desordena a mochila)
    *ordenadaPorNome = false; 

    printf("\nItem '%s' adicionado com sucesso!\n", novoItem.nome);
}

// (Atualizada para status de ordenação)
void removerItem(struct Item mochila[], int *numItens, bool *ordenadaPorNome) {
    char nomeBusca[TAM_NOME];
    int i, j;
    int encontrado = 0; 

    if (*numItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            for (j = i; j < (*numItens - 1); j++) {
                mochila[j] = mochila[j + 1];
            }
            
            (*numItens)--;
            *ordenadaPorNome = false; // (Remoção também desordena)
            printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
            break; 
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

// (Atualizada para listar prioridade)
void listarItens(struct Item mochila[], int numItens) {
    printf("\n--- Itens na Mochila (%d) ---\n", numItens);

    if (numItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    printf("--------------------------------------------------------------------------------\n");
    printf("| %-30s | %-20s | %-10s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("| %-30s | %-20s | %-10d | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade,
               mochila[i].prioridade); //
    }
    printf("--------------------------------------------------------------------------------\n");
}

// --- Funções de Ordenação e Busca (Nível Mestre) ---

// (Menu para escolher o critério de ordenação)
void menuDeOrdenacao(struct Item mochila[], int numItens, int *comparacoes, bool *ordenadaPorNome) {
    int criterio;
    enum CriterioOrdenacao critEnum;
    
    if (numItens == 0) {
        printf("\nA mochila esta vazia. Nao ha o que ordenar.\n");
        return;
    }

    printf("\n--- Ordenar Mochila ---\n");
    printf("Escolha o criterio de ordenacao:\n");
    printf("1. Por Nome (A-Z)\n");
    printf("2. Por Tipo (A-Z)\n");
    printf("3. Por Prioridade (5-1)\n");
    printf("Escolha: ");
    
    scanf("%d", &criterio);
    limparBufferEntrada();
    
    *comparacoes = 0; // (Reseta contador de desempenho)
    
    switch (criterio) {
        case 1:
            critEnum = NOME;
            insertionSort(mochila, numItens, critEnum, comparacoes);
            *ordenadaPorNome = true; // (Marca como ordenada por nome)
            printf("\nMochila ordenada por NOME. ");
            break;
        case 2:
            critEnum = TIPO;
            insertionSort(mochila, numItens, critEnum, comparacoes);
            *ordenadaPorNome = false; // Ordenou por tipo, não por nome
            printf("\nMochila ordenada por TIPO. ");
            break;
        case 3:
            critEnum = PRIORIDADE;
            insertionSort(mochila, numItens, critEnum, comparacoes);
            *ordenadaPorNome = false; // Ordenou por prioridade, não por nome
            printf("\nMochila ordenada por PRIORIDADE. ");
            break;
        default:
            printf("\nCriterio invalido!\n");
            return;
    }
    
    // (Exibe análise de desempenho)
    printf("Total de comparacoes realizadas: %d\n", *comparacoes);
}

// (Algoritmo Insertion Sort)
void insertionSort(struct Item mochila[], int numItens, enum CriterioOrdenacao criterio, int *comparacoes) {
    int i, j;
    struct Item chave;

    for (i = 1; i < numItens; i++) {
        chave = mochila[i];
        j = i - 1;
        
        bool deveTrocar = false;
        
        // Loop 'while' decide se "empurra" o item
        while (j >= 0) {
            (*comparacoes)++; // (Conta cada comparação)
            
            // Lógica de comparação baseada no critério
            switch (criterio) {
                case NOME:
                    deveTrocar = (strcmp(mochila[j].nome, chave.nome) > 0);
                    break;
                case TIPO:
                    deveTrocar = (strcmp(mochila[j].tipo, chave.tipo) > 0);
                    break;
                case PRIORIDADE:
                    // (Prioridade é decrescente, de 5 para 1)
                    deveTrocar = (mochila[j].prioridade < chave.prioridade); 
                    break;
            }
            
            if (deveTrocar) {
                mochila[j + 1] = mochila[j];
                j = j - 1;
            } else {
                break; // Posição correta encontrada
            }
        }
        mochila[j + 1] = chave;
    }
}

// (Busca Binária por Nome)
void buscarItemPorNome(struct Item mochila[], int numItens, bool ordenadaPorNome) {
    char nomeBusca[TAM_NOME];
    
    printf("\n--- Buscar Item por Nome (Busca Binaria) ---\n");
    
    // (Verifica o pré-requisito)
    if (!ordenadaPorNome) {
        printf("ERRO: A mochila nao esta ordenada por nome.\n");
        printf("Por favor, use a Opcao 4 para ordenar por nome antes de buscar.\n");
        return;
    }
    
    if (numItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    printf("Digite o nome do item a ser buscado: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Lógica da Busca Binária
    int esquerda = 0;
    int direita = numItens - 1;
    int encontrado = 0;
    int comparacoesBusca = 0;

    while (esquerda <= direita) {
        comparacoesBusca++; // Conta comparações da busca
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) { // Item encontrado
            printf("\n--- Item Encontrado (em %d comparacoes) ---\n", comparacoesBusca);
            printf("Nome:       %s\n", mochila[meio].nome);
            printf("Tipo:       %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            encontrado = 1;
            break;
        } else if (cmp < 0) { // O item buscado está à direita
            esquerda = meio + 1;
        } else { // O item buscado está à esquerda
            direita = meio - 1;
        }
    }

    if (!encontrado) {
        printf("\nERRO: Item '%s' nao foi encontrado (em %d comparacoes).\n", nomeBusca, comparacoesBusca);
    }
}