#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Criar jogo war 

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;   
};

//Pedindo dados dos 5 territorios e alocando memoria

void alocarMemoriaTerritorios(struct Territorio **territorios, int quantidade) {
    *territorios = (struct Territorio *)malloc(quantidade * sizeof(struct Territorio));
}

void cadastrarTerritorio (struct Territorio *territorio) {
    printf("Digite o nome do territorio: ");
    scanf("%s", territorio->nome);
    printf("Digite a cor do territorio: ");
    scanf("%s", territorio->cor);
    printf("Digite o numero de tropas: ");
    scanf("%d", &territorio->tropas);
}


//Mostrando dados dos 5 territorios

void mostrarTerritorio(struct Territorio territorio) {
    printf("Nome: %s\n", territorio.nome);
    printf("Cor: %s\n", territorio.cor);
    printf("Tropas: %d\n", territorio.tropas);
}

// Função para liberar memória (usada apenas se alocação dinâmica for utilizada)
void liberarMemoria(struct Territorio *territorios);

int main(void) {
    struct Territorio territorios[5];
    int i;

    for(i = 0; i < 5; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);
        cadastrarTerritorio(&territorios[i]);
    }

    // Mostrando os territorios cadastrados
    printf("\nTerritorios cadastrados:\n");
    for(i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        mostrarTerritorio(territorios[i]);
    }


    //Ataque entre territorios

    int atacante, defensor;
    printf("\nDigite o numero do territorio atacante (1-5): ");
    scanf("%d", &atacante);
    printf("Digite o numero do territorio defensor (1-5): ");
    scanf("%d", &defensor);

    // Simulando o ataque com dados aleatorios e turnos

    srand(time(NULL));
    while(territorios[atacante - 1].tropas > 0 && territorios[defensor - 1].tropas > 0) {
        int dadoAtacante = (rand() % 6) + 1;
        int dadoDefensor = (rand() % 6) + 1;

        printf("\nAtacante rolou: %d\n", dadoAtacante);
        printf("Defensor rolou: %d\n", dadoDefensor);

        if(dadoAtacante > dadoDefensor) {
            territorios[defensor - 1].tropas--;
            printf("Defensor perde uma tropa! Tropas restantes: %d\n", territorios[defensor - 1].tropas);
        } else {
            territorios[atacante - 1].tropas--;
            printf("Atacante perde uma tropa! Tropas restantes: %d\n", territorios[atacante - 1].tropas);
        }
    }

    if(territorios[atacante - 1].tropas > 0) {
        printf("\nO territorio %s venceu o ataque!\n", territorios[atacante - 1].nome);
    } else {
        printf("\nO territorio %s defendeu com sucesso!\n", territorios[defensor - 1].nome);
    }

  

    return 0;
}

// Função para liberar memória (usada apenas se alocação dinâmica for utilizada)
void liberarMemoria(struct Territorio *territorios) {
    free(territorios);
};