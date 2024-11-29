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
void checarDesmaiados(player *treinador);
void construirPlayer(player *treinador);
void printatreinador(player treinador);
void imprimirpkdex(pkmn pokedex[]);
void printarpkmn_tochoice(pkmn pokedex[], int i);
int escolhageral(pkmn pkdex[]);
float listaDeFraquezas(move ataque, char tipo[]);
float pegarFraqueza(move ataque, pkmn alvo);
int dano(pkmn *agressor, pkmn *alvo, move ataque, player *treinador);
int trocarPoke(player *treinador);
void inicializa(pkmn *pokemon);
int checarcondicao(player *treinador);
void combate (pkmn *pkmn1, pkmn *pkmn2, player *treinador1, player *treinador2, move ataque1, move ataque2);
int checarArena(player *treinador);
void danoDaArena(player *treinador, int x);
//funcoes----------------------------------

// faz o cls/clear funcionar em ambos Windows e Mac
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int main() {
    setlocale(LC_ALL, "Portuguese");

	/* ----------- Atribuição dos ataques ----------- */
	{
		//moves da emboar
		pkdex[0].moveset[0]=scald;
		pkdex[0].moveset[1]=blast_burn;
		pkdex[0].moveset[2]=roar;
		pkdex[0].moveset[3]=arm_thrust;
		//moves do Dragonite
		pkdex[1].moveset[0]=outrage;
		pkdex[1].moveset[1]=aqua_tail;
		pkdex[1].moveset[2]=wing_attack;
		pkdex[1].moveset[3]=air_cutter;
		//moves do golurk
		pkdex[2].moveset[0]=high_horsepower;
		pkdex[2].moveset[1]=shadow_ball;
		pkdex[2].moveset[2]=earth_power;
		pkdex[2].moveset[3]=protect;
		//moves Salamence
		pkdex[3].moveset[0]=fly;
		pkdex[3].moveset[1]=outrage;
		pkdex[3].moveset[2]=giga_impact;
		pkdex[3].moveset[3]=dual_wingbeat;
		//moves lapras
		pkdex[4].moveset[0]=hydro_pump;
		pkdex[4].moveset[1]=blizzard;
		pkdex[4].moveset[2]=body_slam;
		pkdex[4].moveset[3]=whirlpool;
		//moves Pidgeot
		pkdex[5].moveset[0]=mirror_move;
		pkdex[5].moveset[1]=u_turn;
		pkdex[5].moveset[2]=quick_attack;
		pkdex[5].moveset[3]=tailwind;
		//moves Muk
		pkdex[6].moveset[0]=toxic;
		pkdex[6].moveset[1]=sludge_bomb;
		pkdex[6].moveset[2]=acid_armor;
		pkdex[6].moveset[3]=giga_impact;
		//moves Alakazan
		pkdex[7].moveset[0]=future_sight;
		pkdex[7].moveset[1]=speed_swap;
		pkdex[7].moveset[2]=zen_headbutt;
		pkdex[7].moveset[3]=psycho_cut;
		//moves Tyranitar
		pkdex[8].moveset[0]=stealth_rock;
		pkdex[8].moveset[1]=payback;
		pkdex[8].moveset[2]=sand_tomb;
		pkdex[8].moveset[3]=crunch;
		//moves Metagross
		pkdex[9].moveset[0]=metal_claw;
		pkdex[9].moveset[1]=psyshock;
		pkdex[9].moveset[2]=steel_beam;
		pkdex[9].moveset[3]=meteor_mash;
		//moves Greninja
		pkdex[10].moveset[0]=water_shuriken;
		pkdex[10].moveset[1]=cut;
		pkdex[10].moveset[2]=aerial_ace;
		pkdex[10].moveset[3]=double_team;
		//moves Pinsir
		pkdex[11].moveset[0]=x_scissor;
		pkdex[11].moveset[1]=false_swipe;
		pkdex[11].moveset[2]=dig;
		pkdex[11].moveset[3]=bulk_up;
		//moves Electivire
		pkdex[12].moveset[0]=thunder;
		pkdex[12].moveset[1]=thunder_wave;
		pkdex[12].moveset[2]=thunder_punch;
		pkdex[12].moveset[3]=supercell_slam;
		//moves Primarina
		pkdex[13].moveset[0]=chilling_water;
		pkdex[13].moveset[1]=draining_kiss;
		pkdex[13].moveset[2]=moonblast;
		pkdex[13].moveset[3]=aqua_jet;
		//moves Honchkrow
		pkdex[14].moveset[0]=u_turn;
		pkdex[14].moveset[1]=night_shade;
		pkdex[14].moveset[2]=heat_wave;
		pkdex[14].moveset[3]=confuse_ray;
		//moves Chadelure
		pkdex[15].moveset[0]=substitute;
		pkdex[15].moveset[1]=shadow_ball;
		pkdex[15].moveset[2]=flamethrower;
		pkdex[15].moveset[3]=fire_spin;
		//moves Espeon
		pkdex[16].moveset[0]=psych_up;
		pkdex[16].moveset[1]=charm;
		pkdex[16].moveset[2]=draining_kiss;
		pkdex[16].moveset[3]=body_slam;
		//moves Cubone
		pkdex[17].moveset[0]=Bonemerang;
		pkdex[17].moveset[1]=Dig;
		pkdex[17].moveset[2]=Earthquake;
		pkdex[17].moveset[3]=Sandstorm;
		//moves Ninetales de Alola
		pkdex[18].moveset[0]=AuroraVeil;
		pkdex[18].moveset[1]=FreezeDry;
		pkdex[18].moveset[2]=Hypnosis;
		pkdex[18].moveset[3]=Hail;
		//moves Purugly
		pkdex[19].moveset[0]=FakeOut;
		pkdex[19].moveset[1]=BodySlam;
		pkdex[19].moveset[2]=SuckerPunch;
		pkdex[19].moveset[3]=UTurn;
		//moves Nidoking
		pkdex[20].moveset[0]=SludgeWave;
		pkdex[20].moveset[1]=EarthPower;
		pkdex[20].moveset[2]=IceBeam;
		pkdex[20].moveset[3]=Substitute;
		//moves Venusaur
		pkdex[21].moveset[0]=Growth;
		pkdex[21].moveset[1]=SludgeBomb;
		pkdex[21].moveset[2]=GigaDrain;
		pkdex[21].moveset[3]=BulletSeed;
		//moves Charizard
		pkdex[22].moveset[0]=Substitute;
		pkdex[22].moveset[1]=BreakingSwipe;
		pkdex[22].moveset[2]=Hurricane;
		pkdex[22].moveset[3]=Earthquake;
		//moves Gallade
		pkdex[23].moveset[0]=SwordsDance;
		pkdex[23].moveset[1]=DrainPunch;
		pkdex[23].moveset[2]=PsychoCut;
		pkdex[23].moveset[3]=LeafBlade;
		//moves Gardervoir
		pkdex[24].moveset[0]=HealPulse;
		pkdex[24].moveset[1]=Psyshock;
		pkdex[24].moveset[2]=Moonblast;
		pkdex[24].moveset[3]=CalmMind;
		//moves Magneton
		pkdex[25].moveset[0]=Thunderbolt;
		pkdex[25].moveset[1]=GyroBall;
		pkdex[25].moveset[2]=FlashCannon;
		pkdex[25].moveset[3]=VoltSwitch;
		//moves Decidueye
		pkdex[26].moveset[0]=NastyPlot;
		pkdex[26].moveset[1]=shadow_ball;
		pkdex[26].moveset[2]=LeafStorm;
		pkdex[26].moveset[3]=Roost;
		//moves Umbreon
		pkdex[27].moveset[0]=Wish;
		pkdex[27].moveset[1]=protect;
		pkdex[27].moveset[2]=FoulPlay;
		pkdex[27].moveset[3]=body_slam;		
		//moves Leavanny		
		pkdex[28].moveset[0]=StruggleBug;
		pkdex[28].moveset[1]=LeafBlade;
		pkdex[28].moveset[2]=XScissor;
		pkdex[28].moveset[3]=LeafStorm;		
		//moves Lucario
		pkdex[29].moveset[0]=SwordsDance;
		pkdex[29].moveset[1]=MeteorMash;
		pkdex[29].moveset[2]=CloseCombat;
		pkdex[29].moveset[3]=BulletPunch;
	}
	/* ----------- Atribuição dos ataques ----------- */

//	dano muito pequeno talvez
//	checar por fogo // sera
//	checar por hesitante // sera
//	checar por ataques de status // check
//	protect infinito
//	clear // em progresso
	
	// Declara e monta os jogadores
    player treinador1, treinador2;
    treinador1.rival = &treinador2;
	treinador2.rival = &treinador1;
//	strcpy(treinador1.nome, "BATE");
//	strcpy(treinador2.nome, "APANHA");
	
    printf("Digite o nome do primeiro treinador: ");
    scanf(" %[^\n]", treinador1.nome);
	  
	  construirPlayer(&treinador1);
	  treinador1.ladoDaArena = &padrao1;
	  treinador2.ladoDaArena = &padrao2;
	  treinador1.numero = 1;
	  treinador2.numero = 2;
	  
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
    
    move ataqueEscolhido1, ataqueEscolhido2;
    int futuro1, futuro2;
    int escolha;
    
	do{
		system("pause");
		system(CLEAR);
		printf("\n\nHP do %s: %d/%d", treinador1.pokemonAtivo->nome, treinador1.pokemonAtivo->hp, treinador1.pokemonAtivo->hpMaximo);
		printf("\n\n%s, o que deseja fazer?\n\n1. Atacar\n2. Trocar Pokemon Ativo\n R: ", treinador1.nome);
		scanf("%d", &escolha);
		
		if(!strcmp(treinador1.ladoDaArena->efeitoAtivo, "ausente")) {dano(treinador1.pokemonAtivo, treinador2.pokemonAtivo, rasante, &treinador1);}
			
		if(escolha == 2) { trocarPoke(&treinador1); ataqueEscolhido1 = falho;}
		if(escolha == 1) {
			
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
		
			
			printf("\n\nQual ataque %s irá usar?\n\n1. %s \n2. %s\n3. %s\n4. %s\n  R: ", treinador1.pokemonAtivo->nome, treinador1.pokemonAtivo->moveset[0], treinador1.pokemonAtivo->moveset[1], treinador1.pokemonAtivo->moveset[2], treinador1.pokemonAtivo->moveset[3]);
			scanf("%d", &escolha);
			
			ataqueEscolhido1 = treinador1.pokemonAtivo->moveset[escolha - 1];
			
		
			if(!strcmp(ataqueEscolhido1.nome, "Fly")) {ataqueEscolhido1.extra(&treinador1, &treinador2); ataqueEscolhido1 = falho;}
			
			//isso aqui faz o ataque "future sight" bater so daqui a dois turnos	
			if(futuro1 > 0) {future_sight.extra(&treinador1, &treinador2); futuro1--;}
			if(!strcmp(ataqueEscolhido1.nome, "Future Sight")) {futuro1 = 2;}
							
			if (!strcmp(ataqueEscolhido1.nome, "Protect" )) {ataqueEscolhido1.extra(&treinador1, &treinador2); checarcondicao(&treinador1);} // protege o usuário
			if (!strcmp(treinador2.pokemonAtivo->efeitoTemp, "protegido" )) {ataqueEscolhido1 = falho; checarcondicao(&treinador2); printf("\n%s se protegeu!", treinador2.pokemonAtivo->nome);} // faz o ataque falhar caso o pokemon inimigo esteja protegido
	
		}		
		
		system("pause");
		system(CLEAR);
		printf("\n\n%s HP: %d/%d", treinador2.pokemonAtivo->nome, treinador2.pokemonAtivo->hp, treinador2.pokemonAtivo->hpMaximo);
		printf("\n%s, o que deseja fazer?\n\n1. Atacar\n2. Trocar Pokemon Ativo\n R: ", treinador2.nome);
		scanf("%d", &escolha);
		
		if(!strcmp(treinador1.ladoDaArena->efeitoAtivo, "ausente")) {dano(treinador1.pokemonAtivo, treinador2.pokemonAtivo, rasante, &treinador1);}
		
		if(escolha == 2) { trocarPoke(&treinador2);ataqueEscolhido2 = falho;}
		if(escolha == 1) {
			
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
			
			//isso aqui faz o ataque "future sight" bater so daqui a dois turnos	
			if(futuro2 > 0) {future_sight.extra(&treinador2, &treinador1); futuro2--;}
			if(!strcmp(ataqueEscolhido2.nome, "Future Sight")) {futuro2 = 2;}
			
			if (!strcmp(ataqueEscolhido2.nome, "Protect" )) {ataqueEscolhido1.extra(&treinador2, &treinador1); checarcondicao(&treinador2);} // protege o usuário
			if (!strcmp(treinador1.pokemonAtivo->efeitoTemp, "protegido" )) {ataqueEscolhido2 = falho; checarcondicao(&treinador1); printf("\n%s se protegeu!", treinador1.pokemonAtivo->nome);} // faz o ataque falhar caso o pokemon inimigo esteja protegido
		
		}
		
		if(!strcmp(treinador1.ladoDaArena->efeitoAtivo,"ausente")) {ataqueEscolhido2 = falho;}
		if(!strcmp(treinador2.ladoDaArena->efeitoAtivo,"ausente")) {ataqueEscolhido1 = falho;}
		
		FimDoTurno:		
		combate(treinador1.pokemonAtivo, treinador2.pokemonAtivo, &treinador1, &treinador2, ataqueEscolhido1, ataqueEscolhido2);
		checarArena(&treinador1);
		checarArena(&treinador2);
		
		checarDesmaiados(&treinador1);
		checarDesmaiados(&treinador2);
	} while(treinador1.desmaiados < 6 || treinador2.desmaiados < 6 );

    return 0;
}

void construirPlayer(player *treinador) {
    for (int i = 0; i < TIME_SIZE; i++) {
        strcpy(treinador->timepokemon[i].nome, "placeholder");
    }
    
    treinador->desmaiados = 0;
	
	system(CLEAR);
	
}

void checarDesmaiados(player *treinador) {
	for(int j = 0; j < TIME_SIZE; j++) {
		if(treinador->timepokemon[j].hp <= 0){
			treinador->desmaiados += 1;
		}
	}
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

int dano(pkmn *agressor, pkmn *alvo, move ataque, player *treinador) { // Lembrando que alvo tem que ser ponteiro porque essa função altera diretamente o valor de hp do alvo
	
	srand(time(NULL));
	
	// printf("\n   fiu fiu: %s %s %s ", (*agressor).nome, ataque.nome, (*alvo).nome);
	
	if(!strcmp(ataque.nome, "Night Shade")) {(*alvo).hp -= 100; return 0;} // night shade sempre dá 100 de dano
	
  	if (checarcondicao(treinador) == 4) {printf("\n%s hesitou!", (*agressor).nome); return 0;}
	if (checarcondicao(treinador) == 6) {printf("\n%s está congelado e não conseguiu atacar!", (*agressor).nome); return 0;} 
	if (checarcondicao(treinador) == 7) {printf("\n%s está paralisado e não conseguiu atacar!", (*agressor).nome); return 0;} 
		
	if(!strcmp(ataque.nome, "  ")) {return 0;}
	if(!strcmp(ataque.nome, "Protect")) {printf("\n%s errou o ataque!", (*agressor).nome); return 0;} 
	
	printf("\n\n%s usou %s contra %s\n", (*agressor).nome, ataque.nome, (*alvo).nome);
	
	
	if(rand() % 99 + 1 > ataque.accuracy) // Checa se o ataque errou ou não
	{
		printf("\n\n%s errou o ataque!\n", (*agressor).nome);
		if(!strcmp(ataque.nome,"Supercell Slam")) { (*agressor).hp /=2; }
		return 0;
	}

	int level = 100;
	
	// Os ataques raramente dão o mesmo dano, existe uma margem de 80 a 100
	float margin = 80 + rand() % 21;
	
	// fórmulas diferentes de dano, caso o ataque for físico, de status ou especial
	float dano;
	if (ataque.categoria == 0) {dano = (((2*100/5+2)*(*agressor).ataque*ataque.poder/(*alvo).defesa)/50)+2;}
	if (ataque.categoria == 1) {dano = (((2*100/5+2)*(*agressor).ataqueEspecial*ataque.poder/(*alvo).defesaEspecial)/50)+2;}
	if (ataque.categoria == 2) {dano = 0; ataque.extra(treinador, (*treinador).rival); return 0;} // se o ataque for de status (categoria 2) ele nao dá dano
	dano *= 0.55;
	
	
	// troca o dano do ataque do agressor pelo dano de se bater caso ele esteja confuso //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	if(!strcmp(ataque.nome, " ")) { // (o unico ataque com o nome " " é quando pokemon se bate em confusão, e ele tem dano fixo) 
		dano = 35;
		(*agressor).hp -= dano;
		if ((*agressor).hp <= 0) {(*agressor).hp = 0; strcpy((*agressor).efeitoFixo, "desmaiado");} // (impede que o hp do alvo fique negativo e faz ele ficar desmaiado)
		return dano;
	} 
	
	if(!strcmp(ataque.nome, "Psyshock")) {dano = (((2*100/5+2)*(*agressor).ataqueEspecial*ataque.poder/(*alvo).defesa)/50+2); dano *= 0.55; } // psyshock tem uma formula própria //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	
	// Chama uma função que devolve o quão efetivo é o ataque contra o alvo e guarda o valor em uma variável
	float efetividade = pegarFraqueza(ataque, *alvo);
	
	// Em pokemon tem um negocio chamado STAB, se o  ataque for do mesmo tipo do agressor ele dá mais dano (STAB significa Same Type Attack Bonus)
	if(!(strcmp((*agressor).tipo1, ataque.tipo)) || !(strcmp((*agressor).tipo2, ataque.tipo))){ dano *= 1.5; }
	
	// Esse switch case decide se o ataque é crítico ou não, dependendo do multiplicador de crítico do ataque
	switch(ataque.critico){
		case 0: // 0 chances de ser um ataque crítico
			dano *= 1;
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
	
	ataque.extra(treinador, (*treinador).rival); //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	 printf("\nteste");
	
	if((*treinador).pokemonAtivo->buffsEdebuffs[6] >= 1 ) { // tem certos ataques que acertam múltiplas vezes //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		
		for(int c = 1; c <= (*treinador).pokemonAtivo->buffsEdebuffs[6]; c++)
		{
			printf("\nAcertou %d vezes!", c);
			dano *= 2;
		}
		
		(*treinador).pokemonAtivo->buffsEdebuffs[6] = 0;
	}
	
	if((*treinador).pokemonAtivo->buffsEdebuffs[6] < 0) { //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		(*treinador).pokemonAtivo->buffsEdebuffs[6] += 1;
		return 0; // pokemon nao ataca (acontece depois de usar giga impact, o pokemon fica 1 turno sem atacar)
	}
	
	(*alvo).hp -= (int)dano;
	
	if(!strcmp(ataque.nome, "Giga Impact")) {(*treinador).pokemonAtivo->buffsEdebuffs[6] = -1;} //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	
	if (efetividade >= 2) {printf("\n%s é super efetivo contra %s!\n", ataque.nome, (*alvo).nome);}
	if (efetividade == 0) {printf("\n%s não tem efeito contra %s...\n", ataque.nome, (*alvo).nome);}
	if (efetividade == 0.5) {printf("\n%s não é muito efetivo contra %s...\n", ataque.nome, (*alvo).nome);}
	
	if(!strcmp(ataque.nome, "Draining Kiss")) {printf("\n%s recuperou vida!", (*agressor).nome); (*agressor).hp += dano * 3 / 4;}
	
	Fim:
	if ((*alvo).hp <= 0) {(*alvo).hp = 0; strcpy((*alvo).efeitoFixo, "desmaiado");} // (impede que o hp do alvo fique negativo e faz ele ficar desmaiado)
	return dano;

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
	return 1;
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
		
	} while(escolha < 1 || TIME_SIZE > 6);
	
	for (int j = 0; j < TIME_SIZE; j++)
	{
		
		if( escolha == j + 1)
		{
			(*treinador).pokemonAtivo = &(*treinador).timepokemon[j];
			printf("\n%s enviou %s para lutar!\n\n", (*treinador).nome, (*treinador).pokemonAtivo->nome);
			inicializa((*treinador).pokemonAtivo);
			printf("\n%s", treinador->ladoDaArena->efeitoAtivo);
			printf("\n%d", treinador->ladoDaArena->rodadas);
			if(!strcmp(treinador->ladoDaArena->efeitoAtivo, "Stealth Rock")) {danoDaArena(treinador, 1);  return 0;}
			treinador->pokemonAtivo->hp -= checarArena(treinador);			
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
	if (!strcmp((*treinador).pokemonAtivo->efeitoTemp, "hesitante")) {
		(*treinador).pokemonAtivo->buffsEdebuffs[5] -= 1;
		if((*treinador).pokemonAtivo->buffsEdebuffs[5] <= 0) {strcpy((*treinador).pokemonAtivo->efeitoTemp, " ");}
		return 4;
	}
	if (!strcmp((*treinador).pokemonAtivo->efeitoFixo, "queimando")) { queimar(treinador); }
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
	if (!strcmp((*treinador).pokemonAtivo->efeitoTemp, "irado")) {return 2;}
	if (!strcmp((*treinador).pokemonAtivo->efeitoTemp, "protegido")) {
		
		if((*treinador).pokemonAtivo->buffsEdebuffs[5] == 0) {strcpy((*treinador).pokemonAtivo->efeitoTemp, " "); return 0;}
		
		if((*treinador).pokemonAtivo->buffsEdebuffs[5] == 1) {(*treinador).pokemonAtivo->buffsEdebuffs[5] += 1; printf("\n%s usou protect!", (*treinador).pokemonAtivo->nome); return 5;} // primeiro turno é garantido nao tomar dano
		
		if ((*treinador).pokemonAtivo->buffsEdebuffs[5] > 1) { // pra cada turno depois do primeiro tem uma chance de 1/n de funcionar, onde n é a quantidade de turnos
			if(rand() % (3 * (*treinador).pokemonAtivo->buffsEdebuffs[5]) == 1) {
				(*treinador).pokemonAtivo->buffsEdebuffs[5] += 1;
				printf("\n%s usou protect!", (*treinador).pokemonAtivo->nome);
				return 5;
			}
			strcpy((*treinador).pokemonAtivo->efeitoTemp, " ");
			printf("%s tentou usar protect, mas falhou...", (*treinador).pokemonAtivo->nome);
			(*treinador).pokemonAtivo->buffsEdebuffs[5] = 0;
			return 0;
		}
	}

	//ai aqui tinha que ter que efeitos a gente tem no jogo, que eu n sei
	return 0;
}

void combate (pkmn *pkmn1, pkmn *pkmn2, player *treinador1, player *treinador2, move ataque1, move ataque2) {
	
	int caminho = 1;
	
	srand(time(NULL));
	
	static int pressagio1 = 0;
	static int pressagio2 = 0;
	if(!strcmp(ataque1.nome, "Future Sight")) {printf("\n%s pressagiou %s...", pkmn1->nome, pkmn2->nome); ataque1 = falho;};
	if(!strcmp(ataque2.nome, "Future Sight")) {printf("\n%s pressagiou %s...", pkmn2->nome, pkmn1->nome); ataque2 = falho;};
	 
	if(!strcmp(treinador1->ladoDaArena->efeitoAtivo, "ausente")) {printf("\n%s errou o ataque...", pkmn2->nome, pkmn1->nome); ataque2 = falho;};
	if(!strcmp(treinador2->ladoDaArena->efeitoAtivo, "ausente")) {printf("\n%s errou o ataque...", pkmn1->nome, pkmn1->nome); ataque1 = falho;};

	if(!strcmp(ataque1.nome, "Mirror Move")) {printf("\n%s copiou o ataque de %s!", pkmn1->nome, pkmn2->nome); ataque1 = ataque2;} 
	if(!strcmp(ataque2.nome, "Mirror Move")) {printf("\n%s copiou o ataque de %s!", pkmn1->nome, pkmn2->nome); ataque2 = ataque1;} 

	if (checarcondicao(treinador1) == 1) {printf("\n%s desmaiou!\n", (*pkmn1).nome); trocarPoke(treinador1); caminho = 2;} 
	if (checarcondicao(treinador2) == 1) {printf("\n%s desmaiou!\n", (*pkmn2).nome); trocarPoke(treinador2); caminho = 3;}
	
  	if (checarcondicao(treinador1) == 3) {printf("\n%s está confuso!\n", (*pkmn1).nome); dano(pkmn1, pkmn2, confusionHit, treinador1); caminho = 2;} 
  	if (checarcondicao(treinador2) == 3) {printf("\n%s está confuso!\n", (*pkmn2).nome); dano(pkmn2, pkmn1, confusionHit, treinador2); caminho = 3;} 
	
	switch (caminho) /* OBS: Isso serve para ver quem vai atacar primeiro, mas ambos atacam */
	{
		case 1: // Caso ambos pokemon estiverem vivos
		
			if (ataque1.prioridade > ataque2.prioridade) // se o ataque do p1 tiver prioridade maior
			{
				dano(pkmn1, pkmn2, ataque1, treinador1);	// agressor - alvo - ataque
				// ataque1.extra(treinador1, treinador2);
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				dano(pkmn2, pkmn1, ataque2, treinador2);
				// ataque2.extra(treinador2, treinador1);	
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				return;
				
			} else if (ataque1.prioridade < ataque2.prioridade) // se o ataque do p2 tiver prioridade maior
			{
				dano(pkmn2, pkmn1, ataque2, treinador2);
				// ataque2.extra(treinador2, treinador1);	
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				dano(pkmn1, pkmn2, ataque1, treinador1);
				// ataque1.extra(treinador1, treinador2);	
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				return;
			}
				
			// se ambos ataques tiverem mesma prioridade
			
			if ((*pkmn1).speed > (*pkmn2).speed) // se o p1 tem mais speed
			{
				dano(pkmn1, pkmn2, ataque1, treinador1);
				// ataque1.extra(treinador1, treinador2);	
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				dano(pkmn2, pkmn1, ataque2, treinador2);	
				// ataque2.extra(treinador2, treinador1);
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				return;
			
				
			} else if ((*pkmn1).speed < (*pkmn2).speed) // se o p2 tem mais speed
				dano(pkmn2, pkmn1, ataque2, treinador2);	
				// ataque2.extra(treinador2, treinador1);
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				dano(pkmn1, pkmn2, ataque1, treinador1);
				// ataque1.extra(treinador1, treinador2);	
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				return;
				
			// se ambos pokemon tiverem speed igual e os ataques tiverem prioridade igual
			
			if(rand() % 2 == 0) // vai no aleatorio
			{
				dano(pkmn1, pkmn2, ataque1, treinador1);	
				// ataque1.extra(treinador1, treinador2);
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				dano(pkmn2, pkmn1, ataque2, treinador2);	
				// ataque2.extra(treinador2, treinador1);
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				return;
			}
			else 
				dano(pkmn2, pkmn1, ataque2, treinador2);
				// ataque2.extra(treinador2, treinador1);	
				if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
				dano(pkmn1, pkmn2, ataque1, treinador1);
				// ataque1.extra(treinador1, treinador2);	
				if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
				return;
		
		break;
		
		case 2: // Caso o pokemon do treinador 1 morreu antes de atacar por causa de alguma condição
		
			dano(pkmn2, pkmn1, ataque2, treinador2);	
			// ataque2.extra(treinador2, treinador1); 
			if (checarcondicao(treinador1) == 1) {printf("%s desmaiou!", (*pkmn1).nome); trocarPoke(treinador1); return;}
			return;
			
		break;
		
		case 3: // Caso o pokemon do treinador 2 morreu antes de atacar por causa de alguma condição
		
			dano(pkmn1, pkmn2, ataque1, treinador1);
			// ataque1.extra(treinador1, treinador2);
			if (checarcondicao(treinador2) == 1) {printf("%s desmaiou!", (*pkmn2).nome); trocarPoke(treinador2); return;}
			return;	
			
		break;		
	}
}

int checarArena(player *treinador) {
	
		move caixao = sand_tomb;
		move redemoinho = whirlpool;
		
		if(!strcmp((*treinador).ladoDaArena->efeitoAtivo, " ")) { return 0; }
		if(!strcmp((*treinador).ladoDaArena->efeitoAtivo, "Stealth Rock")) { return 0; }
		
		if(!strcmp((*treinador).ladoDaArena->efeitoAtivo, "Tumba de Areia")) {
			
		if ((*treinador).ladoDaArena->rodadas > 1) {
				danoDaArena(treinador, 3);
				(*treinador).ladoDaArena->rodadas -= 1;
				
				if ((*treinador).ladoDaArena->rodadas <= 1){
					strcpy((*treinador).ladoDaArena->efeitoAtivo, " ");		
					(*treinador).ladoDaArena->rodadas = 1;
				}
				return 0;
			}
		}
		
		if(!strcmp((*treinador).ladoDaArena->efeitoAtivo, "Redemoinho")) {
			
			if ((*treinador).ladoDaArena->rodadas > 1) {
				danoDaArena(treinador, 2);
				(*treinador).ladoDaArena->rodadas -= 1;
				
				if ((*treinador).ladoDaArena->rodadas <= 1){
					strcpy((*treinador).ladoDaArena->efeitoAtivo, " ");		
					(*treinador).ladoDaArena->rodadas = 1;
				}
				return 0;
			}
		}
	return 0;
}

void danoDaArena(player *treinador, int x) {
	if (x == 1) {	
		if ((*treinador).ladoDaArena->rodadas == 1) {return;}
		
		if ((*treinador).ladoDaArena->rodadas >= 2){
			printf("\n%s pisou em pequenas pedras afiadas e se machucou!", treinador->pokemonAtivo->nome);
			(*treinador).pokemonAtivo->hp -= (*treinador).pokemonAtivo->hpMaximo / (32.0 / (2.0 * (*treinador).ladoDaArena->rodadas));			 
		return;
		}
	return;
	}
	
	if (x == 2) {
		if ((*treinador).ladoDaArena->rodadas == 1) {return;}
		
		printf("\nUm redemoinho atingiu %s!\n", (*treinador).pokemonAtivo->nome);
		
		if(!strcmp(treinador->pokemonAtivo->efeitoTemp, "Protect")) {return;}
		
		if(rand() % 99 + 1 > 85) // Checa se o ataque errou ou não
			{
				printf(" e surfou nas ondas!\n");
				return;
			}
	
		float margin = 80 + rand() % 21;
		float dano = ((2*100/5+2)*treinador->rival->pokemonAtivo->ataqueEspecial*35/(*treinador).pokemonAtivo->defesaEspecial/50)+2;
		dano *= 0.55;
		dano *= (margin/100);
		
		treinador->pokemonAtivo->hp -= dano;
	}
	
	if (x == 3) {
		if ((*treinador).ladoDaArena->rodadas == 1) {return;}
		
		printf("\nUm caixão de areia sufocou %s!\n", (*treinador).pokemonAtivo->nome);
		
		if(!strcmp(treinador->pokemonAtivo->efeitoTemp, "Protect")) {return;}
		
		if(rand() % 99 + 1 > 85) // Checa se o ataque errou ou não
			{
				printf(" ...mas nada segura %s!\n", treinador->pokemonAtivo->nome);
				return;
			}
	
		float margin = 80 + rand() % 21;
		float dano = ((2*100/5+2)*treinador->rival->pokemonAtivo->ataqueEspecial*35/(*treinador).pokemonAtivo->defesaEspecial/50)+2;
		dano *= 0.55;
		dano *= (margin/100);
		
		treinador->pokemonAtivo->hp -= dano;
	}
	
	return;
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
