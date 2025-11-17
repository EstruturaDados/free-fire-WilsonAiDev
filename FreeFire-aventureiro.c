#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constantes Globais ---
#define MAX_ITENS 10    // Capacidade da mochila
#define TAM_NOME 50
#define TAM_TIPO 30

// --- Estrutura de Dados ---
// Struct para representar um item
struct Item {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
};

// --- Protótipos das Funções ---
void limparTela();
void pausar();
void limparBufferEntrada();
void exibirMenu();
void inserirItem(struct Item mochila[], int *numItens);
void removerItem(struct Item mochila[], int *numItens);
void listarItens(struct Item mochila[], int numItens);
void buscarItemPorNome(struct Item mochila[], int numItens); // (Nova função)

// --- Função Principal (main) ---
int main() {
    // Vetor estático para a mochila
    struct Item mochila[MAX_ITENS];
    int numItens = 0; // Contador de quantos itens estão na mochila
    int opcao;

    // Laço principal do menu interativo
    do {
        limparTela();
        exibirMenu(numItens);
        
        // Lê a opção do usuário
        printf("Escolha sua acao: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1; // Força "Opção inválida" se não for um número
        }
        limparBufferEntrada();

        // Processa a escolha do usuário
        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItemPorNome(mochila, numItens); // (Nova opção)
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

// --- Implementação das Funções ---

// Simula a limpeza da tela
void limparTela() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

// Pausa a execução até o usuário pressionar Enter
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

// Limpa o buffer de entrada (stdin)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Exibe o menu principal de ações
void exibirMenu(int numItens) {
    printf("===================================\n");
    printf("  MOCHILA DE SOBREVIVENCIA (FF)\n");
    printf("===================================\n");
    printf("Itens na Mochila: %d / %d\n", numItens, MAX_ITENS);
    printf("-----------------------------------\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Buscar item por nome\n"); // (Nova opção de menu)
    printf("0. Sair\n");
    printf("-----------------------------------\n");
}

// Adiciona um item à mochila
void inserirItem(struct Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("\nERRO: A mochila esta cheia! Nao e possivel adicionar mais itens.\n");
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
    limparBufferEntrada();

    mochila[*numItens] = novoItem;
    (*numItens)++;

    printf("\nItem '%s' adicionado com sucesso!\n", novoItem.nome);
}

// Remove um item da mochila pelo nome
void removerItem(struct Item mochila[], int *numItens) {
    char nomeBusca[TAM_NOME];
    int i, j;
    int encontrado = 0; // Flag

    if (*numItens == 0) {
        printf("\nA mochila esta vazia. Nao ha o que remover.\n");
        return;
    }

    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) { // (Comparação de strings)
            encontrado = 1;
            
            for (j = i; j < (*numItens - 1); j++) {
                mochila[j] = mochila[j + 1];
            }
            
            (*numItens)--;
            printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

// Lista todos os itens cadastrados
void listarItens(struct Item mochila[], int numItens) {
    printf("\n--- Itens na Mochila (%d) ---\n", numItens);

    if (numItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    printf("------------------------------------------------------------------\n");
    printf("| %-30s | %-20s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("| %-30s | %-20s | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("------------------------------------------------------------------\n");
}

// --- NOVA FUNÇÃO: NÍVEL AVENTUREIRO ---
// Busca um item pelo nome e exibe seus detalhes
void buscarItemPorNome(struct Item mochila[], int numItens) {
    char nomeBusca[TAM_NOME];
    int i;
    int encontrado = 0; // Flag para controle

    printf("\n--- Buscar Item por Nome ---\n");
    
    if (numItens == 0) {
        printf("A mochila esta vazia. Nao ha o que buscar.\n");
        return;
    }

    printf("Digite o nome do item a ser buscado: "); //
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Implementação da busca sequencial
    for (i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) { //
            printf("\n--- Item Encontrado ---\n");
            printf("Nome:       %s\n", mochila[i].nome);
            printf("Tipo:       %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1; //
            break; // Para o loop assim que encontrar
        }
    }

    // Se o loop terminar e a flag for 0, o item não foi encontrado
    if (!encontrado) {
        printf("\nERRO: Item '%s' nao foi encontrado na mochila.\n", nomeBusca); //
    }
}