#include <stdio.h>
#include <stdbool.h>

// Tamanho do tabuleiro
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Valores para representar o tabuleiro
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se uma posição é válida no tabuleiro
bool posicaoValida(int linha, int coluna)
{
    return (linha >= 0 && linha < TAMANHO_TABULEIRO &&
            coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar se é possível posicionar um navio
bool podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                         int linha, int coluna, bool horizontal)
{
    // Verifica todas as posições que o navio ocuparia
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int linhaAtual = horizontal ? linha : linha + i;
        int colunaAtual = horizontal ? coluna + i : coluna;

        if (!posicaoValida(linhaAtual, colunaAtual) ||
            tabuleiro[linhaAtual][colunaAtual] != AGUA)
        {
            return false;
        }
    }
    return true;
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linha, int coluna, bool horizontal)
{
    // Verifica se é possível posicionar o navio
    if (!podePosicionarNavio(tabuleiro, linha, coluna, horizontal))
    {
        printf("Erro: Não é possível posicionar o navio nas coordenadas (%d, %d) %s\n",
               linha, coluna, horizontal ? "horizontal" : "vertical");
        return;
    }

    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        int linhaAtual = horizontal ? linha : linha + i;
        int colunaAtual = horizontal ? coluna + i : coluna;
        tabuleiro[linhaAtual][colunaAtual] = NAVIO;
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO])
{
    printf("Tabuleiro do Batalha Naval:\n");
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++)
    {
        printf("%2d ", j); // Cabeçalho das colunas
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
    {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
        {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    // Declaração do tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios (coordenadas definidas no código)
    // Navio horizontal: linha 2, coluna 3
    posicionarNavio(tabuleiro, 2, 3, true);

    // Navio vertical: linha 5, coluna 7
    posicionarNavio(tabuleiro, 5, 7, false);

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}