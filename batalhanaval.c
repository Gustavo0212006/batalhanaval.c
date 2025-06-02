#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define HABILIDADE 5

// Começa com tudo como água (0)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Mostra o tabuleiro na tela
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Coloca o navio no tabuleiro, com base na direcao
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < 3; i++) {
        if (direcao == 'h') // horizontal
            tabuleiro[linha][coluna + i] = NAVIO;
        else if (direcao == 'v') // vertical
            tabuleiro[linha + i][coluna] = NAVIO;
        else if (direcao == 'd') // diagonal principal
            tabuleiro[linha + i][coluna + i] = NAVIO;
        else if (direcao == 'a') // diagonal invertida
            tabuleiro[linha + i][coluna - i] = NAVIO;
    }
}

// Aplica habilidade (matriz 5x5) no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int origem_linha, int origem_coluna, int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linha = origem_linha + i - 2;
            int coluna = origem_coluna + j - 2;
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linha][coluna] != NAVIO)
                    tabuleiro[linha][coluna] = HABILIDADE;
            }
        }
    }
}

// Monta o formato do cone
void definirCone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i >= j - 2 && i >= 2 - j)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Monta o formato da cruz
void definirCruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Monta o formato do octaedro (tipo um losango)
void definirOctaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[5][5], cruz[5][5], octaedro[5][5];

    inicializarTabuleiro(tabuleiro);

    // Posiciona os 4 navios (2 retos, 2 diagonais)
    posicionarNavio(tabuleiro, 0, 0, 'h');
    posicionarNavio(tabuleiro, 3, 3, 'v');
    posicionarNavio(tabuleiro, 6, 0, 'd');
    posicionarNavio(tabuleiro, 6, 9, 'a');

    // Define as 3 habilidades
    definirCone(cone);
    definirCruz(cruz);
    definirOctaedro(octaedro);

    // Aplica as habilidades em pontos do tabuleiro
    aplicarHabilidade(tabuleiro, 2, 2, cone);
    aplicarHabilidade(tabuleiro, 5, 5, cruz);
    aplicarHabilidade(tabuleiro, 8, 8, octaedro);

    // Mostra o tabuleiro final com navios e efeitos
    exibirTabuleiro(tabuleiro);

    return 0;
}



