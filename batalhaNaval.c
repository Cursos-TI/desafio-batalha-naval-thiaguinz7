#include <stdio.h>

#define TAM_TAB 10    // Tamanho do tabuleiro (10x10)
#define NAVIO 3       // Tamanho fixo de cada navio
#define AGUA 0        // Valor que representa água
#define PARTE_NAVIO 3 // Valor que representa parte do navio

/* Função para imprimir o tabuleiro */
void imprimirTabuleiro(int tab[TAM_TAB][TAM_TAB]) {
    printf("  "); // espaçamento para os índices das colunas
    for (int c = 0; c < TAM_TAB; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int r = 0; r < TAM_TAB; r++) {
        printf("%d ", r); // índice da linha
        for (int c = 0; c < TAM_TAB; c++) {
            printf("%d ", tab[r][c]);
        }
        printf("\n");
    }
}

/* Verifica se um navio horizontal cabe e não sai do tabuleiro */
int validaHorizontal(int startRow, int startCol) {
    if (startRow < 0 || startRow >= TAM_TAB) return 0;
    if (startCol < 0 || startCol + (NAVIO - 1) >= TAM_TAB) return 0;
    return 1;
}

/* Verifica se um navio vertical cabe e não sai do tabuleiro */
int validaVertical(int startRow, int startCol) {
    if (startCol < 0 || startCol >= TAM_TAB) return 0;
    if (startRow < 0 || startRow + (NAVIO - 1) >= TAM_TAB) return 0;
    return 1;
}

/* Checa sobreposição: retorna 1 se há sobreposição, 0 se não */
int checaSobreposicaoHorizontal(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int c = startCol; c < startCol + NAVIO; c++) {
        if (tab[startRow][c] == PARTE_NAVIO) return 1;
    }
    return 0;
}

int checaSobreposicaoVertical(int tab[TAM_TAB][TAM_TAB], int startRow, int startCol) {
    for (int r = startRow; r < startRow + NAVIO; r++) {
        if (tab[r][startCol] == PARTE_NAVIO) return 1;
    }
    return 0;
}

int main() {
    // 1) Cria e inicializa o tabuleiro com 0 (água)
    int tab[TAM_TAB][TAM_TAB];
    for (int r = 0; r < TAM_TAB; r++) {
        for (int c = 0; c < TAM_TAB; c++) {
            tab[r][c] = AGUA;
        }
    }

    // 2) Coordenadas iniciais definidas no código
    // Use 0..9 para linhas e colunas (0-based).
    // Exemplo que NÃO se sobrepõe:
    // Navio horizontal: começa na linha 1, coluna 2 -> cobre (1,2),(1,3),(1,4)
    int h_row = 1;
    int h_col = 2;

    // Navio vertical: começa na linha 5, coluna 7 -> cobre (5,7),(6,7),(7,7)
    int v_row = 5;
    int v_col = 7;

    // 3) Validações de limite
    if (!validaHorizontal(h_row, h_col)) {
        printf("Erro: navio horizontal nao cabe nas coordenadas fornecidas.\n");
        return 1;
    }
    if (!validaVertical(v_row, v_col)) {
        printf("Erro: navio vertical nao cabe nas coordenadas fornecidas.\n");
        return 1;
    }

    // 4) Verifica sobreposição antes de posicionar
    if (checaSobreposicaoHorizontal(tab, h_row, h_col)) {
        printf("Erro: sobreposicao detectada ao posicionar o navio horizontal.\n");
        return 1;
    }
    if (checaSobreposicaoVertical(tab, v_row, v_col)) {
        printf("Erro: sobreposicao detectada ao posicionar o navio vertical.\n");
        return 1;
    }

    // 5) Posiciona o navio horizontal no tabuleiro (valor 3)
    for (int c = h_col; c < h_col + NAVIO; c++) {
        tab[h_row][c] = PARTE_NAVIO;
    }

    // 6) Antes de posicionar o navio vertical, verificar se não ocorreu sobreposição
    // (checa novamente agora que o horizontal já está posicionado)
    if (checaSobreposicaoVertical(tab, v_row, v_col)) {
        printf("Erro: sobreposicao detectada - o navio vertical sobrepoe o horizontal.\n");
        return 1;
    }

    // 7) Posiciona o navio vertical no tabuleiro
    for (int r = v_row; r < v_row + NAVIO; r++) {
        tab[r][v_col] = PARTE_NAVIO;
    }

    // 8) Exibe o tabuleiro final
    printf("Tabuleiro com navios posicionados (0 = agua, 3 = parte do navio):\n");
    imprimirTabuleiro(tab);

    return 0;
}
