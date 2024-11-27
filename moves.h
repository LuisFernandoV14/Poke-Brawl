#ifndef moves_h
#define moves_h

#include <time.h> // vários ataques envolvem certa aleatoriadade, como quando será aplicado efeitos de status
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // aparente mente a time.h não funciona sem a stdlib (???)

#define TIME_SIZE 2

/* ----------- Declarações das estruturas ----------- */

struct Pokemon;
struct Ataque;
struct Player;


// Estrutura do ataque
typedef struct Ataque{
    char nome[50];         // Nome do ataque
    char tipo[20];         // Tipo do ataque (Fogo, Água, etc.)
    int pp;                // Pontos de poder (PP)
    int categoria;         // 0 (Físico), 1 (Especial)
    int poder;             // Poder do ataque
    int prioridade;        // Prioridade do ataque
    int accuracy;          // Precisão do ataque (0-100)
    int critico;           // Multiplicador de chance de crítico
    void (*extra)(struct Player*, struct Player*);
} move;

 // Estrutura dos pokemon
typedef struct Pokemon {
    char nome[20];
    int dex;
    int hpMaximo; // existem funções, como queimar(), que usam o valor do hp total do pokemon, nao do atual
    int hp;
    int ataque;
    int defesa;
    int ataqueEspecial;
    int defesaEspecial;
    int speed;
    int escolhido; // 0 = não foi escolhido, 1 = escolhido
    char tipo1[10];
	char tipo2[10];
	char efeitoFixo[20];
	char efeitoTemp[15];
    move moveset[4];
    int buffsEdebuffs[7]; // linhas: 0 - ataque, 1 - defesa, 2 - atkEspecial, 3 - defEspecial, 4 - speed, 5 - numero de turnos para uma condição acabar, 6 - efeitos especificos de ataques
} pkmn;

typedef struct Player {
    char nome[15]; // Nome dos jogadores
    pkmn timepokemon[6]; // Pokémons dos jogadores
    pkmn *pokemonAtivo;
    struct Player *inimigo;
} player;

/* ----------- Declarações das estruturas ----------- */



/* ----------- Declaração das funções de efeitos de status ----------- */

void queimar(player *treinador) {
	
	printf("\n%s está pegando fogo!", (*treinador).pokemonAtivo->nome);
	strcpy((*treinador).pokemonAtivo->efeitoTemp, "queimando");
	(*treinador).pokemonAtivo->hp -= (*treinador).pokemonAtivo->hpMaximo / 16.0; // quando o alvo está queimando ele toma 1/16 do hp maximo de dano por turno	
}

void congelar(player *treinador) {
	printf("\n%s foi congelado!\n", (*treinador).pokemonAtivo->nome);
	strcpy((*treinador).pokemonAtivo->efeitoFixo, "congelado");
	(*treinador).pokemonAtivo->buffsEdebuffs[5] = rand() % 2 + 1; // (entre 1 e 2 turnos)
}

void paralisar(player *treinador) {
	if(strcmp((*treinador).pokemonAtivo->tipo1, "elétrico") || (strcmp((*treinador).pokemonAtivo->tipo2, "elétrico"))) {
		printf("\n%s não pode ser paralisado!\n", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	if(strcmp((*treinador).pokemonAtivo->tipo1, "terra") || (strcmp((*treinador).pokemonAtivo->tipo2, "terra"))) {
		printf("\n%s não pode ser paralisado!\n", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	printf("\n%s está paralisado!\n", (*treinador).pokemonAtivo->nome);
	strcpy((*treinador).pokemonAtivo->efeitoFixo, "paralisado");
	(*treinador).pokemonAtivo->speed = (*treinador).pokemonAtivo->speed / 2.0;
}

void confundir(player *treinador) {
	printf("\n%s está confuso!", (*treinador).pokemonAtivo->nome);
	strcpy((*treinador).pokemonAtivo->efeitoTemp, "confuso");
	(*treinador).pokemonAtivo->buffsEdebuffs[5] = rand() % 3 + 1;	
}

void hesitar(player *treinador) {
	printf("\n%s está hesitante!\n", (*treinador).pokemonAtivo->nome);
	strcpy((*treinador).pokemonAtivo->efeitoTemp, "hesitante");
	(*treinador).pokemonAtivo->buffsEdebuffs[5] = 1;
}

void diminuirAtaqueEspecial(player *treinador){
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[2] <= -6)
	{
		printf("\nO ataque especial de %s não pode mais ser diminuido.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[2] -= 1;
	(*treinador).pokemonAtivo->ataqueEspecial -= (*treinador).pokemonAtivo->ataqueEspecial *  11.0 / 100.0; // diminui em 11% o atkespecial por estágio
	printf("\nO ataque especial de %s diminuiu!", (*treinador).pokemonAtivo->nome);
}

void diminuirDefesaEspecial(player *treinador){
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[3] <= -6)
	{
		printf("\nA defesa especial de %s não pode mais ser diminuida.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[3] -= 1;
	(*treinador).pokemonAtivo->defesaEspecial -= (*treinador).pokemonAtivo->defesaEspecial *  11.0 / 100.0; // diminui em 11% a defespecial por estágio
	printf("\nA defesa especial de %s diminuiu!", (*treinador).pokemonAtivo->nome);
}

void diminuirDefesa(player *treinador){
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[1] <= -6)
	{
		printf("\nA defesa de %s não pode mais ser diminuida.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[1] -= 1;
	(*treinador).pokemonAtivo->defesa -= (*treinador).pokemonAtivo->defesa *  11.0 / 100.0; // diminui em 11% a def por estágio
	printf("\nA defesa de %s diminuiu!", (*treinador).pokemonAtivo->nome);
}

void aumentarAtaque(player *treinador) {
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[0] >= 6)
	{
		printf("\nO ataque de %s não pode mais ser aumentado.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[0] += 1;
	(*treinador).pokemonAtivo->ataque += (*treinador).pokemonAtivo->ataque *  11.0 / 100.0; // aumenta em 11% o atk por estágio
	printf("\nO ataque de %s aumentou!", (*treinador).pokemonAtivo->nome);

}

/* ----------- Declaração das funções de efeitos de status ----------- */



/* ----------- Declaração das funções de ataque ----------- */

void F_scald(player *treinador1, player *treinador2){
	
	srand(time(NULL));

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if( !strcmp((*treinador2).pokemonAtivo->tipo1, "fogo") || !strcmp((*treinador2).pokemonAtivo->tipo2, "fogo") ) // pokemon do tipo fogo nao podem ser queimados
	{
		return;
	}
	
	if (rand() % 100 < 30) // 30% de chance de queimar o alvo
	{
		if (!strcmp((*treinador2).pokemonAtivo->efeitoFixo, " ")) // se o alvo ja estiver sendo afetado por outro efeito de status (como poison, paralyze, etc) ele não é afetado
		{
			printf("%s já está sofrendo de mais.", (*treinador2).pokemonAtivo->nome);
			return;
		}
		else
		{
			strcpy((*treinador2).pokemonAtivo->efeitoFixo, "queimando");
			queimar(treinador2);
		}
	}
}

void F_roar(player *treinador1, player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	extern int trocarPoke(player *treinador); // essa linha garante para o compilador que existe uma função trocarPoke() em um arquivo externo
	printf("\nUm rugido estremecedor fez com que %s recuasse!", (*treinador2).pokemonAtivo->nome);
	trocarPoke(treinador2); // essa linha faz o compilador ir procurar e rodar a função
}

void F_shadow_ball(player *treinador1, player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if( rand() % 100 < 20 ) // shadow ball tem 20% de chance de diminuir a defesa especial do alvo
	{
		diminuirDefesaEspecial(treinador2);
	}
}

void F_earth_power(player *treinador1, player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if(rand() % 100 < 10) // earth power tem 10% de chance de diminuir a defesa especial do alvo
	{
		diminuirDefesaEspecial(treinador2);
	}
}

void F_outrage(player *treinador1, player *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if ((*treinador1).pokemonAtivo->buffsEdebuffs[5] <= 0 &&  !strcmp((*treinador1).pokemonAtivo->efeitoTemp, "irado"))
	{
		strcpy((*treinador1).pokemonAtivo->efeitoTemp, "confuso");
		confundir(treinador1);
		return;
	}
	
	if(strcmp((*treinador1).pokemonAtivo->efeitoTemp, " "))
	{
		strcpy((*treinador1).pokemonAtivo->efeitoTemp, "irado"); // a condição irado sobrepõe qualquer outra condição temporária		
		(*treinador1).pokemonAtivo->buffsEdebuffs[5] = 0;		
	}
	
	if((*treinador1).pokemonAtivo->buffsEdebuffs[5] <= 0)
	{
		(*treinador1).pokemonAtivo->buffsEdebuffs[5] = (rand() % 2) + 2; // a função rand gera 0 ou 1, o +2 garante que outrage dure 2 ou 3 turnos
		strcpy((*treinador1).pokemonAtivo->efeitoTemp, "irado");
		return;
	} 
	
	(*treinador1).pokemonAtivo->buffsEdebuffs[5] -= 1;	
}

void F_StruggleBug(player *treinador1, player  *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	diminuirAtaqueEspecial(treinador2);
}

void F_blast_burn(player *treinador1, player  *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	hesitar(treinador1);
}

void F_confusao(player *treinador1, player  *treinador2){
	printf("e por isso, se bateu em confusão!");
}

void F_sem_efeito(player *treinador1, player  *treinador2){
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	return;
}

void F_protect(player *treinador1, player  *treinador2){
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	strcpy((*treinador1).pokemonAtivo->efeitoTemp, "protegido");
}

void F_blizzard(player *treinador1, player  *treinador2){
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if(rand() % 10 == 7) { // 10% de chance de rodar
		congelar(treinador2);
	}
}

void F_body_slam(player *treinador1, player  *treinador2){
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if(rand () % 3 == 1) {
		paralisar(treinador2);
	}
}

void F_arm_thrust(player *treinador1, player  *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	(*treinador1).pokemonAtivo->buffsEdebuffs[6] = rand() % 4 + 2; 
}

void F_dual_wingbeat(player *treinador1, player  *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	(*treinador1).pokemonAtivo->buffsEdebuffs[6] = 2; 
}

void F_giga_impact(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
		
		hesitar(treinador1);
	}

}

void F_zen_headbutt(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if (rand() % 100 < 20) // 20% de chance de fazer o alvo hesitar
	{
		hesitar(treinador2);
	}
	
}

void F_crunch(player *treinador1, player  *treinador2){
	if (rand() % 100 < 20 ) {
		diminuirDefesa(treinador2);
	}
}

void F_metal_claw(player *treinador1, player  *treinador2) {
	if(rand() % 100 < 10)
	{
		aumentarAtaque(treinador1); 
	}
}

void F_fly(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if((*treinador1).pokemonAtivo->buffsEdebuffs[6] != 14){
		printf("\n%s alçoou voo", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] = 14; // a função checarcondicao() procura pelo numero 14 para ver se o pokemon está voando ou não	
	}
	
	else
	
	printf("\n%s atacou em um incrivel rajante!");
	(*treinador1).pokemonAtivo->buffsEdebuffs[6] = 0;
	
}

//template
void F_(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
}


/* ----------- Declaração das funções de ataque ----------- */


/* ----------- Declaração dos ataques ----------- */

// Declaração dos ataques de Emboar
move scald = {"Scald", "água", 15, 1, 80, 0, 100, 1, F_scald};        
move blast_burn = {"Blast Burn", "fogo", 5, 1, 150, 0, 90, 1, F_blast_burn}; 
move roar = {"Roar", "normal", 20, 0, 0, 0, 100, 1, F_roar};         
move arm_thrust = {"Arm Thrust", "luta", 20, 0, 15, 0, 100, 1, F_arm_thrust}; 

// Declaração dos ataques de Dragonite
move outrage = {"Outrage", "dragão", 10, 0, 3, 0, 100, 1, F_outrage};     
move aqua_tail = {"Aqua Tail", "água", 10, 0, 90, 0, 90, 1, F_sem_efeito};      
move wing_attack = {"Wing Attack", "voador", 35, 0, 60, 0, 100, 1, F_sem_efeito}; 
move air_cutter = {"Air Cutter", "voador", 25, 1, 60, 0, 95, 2, F_sem_efeito};   

//Declaração dos ataques de Golurk
move high_horsepower = {"High Horsepower", "terra", 10, 0, 95, 0, 95, 1, F_sem_efeito}; 
move shadow_ball = {"Shadow Ball", "fantasma", 15, 1, 80, 0, 100, 1, F_shadow_ball};         
move earth_power = {"Earth Power", "terra", 10, 1, 90, 0, 100, 1, F_earth_power};       
move protect = {"Protect", "normal", 10, 0, 0, 4, 0, 1, F_protect};                     

//Declaração dos Ataques de Salamence
move fly = {"Fly", "voador", 15, 0, 90, 0, 95, 1, F_fly};                
// move outrage = {"Outrage", "dragão", 10, 0, 120, 0, 100, 1};      
move giga_impact = {"Giga Impact", "normal", 5, 0, 150, 0, 90, 1, F_giga_impact}; 
move dual_wingbeat = {"Dual Wingbeat", "voador", 15, 0, 40, 0, 90, 1, F_dual_wingbeat}; 

// Declaração dos Ataques de Lapras
move hydro_pump = {"Hydro Pump", "água", 5, 1, 110, 0, 80, 1, F_sem_efeito};      
move blizzard = {"Blizzard", "gelo", 5, 1, 110, 0, 70, 1, F_blizzard};        
move body_slam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1, F_body_slam};     
move whirlpool = {"Whirlpool", "água", 15, 1, 35, 0, 85, 1};       

//Declaração dos Ataques de Pidgeot
move mirror_move = {"Mirror Move", "voador", 15, 0, 0, 0, 100, 1}; 
move u_turn = {"U-turn", "inseto", 20, 0, 70, 0, 100, 1};          
move quick_attack = {"Quick Attack", "normal", 30, 0, 40, 1, 100, 1}; 
move tailwind = {"Tailwind", "voador", 20, 0, 0, 0, 100, 1};       

// Declaração dos Ataques de Muk
move toxic = {"Toxic", "veneno", 10, 0, 0, 0, 90, 1};            
move sludge_bomb = {"Sludge Bomb", "veneno", 10, 1, 90, 0, 100, 1}; 
move acid_armor = {"Acid Armor", "veneno", 20, 0, 0, 0, 100, 1};  
//move giga_impact = {"Giga Impact", "normal", 5, 0, 150, 0, 90, 1};  

// Declaração dos Ataques de Alakazam
move future_sight = {"Future Sight", "psíquico", 10, 1, 120, 0, 100, 1}; 
move speed_swap = {"Speed Swap", "psíquico", 10, 0, 0, 0, 100, 1};        
move zen_headbutt = {"Zen Headbutt", "psíquico", 15, 0, 80, 0, 90, 1, F_zen_headbutt};    
move psycho_cut = {"Psycho Cut", "psíquico", 15, 0, 70, 0, 100, 2};      

//Declaração dos Ataques de Tyranitar
move stealth_rock = {"Stealth Rock", "pedra", 10, 0, 0, 0, 100, 1};   
move payback = {"Payback", "sombrio", 10, 0, 50, 0, 100, 1};          
move sand_tomb = {"Sand Tomb", "terra", 15, 0, 35, 0, 85, 1};      
move crunch = {"Crunch", "sombrio", 15, 0, 80, 0, 100, 1, F_crunch};            

//Declaração dos Ataques de Metagross
move metal_claw = {"Metal Claw", "ferro", 15, 0, 50, 0, 95, 1};         
move psyshock = {"Psyshock", "psíquico", 10, 1, 80, 0, 100, 1, F_sem_efeito};        
move steel_beam = {"Steel Beam", "ferro", 5, 1, 140, 0, 95, 1};         
move meteor_mash = {"Meteor Mash", "ferro", 15, 0, 90, 0, 90, 1};       

//Declaração dos Ataques de Greninja
move water_shuriken = {"Water Shuriken", "água", 15, 1, 15, 0, 100, 1}; 
move cut = {"Cut", "normal", 30, 0, 50, 0, 95, 1};                   
move aerial_ace = {"Aerial Ace", "voador", 20, 0, 60, 0, 100, 1};     
move double_team = {"Double Team", "normal", 15, 0, 0, 0, 100, 1};    

//Declaração dos Ataques de Pinsir
move x_scissor = {"X-Scissor", "inseto", 15, 0, 80, 0, 100, 1};       
move false_swipe = {"False Swipe", "normal", 10, 0, 40, 0, 100, 1};    
move dig = {"Dig", "terra", 10, 0, 80, 0, 100, 1};               
move bulk_up = {"Bulk Up", "luta", 20, 0, 0, 0, 100, 1};           

//Declaração dos Ataques de Electivire
move thunder = {"Thunder", "elétrico", 10, 1, 110, 0, 70, 1};         
move thunder_wave = {"Thunder Wave", "elétrico", 20, 0, 0, 0, 90, 1};  
move thunder_punch = {"Thunder Punch", "elétrico", 15, 0, 75, 0, 100, 1}; 
move supercell_slam = {"Supercell Slam", "elétrico", 5, 0, 100, 0, 95, 1}; 

//Declaração dos Ataques de Primarina
move chilling_water = {"Chilling Water", "água", 15, 1, 50, 0, 100, 1}; 
move draining_kiss = {"Draining Kiss", "fada", 15, 1, 50, 0, 100, 1};   
move moonblast = {"Moonblast", "fada", 15, 1, 95, 0, 100, 1};         
move aqua_jet = {"Aqua Jet", "água", 30, 0, 40, 1, 100, 1};           

//Declaração dos Ataques de Honchkrow
//move u_turn = {"U-turn", "inseto", 20, 0, 70, 0, 100, 1};             
move night_shade = {"Night Shade", "fantasma", 15, 1, 0, 0, 100, 1};    
move heat_wave = {"Heat Wave", "fogo", 5, 1, 95, 0, 90, 1};            
move confuse_ray = {"Confuse Ray", "fantasma", 10, 1, 0, 0, 100, 1};    

//Declaração dos Ataques de Chandelure
move substitute = {"Substitute", "normal", 10, 0, 0, 0, 100, 1};      
//move shadow_ball = {"Shadow Ball", "fantasma", 15, 1, 80, 0, 100, 1};  
move flamethrower = {"Flamethrower", "fogo", 15, 1, 90, 0, 100, 1};    
move fire_spin = {"Fire Spin", "fogo", 15, 1, 35, 0, 85, 1};          

//Declaração dos Ataques de Espeon
move psych_up = {"Psych Up", "normal", 15, 1, 0, 0, 100, 1};           
move charm = {"Charm", "fada", 20, 0, 0, 0, 100, 1};                  
//move draining_kiss = {"Draining Kiss", "fada", 15, 1, 50, 0, 100, 1};  
//move body_slam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1};        

//Declaração dos Ataques de Cubone
move Bonemerang = {"Bonemerang", "terra", 10, 0, 50, 0, 90, 1};
move Dig = {"Dig", "terra", 10, 0, 80, 0, 100, 1};
move Earthquake = {"Earthquake", "terra", 10, 0, 100, 0, 100, 1};
move Sandstorm = {"Sandstorm", "pedra", 10, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Ninetales de Alola
move AuroraVeil = {"Aurora Veil", "gelo", 20, 2, 0, 0, 0, 0};
move FreezeDry = {"Freeze-Dry", "gelo", 10, 1, 70, 0, 100, 1};
move Hypnosis = {"Hypnosis", "psíquico", 20, 2, 0, 0, 60, 1};
move Hail = {"Hail", "gelo", 10, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Purugly
move FakeOut = {"Fake Out", "normal", 10, 0, 40, 3, 100, 1};
move BodySlam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1};
move SuckerPunch = {"Sucker Punch", "sombrio", 5, 0, 70, 1, 100, 1};
move UTurn = {"U-turn", "inseto", 20, 0, 70, 0, 100, 1};

//Declaração dos Ataques de Nidoking
move SludgeWave = {"Sludge Wave", "veneno", 10, 1, 95, 0, 100, 1};
move EarthPower = {"Earth Power", "terra", 10, 1, 90, 0, 100, 1};
move IceBeam = {"Ice Beam", "gelo", 10, 1, 90, 0, 100, 1};
move Substitute = {"Substitute", "normal", 10, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Venusaur
move Growth = {"Growth", "normal", 40, 2, 0, 0, 0, 0};
move SludgeBomb = {"Sludge Bomb", "veneno", 10, 1, 90, 0, 100, 1};
move GigaDrain = {"Giga Drain", "grama", 10, 1, 75, 0, 100, 1};
move BulletSeed = {"Bullet Seed", "grama", 30, 0, 25, 0, 100, 1};

//Declaração dos Ataques de Charizard
//move Substitute = {"Substitute", "normal", 10, 2, 0, 0, 0, 0};
move BreakingSwipe = {"Breaking Swipe", "dragão", 5, 0, 60, 0, 100, 1};
move Hurricane = {"Hurricane", "voador", 10, 1, 110, 0, 70, 1};
//move Earthquake = {"Earthquake", "terra", 10, 0, 100, 0, 100, 1};

//Declaração dos Ataques de Gallade
move SwordsDance = {"Swords Dance", "normal", 20, 2, 0, 0, 0, 0};
move DrainPunch = {"Drain Punch", "luta", 10, 0, 75, 0, 100, 1};
move PsychoCut = {"Psycho Cut", "psíquico", 10, 0, 70, 0, 100, 2};
move LeafBlade = {"Leaf Blade", "grama", 10, 0, 90, 0, 100, 2};

//Declaração dos Ataques de Gardevoir
move HealPulse = {"Heal Pulse", "psíquico", 10, 2, 0, 0, 0, 0};
move Psyshock = {"Psyshock", "psíquico", 10, 1, 80, 0, 100, 1};
move Moonblast = {"Moonblast", "fada", 10, 1, 95, 0, 100, 1};
move CalmMind = {"Calm Mind", "psíquico", 40, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Magneton
move Thunderbolt = {"Thunderbolt", "elétrico", 10, 1, 90, 0, 100, 1};
move GyroBall = {"Gyro Ball", "ferro", 5, 0, 0, 0, 100, 1};
move FlashCannon = {"Flash Cannon", "ferro", 10, 1, 80, 0, 100, 1};
move VoltSwitch = {"Volt Switch", "elétrico", 10, 1, 70, 0, 100, 1};

//Declaração dos Ataques de Decidueye
move NastyPlot = {"Nasty Plot", "sombrio", 20, 2, 0, 0, 0, 0};
move ShadowBall = {"Shadow Ball", "fantasma", 10, 1, 80, 0, 100, 1};
move LeafStorm = {"Leaf Storm", "grama", 5, 1, 130, 0, 90, 1};
move Roost = {"Roost", "voador", 10, 2, 0, 0, 0, 0};

//Declaração dos Ataques de Umbreon
move Wish = {"Wish", "normal", 10, 2, 0, 0, 0, 0};
move Protect = {"Protect", "normal", 10, 2, 0, 4, 0, 0};
move FoulPlay = {"Foul Play", "sombrio", 10, 0, 95, 0, 100, 1};
//move BodySlam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1};

//Declaração dos Ataques de Leavanny
move StruggleBug = {"Struggle Bug", "inseto", 20, 1, 50, 0, 100, 1, F_StruggleBug};
//move LeafBlade = {"Leaf Blade", "grama", 15, 0, 90, 0, 100, 2};
move XScissor = {"X-Scissor", "inseto", 15, 0, 80, 0, 100, 1};
//move LeafStorm = {"Leaf Storm", "grama", 5, 1, 130, 0, 90, 1};

//Declaração dos Ataques de Lucario
//move SwordsDance = {"Swords Dance", "normal", 20, 2, 0, 0, 0, 0};
move MeteorMash = {"Meteor Mash", "ferro", 10, 0, 90, 0, 90, 1};
move CloseCombat = {"Close Combat", "luta", 5, 0, 120, 0, 100, 1};
move BulletPunch = {"Bullet Punch", "ferro", 20, 0, 40, 1, 100, 1};

move confusionHit = {" ", "normal", 99, 0, 999, 100, 0, 0, F_confusao};

/* ----------- Declaração dos ataques ----------- */


#endif
