#include <stdio.h>
#include <string.h>

//Criar jogo war 

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;   
};

//Pedindo dados dos 5 territorios

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

int main(void) {
    struct Territorio territorios[5];
    int i;

    // Cadastrando os territorios
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

    return 0;
}
