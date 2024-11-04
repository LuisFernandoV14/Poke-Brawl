#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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


/* fun  es */
void construirPlayer(player *treinador); //foi o jeito que eu pensei de fazer um metodo construtor em C
//void pokedex(pkmn pkdex[]); 
void adicionarNaPokedex(pkmn pokemon, pkmn pkdex[]); //adiciona um pokemon na lista pokedex
void printarpkmn(pkmn pokemon, pkmn vetor[]); 
void printatreinador(player treinador);
/* fun  es */

int main()
{
	setlocale(LC_ALL, "Portuguese");
	// declara e monta a pokedex (ta funcionando ja)
	pkmn pkdex[30];
	
	// declara e monta os players (ta funcionando ja)
	player treinador1; 
	player treinador2;

	printf("Digite o nome do treinador: ");
	fflush(stdin);
	fgets(treinador1.nome, 20, stdin);
	construirPlayer(&treinador1);

	printf("Digite o nome do treinador: ");
	fflush(stdin);
	fgets(treinador2.nome, 20, stdin);
	construirPlayer(&treinador2);
	
	printatreinador(treinador1);
	printatreinador(treinador2);
	
	// declara, adiciona na pokedex e printa o nome dos pokemon (n ta funcionando por algum motivo maligno)
	
	pkmn umbreon = {"Umbreon", 2, 20, 14, "nenhum"};
	pkmn gardevoir = {"Gardevoir", 1, 15, 10, "nenhum"};
	pkmn garchomp = {"Garchomp", 9, 25, 9, "nenhum"};

	adicionarNaPokedex(umbreon, pkdex);
	adicionarNaPokedex(gardevoir, pkdex);
	adicionarNaPokedex(garchomp, pkdex);

	printf("\n\n");
	printarpkmn(umbreon, pkdex);
	printarpkmn(gardevoir, pkdex);
	printarpkmn(garchomp, pkdex);
	
	return 0;
}

void construirPlayer(player *treinador)
{
	treinador->dinheiro = 1000; //inicializa o dinheiro inicial do jogador, (1000   um valor tempor rio)
	
	int i;
	for(i = 0; i < 6; i++) {strcpy(treinador->timepokemon[i].nome, "placeholder");} //inicializa todos os pokemons como placeholders
	system("cls");
	
}

void adicionarNaPokedex(pkmn pokemon, pkmn pkdex[])
{
	int i;
	
	for(i = 0; i < 24; i++) //tamanho provis rio pq eu n sei quantos pokemon a gente tem lol	
	{
		if(pkdex[i].dex == 0) 
		{ 
			strcpy(pkdex[i].nome, pokemon.nome);
			pkdex[i].dex = pokemon.dex;
			pkdex[i].hp = pokemon.hp;
			pkdex[i].ataque = pokemon.ataque;
			pkdex[i].defesa = pokemon.defesa;
			pkdex[i].ataqueEspecial = pokemon.ataqueEspecial;
			pkdex[i].defesaEspecial = pokemon.defesaEspecial;
			pkdex[i].speed = pokemon.speed;
			return;
			
		}
	
		/* (teste) printf("\n%d", pkdex[i].dex); (teste)* /
	}


}

void printatreinador(player treinador){

	printf("Treinador: %s\n", treinador.nome);
	printf("Dinheiro: %d\n\n", treinador.dinheiro);

}

void printarpkmn(pkmn pokemon, pkmn vetor[])
{
	int i;
	for(i = 0; i < 30; i++)
	{
		if(pokemon.dex == vetor[i].dex)
		{
			printf("O pokemon na posi  o %d  : %s \n", pokemon.dex, pokemon.nome);
			fflush(stdout);
		}
	}

	
}

/* Sla q q é isso menor
void pokedex(pkmn pkdex[])
{
	pkmn *listadepokemons = (pkmn *)malloc(sizeof(int) * 6); //tamanho provis rio pq eu n sei quantos pokemon a gente tem lol
	int i;
	for(i = 0; i < 30; i++) { listadepokemons[i].dex = 0; /* (teste) printf("%d\n", listadepokemons[i]);  }
	/* printf("\n\n"); 

	
	pkdex = listadepokemons;
}
*/
