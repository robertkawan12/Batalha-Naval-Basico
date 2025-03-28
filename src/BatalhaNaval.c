#include <stdio.h>
#include <stdbool.h>

// Constantes do jogo
#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO])
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar coordenadas válidas
bool coordenadasValidas(int linha, int coluna)
{
    return (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO);
}

// Função para verificar sobreposição
bool semSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo)
{
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int x = linha, y = coluna;

        // Calcula a posição de acordo com o tipo de navio
        switch (tipo)
        {
        case 0: // Horizontal
            y += i;
            break;
        case 1: // Vertical
            x += i;
            break;
        case 2: // Diagonal principal (\)
            x += i;
            y += i;
            break;
        case 3: // Diagonal secundária (/)
            x += i;
            y -= i;
            break;
        }

        // Verifica se a posição está ocupada
        if (!coordenadasValidas(x, y) || tabuleiro[x][y] != AGUA)
        {
            return false;
        }
    }
    return true;
}

// Função para posicionar navio
bool posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo)
{
    // Verifica se é possível posicionar o navio
    if (!semSobreposicao(tabuleiro, linha, coluna, tipo))
    {
        return false;
    }

    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int x = linha, y = coluna;

        switch (tipo)
        {
        case 0: // Horizontal
            y += i;
            break;
        case 1: // Vertical
            x += i;
            break;
        case 2: // Diagonal principal
            x += i;
            y += i;
            break;
        case 3: // Diagonal secundária
            x += i;
            y -= i;
            break;
        }

        tabuleiro[x][y] = NAVIO;
    }

    return true;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO])
{
    printf("\n  ");
    for (int j = 0; j < TAMANHO; j++)
    {
        printf("%2d", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%2d", i);
        for (int j = 0; j < TAMANHO; j++)
        {
            printf("%2d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios
    printf("Posicionando navios...\n");

    // Navio horizontal (linha 2, coluna 3)
    if (!posicionarNavio(tabuleiro, 2, 3, 0))
    {
        printf("Erro ao posicionar navio horizontal!\n");
        return 1;
    }

    // Navio vertical (linha 5, coluna 7)
    if (!posicionarNavio(tabuleiro, 5, 7, 1))
    {
        printf("Erro ao posicionar navio vertical!\n");
        return 1;
    }

    // Navio diagonal principal (linha 1, coluna 1)
    if (!posicionarNavio(tabuleiro, 1, 1, 2))
    {
        printf("Erro ao posicionar navio diagonal principal!\n");
        return 1;
    }

    // Navio diagonal secundária (linha 0, coluna 8)
    if (!posicionarNavio(tabuleiro, 0, 8, 3))
    {
        printf("Erro ao posicionar navio diagonal secundaria!\n");
        return 1;
    }

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}