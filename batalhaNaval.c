#include <stdio.h>

#define TAM_TAB 10    // Tamanho do tabuleiro (10x10)
#define NAVIO 3       // Tamanho fixo de cada navio
#define AGUA 0        // Valor que representa água
#define PARTE_NAVIO 3 // Valor que representa parte do navio

/* Imprime o tabuleiro com índices das linhas e colunas */
void imprimirTabuleiro(int tab[TAM_TAB][TAM_TAB]) {
    printf("   "); // espaçamento para os índices das colunas
    for (int c = 0; c < TAM_TAB; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < TAM_TAB; r++) {
        printf("%d: ", r); // índice da linha
        for (int c = 0; c < TAM_TAB; c++) {
            printf("%d ", tab[r][c]);
        }
        printf("\n");
    }
}

/* Valida se um navio horizontal cabe no tabuleiro */
int validaHorizontal(int startRow, int startCol) {
    if (startRow < 0 || startRow >= TAM_TAB) return 0;
    if (startCol < 0 || startCol + (NAVIO - 1) >= TAM_TAB) return 0;
    return 1;
}

/* Valida se um navio vertical cabe no tabuleiro */
int validaVertical(int startRow, int startCol) {
    if (startCol < 0 || startCol >= TAM_TAB) return 0;
    if (startRow < 0 || startRow + (NAVIO - 1) >= TAM_TAB) return 0;
    return 1;
}

/* Valida se um navio diagonal (down-right) cabe: linha++ e coluna++ */
int validaDiagonalDownRight(int startRow, int startCol) {
    if (startRow < 0 || startCol < 0) return 0;
    if (startRow + (NAVIO - 1) >= TAM_TAB) return 0;
    if (startCol + (NAVIO - 1) >= TAM_TAB) return 0;
    return 1;
}

/* Valida se um navio diagonal (down-left) cabe: linha++ e coluna-- */
int validaDiagonalDownLeft(int startRow, int startCol) {
    if (startRow < 0 || startCol >= TAM_TAB) return 0;
    if (startRow + (NAVIO - 1) >= TAM_TAB) return 0;
    if (startCol - (NAVIO - 1) < 0) return 0;
    return 1;
}

/* Checa sobreposição para horizontal */
int checaSobreposicaoHorizontal(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int c = startCol; c < startCol + NAVIO; c++) {
        if (tab[startRow][c] == PARTE_NAVIO) return 1;
    }
    return 0;
}

/* Checa sobreposição para vertical */
int checaSobreposicaoVertical(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int r = startRow; r < startRow + NAVIO; r++) {
        if (tab[r][startCol] == PARTE_NAVIO) return 1;
    }
    return 0;
}

/* Checa sobreposição para diagonal down-right (linha+i, col+i) */
int checaSobreposicaoDiagonalDR(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int i = 0; i < NAVIO; i++) {
        int r = startRow + i;
        int c = startCol + i;
        if (tab[r][c] == PARTE_NAVIO) return 1;
    }
    return 0;
}

/* Checa sobreposição para diagonal down-left (linha+i, col-i) */
int checaSobreposicaoDiagonalDL(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int i = 0; i < NAVIO; i++) {
        int r = startRow + i;
        int c = startCol - i;
        if (tab[r][c] == PARTE_NAVIO) return 1;
    }
    return 0;
}

/* Posiciona navio horizontal no tabuleiro (assume validação já feita) */
void posicionaHorizontal(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int c = startCol; c < startCol + NAVIO; c++) {
        tab[startRow][c] = PARTE_NAVIO;
    }
}

/* Posiciona navio vertical no tabuleiro */
void posicionaVertical(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int r = startRow; r < startRow + NAVIO; r++) {
        tab[r][startCol] = PARTE_NAVIO;
    }
}

/* Posiciona navio diagonal down-right */
void posicionaDiagonalDR(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int i = 0; i < NAVIO; i++) {
        tab[startRow + i][startCol + i] = PARTE_NAVIO;
    }
}

/* Posiciona navio diagonal down-left */
void posicionaDiagonalDL(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int i = 0; i < NAVIO; i++) {
        tab[startRow + i][startCol - i] = PARTE_NAVIO;
    }
}

int main() {
    int tab[TAM_TAB][TAM_TAB];

    /* 1) Inicializa o tabuleiro com AGUA (0) */
    for (int r = 0; r < TAM_TAB; r++) {
        for (int c = 0; c < TAM_TAB; c++) {
            tab[r][c] = AGUA;
        }
    }

    /* 2) Coordenadas iniciais (definidas no código)
       Escolhi posições que respeitam limites e não sobrepõem:
       - Navio horizontal: (1,2) -> (1,2),(1,3),(1,4)
       - Navio vertical:   (5,7) -> (5,7),(6,7),(7,7)
       - Navio diagonal DR: (3,0) -> (3,0),(4,1),(5,2)
       - Navio diagonal DL: (2,9) -> (2,9),(3,8),(4,7)
    */
    int h_row = 1, h_col = 2;
    int v_row = 5, v_col = 7;
    int dr_row = 3, dr_col = 0; // diagonal down-right
    int dl_row = 2, dl_col = 9; // diagonal down-left

    /* 3) Valida limites para cada navio */
    if (!validaHorizontal(h_row, h_col)) {
        printf("Erro: navio horizontal nao cabe nas coordenadas fornecidas.\n");
        return 1;
    }
    if (!validaVertical(v_row, v_col)) {
        printf("Erro: navio vertical nao cabe nas coordenadas fornecidas.\n");
        return 1;
    }
    if (!validaDiagonalDownRight(dr_row, dr_col)) {
        printf("Erro: navio diagonal down-right nao cabe nas coordenadas fornecidas.\n");
        return 1;
    }
    if (!validaDiagonalDownLeft(dl_row, dl_col)) {
        printf("Erro: navio diagonal down-left nao cabe nas coordenadas fornecidas.\n");
        return 1;
    }

    /* 4) Verifica sobreposições antes de posicionar:
       checamos na ordem: horizontal -> vertical -> diag DR -> diag DL,
       sempre testando sobreposição contra o tab atual (com navios já posicionados).
    */
    if (checaSobreposicaoHorizontal(tab, h_row, h_col)) {
        printf("Erro: sobreposicao detectada ao posicionar o navio horizontal.\n");
        return 1;
    }
    posicionaHorizontal(tab, h_row, h_col); // posiciona horizontal

    if (checaSobreposicaoVertical(tab, v_row, v_col)) {
        printf("Erro: sobreposicao detectada ao posicionar o navio vertical.\n");
        return 1;
    }
    posicionaVertical(tab, v_row, v_col); // posiciona vertical

    if (checaSobreposicaoDiagonalDR(tab, dr_row, dr_col)) {
        printf("Erro: sobreposicao detectada ao posicionar o navio diagonal DR.\n");
        return 1;
    }
    posicionaDiagonalDR(tab, dr_row, dr_col); // posiciona diag down-right

    if (checaSobreposicaoDiagonalDL(tab, dl_row, dl_col)) {
        printf("Erro: sobreposicao detectada ao posicionar o navio diagonal DL.\n");
        return 1;
    }
    posicionaDiagonalDL(tab, dl_row, dl_col); // posiciona diag down-left

    /* 5) Exibe o tabuleiro final */
    printf("Tabuleiro com 4 navios posicionados (0 = agua, 3 = parte do navio):\n");
    imprimirTabuleiro(tab);

    return 0;
}
