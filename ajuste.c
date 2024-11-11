#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TOTAL_PKMNS 30
#define TIME_SIZE 6

typedef struct Pokemon {
    char nome[20];
    int dex;
    int hp;
    int ataque;
    int defesa;
    int ataqueEspecial;
    int defesaEspecial;
    int speed;
    int escolhido; // 0 = não foi escolhido, 1 = escolhido
} pkmn;

typedef struct Player {
    char nome[15]; // Nome dos jogadores
    pkmn timepokemon[TIME_SIZE]; // Pokémons dos jogadores
} player;

// Funções
void construirPlayer(player *treinador);
void printatreinador(player treinador);
void imprimirpkdex(pkmn pokedex[]);
void printarpkmn_tochoice(pkmn pokedex[], int i);
int escolhageral(pkmn pkdex[]);

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int main() {
    setlocale(LC_ALL, "Portuguese");

    // Declara e monta a Pokedex
    pkmn pkdex[TOTAL_PKMNS] = {
        {"Emboar", 1, 110, 123, 65, 100, 65, 65, 0},
        {"Dragonite", 2, 91, 134, 95, 100, 100, 80, 0},
        {"Golurk", 3, 89, 124, 80, 55, 80, 55, 0},
        {"Salamence", 4, 95, 135, 80, 110, 80, 100, 0},
        {"Lapras", 5, 130, 85, 80, 85, 95, 60, 0},
        {"Pidgeot", 6, 83, 80, 75, 70, 70, 101, 0},
        {"Muk", 7, 105, 105, 75, 65, 100, 50, 0},
        {"Alakazam", 8, 55, 40, 45, 135, 95, 120, 0},
        {"Tyranitar", 9, 100, 134, 110, 95, 100, 61, 0},
        {"Metagross", 10, 80, 135, 130, 95, 90, 70, 0},
        {"Greninja", 11, 72, 95, 67, 103, 71, 122, 0},
        {"Pinsir", 12, 65, 125, 100, 55, 70, 85, 0},
        {"Electivire", 13, 75, 123, 67, 95, 85, 95, 0},
        {"Primarina", 14, 80, 74, 74, 126, 116, 60, 0},
        {"Honchkrow", 15, 100, 125, 52, 105, 52, 71, 0},
        {"Chandelure", 16, 60, 55, 90, 145, 90, 80, 0},
        {"Espeon", 17, 65, 65, 60, 130, 95, 110, 0},
        {"Cubone", 18, 50, 50, 95, 40, 50, 35, 0},
        {"Ninetales de Alola", 19, 73, 67, 75, 81, 100, 109, 0},
        {"Purugly", 20, 71, 82, 64, 64, 59, 112, 0},
        {"Nidoking", 21, 81, 102, 77, 85, 75, 85, 0},
        {"Venusaur", 22, 80, 82, 83, 100, 100, 80, 0},
        {"Charizard", 23, 78, 84, 78, 109, 85, 100, 0},
        {"Gallade", 24, 68, 125, 65, 65, 115, 80, 0},
        {"Gardevoir", 25, 68, 65, 65, 125, 115, 80, 0},
        {"Magneton", 26, 50, 60, 95, 120, 70, 70, 0},
        {"Decidueye", 27, 78, 107, 75, 100, 100, 70, 0},
        {"Umbreon", 28, 95, 65, 110, 60, 130, 65, 0},
        {"Leavanny", 29, 75, 103, 80, 70, 80, 92, 0},
        {"Lucario", 30, 70, 110, 70, 115, 70, 90, 0}
    };

    // Declara e monta os jogadores
    player treinador1;
    player treinador2;

    printf("Digite o nome do primeiro treinador: ");
    scanf(" %[^\n]", treinador1.nome);
    construirPlayer(&treinador1);

    printf("Digite o nome do segundo treinador: ");
    scanf(" %[^\n]", treinador2.nome);
    construirPlayer(&treinador2);

    printatreinador(treinador1);
    printatreinador(treinador2);

    // Escolher os pokemons
    for (int j = 0; j < TIME_SIZE; j++) {
        printf("%s, escolha um Pokémon!\n\n", treinador1.nome);
        treinador1.timepokemon[j] = pkdex[escolhageral(pkdex)];
        pkdex[treinador1.timepokemon[j].dex - 1].escolhido = 1;

        printf("%s, escolha um Pokémon!\n\n", treinador2.nome);
        treinador2.timepokemon[j] = pkdex[escolhageral(pkdex)];
        pkdex[treinador2.timepokemon[j].dex - 1].escolhido = 1;
    }

    return 0;
}

void construirPlayer(player *treinador) {
    for (int i = 0; i < TIME_SIZE; i++) {
        strcpy(treinador->timepokemon[i].nome, "placeholder");
    }
    system(CLEAR);
}

void printatreinador(player treinador) {
    printf("Treinador: %s\n", treinador.nome);

    for (int i = 0; i < TIME_SIZE; i++) {
        printf("%d - %s\n", i + 1, treinador.timepokemon[i].nome);
    }
    printf("\n");
}

void imprimirpkdex(pkmn pokedex[]) {
    for (int i = 0; i < TOTAL_PKMNS; i++) {
        if (pokedex[i].escolhido) {
            printf("%d - Pokémon já escolhido\n", i + 1);
        } else {
            printf("%d - %s\n", i + 1, pokedex[i].nome);
        }
    }
    printf("\n");
}

void printarpkmn_tochoice(pkmn pokedex[], int i) {
    printf("NOME: %s | Nº DEX: %d\n\n", pokedex[i].nome, pokedex[i].dex);
    printf("HP: %d\n", pokedex[i].hp);
    printf("ATAQUE: %d\n", pokedex[i].ataque);
    printf("DEFESA: %d\n", pokedex[i].defesa);
    printf("ATAQUE ESPECIAL: %d\n", pokedex[i].ataqueEspecial);
    printf("DEFESA ESPECIAL: %d\n", pokedex[i].defesaEspecial);
    printf("SPEED: %d\n\n", pokedex[i].speed);
}

int escolhageral(pkmn pkdex[]) {
    int option;
    int confirmacao;

    do {

        imprimirpkdex(pkdex);

        printf("Digite o número do Pokémon para abrir as informações: ");
        scanf("%d", &option);
        system(CLEAR);

        // Vai verificar se o pokemon já foi escolhido
        if (pkdex[option - 1].escolhido) {
            printf("Esse Pokémon já foi escolhido por outro treinador. Escolha outro Pokémon.\n\n");
            continue; // Volta pro início do loop para escolher denovo
        }

        // Exibe os poderzinhos dos bichinhos
        printarpkmn_tochoice(pkdex, option - 1);

        do {
            printf("Digite:\n1 - Confirmar Escolha do Pokémon\n0 - Para Voltar\nR: ");
            scanf("%d", &confirmacao);

            if (confirmacao != 0 && confirmacao != 1) {
                printf("Escolha Inválida\n\n");
                confirmacao = 2;
            }
        } while (confirmacao == 2);

    } while (confirmacao == 0 || pkdex[option - 1].escolhido);

    // Marca o pokemon como escolhido antes de voltar praquela bagaça
    pkdex[option - 1].escolhido = 1;

    return option - 1;
}

