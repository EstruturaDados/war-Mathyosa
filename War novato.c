
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Estrutura dos territórios
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;   
};

// Funções principais
void alocarMemoriaTerritorios(struct Territorio **territorios, int quantidade);
void cadastrarTerritorio(struct Territorio *territorio);
void mostrarTerritorio(struct Territorio territorio);
void liberarMemoria(struct Territorio *territorios);
void atacar(struct Territorio *atacante, struct Territorio *defensor);
void exibirMapa(struct Territorio *territorios, int quantidade);

// Funções de missão
void atribuirMissao(char *destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, struct Territorio *mapa, int tamanho);

int main(void) {
    srand(time(NULL));

    int quantidade = 5;
    struct Territorio *territorios = NULL;

    alocarMemoriaTerritorios(&territorios, quantidade);

    for (int i = 0; i < quantidade; i++) {
        printf("\nCadastro do territorio %d:\n", i + 1);
        cadastrarTerritorio(&territorios[i]);
    }

    printf("\n--- Territorios cadastrados ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        mostrarTerritorio(territorios[i]);
    }

    // ======== MISSÕES =========
    char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Possuir 2 territorios",
        "Eliminar todas as tropas da cor azul",
        "Possuir 4 territorios"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Cada jogador (exemplo com 5 jogadores)
    int numJogadores = 5;
    char *coresJogadores[] = {"vermelha", "azul", "verde", "amarelo", "roxo"};

    // Alocar missões dinamicamente
    
    char **missoesJogadores = (char **)malloc(numJogadores * sizeof(char *));
    for (int i = 0; i < numJogadores; i++) {
        missoesJogadores[i] = (char *)malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoes, totalMissoes);
        printf("\nJogador %d (%s) - Missao: %s\n", i + 1, coresJogadores[i], missoesJogadores[i]);
    }

    // ======== ATAQUE =========

    exibirMapa(territorios, quantidade);
    int atacante, defensor;
    printf("\nDigite o numero do territorio atacante (1-%d): ", quantidade);
    scanf("%d", &atacante);
    printf("Digite o numero do territorio defensor (1-%d): ", quantidade);
    scanf("%d", &defensor);

    atacar(&territorios[atacante - 1], &territorios[defensor - 1]);

    // ======== Verificação de missão =========
    for (int i = 0; i < numJogadores; i++) {
        if (verificarMissao(missoesJogadores[i], territorios, quantidade)) {
            printf("\n>>> Jogador %d (%s) CUMPRIU sua missão: %s\n",
                   i + 1, coresJogadores[i], missoesJogadores[i]);
        } else {
            printf("\nJogador %d (%s) ainda não cumpriu sua missão.\n",
                   i + 1, coresJogadores[i]);
        }
    }

    // Libera memória
    liberarMemoria(territorios);
    for (int i = 0; i < numJogadores; i++) free(missoesJogadores[i]);
    free(missoesJogadores);

    return 0;
}

// ======================================================
// IMPLEMENTAÇÕES
// ======================================================

void alocarMemoriaTerritorios(struct Territorio **territorios, int quantidade) {
    *territorios = (struct Territorio *)malloc(quantidade * sizeof(struct Territorio));
    if (*territorios == NULL) {
        printf("Erro ao alocar memoria para territorios.\n");
        exit(1);
    }
}

void cadastrarTerritorio(struct Territorio *territorio) {
    printf("Digite o nome do territorio: ");
    scanf("%s", territorio->nome);
    printf("Digite a cor do territorio: ");
    scanf("%s", territorio->cor);
    printf("Digite o numero de tropas: ");
    scanf("%d", &territorio->tropas);
}

void mostrarTerritorio(struct Territorio territorio) {
    printf("Nome: %s\n", territorio.nome);
    printf("Cor: %s\n", territorio.cor);
    printf("Tropas: %d\n", territorio.tropas);
}

void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nAtaque invalido! Mesma cor.\n");
        return;
    }

    printf("\n--- Iniciando ataque ---\n");
    while (atacante->tropas > 0 && defensor->tropas > 0) {
        int dadoA = (rand() % 6) + 1;
        int dadoD = (rand() % 6) + 1;

        printf("\n%s rolou %d | %s rolou %d\n", atacante->nome, dadoA, defensor->nome, dadoD);

        if (dadoA > dadoD) {
            defensor->tropas--;
            printf("Defensor perde 1 tropa! Restantes: %d\n", defensor->tropas);
        } else {
            atacante->tropas--;
            printf("Atacante perde 1 tropa! Restantes: %d\n", atacante->tropas);
        }
    }

    if (atacante->tropas > 0) {
        printf("\n%s conquistou o territorio %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("\n%s defendeu com sucesso!\n", defensor->nome);
    }
}

void exibirMapa(struct Territorio *territorios, int quantidade) {
    printf("\n--- MAPA ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%s | Cor: %s | Tropas: %d\n",
               territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

// Sorteia missão
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// Verifica se missão foi cumprida
int verificarMissao(char *missao, struct Territorio *mapa, int tamanho) {
    if (strstr(missao, "Conquistar 3 territorios seguidos")) {
        for (int i = 0; i < tamanho - 2; i++) {
            if (strcmp(mapa[i].cor, mapa[i + 1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i + 2].cor) == 0) {
                return 1;
            }
        }
    } else if (strstr(missao, "Eliminar todas as tropas da cor vermelha")) {
        int existe = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                existe = 1;
        }
        if (!existe) return 1;
    } else if (strstr(missao, "Eliminar todas as tropas da cor azul")) {
        int existe = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 0)
                existe = 1;
        }
        if (!existe) return 1;
    } else if (strstr(missao, "Possuir 2 territorios")) {
        // conta por cor
        char cores[10][10];
        int cont[10];
        int n = 0;
        for (int i = 0; i < tamanho; i++) {
            int found = -1;
            for (int j = 0; j < n; j++)
                if (strcmp(cores[j], mapa[i].cor) == 0) found = j;
            if (found == -1) {
                strcpy(cores[n], mapa[i].cor);
                cont[n] = 1;
                n++;
            } else cont[found]++;
        }
        for (int i = 0; i < n; i++) if (cont[i] >= 2) return 1;
    } else if (strstr(missao, "Possuir 4 territorios")) {
        char cores[10][10];
        int cont[10];
        int n = 0;
        for (int i = 0; i < tamanho; i++) {
            int found = -1;
            for (int j = 0; j < n; j++)
                if (strcmp(cores[j], mapa[i].cor) == 0) found = j;
            if (found == -1) {
                strcpy(cores[n], mapa[i].cor);
                cont[n] = 1;
                n++;
            } else cont[found]++;
        }
        for (int i = 0; i < n; i++) if (cont[i] >= 4) return 1;
    }

    return 0;
}

void liberarMemoria(struct Territorio *territorios) {
    free(territorios);
}