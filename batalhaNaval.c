#include <stdio.h>

#define TAM_TAB 10    // Tamanho do tabuleiro (10x10)
#define NAVIO 3       // Tamanho fixo de cada navio
#define AGUA 0        // Valor que representa água
#define PARTE_NAVIO 3 // Valor que representa parte do navio
#define HABILIDADE 5  // Valor que representa área afetada por habilidade

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

/* ================================
   Construção DINÂMICA das matrizes
   de habilidade (usando loops e
   condicionais)
   Retornam matrizes 5x5 com 0/1
   ================================ */

/* Preenche matrizCone 5x5: cone apontando para baixo.
   Convenção: origem (ponto de emissão) da habilidade dentro da matriz é (0,2)
   A função preenche o array passed como parametro (mat[5][5]).
*/
void constroiCone(int mat[5][5]) {
    int size = 5;
    // Inicializa com zeros
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mat[i][j] = 0;

    // Cone com topo no row 0, coluna central (2), expandindo pra baixo
    // Condição: para cada linha r (0..2), o cone ocupa colunas com |col - 2| <= r
    for (int r = 0; r <= 2; r++) {
        for (int c = 0; c < size; c++) {
            if ( (c - 2 < 0 ? 2 - c : c - 2) <= r ) { // abs(c-2) <= r
                mat[r][c] = 1;
            }
        }
    }
}

/* Preenche matrizCruz 5x5: cruz (mais) com centro em (2,2) */
void constroiCruz(int mat[5][5]) {
    int size = 5;
    // Inicializa com zeros
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mat[i][j] = 0;

    // Cruz simples: linha central e coluna central
    for (int i = 0; i < size; i++) {
        mat[2][i] = 1; // linha central
        mat[i][2] = 1; // coluna central
    }
}

/* Preenche matrizOctaedro 5x5: losango (diamond) com centro em (2,2)
   Condição: abs(r-2) + abs(c-2) <= 2 */
void constroiOctaedro(int mat[5][5]) {
    int size = 5;
    // Inicializa com zeros
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mat[i][j] = 0;

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            int dist = (r > 2 ? r - 2 : 2 - r) + (c > 2 ? c - 2 : 2 - c); // abs(r-2)+abs(c-2)
            if (dist <= 2) mat[r][c] = 1;
        }
    }
}

/* Sobrepõe a matriz de habilidade (matA mxm) ao tabuleiro,
   centrando a matA no ponto (boardRow, boardCol) do tabuleiro.
   abilityOriginRow/Col : coordenadas do "ponto de origem" dentro da matriz da habilidade
   Ex.: para cruz/oct/normal usar origin (2,2); para cone usamos (0,2).
   Só marca HABILIDADE (5) se célula for 1 e se posição do tabuleiro for AGUA (0).
   Se já houver navio (3), mantemos o 3.
*/
void aplicaHabilidadeNoTabuleiro(int tab[TAM_TAB][TAM_TAB],
                                int matA[5][5], int mSize,
                                int abilityOriginRow, int abilityOriginCol,
                                int boardRow, int boardCol) {
    for (int i = 0; i < mSize; i++) {
        for (int j = 0; j < mSize; j++) {
            if (matA[i][j] != 1) continue; // só nos pontos afetados

            // Calcula posição no tabuleiro alinhando origem
            int tr = boardRow + (i - abilityOriginRow);
            int tc = boardCol + (j - abilityOriginCol);

            // Verifica limites do tabuleiro
            if (tr < 0 || tr >= TAM_TAB || tc < 0 || tc >= TAM_TAB) {
                // Fora do tabuleiro: ignorar (simplificação permitida)
                continue;
            }

            // Se já há navio (3), preserva-o. Caso contrário, marca área de habilidade com 5.
            if (tab[tr][tc] == PARTE_NAVIO) {
                // preserva navio (mantém 3)
                continue;
            } else {
                tab[tr][tc] = HABILIDADE;
            }
        }
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
       Navios (tamanho 3):
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

    /* 4) Verifica sobreposições e posiciona na ordem definida */
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

    /* ====== 5) Construção das matrizes de habilidade dinamicamente ====== */
    int cone[5][5], cruz[5][5], octaedro[5][5];
    constroiCone(cone);     // origin (0,2) dentro da matriz
    constroiCruz(cruz);     // origin (2,2)
    constroiOctaedro(octaedro); // origin (2,2)

    /* ====== 6) Define pontos de origem no tabuleiro para aplicar habilidades ======
       (estas coordenadas são definidas no código conforme simplificação do exercício)
       - Para o cone: vamos colocar o "ponto de emissão" (origem) em (2,4) no tabuleiro.
         Lembre: dentro da matriz cone a origem é (0,2) (topo central).
       - Para a cruz: centro da cruz ficará em (6,2).
       - Para o octaedro: centro ficará em (4,5).
    */
    int cone_board_row = 2, cone_board_col = 4;
    int cruz_board_row = 6, cruz_board_col = 2;
    int oct_board_row = 4, oct_board_col = 5;

    /* ====== 7) Aplica as habilidades no tabuleiro (sobreposição centrada usando origem) ======
       Observação: para cone usamos abilityOriginRow=0, abilityOriginCol=2 (top-center)
                    para cruz/oct usamos 2,2 (center)
    */
    aplicaHabilidadeNoTabuleiro(tab, cone, 5, 0, 2, cone_board_row, cone_board_col);
    aplicaHabilidadeNoTabuleiro(tab, cruz, 5, 2, 2, cruz_board_row, cruz_board_col);
    aplicaHabilidadeNoTabuleiro(tab, octaedro, 5, 2, 2, oct_board_row, oct_board_col);

    /* ====== 8) Exibe o tabuleiro final com navios e áreas de habilidade ======
       Convenção de valores:
         0 -> água
         3 -> navio (parte do navio)
         5 -> área afetada por habilidade
    */
    printf("Tabuleiro final (0 = agua, 3 = navio, 5 = area de habilidade):\n");
    imprimirTabuleiro(tab);

    return 0;
}


