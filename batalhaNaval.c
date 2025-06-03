#include <stdio.h> 

// Definições de constantes para facilitar a manutenção e legibilidade do código
#define TAMANHO_TABULEIRO 10 // Define o tamanho do tabuleiro (10x10)
#define TAMANHO_NAVIO 3      // Define o tamanho fixo dos navios (3 posições)
#define AGUA 0               // Representa uma posição no tabuleiro que é água
#define NAVIO 3              // Representa uma posição no tabuleiro ocupada por um navio

/**
 * @brief Inicializa todas as posições do tabuleiro com o valor de água.
 *
 * @param tabuleiro A matriz bidimensional que representa o tabuleiro do jogo.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Loop aninhado para percorrer todas as linhas do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Loop aninhado para percorrer todas as colunas da linha atual
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // Define o valor da posição atual como água
        }
    }
}

/**
 * @brief Exibe o estado atual do tabuleiro no console.
 * Mostra os números das linhas e colunas para facilitar a visualização.
 *
 * @param tabuleiro A matriz bidimensional que representa o tabuleiro do jogo.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("  "); // Espaço inicial para alinhar os números das colunas
    // Imprime os números das colunas (0 a 9)
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j); // Imprime o número da coluna seguido de um espaço
    }
    printf("\n"); // Nova linha após os números das colunas

    // Loop aninhado para percorrer e exibir cada elemento do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Imprime o número da linha atual
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]); // Imprime o valor da posição (0 para água, 3 para navio)
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro
    }
}

/**
 * @brief Tenta posicionar um navio no tabuleiro.
 * Realiza validações para garantir que o navio esteja dentro dos limites e não se sobreponha a outro navio.
 *
 * @param tabuleiro A matriz bidimensional que representa o tabuleiro.
 * @param linhaInicial A coordenada da linha onde o navio começará.
 * @param colunaInicial A coordenada da coluna onde o navio começará.
 * @param orientacao A orientação do navio ('H' ou 'h' para horizontal, 'V' ou 'v' para vertical).
 * @return 1 se o navio foi posicionado com sucesso, 0 caso contrário.
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, char orientacao) {
    // 1. Validação de limites para as coordenadas iniciais
    if (linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO ||
        colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
        printf("Erro: Coordenadas iniciais do navio (%d, %d) fora dos limites do tabuleiro.\n", linhaInicial, colunaInicial);
        return 0; // Retorna 0 indicando falha
    }

    // 2. Pré-verificação para sobreposição e limites para o tamanho total do navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 'H' || orientacao == 'h') { // Se a orientação for Horizontal
            // Verifica se o navio horizontal excede o limite da coluna
            if (colunaInicial + i >= TAMANHO_TABULEIRO) {
                printf("Erro: Navio horizontal excede os limites do tabuleiro na coluna %d.\n", colunaInicial + i);
                return 0;
            }
            // Verifica se a posição já está ocupada por outro navio
            if (tabuleiro[linhaInicial][colunaInicial + i] == NAVIO) {
                printf("Erro: Sobreposição de navios na posição (%d, %d).\n", linhaInicial, colunaInicial + i);
                return 0;
            }
        } else if (orientacao == 'V' || orientacao == 'v') { // Se a orientação for Vertical
            // Verifica se o navio vertical excede o limite da linha
            if (linhaInicial + i >= TAMANHO_TABULEIRO) {
                printf("Erro: Navio vertical excede os limites do tabuleiro na linha %d.\n", linhaInicial + i);
                return 0;
            }
            // Verifica se a posição já está ocupada por outro navio
            if (tabuleiro[linhaInicial + i][colunaInicial] == NAVIO) {
                printf("Erro: Sobreposição de navios na posição (%d, %d).\n", linhaInicial + i, colunaInicial);
                return 0;
            }
        } else { // Orientação inválida
            printf("Erro: Orientação inválida '%c'. Use 'H' para horizontal ou 'V' para vertical.\n", orientacao);
            return 0;
        }
    }

    // 3. Posicionamento do navio no tabuleiro (se todas as validações passaram)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 'H' || orientacao == 'h') { // Horizontal
            tabuleiro[linhaInicial][colunaInicial + i] = NAVIO; // Marca a posição como navio
        } else { // Vertical
            tabuleiro[linhaInicial + i][colunaInicial] = NAVIO; // Marca a posição como navio
        }
    }
    return 1; // Retorna 1 indicando sucesso
}

/**
 * @brief Função principal do programa.
 * Inicializa o tabuleiro, tenta posicionar dois navios e exibe o tabuleiro final.
 * Contém exemplos de testes para sobreposição e limites (comentados).
 */
int main() {
    // Declaração da matriz que representa o tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Chama a função para inicializar todas as posições do tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);

    printf("--- Posicionamento dos Navios ---\n");

    // --- Posicionamento do Navio 1: Horizontal ---
    // Define as coordenadas iniciais e a orientação para o primeiro navio
    int linhaNavio1 = 0;
    int colunaNavio1 = 0;
    char orientacaoNavio1 = 'H'; // 'H' para horizontal

    printf("Tentando posicionar Navio 1 (Horizontal) em (%d, %d)...\n", linhaNavio1, colunaNavio1);
    // Tenta posicionar o Navio 1 e verifica o retorno da função
    if (!posicionarNavio(tabuleiro, linhaNavio1, colunaNavio1, orientacaoNavio1)) {
        printf("Falha ao posicionar Navio 1. Verifique as coordenadas ou sobreposição.\n");
    } else {
        printf("Navio 1 posicionado com sucesso.\n");
    }

    // --- Posicionamento do Navio 2: Vertical ---
    // Define as coordenadas iniciais e a orientação para o segundo navio
    int linhaNavio2 = 2;
    int colunaNavio2 = 4;
    char orientacaoNavio2 = 'V'; // 'V' para vertical

    printf("\nTentando posicionar Navio 2 (Vertical) em (%d, %d)...\n", linhaNavio2, colunaNavio2);
    // Tenta posicionar o Navio 2 e verifica o retorno da função
    if (!posicionarNavio(tabuleiro, linhaNavio2, colunaNavio2, orientacaoNavio2)) {
        printf("Falha ao posicionar Navio 2. Verifique as coordenadas ou sobreposição.\n");
    } else {
        printf("Navio 2 posicionado com sucesso.\n");
    }

    // --- Exemplos de Teste (descomente para verificar o comportamento de erro) ---

    // Exemplo de sobreposição: Tenta posicionar um navio que se sobrepõe ao Navio 1
    // int linhaNavio3 = 0;
    // int colunaNavio3 = 1;
    // char orientacaoNavio3 = 'H';
    // printf("\nTentando posicionar Navio 3 (Horizontal) em (%d, %d) para testar sobreposição...\n", linhaNavio3, colunaNavio3);
    // if (!posicionarNavio(tabuleiro, linhaNavio3, colunaNavio3, orientacaoNavio3)) {
    //     printf("Falha ao posicionar Navio 3. (Era esperado para teste de sobreposição)\n");
    // } else {
    //     printf("Navio 3 posicionado com sucesso (NÃO deveria ter sobreposto).\n");
    // }

    // Exemplo de navio fora dos limites: Tenta posicionar um navio que excede o tabuleiro
    // int linhaNavio4 = 9; // Linha muito próxima do limite
    // int colunaNavio4 = 9; // Coluna muito próxima do limite
    // char orientacaoNavio4 = 'H'; // Navio horizontal de tamanho 3 a partir de (9,9)
    // printf("\nTentando posicionar Navio 4 (Horizontal) em (%d, %d) para testar fora dos limites...\n", linhaNavio4, colunaNavio4);
    // if (!posicionarNavio(tabuleiro, linhaNavio4, colunaNavio4, orientacaoNavio4)) {
    //     printf("Falha ao posicionar Navio 4. (Era esperado para teste de fora dos limites)\n");
    // } else {
    //     printf("Navio 4 posicionado com sucesso (NÃO deveria ter ficado fora dos limites).\n");
    // }


    printf("\n--- Tabuleiro Final ---\n");
    // Exibe o tabuleiro com os navios que foram posicionados com sucesso
    exibirTabuleiro(tabuleiro);

    return 0; // Indica que o programa foi executado com sucesso
}
