#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Constantes do jogo
#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define TAM_HABILIDADE 5 // Tamanho das matrizes de habilidade (5x5)

// Protótipos de funções
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]);
bool coordenadasValidas(int linha, int coluna);
bool semSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo);
bool posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo);
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]);
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]);
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int linha, int coluna);

int main()
{
    int tabuleiro[TAMANHO][TAMANHO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios (mesmo do nível anterior)
    posicionarNavio(tabuleiro, 2, 3, 0); // Horizontal
    posicionarNavio(tabuleiro, 5, 7, 1); // Vertical
    posicionarNavio(tabuleiro, 1, 1, 2); // Diagonal principal
    posicionarNavio(tabuleiro, 0, 8, 3); // Diagonal secundária

    // Cria as matrizes de habilidade
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

    // Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 4, 4);     // Cone no centro
    aplicarHabilidade(tabuleiro, cruz, 7, 2);     // Cruz na parte inferior
    aplicarHabilidade(tabuleiro, octaedro, 2, 6); // Octaedro próximo a navios

    // Exibe o tabuleiro com as habilidades aplicadas
    exibirTabuleiro(tabuleiro);

    return 0;
}

// Implementação das funções

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

bool coordenadasValidas(int linha, int coluna)
{
    return (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO);
}

bool semSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo)
{
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int x = linha, y = coluna;

        switch (tipo)
        {
        case 0:
            y += i;
            break; // Horizontal
        case 1:
            x += i;
            break; // Vertical
        case 2:
            x += i;
            y += i;
            break; // Diagonal principal
        case 3:
            x += i;
            y -= i;
            break; // Diagonal secundária
        }

        if (!coordenadasValidas(x, y) || tabuleiro[x][y] != AGUA)
        {
            return false;
        }
    }
    return true;
}

bool posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tipo)
{
    if (!semSobreposicao(tabuleiro, linha, coluna, tipo))
    {
        return false;
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int x = linha, y = coluna;

        switch (tipo)
        {
        case 0:
            y += i;
            break;
        case 1:
            x += i;
            break;
        case 2:
            x += i;
            y += i;
            break;
        case 3:
            x += i;
            y -= i;
            break;
        }

        tabuleiro[x][y] = NAVIO;
    }

    return true;
}

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

void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE])
{
    for (int i = 0; i < TAM_HABILIDADE; i++)
    {
        for (int j = 0; j < TAM_HABILIDADE; j++)
        {
            // Forma um cone apontando para baixo
            if (j >= i && j < TAM_HABILIDADE - i)
            {
                habilidade[i][j] = 1;
            }
            else
            {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE])
{
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++)
    {
        for (int j = 0; j < TAM_HABILIDADE; j++)
        {
            // Forma uma cruz com centro no meio
            if (i == centro || j == centro)
            {
                habilidade[i][j] = 1;
            }
            else
            {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE])
{
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++)
    {
        for (int j = 0; j < TAM_HABILIDADE; j++)
        {
            // Forma um losango (vista frontal do octaedro)
            int dist = abs(i - centro) + abs(j - centro);
            if (dist <= centro)
            {
                habilidade[i][j] = 1;
            }
            else
            {
                habilidade[i][j] = 0;
            }
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int linha, int coluna)
{
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++)
    {
        for (int j = 0; j < TAM_HABILIDADE; j++)
        {
            int x = linha + i - offset;
            int y = coluna + j - offset;

            if (coordenadasValidas(x, y) && habilidade[i][j] == 1)
            {
                // Marca apenas as células de água ou navio (não sobrescreve outras habilidades)
                if (tabuleiro[x][y] == AGUA || tabuleiro[x][y] == NAVIO)
                {
                    tabuleiro[x][y] = HABILIDADE;
                }
            }
        }
    }
}