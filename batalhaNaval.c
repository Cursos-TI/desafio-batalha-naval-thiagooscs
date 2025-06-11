#include <stdio.h> 
#include <stdbool.h>

// Define as dimensões do tabuleiro.
#define LINHAS 10
#define COLUNAS 10
#define TAMANHO_NAVIO 3 // Define o tamanho fixo dos navios.

// Função para inicializar o tabuleiro com água (0).
void inicializarTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++) { // Percorre cada linha do tabuleiro.
        for (int j = 0; j < COLUNAS; j++) { // Percorre cada coluna da linha atual.
            tabuleiro[i][j] = 0; // Define a posição como água.
        }
    }
}

// Função para verificar se uma posição está dentro dos limites do tabuleiro.
bool estaDentroDosLimites(int linha, int coluna) {
    return (linha >= 0 && linha < LINHAS && coluna >= 0 && coluna < COLUNAS);
}

// Função para verificar se o posicionamento de um navio é válido (não sobrepõe e está dentro dos limites).
// Retorna true se válido, false caso contrário.
bool podePosicionarNavio(int tabuleiro[LINHAS][COLUNAS], int inicioLinha, int inicioColuna, char orientacao) {
    // Verifica navio horizontal
    if (orientacao == 'H' || orientacao == 'h') {
        for (int j = 0; j < TAMANHO_NAVIO; j++) {
            if (!estaDentroDosLimites(inicioLinha, inicioColuna + j) || tabuleiro[inicioLinha][inicioColuna + j] == 3) {
                return false; // Fora dos limites ou sobrepõe um navio existente.
            }
        }
    }
    // Verifica navio vertical
    else if (orientacao == 'V' || orientacao == 'v') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (!estaDentroDosLimites(inicioLinha + i, inicioColuna) || tabuleiro[inicioLinha + i][inicioColuna] == 3) {
                return false; // Fora dos limites ou sobrepõe um navio existente.
            }
        }
    }
    // Verifica navio diagonal (aumentando linha e coluna)
    else if (orientacao == 'D' || orientacao == 'd') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (!estaDentroDosLimites(inicioLinha + i, inicioColuna + i) || tabuleiro[inicioLinha + i][inicioColuna + i] == 3) {
                return false; // Fora dos limites ou sobrepõe um navio existente.
            }
        }
    }
    // Verifica navio diagonal (aumentando linha, diminuindo coluna)
    else if (orientacao == 'A' || orientacao == 'a') { // 'A' de anti-diagonal ou decrescente
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (!estaDentroDosLimites(inicioLinha + i, inicioColuna - i) || tabuleiro[inicioLinha + i][inicioColuna - i] == 3) {
                return false; // Fora dos limites ou sobrepõe um navio existente.
            }
        }
    }
    return true; // Posição válida.
}

// Função para posicionar um navio no tabuleiro.
// Retorna true se o navio foi posicionado com sucesso, false caso contrário.
bool posicionarNavio(int tabuleiro[LINHAS][COLUNAS], int inicioLinha, int inicioColuna, char orientacao) {
    if (!podePosicionarNavio(tabuleiro, inicioLinha, inicioColuna, orientacao)) {
        return false; // Não é possível posicionar o navio.
    }

    // Posiciona o navio horizontalmente.
    if (orientacao == 'H' || orientacao == 'h') {
        for (int j = 0; j < TAMANHO_NAVIO; j++) {
            tabuleiro[inicioLinha][inicioColuna + j] = 3;
        }
    }
    // Posiciona o navio verticalmente.
    else if (orientacao == 'V' || orientacao == 'v') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[inicioLinha + i][inicioColuna] = 3;
        }
    }
    // Posiciona o navio diagonalmente (linha e coluna aumentam).
    else if (orientacao == 'D' || orientacao == 'd') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[inicioLinha + i][inicioColuna + i] = 3;
        }
    }
    // Posiciona o navio diagonalmente (linha aumenta, coluna diminui).
    else if (orientacao == 'A' || orientacao == 'a') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[inicioLinha + i][inicioColuna - i] = 3;
        }
    }
    return true; // Navio posicionado com sucesso.
}

// Função para exibir o tabuleiro.
void exibirTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    printf("  "); // Espaço para alinhar as colunas.
    for (int j = 0; j < COLUNAS; j++) {
        printf("%d ", j); // Exibe os índices das colunas.
    }
    printf("\n"); // Nova linha.

    for (int i = 0; i < LINHAS; i++) {
        printf("%d ", i); // Exibe os índices das linhas.
        for (int j = 0; j < COLUNAS; j++) {
            printf("%d ", tabuleiro[i][j]); // Exibe o conteúdo da posição (0 para água, 3 para navio).
        }
        printf("\n"); // Nova linha após cada linha do tabuleiro.
    }
}

int main() {
    int tabuleiro[LINHAS][COLUNAS]; // Declara a matriz do tabuleiro.

    inicializarTabuleiro(tabuleiro); // Inicializa o tabuleiro com água.

    printf("Posicionando navios...\n");

    // Posicionar os quatro navios.
    // Navio 1: Horizontal
    if (posicionarNavio(tabuleiro, 0, 0, 'H')) {
        printf("Navio 1 posicionado com sucesso (0,0,H).\n");
    } else {
        printf("Falha ao posicionar Navio 1 (0,0,H) - sobreposição ou fora dos limites.\n");
    }

    // Navio 2: Vertical
    if (posicionarNavio(tabuleiro, 5, 2, 'V')) {
        printf("Navio 2 posicionado com sucesso (5,2,V).\n");
    } else {
        printf("Falha ao posicionar Navio 2 (5,2,V) - sobreposição ou fora dos limites.\n");
    }

    // Navio 3: Diagonal (linha e coluna aumentam)
    if (posicionarNavio(tabuleiro, 1, 6, 'D')) {
        printf("Navio 3 posicionado com sucesso (1,6,D).\n");
    } else {
        printf("Falha ao posicionar Navio 3 (1,6,D) - sobreposição ou fora dos limites.\n");
    }

    // Navio 4: Diagonal (linha aumenta, coluna diminui)
    if (posicionarNavio(tabuleiro, 6, 8, 'A')) { // Ex: (6,8) -> (7,7) -> (8,6)
        printf("Navio 4 posicionado com sucesso (6,8,A).\n");
    } else {
        printf("Falha ao posicionar Navio 4 (6,8,A) - sobreposição ou fora dos limites.\n");
    }

    printf("\nTabuleiro Final:\n");
    exibirTabuleiro(tabuleiro); // Exibe o tabuleiro com os navios posicionados.

    return 0; // Retorna 0 indicando que o programa executou com sucesso.
}
