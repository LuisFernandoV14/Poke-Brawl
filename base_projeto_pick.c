#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct ataque
{
	char nome[25];
	char tipo[10];
	int pp;
	int categoria;
	int poder;
	int prioridade; 
	int accuracy; 
	int critico; 
} move;

typedef struct Pokemon
{
	//nome do pokemon
	char nome[20];
	//numero do pokemon na pokedex (vai ser util depois)
	int dex; 
	// status dos pokemon
	int hp;
	int ataque;
	int defesa;
	int ataqueEspecial;
	int defesaEspecial;
	int speed;
	
} pkmn;

typedef struct Player
{
	char nome[15]; //nome dos jogadores
	int dinheiro; //dinheiro dos jogadores
	pkmn timepokemon[6]; // pokemons dos jogadores
} player;

//funcoes----------------------------------
void construirPlayer(player *treinador);
void printatreinador(player treinador);
void imprimirpkdex(pkmn pokedex[]);
void printarpkmn_tochoice(pkmn pokedex[], int i);
int escolhageral(pkmn pkdex[]);
//funcoes----------------------------------

int main()
{
	setlocale(LC_ALL, "Portuguese");
	// declara e monta a pokedex (ta funcionando ja)
	pkmn pkdex[30];
	
	// declara e monta os players (ta funcionando ja)
	player treinador1; 
	player treinador2;

	printf("Digite o nome do treinador1: ");
	fflush(stdin);
	fgets(treinador1.nome, 20, stdin);
	construirPlayer(&treinador1);

	printf("Digite o nome do treinador2: ");
	fflush(stdin);
	fgets(treinador2.nome, 20, stdin);
	construirPlayer(&treinador2);
	
	printatreinador(treinador1);
	printatreinador(treinador2);

 	//----------//Declaração de Pokémons//-----------//
	pkmn emboar = {"Emboar", 1, 110, 123, 65, 100, 65, 65};
 	pkmn dragonite = {"Dragonite", 2, 91, 134, 95, 100, 100, 80};
	pkmn golurk = {"Golurk", 3, 89, 124, 80, 55, 80, 55};
	pkmn salamence = {"Salamence", 4, 95, 135, 80, 110, 80, 100};
 	pkmn lapras = {"Lapras", 5, 130, 85, 80, 85, 95, 60};
	pkmn pidgeot = {"Pidgeot", 6, 83, 80, 75, 70, 70, 101};
	pkmn muk = {"Muk", 7, 105, 105, 75, 65, 100, 50};
	pkmn alakazam = {"Alakazam", 8, 55, 40, 45, 135, 95, 120};
	pkmn tyranitar = {"Tyranitar", 9, 100, 134, 110, 95, 100, 61};
 	pkmn metagross = {"Metagross", 10, 80, 135, 130, 95, 90, 70}; 
	pkmn greninja = {"Greninja", 11, 72, 95, 67, 103, 71, 122};
	pkmn pinsir = {"Pinsir", 12, 65, 125, 100, 55, 70, 85};
 	pkmn electivire = {"Electivire", 13, 75, 123, 67, 95, 85, 95};
	pkmn primarina = {"Primarina", 14, 80, 74, 74, 126, 116, 60};
	pkmn honchkrow = {"Honchkrow", 15, 100, 125, 52, 105, 52, 71};
 	pkmn chandelure = {"Chandelure", 16, 60, 55, 90, 145, 90, 80};
	pkmn espeon = {"Espeon", 17, 65, 65, 60, 130, 95, 110};
	pkmn cubone = {"Cubone", 18, 50, 50, 95, 40, 50, 35};
	pkmn ninetalesdealola = {"Ninetales de Alola", 19, 73, 67, 75, 81, 100, 109};
 	pkmn purugly = {"Purugly", 20, 71, 82, 64, 64, 59, 112};
	pkmn nidoking = {"Nidoking", 21, 81, 102, 77, 85, 75, 85};
	pkmn venusaur = {"Venusaur", 22, 80, 82, 83, 100, 100, 80};
	pkmn charizard = {"Charizard", 23, 78, 84, 78, 109, 85, 100};
	pkmn gallade = {"Gallade", 24, 68, 125, 65, 65, 115, 80};
	pkmn gardevoir = {"Gardevoir", 25, 68, 65, 65, 125, 115, 80};
	pkmn magneton = {"Magneton", 26, 50, 60, 95, 120, 70, 70};
	pkmn decidueye = {"Decidueye", 27, 78, 107, 75, 100, 100, 70};
	pkmn umbreon = {"Umbreon", 28, 95, 65, 110, 60, 130, 65};
	pkmn leavanny = {"Leavanny", 29, 75, 103, 80, 70, 80, 92};
	pkmn lucario = {"Lucario", 30, 70, 110, 70, 115, 70, 90};
	//----------//Declaração de Pokémons//-----------//


	 //----------//Alocação dos Pokémons na Pokedex//-----------//
	pkdex[0] = emboar;
	pkdex[1] = dragonite;
	pkdex[2] = golurk;
	pkdex[3] = salamence;
	pkdex[4] = lapras;
	pkdex[5] = pidgeot;
	pkdex[6] = muk;
	pkdex[7] = alakazam;
	pkdex[8] = tyranitar;
	pkdex[9] = metagross;
	pkdex[10] = greninja;
	pkdex[11] = pinsir;
	pkdex[12] = electivire;
	pkdex[13] = primarina;
	pkdex[14] = honchkrow;
	pkdex[15] = chandelure;
	pkdex[16] = espeon;
	pkdex[17] = cubone;
	pkdex[18] = ninetalesdealola;
	pkdex[19] = purugly;
	pkdex[20] = nidoking;
	pkdex[21] = venusaur;
	pkdex[22] = charizard;
	pkdex[23] = gallade;
	pkdex[24] = gardevoir;
	pkdex[25] = magneton;
	pkdex[26] = decidueye;
	pkdex[27] = umbreon;
	pkdex[28] = leavanny;
	pkdex[29] = lucario;
	//----------//Alocação dos Pokémons na Pokedex//-----------//

	

	printf("%s escolha um Pokémon!\n\n", treinador1.nome);
 	treinador1.timepokemon[0] = pkdex[escolhageral(pkdex)];
  	printf("%s escolha um Pokémon!\n\n", treinador2.nome);
  	treinador2.timepokemon[0] = pkdex[escolhageral(pkdex)];
   	
	int j = 1;
 	while(j < 6){
		printf("%s escolha outro Pokémon!\n\n", treinador1.nome);
  		treinador1.timepokemon[j] = pkdex[escolhageral(pkdex)];

    		printf("%s escolha outro Pokémon!\n\n", treinador2.nome);
  		treinador2.timepokemon[j] = pkdex[escolhageral(pkdex)];
		j++;
  	}
 	
	return 0;
}

void construirPlayer(player *treinador)
{
	treinador->dinheiro = 1000; //inicializa o dinheiro inicial do jogador, (1000   um valor tempor rio)
	
	int i;
	for(i = 0; i < 6; i++) {strcpy(treinador->timepokemon[i].nome, "placeholder");} //inicializa todos os pokemons como placeholders
	system("cls");
	
}

void printatreinador(player treinador){

	printf("Treinador: %s\n", treinador.nome);
	printf("Dinheiro: %d\n\n", treinador.dinheiro);

	for(int i = 0; i < 6; i++){
		printf("%d - %s\n", i + 1, treinador.timepokemon[i]);
	}
	printf("\n");

}


void imprimirpkdex(pkmn pokedex[]){
	
	for(int i = 0; i < 30; i++){
		
		printf("%d - %s\n", i+1, pokedex[i].nome);
		
	}
	printf("\n");
}

void printarpkmn_tochoice(pkmn pokedex[], int i){
	
	printf("NOME: %s | Nº DEX: %d\n\n", pokedex[i].nome, pokedex[i].dex);
	printf("HP: %d\n", pokedex[i].hp);
	printf("ATAQUE: %d\n", pokedex[i].ataque);
	printf("DEFESA: %d\n", pokedex[i].defesa);
	printf("ATAQUE ESPECIAL: %d\n", pokedex[i].ataqueEspecial);
	printf("DEFESA ESPECIAL: %d\n", pokedex[i].defesaEspecial);
	printf("SPEED: %d\n\n", pokedex[i].speed);
	printf("MOVES\n");
	
}

int escolhageral(pkmn pkdex[]){

    	int option;
    	int confirmacao;

	do{
  		//imprime a pokédex na tela
  		imprimirpkdex(pkdex);
	
	   	printf("Digite o número do pokémon para abrir as informações: ");
	    	scanf("%d", &option);
      		system("cls");
	
	     	printarpkmn_tochoice(pkdex, option - 1);

		printf("Digite:\n1 - Confirmar Escolha do Pokémon\n0 - Para Voltar");
  		scanf("%d", &confirmacao);
	} while(confirmacao == 0);

 	return option - 1;
 
}
