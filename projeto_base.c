#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include "moves.h" // biblioteca que tem todos os ataques, optei por deixar separado pois eram muitas linhas de código que teriam que vir antes de começar de fato o jogo na int main

#define TOTAL_PKMNS 30
//#define TIME_SIZE 6

//funcoes----------------------------------
void construirPlayer(player *treinador);
void printatreinador(player treinador);
void imprimirpkdex(pkmn pokedex[]);
void printarpkmn_tochoice(pkmn pokedex[], int i);
int escolhageral(pkmn pkdex[]);
float listaDeFraquezas(move ataque, char tipo[]);
float pegarFraqueza(move ataque, pkmn alvo);
void dano(pkmn *agressor, pkmn *alvo, move ataque, player *treinador);
int trocarPoke(player *treinador);
void inicializa(pkmn *pokemon);
int checarcondicao(player *treinador);
void combate (pkmn *pkmn1, pkmn *pkmn2, player *treinador1, player *treinador2, move ataque1, move ataque2);
//funcoes----------------------------------

// faz o cls/clear funcionar em ambos Windows e Mac
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    // Declara e monta a Pokedex
    pkmn pkdex[TOTAL_PKMNS] = {
    {"Emboar", 1, 212, 212, 123, 65, 100, 65, 65, 0, "fogo", "luta", " "}, 
    {"Dragonite", 2, 193, 193, 134, 95, 100, 100, 80, 0, "dragão", "voador", " "},
    {"Golurk", 3, 191, 191, 124, 80, 55, 80, 55, 0, "fantasma", "terra", " "},
    {"Salamence", 4, 197, 197, 135, 80, 110, 80, 100, 0, "dragão", "voador", " "},
    {"Lapras", 5, 232, 232, 85, 80, 85, 95, 60, 0, "água", "gelo", " "},
    {"Pidgeot", 6, 185, 185, 80, 75, 70, 70, 101, 0, "normal", "voador", " "},
    {"Muk", 7, 207, 207, 105, 75, 65, 100, 50, 0, "veneno", "veneno", " "},
    {"Alakazam", 8, 157, 157, 40, 45, 135, 95, 120, 0, "psíquico", "psíquico", " "},
    {"Tyranitar", 9, 202, 202, 134, 110, 95, 100, 61, 0, "pedra", "sombrio", " "},
    {"Metagross", 10, 182, 182, 135, 130, 95, 90, 70, 0, "ferro", "psíquico", " "},
    {"Greninja", 11, 174, 174, 95, 67, 103, 71, 122, 0, "água", "sombrio", " "},
    {"Pinsir", 12, 167, 167, 125, 100, 55, 70, 85, 0, "inseto", "inseto", " "},
    {"Electivire", 13, 177, 177, 123, 67, 95, 85, 95, 0, "elétrico", "elétrico", " "},
    {"Primarina", 14, 182, 182, 74, 74, 126, 116, 60, 0, "água", "fada", " "},
    {"Honchkrow", 15, 202, 202, 125, 52, 105, 52, 71, 0, "sombrio", "voador", " "},
    {"Chandelure", 16, 162, 162, 55, 90, 145, 90, 80, 0, "fantasma", "fogo", " "},
    {"Espeon", 17, 167, 167, 65, 60, 130, 95, 110, 0, "psíquico", "psíquico", " "},
    {"Cubone", 18, 152, 152, 50, 95, 40, 50, 35, 0, "terra", "terra", " "},
    {"Ninetales de Alola", 19, 175, 175, 67, 75, 81, 100, 109, 0, "gelo", "fada", " "},
    {"Purugly", 20, 173, 173, 82, 64, 64, 59, 112, 0, "normal", "normal", " "},
    {"Nidoking", 21, 183, 183, 102, 77, 85, 75, 85, 0, "veneno", "terra", " "},
    {"Venusaur", 22, 182, 182, 82, 83, 100, 100, 80, 0, "grama", "veneno", " "},
    {"Charizard", 23, 180, 180, 84, 78, 109, 85, 100, 0, "fogo", "voador", " "},
    {"Gallade", 24, 170, 170, 125, 65, 65, 115, 80, 0, "psíquico", "luta", " "},
    {"Gardevoir", 25, 170, 170, 65, 65, 125, 115, 80, 0, "psíquico", "fada", " "},
    {"Magneton", 26, 152, 152, 60, 95, 120, 70, 70, 0, "elétrico", "ferro", " "},
    {"Decidueye", 27, 180, 180, 107, 75, 100, 100, 70, 0, "grama", "fantasma", " "},
    {"Umbreon", 28, 197, 197, 65, 110, 60, 130, 65, 0, "sombrio", "sombrio", " "},
    {"Leavanny", 29, 177, 177, 103, 80, 70, 80, 92, 0, "inseto", "grama", " "},
    {"Lucario", 30, 172, 172, 110, 70, 115, 70, 90, 0, "luta", "ferro", " "}
};

    // Declara e monta os jogadores
    player treinador1, treinador2;
    treinador1.inimigo = &treinador2;
	treinador2.inimigo = &treinador1;
	
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
		
		system(CLEAR);
		printatreinador(treinador1); // Mostra a equipe dos jogadores com os pokemon escolhidos até então
   		printatreinador(treinador2);
        
		printf("%s, escolha um Pokémon!\n\n", treinador2.nome);
        treinador2.timepokemon[j] = pkdex[escolhageral(pkdex)];
        pkdex[treinador2.timepokemon[j].dex - 1].escolhido = 1;
        
        system(CLEAR);
        
        // não precisa mais disso aqui pq a função trocarPoke tem printatreinador tbm
		// printatreinador(treinador1); 
   		// printatreinador(treinador2);
    }		
	    
	trocarPoke(&treinador1);    
	trocarPoke(&treinador2);
	    
    system("pause");
    system(CLEAR);
    
    move ataqueEscolhido1;
    move ataqueEscolhido2;
    int escolha;
    
	do{
		printf("\n%s, o que deseja fazer?\n\n1. Trocar Pokemon Ativo\n2. Atacar\n R: ", treinador1.nome);
		scanf("%d", &escolha);
		
		if(escolha == 1) { trocarPoke(&treinador1);}
		if(escolha == 2) {
			
			VezDoJogador1:
				
			if(checarcondicao(&treinador1) == 2) { // Checa pra ver se o pokemon usou outrage em algum turno
				
				if(treinador1.pokemonAtivo->buffsEdebuffs[5] <= 0){strcpy(treinador1.pokemonAtivo->efeitoTemp, " "); goto VezDoJogador1;} //medida de segurança
				
				treinador1.pokemonAtivo->buffsEdebuffs[5] -= 1;
				
				
				for(int a; a < 4; a++)
				{
					if(!strcmp(treinador1.pokemonAtivo->moveset[a].nome, "Outrage"))
					{
						printf("%s está irado! E por isso não consegue usar outro ataque.", treinador1.pokemonAtivo->nome);
						ataqueEscolhido1 = treinador1.pokemonAtivo->moveset[a];
						goto VezDoJogador2;
					}
				}
			}
		
			printf("\n\nQual ataque %s irá usar?\n\n1. %s \n2. %s\n3. %s\n 4. %s\n  R: ", treinador1.pokemonAtivo->nome, treinador1.pokemonAtivo->moveset[0], treinador1.pokemonAtivo->moveset[1], treinador1.pokemonAtivo->moveset[2], treinador1.pokemonAtivo->moveset[3]);
			scanf("%d", &escolha);
			
			ataqueEscolhido1 = treinador1.pokemonAtivo->moveset[escolha - 1];
		}		
		
		printf("\n%s, o que deseja fazer?\n\n1. Trocar Pokemon Ativo\n2. Atacar\n R: ", treinador2.nome);
		scanf("%d", &escolha);
		
		if(escolha == 1) { trocarPoke(&treinador2);}
		if(escolha == 2) {
			
			VezDoJogador2:
				
			if(checarcondicao(&treinador2) == 2) { // Checa pra ver se o pokemon usou outrage em algum turno
				
				if(treinador2.pokemonAtivo->buffsEdebuffs[5] <= 0){strcpy(treinador2.pokemonAtivo->efeitoTemp, " "); goto VezDoJogador2;} //medida de segurança
				
				treinador2.pokemonAtivo->buffsEdebuffs[5] -= 1;
				
				
				for(int a; a < 4; a++)
				{
					if(!strcmp(treinador2.pokemonAtivo->moveset[a].nome, "Outrage"))
					{
						printf("%s está irado! E por isso não consegue usar outro ataque.", treinador2.pokemonAtivo->nome);
						ataqueEscolhido1 = treinador2.pokemonAtivo->moveset[a];
						goto FimDoTurno;
					}
				}
			}
				
			printf("Qual ataque %s irá usar?\n\n1. %s \n2. %s\n3. %s\n4. %s\n  R: ", treinador2.pokemonAtivo->nome, treinador2.pokemonAtivo->moveset[0], treinador2.pokemonAtivo->moveset[1], treinador2.pokemonAtivo->moveset[2], treinador2.pokemonAtivo->moveset[3]);
			scanf("%d", &escolha);
			
			ataqueEscolhido2 = treinador2.pokemonAtivo->moveset[escolha - 1];
		}
		
		FimDoTurno:		
		combate(treinador1.pokemonAtivo, treinador2.pokemonAtivo, &treinador1, &treinador2, ataqueEscolhido1, ataqueEscolhido2);
		
	} while(1);

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
    	if (!(strcmp(treinador.timepokemon[i].nome, "placeholder"))) {printf("%d - \n", i + 1); continue;}
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
    
    
    strcpy(pokedex[i].efeitoTemp, " ");
    for(int j = 0; j < 6; j++)
    {
    	pokedex[i].buffsEdebuffs[j] = 0; //encapsulamento em C????? oh my god
	}
}

int escolhageral(pkmn pkdex[]) {
    int option;
    int confirmacao;	
	int erro;
    do {
        imprimirpkdex(pkdex);
        fflush(stdin);
		printf("Digite o número do Pokémon para abrir as informações: ");
		scanf("%d", &option);
		
   		while (option) { 
		   // Se não for um número
        	if (!isdigit(option)) {
        		system(CLEAR);
            	printf("\nOpção Inválida, por favor digite um número\n\n");
            	erro = 1;
            	break;
        	}
    	}
    	
    	if (option >= 1 && option <= 30) { erro = 0; }
    	if(erro) { continue; }

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

float pegarFraqueza(move ataque, pkmn alvo) {
	if (strcmp(alvo.tipo1, alvo.tipo2) == 0) // Esse if existe para verificar se o pokémon tem só um tipo (tepig é fogo, emboar é fogo e lutador, por exemplo)
	{ return listaDeFraquezas(ataque, alvo.tipo1); }
	
	else // Checa a efetividade do ataque contra os dois tipos do pokemon 
	{ return listaDeFraquezas(ataque, alvo.tipo1) * listaDeFraquezas(ataque, alvo.tipo2); } 
}

void dano(pkmn *agressor, pkmn *alvo, move ataque, player *treinador) { // Lembrando que alvo tem que ser ponteiro porque essa função altera diretamente o valor de hp do alvo
	
	srand(time(NULL));

	printf("\n\n%s usou %s contra %s\n", (*agressor).nome, ataque.nome, (*alvo).nome);
	
	if(rand() % 99 + 1 > ataque.accuracy) // Checa se o ataque errou ou não
	{
		printf("\n\n%s errou o ataque!\n", (*agressor).nome);
		return;
	}

	int level = 100;
	
	// Os ataques raramente dão o mesmo dano, existe uma margem de 80 a 100
	float margin = 80 + rand() % 21;
	
	// Duas fórmulas diferentes de dano, caso o ataque for físico e caso for especial
	float dano = (ataque.categoria == 0) ? (((2*100/5+2)*(*agressor).ataque*ataque.poder/(*alvo).defesa)/50) : (((2*100/5+2)*(*agressor).ataqueEspecial*ataque.poder/(*alvo).defesaEspecial)/50);
	dano *= 0.55;
	
	if(!strcmp(ataque.nome, "Psyshock")) {dano = (((2*100/5+2)*(*agressor).ataqueEspecial*ataque.poder/(*alvo).defesa)/50); dano *= 0.55; } // psyshock tem uma forma própria
	
	// Chama uma função que devolve o quão efetivo é o ataque contra o alvo e guarda o valor em uma variável
	float efetividade = pegarFraqueza(ataque, *alvo);
	
	// Em pokemon tem um negocio chamado STAB, se o  ataque for do mesmo tipo do agressor ele dá mais dano (STAB significa Same Type Attack Bonus)
	if(!(strcmp((*agressor).tipo1, ataque.tipo)) || !(strcmp((*agressor).tipo2, ataque.tipo))){ dano *= 1.5; }
	
	// Esse switch case decide se o ataque é crítico ou não, dependendo do multiplicador de crítico do ataque
	switch(ataque.critico){
		case 0: // 0 chances de ser um ataque crítico
		break;
		case 1:
			if(rand() % 16 == 14) {printf("\n\nÉ um ataque crítico!"); dano *= 2;} // uma em 16 chances de ser critico
		break;
		
		case 2:
			if(rand() % 8 == 7) {printf("\n\nÉ um ataque crítico!"); dano *= 2;} // uma em 8 chances de ser critico
		break;
		
		case 3:
			if(rand() % 4 == 1) {printf("\n\nÉ um ataque crítico!"); dano *= 2;} // uma em 4 chances de ser critico
		break;
		
		case 4:
			printf("\nÉ um ataque crítico!\n");
			dano *= 2; // 100% de ser critico
		break;
	}
	
	dano *= (margin/100);
	
	dano *= efetividade;
	
	
	int c = 0;
	
	Repetir:	
	if((*treinador).pokemonAtivo->buffsEdebuffs[6] >= 1) // tem certos ataques que acertam múltiplas vezes
	{
		printf("\nAcertou %d vezes", c + 1);
		(*treinador).pokemonAtivo->buffsEdebuffs[6] -= 1;
		c++;
		(*alvo).hp -= (int)dano;
		goto Repetir;
	}
	
	
	if((*treinador).pokemonAtivo->buffsEdebuffs[6] < 0) {
		(*treinador).pokemonAtivo->buffsEdebuffs[6] += 1;
		return; // pokemon nao ataca (acontece depois de usar giga impact, o pokemon fica 1 turno sem atacar)
	}
	
	// troca o dano do ataque do agressor pelo dano de se bater
	if(!strcmp(ataque.nome, " ")) { // (o unico ataque com o nome " " é quando pokemon se bate em confusão, e ele tem dano fixo) 
		dano = 35;
		(*agressor).hp -= dano;
		if ((*agressor).hp <= 0) {(*agressor).hp = 0; strcpy((*agressor).efeitoFixo, "desmaiado");} // (impede que o hp do alvo fique negativo e faz ele ficar desmaiado)
		return;
	} 
	
	(*alvo).hp -= (int)dano;
	
	if(!strcmp(ataque.nome, "Giga Impact")) {(*treinador).pokemonAtivo->buffsEdebuffs[6] = -1;}
	
	if (efetividade >= 2) {printf("\n%s é super efetivo contra %s!\n", ataque.nome, (*alvo).nome);}
	if (efetividade == 0) {printf("\n%s não tem efeito contra %s...\n", ataque.nome, (*alvo).nome);}
	if (efetividade == 0.5) {printf("\n%s não é muito efetivo contra %s...\n", ataque.nome, (*alvo).nome);}
	
	Fim:
	if ((*alvo).hp <= 0) {(*alvo).hp = 0; strcpy((*alvo).efeitoFixo, "desmaiado");} // (impede que o hp do alvo fique negativo e faz ele ficar desmaiado)

}

float listaDeFraquezas(move ataque, char tipo[]) {

	switch (ataque.tipo[0])
	{
		case 'n': // normal
			if (!(strcmp(tipo, "fantasma"))) {return 0;}			  
			if (!(strcmp(tipo, "pedra"))) {return 0.5;}
			if (!(strcmp(tipo, "ferro"))) {return 0.5;}
			return 1;
		break;
		
		case 'l': // luta
			if (!(strcmp(tipo, "fantasma"))) {return 0;}	
			if (!(strcmp(tipo, "veneno"))) {return 0.5;}
			if (!(strcmp(tipo, "voador"))) {return 0.5;}			  
			if (!(strcmp(tipo, "psíquico"))) {return 0.5;}
			if (!(strcmp(tipo, "inseto"))) {return 0.5;}
			if (!(strcmp(tipo, "fada"))) {return 0.5;}
			if (!(strcmp(tipo, "normal"))) {return 2;}
			if (!(strcmp(tipo, "gelo"))) {return 2;}
			if (!(strcmp(tipo, "pedra"))) {return 2;}
			if (!(strcmp(tipo, "sombrio"))) {return 2;}
			if (!(strcmp(tipo, "ferro"))) {return 2;}
			return 1;
		break;
		
		case 't': // terra
			if (!(strcmp(tipo, "voador"))) {return 0;}
			if (!(strcmp(tipo, "grama"))) {return 0.5;}			  
			if (!(strcmp(tipo, "inseto"))) {return 0.5;}
			if (!(strcmp(tipo, "pedra"))) {return 2;}
			if (!(strcmp(tipo, "fogo"))) {return 2;}
			if (!(strcmp(tipo, "elétrico"))) {return 2;}
			if (!(strcmp(tipo, "veneno"))) {return 2;}
			if (!(strcmp(tipo, "ferro"))) {return 2;}
			return 1;
		break;
		
		case 's': // sombrio
			if (!(strcmp(tipo, "luta"))) {return 0.5;}			  
			if (!(strcmp(tipo, "dragão"))) {return 0.5;}
			if (!(strcmp(tipo, "fada"))) {return 0.5;}
			if (!(strcmp(tipo, "psíquico"))) {return 2;}
			if (!(strcmp(tipo, "fantasma"))) {return 2;}
			return 1;
		break;
		
		case 'd': // dragão
			if (!(strcmp(tipo, "fada"))) {return 0;}
			if (!(strcmp(tipo, "ferro"))) {return 0.5;}			  
			if (!(strcmp(tipo, "dragão"))) {return 2;}
			return 1;
		break;
		
		case 'e': // elétrico
			if (!(strcmp(tipo, "terra"))) {return 0;}
			if (!(strcmp(tipo, "elétrico"))) {return 0.5;}			  
			if (!(strcmp(tipo, "grama"))) {return 0.5;}			  
			if (!(strcmp(tipo, "dragão"))) {return 0.5;}			  
			if (!(strcmp(tipo, "água"))) {return 2;}
			if (!(strcmp(tipo, "voador"))) {return 2;}
			return 1;
		break;
		
		case 'i': // inseto
			if (!(strcmp(tipo, "fogo"))) {return 0.5;}
			if (!(strcmp(tipo, "luta"))) {return 0.5;}
			if (!(strcmp(tipo, "terra"))) {return 0.5;}
			if (!(strcmp(tipo, "veneno"))) {return 0.5;}
			if (!(strcmp(tipo, "voador"))) {return 0.5;}
			if (!(strcmp(tipo, "fantasma"))) {return 0.5;}
			if (!(strcmp(tipo, "ferro"))) {return 0.5;}			  
			if (!(strcmp(tipo, "fada"))) {return 0.5;}			  
			if (!(strcmp(tipo, "grama"))) {return 2;}
			if (!(strcmp(tipo, "psíquico"))) {return 2;}
			if (!(strcmp(tipo, "sombrio"))) {return 2;}
			return 1;
		break;
		
		case 'á': // água
			if (!(strcmp(tipo, "água"))) {return 0.5;}			  
			if (!(strcmp(tipo, "grama"))) {return 0.5;}
			if (!(strcmp(tipo, "dragão"))) {return 0.5;}
			if (!(strcmp(tipo, "fogo"))) {return 2;}
			if (!(strcmp(tipo, "terra"))) {return 2;}
			if (!(strcmp(tipo, "pedra"))) {return 2;}
			return 1;
		break;
		
		case 'f': // fogo, fada, fantasma e ferro
			switch (ataque.tipo[2])
			{
				case 'g': // fogo
					if (!(strcmp(tipo, "fogo"))) {return 0.5;}
					if (!(strcmp(tipo, "água"))) {return 0.5;}
					if (!(strcmp(tipo, "pedra"))) {return 0.5;}
					if (!(strcmp(tipo, "dragao"))) {return 0.5;}
					if (!(strcmp(tipo, "grama"))) {return 2;}
					if (!(strcmp(tipo, "gelo"))) {return 2;}
					if (!(strcmp(tipo, "inseto"))) {return 2;}
					if (!(strcmp(tipo, "ferro"))) {return 2;}
					return 1;
				break;
				
				case 'd': //fada
					if (!(strcmp(tipo, "fogo"))) {return 0.5;}
					if (!(strcmp(tipo, "veneno"))) {return 0.5;}
					if (!(strcmp(tipo, "ferro"))) {return 0.5;}
					if (!(strcmp(tipo, "luta"))) {return 2;}
					if (!(strcmp(tipo, "fantasma"))) {return 2;}
					if (!(strcmp(tipo, "dragão"))) {return 2;}
					return 1;
				break;
				
				case 'n': //fantasma
					if (!(strcmp(tipo, "normal"))) {return 0;}
					if (!(strcmp(tipo, "sombrio"))) {return 0.5;}
					if (!(strcmp(tipo, "psíquico"))) {return 2;}
					if (!(strcmp(tipo, "fantasma"))) {return 2;}
					return 1;
				break;
				
				case 'r': // ferro
					if (!(strcmp(tipo, "fogo"))) {return 0.5;}
					if (!(strcmp(tipo, "água"))) {return 0.5;}
					if (!(strcmp(tipo, "elétrico"))) {return 0.5;}
					if (!(strcmp(tipo, "ferro"))) {return 0.5;}
					if (!(strcmp(tipo, "gelo"))) {return 2;}
					if (!(strcmp(tipo, "pedra"))) {return 2;}
					if (!(strcmp(tipo, "fada"))) {return 2;}
					return 1;
				break;	
			}
		break;
		
		case 'p': // pedra e psíquico
			switch (ataque.tipo[1])
			{
				case 'e': // pedra
					if (!(strcmp(tipo, "luta"))) {return 0.5;}			  
					if (!(strcmp(tipo, "terra"))) {return 0.5;}
					if (!(strcmp(tipo, "ferro"))) {return 0.5;}
					if (!(strcmp(tipo, "fogo"))) {return 2;}
					if (!(strcmp(tipo, "gelo"))) {return 2;}
					if (!(strcmp(tipo, "voador"))) {return 2;}
					if (!(strcmp(tipo, "inseto"))) {return 2;}
					return 1;
				break;
				
				case 's': // psíquico
					if (!(strcmp(tipo, "sombrio"))) {return 0;}
					if (!(strcmp(tipo, "psíquico"))) {return 0.5;}
					if (!(strcmp(tipo, "ferro"))) {return 0.5;}
					if (!(strcmp(tipo, "luta"))) {return 2;}
					if (!(strcmp(tipo, "veneno"))) {return 2;}
					return 1;
				break;				
			}
		break;	
		
		case 'g': // grama e gelo
			switch (ataque.tipo[2])
			{
				case 'a': // grama
					if (!(strcmp(tipo, "fogo"))) {return 0.5;}
					if (!(strcmp(tipo, "grama"))) {return 0.5;}
					if (!(strcmp(tipo, "veneno"))) {return 0.5;}
					if (!(strcmp(tipo, "voador"))) {return 0.5;}
					if (!(strcmp(tipo, "inseto"))) {return 0.5;}
					if (!(strcmp(tipo, "ferro"))) {return 0.5;}
					if (!(strcmp(tipo, "dragão"))) {return 0.5;}
					if (!(strcmp(tipo, "terra"))) {return 2;}
					if (!(strcmp(tipo, "pedra"))) {return 2;}
					if (!(strcmp(tipo, "água"))) {return 2;}			  
					return 1;
				break;
				
				case 'l': // gelo
					if (!(strcmp(tipo, "fogo"))) {return 0.5;}
					if (!(strcmp(tipo, "água"))) {return 0.5;}
					if (!(strcmp(tipo, "ferro"))) {return 0.5;}
					if (!(strcmp(tipo, "gelo"))) {return 0.5;}
					if (!(strcmp(tipo, "grama"))) {return 2;}
					if (!(strcmp(tipo, "terra"))) {return 2;}
					if (!(strcmp(tipo, "dragão"))) {return 2;}
					if (!(strcmp(tipo, "voador"))) {return 2;}
					return 1;
				break;				
			}
		break;
		
		case 'v': // voador e veneno
			switch (ataque.tipo[2])
			{
				case 'a': // voador
					if (!(strcmp(tipo, "elétrico"))) {return 0.5;}
					if (!(strcmp(tipo, "pedra"))) {return 0.5;}
					if (!(strcmp(tipo, "ferro"))) {return 0.5;}
					if (!(strcmp(tipo, "grama"))) {return 2;}
					if (!(strcmp(tipo, "luta"))) {return 2;}
					if (!(strcmp(tipo, "inseto"))) {return 2;}			  			  
					return 1;
				break;
				
				case 'n': // veneno
					if (!(strcmp(tipo, "ferro"))) {return 0;}
					if (!(strcmp(tipo, "veneno"))) {return 0.5;}
					if (!(strcmp(tipo, "terra"))) {return 0.5;}
					if (!(strcmp(tipo, "fantasma"))) {return 0.5;}
					if (!(strcmp(tipo, "pedra"))) {return 0.5;}
					if (!(strcmp(tipo, "grama"))) {return 2;}
					if (!(strcmp(tipo, "fada"))) {return 2;}
					return 1;
				break;				
			}
		break;		
	}
}

int trocarPoke(player *treinador) {
	int escolha;
	printf("\n");
	printatreinador(*treinador);
	
	printf("\n%s, digite a posição do pokémon que você quer enviar para o combate!", (*treinador).nome);
	do{
	
		printf("\n R: ");
		scanf("%d", &escolha);
		if((escolha < 1 && escolha > 6)) { 
			(printf("Não entendi... por favor escreva novamente"));
		}
		
//		if(( !(strcmp((*treinador).timepokemon[escolha].nome, (*treinador).pokemonAtivo->nome) ))) { // impede que o usuário troque pro mesmo pokemon
//			printf("%s já está em batalha", (*treinador).pokemonAtivo->nome);
//			continue;
//		}		

		fflush(stdin);
	
	} while(escolha < 1 || escolha > 6);
	
	for (int j = 0; j < 6; j++)
	{
		
		if( escolha == j + 1)
		{
			(*treinador).pokemonAtivo = &(*treinador).timepokemon[j];
			printf("\n%s enviou %s para lutar!\n\n", (*treinador).nome, (*treinador).pokemonAtivo->nome);
			inicializa((*treinador).pokemonAtivo);
			return 0;
		}
		
	}
}

void inicializa(pkmn *pokemon) {
	for(int j = 0; j < 7; j++)
    {
    	(*pokemon).buffsEdebuffs[j] = 0;
	}
	
	strcpy((*pokemon).efeitoTemp, " ");
}

int checarcondicao(player *treinador) {
	if (!strcmp((*treinador).pokemonAtivo->efeitoFixo, "desmaiado")) { return 1; }
	if (!strcmp((*treinador).pokemonAtivo->efeitoFixo, "queimando")) { queimar(treinador); }
	if (!strcmp((*treinador).pokemonAtivo->efeitoTemp, "irado")) {return 2;}
	if (!strcmp((*treinador).pokemonAtivo->efeitoTemp, "confuso")) {
		if(rand() % 3 == 1)
			{  
				(*treinador).pokemonAtivo->buffsEdebuffs[5] -= 1;
				if((*treinador).pokemonAtivo->buffsEdebuffs[5] <= 0) {(*treinador).pokemonAtivo->buffsEdebuffs[5] = 0; strcpy((*treinador).pokemonAtivo->efeitoTemp, " ");}
				return 3;
			} 
		else 
		(*treinador).pokemonAtivo->buffsEdebuffs[5] -= 1;
		if((*treinador).pokemonAtivo->buffsEdebuffs[5] <= 0) {(*treinador).pokemonAtivo->buffsEdebuffs[5] = 0; strcpy((*treinador).pokemonAtivo->efeitoTemp, " ");}
		return 0;
	}
	if (!strcmp((*treinador).pokemonAtivo->efeitoTemp, "hesitante")) {
		(*treinador).pokemonAtivo->buffsEdebuffs[5] -= 1;
		if((*treinador).pokemonAtivo->buffsEdebuffs[5] <= 0) {strcpy((*treinador).pokemonAtivo->efeitoTemp, " ");}
		return 4;
	}
	if (!strcmp((*treinador).pokemonAtivo->efeitoTemp, "protegido")) {
		
		if((*treinador).pokemonAtivo->buffsEdebuffs[5] == 1) {(*treinador).pokemonAtivo->buffsEdebuffs[5] += 1; return 5;} // primeiro turno é garantido nao tomar dano
		
		if ((*treinador).pokemonAtivo->buffsEdebuffs[5] > 1) { // pra cada turno depois do primeiro tem uma chance de 1/n de funcionar, onde n é a quantidade de turnos
			if(rand() % (3 * (*treinador).pokemonAtivo->buffsEdebuffs[5]) == 1) {
				(*treinador).pokemonAtivo->buffsEdebuffs[5] += 1;
				return 5;
			}
			strcpy((*treinador).pokemonAtivo->efeitoTemp, " ");
			(*treinador).pokemonAtivo->buffsEdebuffs[5] = 0;
			return 0;
		}
	}
	if (!strcmp((*treinador).pokemonAtivo->efeitoFixo, "congelado")) {
		(*treinador).pokemonAtivo->buffsEdebuffs[5] -= 1;
		return 6;
	}
	if (!strcmp((*treinador).pokemonAtivo->efeitoFixo, "paralisado")) {
		if(rand() % 4 == 2){ // 25 % de chance de não atacar
			return 7;	
		}
		return 0;
	
	}
	
	return 0;

	//ai aqui tinha que ter que efeitos a gente tem no jogo, que eu n sei
}

void combate (pkmn *pkmn1, pkmn *pkmn2, player *treinador1, player *treinador2, move ataque1, move ataque2) {
	
	int caminho = 1;
	
	srand(time(NULL));
	
	// checa se tem pokemon desmaiado
	if (checarcondicao(treinador1) == 1) {printf("\n%s desmaiou!\n", (*pkmn1).nome); trocarPoke(treinador1); caminho = 2;} 
	if (checarcondicao(treinador2) == 1) {printf("\n%s desmaiou!\n", (*pkmn2).nome); trocarPoke(treinador2); caminho = 3;}
	
  	if (checarcondicao(treinador1) == 3) {printf("\n%s está confuso!\n", (*pkmn1).nome); dano(pkmn1, pkmn2, confusionHit, treinador1); caminho = 2;} 
  	if (checarcondicao(treinador2) == 3) {printf("\n%s está confuso!\n", (*pkmn2).nome); dano(pkmn2, pkmn1, confusionHit, treinador2); caminho = 3;} 
  	
  	if (checarcondicao(treinador1) == 4) {printf("\n%s hesitou!\n", (*pkmn1).nome); caminho = 2;} 
  	if (checarcondicao(treinador2) == 4) {printf("\n%s hesitou!\n", (*pkmn2).nome); caminho = 3;}
	  
	if (checarcondicao(treinador1) == 5) {printf("\n%s se protegeu!\n", (*pkmn1).nome); caminho = 3;} 
  	if (checarcondicao(treinador2) == 5) {printf("\n%s se protegeu!\n", (*pkmn2).nome); caminho = 2;}   
	
	if (checarcondicao(treinador1) == 6) {printf("\n%s está congelado e não conseguiu atacar!\n", (*pkmn1).nome); caminho = 2;} 
  	if (checarcondicao(treinador2) == 6) {printf("\n%s está congelado e não conseguiu atacar!\n", (*pkmn2).nome); caminho = 3;}

	if (checarcondicao(treinador1) == 7) {printf("\n%s está paralisado e não conseguiu atacar!\n", (*pkmn1).nome); caminho = 2;} 
  	if (checarcondicao(treinador2) == 7) {printf("\n%s está paralisado e não conseguiu atacar!\n", (*pkmn2).nome); caminho = 3;}	
	
	switch (caminho) /* OBS: Isso serve para ver quem vai atacar primeiro, mas ambos atacam */
	{
		case 1: // Caso ambos pokemon estiverem vivos
		
			if (ataque1.prioridade > ataque2.prioridade) // se o ataque do p1 tiver prioridade maior
			{
				dano(pkmn1, pkmn2, ataque1, treinador1);	// agressor - alvo - ataque
				ataque1.extra(treinador1, treinador2);
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				dano(pkmn2, pkmn1, ataque2, treinador2);
				ataque2.extra(treinador2, treinador1);	
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				return;
				
			} else if (ataque1.prioridade < ataque2.prioridade) // se o ataque do p2 tiver prioridade maior
			{
				dano(pkmn2, pkmn1, ataque2, treinador2);
				ataque2.extra(treinador2, treinador1);	
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				dano(pkmn1, pkmn2, ataque1, treinador1);
				ataque1.extra(treinador1, treinador2);	
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				return;
			}
				
			// se ambos ataques tiverem mesma prioridade
			
			if ((*pkmn1).speed > (*pkmn2).speed) // se o p1 tem mais speed
			{
				dano(pkmn1, pkmn2, ataque1, treinador1);
				ataque1.extra(treinador1, treinador2);	
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				dano(pkmn2, pkmn1, ataque2, treinador2);	
				ataque2.extra(treinador2, treinador1);
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				return;
			
				
			} else if ((*pkmn1).speed < (*pkmn2).speed) // se o p2 tem mais speed
				dano(pkmn2, pkmn1, ataque2, treinador2);	
				ataque2.extra(treinador2, treinador1);
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				dano(pkmn1, pkmn2, ataque1, treinador1);
				ataque1.extra(treinador1, treinador2);	
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				return;
				
			// se ambos pokemon tiverem speed igual e os ataques tiverem prioridade igual
			
			if(rand() % 2 == 0) // vai no aleatorio
			{
				dano(pkmn1, pkmn2, ataque1, treinador1);	
				ataque1.extra(treinador1, treinador2);
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				dano(pkmn2, pkmn1, ataque2, treinador2);	
				ataque2.extra(treinador2, treinador1);
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				return;
			}
			else 
				dano(pkmn2, pkmn1, ataque2, treinador2);
				ataque2.extra(treinador2, treinador1);	
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				dano(pkmn1, pkmn2, ataque1, treinador1);
				ataque1.extra(treinador1, treinador2);	
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				return;
		
		break;
		
		case 2: // Caso o pokemon do treinador 1 morreu antes de atacar por causa de alguma condição
		
			dano(pkmn2, pkmn1, ataque2, treinador2);	
			ataque2.extra(treinador2, treinador1); 
			if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
			return;
			
		break;
		
		case 3: // Caso o pokemon do treinador 2 morreu antes de atacar por causa de alguma condição
		
			dano(pkmn1, pkmn2, ataque1, treinador1);
			ataque1.extra(treinador1, treinador2);
			if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
			return;	
			
		break;		
	}
}

// tenho que botar a funcao de trocar o pokemon pra nao funcionar caso o pokemon ativo seja escolhido novamente
// atribuir os ataques aos pokemon -> Luis Gustavo
// dar continuação a mecanica de turnos de combate (no momento tem infinitos turnos)
// criar a função dos ataques 
// terminar a função checarCondicao

/* ----- Fórmulas de cálculo de dano ----- //
((((2*LEVEL/5+2)*ATKSTAT*ATKPOWER/DEFSTAT)/50)+2) IFS: *STAB*WEAKNESS/RESISTANCE*CRITICAL*OTHER*(MARGIN/100)
((((2*LEVEL/5+2)*SPATKSTAT*ATKPOWER/SPDEFSTAT)/50)+2) IFS: *STAB*WEAKNESS/RESISTANCE*CRITICAL*OTHER*(MARGIN/100)
// ----- Fórmulas de cálculo de dano ----- */
