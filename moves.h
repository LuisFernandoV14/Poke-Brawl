#ifndef moves_h
#define moves_h

#include <time.h> // vários ataques envolvem certa aleatoriadade, como quando será aplicado efeitos de status
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // aparente mente a time.h não funciona sem a stdlib (???)

#define TOTAL_PKMNS 30
#define TIME_SIZE 2


/* ----------- Declarações das estruturas ----------- */

struct Pokemon;
struct Ataque;
struct Player;
struct Campo;


// Estrutura do ataque
typedef struct Ataque{
    char nome[50];         // Nome do ataque
    char tipo[20];         // Tipo do ataque (Fogo, Água, etc.)
    int pp;                // Pontos de poder (PP)
    int categoria;         // 0 (Físico), 1 (Especial), 2(Status)
    int poder;             // Poder do ataque
    int prioridade;        // Prioridade do ataque
    int accuracy;          // Precisão do ataque (0-100)
    int critico;           // Multiplicador de chance de crítico
    void (*extra)(struct Player*, struct Player*); // Função que chama o efeito especial do ataque
} move;

 // Estrutura dos pokemon
typedef struct Pokemon {
    char nome[20]; // Nome do pokemon
    int dex; // Numero que o pokemon ocupa na pokedex
    int hpMaximo; // Existem funções, como queimar(), que usam o valor do hp total do pokemon, nao do atual
    int hp; // Vida atual do pokemon
    int ataque;
    int defesa;
    int ataqueEspecial;
    int defesaEspecial;
    int speed;
    int escolhido; // 0 = não foi escolhido, 1 = escolhido, o mesmo pokemon nao pode ser escolhido duas vezes
    // tipos do pokemon    
    char tipo1[10]; 
    char tipo2[10];
    // efeitos do pokemon
    char efeitoFixo[20];
    char efeitoTemp[15];
    // lista de golpes que o pokemon tem
    move moveset[4];
    int buffsEdebuffs[8]; // existem ataques que aumentam o status do pokemon, esse vetor serve como limite para cada status
    // 0 - ataque, 1 - defesa, 2 - atkEspecial, 3 - defEspecial, 4 - speed, 5 - numero de turnos para uma condição acabar, 6 - efeitos especificos de ataques
    // 7 - efeitos que afetam o campo
} pkmn;

typedef struct Campo{
	char efeitoAtivo[24];
	int rodadas;
}campo;

typedef struct Player {
    char nome[15]; // Nome dos jogadores
    pkmn timepokemon[6]; // Time de pokemon dos jogadores
    int numero; // numero do jogador, tem funções que utilizam esse numero para diferenciar o contador de ataques
    pkmn *pokemonAtivo; // ponteiro para um pkmn do time do player, esse ponteiro que vai ser o alvo dos efeitos dos ataques
    struct Player *rival;
    campo *ladoDaArena; 
    int desmaiados; // numero de pokemon desmaiados, se este numero chegar a TIME_SIZE o jogo acaba
} player;

/* ----------- Declarações das estruturas ----------- */


void F_future_sight(player *treinador1, player *treinador2);


/* ----------- Declaração das funções de efeitos de status ----------- */

void queimar(player *treinador) {
	printf("\n%s está pegando fogo!", (*treinador).pokemonAtivo->nome);
	strcpy((*treinador).pokemonAtivo->efeitoFixo, "queimando");
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

void envenenar(player *treinador){

	printf("\n%s está envenenado!", (*treinador).pokemonAtivo->nome);
	strcpy((*treinador).pokemonAtivo->efeitoFixo, "envenenado");
	(*treinador).pokemonAtivo->hp -= (*treinador).pokemonAtivo->hpMaximo / 8.0;

}

void diminuirAtaqueEspecial(player *treinador, float x){
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[2] <= -6)
	{
		printf("\nO ataque especial de %s não pode mais ser diminuido.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[2] -= 1;
	(*treinador).pokemonAtivo->ataqueEspecial -= (*treinador).pokemonAtivo->ataqueEspecial *  x / 100.0; // diminui em x% o atkespecial por estágio
	printf("\nO ataque especial de %s diminuiu!", (*treinador).pokemonAtivo->nome);
}

void diminuirDefesaEspecial(player *treinador, float x){
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[3] <= -6)
	{
		printf("\nA defesa especial de %s não pode mais ser diminuida.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[3] -= 1;
	(*treinador).pokemonAtivo->defesaEspecial -= (*treinador).pokemonAtivo->defesaEspecial *   x / 100.0; // diminui em x% a defespecial por estágio
	printf("\nA defesa especial de %s diminuiu!", (*treinador).pokemonAtivo->nome);
}

void diminuirDefesa(player *treinador, float x){
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[1] <= -6)
	{
		printf("\nA defesa de %s não pode mais ser diminuida.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[1] -= 1;
	(*treinador).pokemonAtivo->defesa -= (*treinador).pokemonAtivo->defesa *  x / 100.0; // diminui em x% a def por estágio
	printf("\nA defesa de %s diminuiu!", (*treinador).pokemonAtivo->nome);
}

void aumentarAtaque(player *treinador,  float x) {
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[0] >= 6)
	{
		printf("\nO ataque de %s não pode mais ser aumentado.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[0] += 1;
	(*treinador).pokemonAtivo->ataque += (*treinador).pokemonAtivo->ataque *  x / 100.0; // aumenta em x% o atk por estágio
	printf("\nO ataque de %s aumentou!", (*treinador).pokemonAtivo->nome);

}

void aumentarDefesa(player *treinador,  float x) {
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[1] >= 6)
	{
		printf("\nA defesa de %s não pode mais ser aumentada.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[1] += 1;
	(*treinador).pokemonAtivo->defesa += (*treinador).pokemonAtivo->defesa *  x / 100.0; // aumenta em x% a def por estágio
	printf("\nA defesa de %s aumentou!", (*treinador).pokemonAtivo->nome);

}

void diminuirAtaque(player *treinador, float x){
	
	if ((*treinador).pokemonAtivo->buffsEdebuffs[0] <= -6)
	{
		printf("\nO ataque de %s não pode mais ser diminuida.", (*treinador).pokemonAtivo->nome);
		return;
	}
	
	else
	(*treinador).pokemonAtivo->buffsEdebuffs[0] -= 1;
	(*treinador).pokemonAtivo->ataque -= (*treinador).pokemonAtivo->ataque *  x / 100.0; // diminui em x% o atk por estágio
	printf("\nO ataque de %s diminuiu!", (*treinador).pokemonAtivo->nome);
}


/* ----------- Declaração das funções de efeitos de status ----------- */



/* ----------- Declaração das funções de ataque ----------- */

void F_scald(player *treinador1, player *treinador2){
	
	srand(time(NULL));

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if( !strcmp((*treinador2).pokemonAtivo->tipo1, "fogo") || !strcmp((*treinador2).pokemonAtivo->tipo2, "fogo") ) // pokemon do tipo fogo nao podem ser queimados
	{
		return;
	}
	
	if (rand() % 100 < 30) // 30% de chance de queimar o alvo
	{
		if (strcmp((*treinador2).pokemonAtivo->efeitoFixo, " ")) // se o alvo ja estiver sendo afetado por outro efeito de status (como poison, paralyze, etc) ele não é afetado
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
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	extern int trocarPoke(player *treinador); // essa linha garante para o compilador que existe uma função trocarPoke() em um arquivo externo
	printf("\nUm rugido estremecedor fez com que %s recuasse!", (*treinador2).pokemonAtivo->nome);
	trocarPoke(treinador2); // essa linha faz o compilador ir procurar e rodar a função
}

void F_shadow_ball(player *treinador1, player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if( rand() % 100 < 20 ) // shadow ball tem 20% de chance de diminuir a defesa especial do alvo
	{
		diminuirDefesaEspecial(treinador2, 20);
	}
}

void F_earth_power(player *treinador1, player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if(rand() % 100 < 10) // earth power tem 10% de chance de diminuir a defesa especial do alvo
	{
		diminuirDefesaEspecial(treinador2, 20);
	}
}

void F_outrage(player *treinador1, player *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
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
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	diminuirAtaqueEspecial(treinador2, 40);
}

void F_blast_burn(player *treinador1, player  *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
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
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	return;
}

void F_protect(player *treinador1, player  *treinador2){
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
	strcpy((*treinador1).pokemonAtivo->efeitoTemp, "protegido");
}

void F_blizzard(player *treinador1, player  *treinador2){
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if(rand() % 10 == 7) { // 10% de chance de rodar
		congelar(treinador2);
	}
}

void F_body_slam(player *treinador1, player  *treinador2){
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	if(rand () % 3 == 1) {
		paralisar(treinador2);
	}
}

void F_arm_thrust(player *treinador1, player  *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	(*treinador1).pokemonAtivo->buffsEdebuffs[6] = rand() % 4 + 2; 
}

void F_dual_wingbeat(player *treinador1, player  *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	(*treinador1).pokemonAtivo->buffsEdebuffs[6] = 2; 
}

void F_giga_impact(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
		
		hesitar(treinador1);
	}

}

void F_zen_headbutt(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
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
		diminuirDefesa(treinador2, 20);
	}
}

void F_metal_claw(player *treinador1, player  *treinador2) {
	if(rand() % 100 < 10)
	{
		aumentarAtaque(treinador1, 20); 
	}
}

void F_fly(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	printf("\n%s alçoou voo", treinador1->pokemonAtivo->nome);
	
	strcpy(treinador1->ladoDaArena->efeitoAtivo, "ausente");
	treinador1->ladoDaArena->rodadas = 2;
}

void F_dig(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		treinador1->ladoDaArena->rodadas = 1;
		return;
	}
	
	printf("\n%s cavou um buraco!", treinador1->pokemonAtivo->nome);
	
	strcpy(treinador1->ladoDaArena->efeitoAtivo, "ausente");
	treinador1->ladoDaArena->rodadas = 3;
}

void F_rasante(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		treinador1->ladoDaArena->rodadas = 1;
		return;
	}
	
	if(treinador1->ladoDaArena->rodadas == 3) {
		printf("\n%s emergiu da terra em um poderoso ataque!", treinador1->pokemonAtivo->nome);
		strcpy(treinador1->ladoDaArena->efeitoAtivo, " ");
		treinador1->ladoDaArena->rodadas = 1;
	}
	
	if(treinador1->ladoDaArena->rodadas == 2) {
		printf("\n%s desceu em um rasante incrível", treinador1->pokemonAtivo->nome);
		strcpy(treinador1->ladoDaArena->efeitoAtivo, " ");
		treinador1->ladoDaArena->rodadas = 1;
	}
	
}

void F_acid_armor(player *treinador1, player *treinador2) {
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	
	
}

void F_stealth_rock(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
		 printf("\nteste2");

	if (!treinador1 || !treinador2 || !treinador1->ladoDaArena || !treinador2->ladoDaArena) {
    return;
	}
	
	if(!strcmp((*treinador2).ladoDaArena->efeitoAtivo, "Redemoinho"))
	{
		printf("\nPequenas pedras afiadas espalharam-se pelo campo de %s...", treinador2->nome);
		printf("\n...mas foram todas varridas por um redemoinho.\n");
		return;
	}
	
	
	if (!strcmp(treinador2->ladoDaArena->efeitoAtivo, "Tumba de Areia")) {
		printf("\nPequenas pedras afiadas espalharam-se pelo campo de %s...", treinador2->nome);
		printf("\n...mas foram todas aterradas por um caixão de areia.\n");
		return;
	}
	
	if(!strcmp((*treinador2).ladoDaArena->efeitoAtivo, "Stealth Rock"))
	{
		if ((*treinador2).ladoDaArena->rodadas < 6){
			(*treinador2).ladoDaArena->rodadas += 1;
			printf("\nPequenas pedras afiadas espalharam-se pelo campo de %s!", treinador2->nome);
			strcpy(treinador2->ladoDaArena->efeitoAtivo, "Stealth Rock");
			return;
		}
			printf("\nNão cabem mais pedras no campo de %s...", treinador2->nome);
			return;
	}
	
	if(!strcmp((*treinador2).ladoDaArena->efeitoAtivo, " "))
	{
		printf("\nPequenas pedras afiadas espalharam-se pelo campo de %s!", treinador2->nome);
		(*treinador2).ladoDaArena->rodadas = 2;
		strcpy(treinador2->ladoDaArena->efeitoAtivo, "Stealth Rock");
		printf("\n cu: %s  ", treinador2->ladoDaArena->efeitoAtivo);
		return;
	}
}

void F_whirlpool(player *treinador1, player *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	printf("\n%s foi pego em um redemoinho!", treinador2->pokemonAtivo->nome);
	
	if(treinador2->ladoDaArena->rodadas <= 1 && !strcmp(treinador2->ladoDaArena->efeitoAtivo, "Redemoinho")) {
		treinador2->ladoDaArena->rodadas = 1;
		return;
	}
	
	if(treinador2->ladoDaArena->rodadas >= 2 && !strcmp(treinador2->ladoDaArena->efeitoAtivo, "Redemoinho")) {
		treinador2->ladoDaArena->rodadas -= 1;
		return;
	}
	
	if (!strcmp(treinador2->ladoDaArena->efeitoAtivo, " ")) {
		strcpy(treinador2->ladoDaArena->efeitoAtivo, "Redemoinho");
		treinador2->ladoDaArena->rodadas = rand() % 2 + 5; // rand() % 2 pede pra função rand gerar dois numeros, como ele começa a contar de 0 então ele vai gerar ou 1 ou 0, + 4 garante que dure de 4 a 5 turno
		return;
	}
	
	if (!strcmp(treinador2->ladoDaArena->efeitoAtivo, "Stealth Rock")) {
		printf("\nUm redemoinho varreu todas as pequenas pedras do campo de %s!", treinador2->nome);
		strcpy(treinador2->ladoDaArena->efeitoAtivo, "Redemoinho");
		treinador2->ladoDaArena->rodadas = rand() % 2 + 5; 
		return;
	}
	
	if (!strcmp(treinador2->ladoDaArena->efeitoAtivo, "Tumba de Areia")) {
		printf("\nUm redemoinho varreu toda a areia do campo de %s!", treinador2->nome);
		strcpy(treinador2->ladoDaArena->efeitoAtivo, "Redemoinho");
		treinador2->ladoDaArena->rodadas = rand() % 2 + 5; 
		return;
	}
	
		
}

void F_sand_tomb(player *treinador1, player *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	printf("\n%s foi pego em um caixão de areia!", treinador2->pokemonAtivo->nome);
	
	if(treinador2->ladoDaArena->rodadas <= 1 && !strcmp(treinador2->ladoDaArena->efeitoAtivo, "Tumba de Areia")) {
		treinador2->ladoDaArena->rodadas = 1;
		return;
	}
	
	if(treinador2->ladoDaArena->rodadas >= 2 && !strcmp(treinador2->ladoDaArena->efeitoAtivo, "Tumba de Areia")) {
		treinador2->ladoDaArena->rodadas -= 1;
		return;
	}
	
	if (!strcmp(treinador2->ladoDaArena->efeitoAtivo, " ")) {
		strcpy(treinador2->ladoDaArena->efeitoAtivo, "Tumba de Areia");
		treinador2->ladoDaArena->rodadas = rand() % 2 + 5; // rand() % 2 pede pra função rand gerar dois numeros, como ele começa a contar de 0 então ele vai gerar ou 1 ou 0, + 4 garante que dure de 4 a 5 turno
		return;
	}
	
	if (!strcmp(treinador2->ladoDaArena->efeitoAtivo, "Stealth Rock")) {
		printf("\nUm caixão areia enterrou todas as pequenas pedras do campo de %s!", treinador2->nome);
		strcpy(treinador2->ladoDaArena->efeitoAtivo, "Redemoinho");
		treinador2->ladoDaArena->rodadas = rand() % 2 + 5; 
		return;
	}
	
	if (!strcmp(treinador2->ladoDaArena->efeitoAtivo, "Redemoinho")) {
		printf("\nO redemoinho foi parado por um caixão de areia no campo de %s!", treinador2->nome);
		strcpy(treinador2->ladoDaArena->efeitoAtivo, "Redemoinho");
		treinador2->ladoDaArena->rodadas = rand() % 2 + 5; 
		return;
	}
	
		
}

void F_Uturn(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	extern int trocarPoke(player *treinador); // essa linha garante para o compilador que existe uma função trocarPoke() em um arquivo externo
	trocarPoke(treinador1);

}

void F_Tailwind(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[5] <= 0)){
		(*treinador1).pokemonAtivo->speed *= 2;
		printf("\nA velocidade de %s dobrou!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[5] += 1;
	}

}

void F_Toxic(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", treinador1->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	if( !strcmp((*treinador2).pokemonAtivo->tipo1, "venenoso") || !strcmp((*treinador2).pokemonAtivo->tipo2, "venenoso") ) // pokemon do tipo fogo nao podem ser envenenado
	{
		return;
	}

	if (strcmp((*treinador2).pokemonAtivo->efeitoFixo, " "))
		{
			printf("%s não pode ser envenenado pois já está sofrendo de mais.", (*treinador2).pokemonAtivo->nome);
			return;
		}
		else
		{
			envenenar(*treinador2);
		}

}

void F_SludgeBomb(player *treinador1,  player *treinador2){
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", treinador1->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	if( !strcmp((*treinador2).pokemonAtivo->tipo1, "venenoso") || !strcmp((*treinador2).pokemonAtivo->tipo2, "venenoso") ) // pokemon do tipo poison nao podem ser envenenado
	{
		return;
	}

	srand(time(NULL));

	if (rand() % 100 < 30){ // 30% de chance de envenenar o alvo

		if (!strcmp((*treinador2).pokemonAtivo->efeitoFixo, " "))
		{
			printf("%s não pode ser envenenado pois já está sofrendo de mais.", (*treinador2).pokemonAtivo->nome);
			return;
		}
		else
		{
			envenenar(*treinador2);
		}

	}

}

void F_AcidArmor(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	aumentarDefesa(treinador1, 30);
	printf("A defesa de %s aumentou!", (*treinador1).pokemonAtivo->nome);
		//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

}

void F_SpeedSwap(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	printf("\n%s trocou de velocidade com %s!", treinador1->pokemonAtivo->nome, treinador2->pokemonAtivo->nome);
	
	int aux = (*treinador1).pokemonAtivo->speed;
	(*treinador1).pokemonAtivo->speed = (*treinador2).pokemonAtivo->speed;
	(*treinador2).pokemonAtivo->speed = aux;

}

void F_SteelBeam(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	printf("\n%s trocou tempo de vida por poder!", treinador1->pokemonAtivo->nome);
	(*treinador1).pokemonAtivo->hp /= 2;

}

void F_MeteorMash(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	srand(time(NULL));

	if(rand() % 100 < 20){

		aumentarAtaque(treinador1, 20); //mudar para as funções de buff e debuff receberem a porcentagem.	AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

	}
	
}

void F_WaterShuriken(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	(*treinador1).pokemonAtivo->buffsEdebuffs[6] = rand() % 4 + 2;

}

void F_DoubleTeam(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	for(int i = 0;  i < 4; i++){
		if((*treinador2).pokemonAtivo->moveset[i].categoria != 2) {
			(*treinador2).pokemonAtivo->moveset[1].accuracy -= 5;
		}
	}
	
	printf("\nA evasão de %s aumentou!\n", (*treinador1).pokemonAtivo->nome);
	
}

void F_FalseSwipe(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	if((*treinador2).pokemonAtivo->hp <= 0){
		(*treinador2).pokemonAtivo->hp = 1;
	}

}

void F_BulkUp(player *treinador1,  player *treinador2){

	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	aumentarAtaque(treinador1, 30);
	aumentarDefesa(treinador1, 30);

}

void F_Thunder(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	if(rand() % 100 < 30){
		paralisar(treinador2);
	}

}

void F_ThunderWave(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	paralisar(treinador2);
	
}

void F_ThunderPunch(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	srand(time(NULL));

	if(rand() % 100 < 10){
		paralisar(treinador2);
	}

}

void F_ChillingWater(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	diminuirAtaque(treinador2, 20);
	

}

void F_Moonblast(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	srand(time(NULL));
	
	if(rand() % 100 < 30){
		diminuirAtaqueEspecial(treinador2, 20);
	}

}

void F_HeatWave(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	srand(time(NULL));
	
	if(rand() % 100 < 10){
		queimar(treinador2);
	}
	
}

void F_ConfuseRay(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!");
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}

	confundir(treinador2);

}

void F_charm(player *treinador1, player *treinador2) {
	diminuirAtaque(treinador2, 30);
}

void F_Psych_Up(player *treinador1, player *treinador2) {
	for(int i = 0; i < 5; i++) {
		treinador1->pokemonAtivo->buffsEdebuffs[i] = treinador2->pokemonAtivo->buffsEdebuffs[i];
	}
	
	printf("\n%s está tão imponente quanto %s!", treinador1->pokemonAtivo->nome, treinador2->pokemonAtivo->nome);
	
	treinador1->pokemonAtivo->ataque += (treinador1->pokemonAtivo->ataque * 30 / 100) * treinador1->pokemonAtivo->buffsEdebuffs[0];
	treinador1->pokemonAtivo->defesa += (treinador1->pokemonAtivo->defesa * 30 / 100) * treinador1->pokemonAtivo->buffsEdebuffs[1];
	treinador1->pokemonAtivo->ataqueEspecial += (treinador1->pokemonAtivo->ataqueEspecial * 30 / 100) * treinador1->pokemonAtivo->buffsEdebuffs[2];
	treinador1->pokemonAtivo->defesaEspecial += (treinador1->pokemonAtivo->defesaEspecial * 30 / 100) * treinador1->pokemonAtivo->buffsEdebuffs[3];
	treinador1->pokemonAtivo->speed += (treinador1->pokemonAtivo->speed * 30 / 100) * treinador1->pokemonAtivo->buffsEdebuffs[4];
	
}

//template
void F_(player *treinador1, player  *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
}



/* ----------- Declaração das funções de ataque ----------- */


/* ----------- Declaração dos ataques ----------- */

// Declaração dos ataques de Emboar
move scald = {"Scald", "água", 15, 1, 80, 0, 100, 1, F_scald};        
move blast_burn = {"Blast Burn", "fogo", 5, 1, 150, 0, 90, 1, F_blast_burn}; 
move roar = {"Roar", "normal", 20, 0, 2, 0, 100, 1, F_roar};         
move arm_thrust = {"Arm Thrust", "luta", 20, 0, 15, 0, 100, 1, F_arm_thrust}; 

// Declaração dos ataques de Dragonite
move outrage = {"Outrage", "dragão", 10, 0, 120, 0, 100, 1, F_outrage};     
move aqua_tail = {"Aqua Tail", "água", 10, 0, 90, 0, 90, 1, F_sem_efeito};      
move wing_attack = {"Wing Attack", "voador", 35, 0, 60, 0, 100, 1, F_sem_efeito}; 
move air_cutter = {"Air Cutter", "voador", 25, 1, 60, 0, 95, 2, F_sem_efeito};   

//Declaração dos ataques de Golurk
move high_horsepower = {"High Horsepower", "terra", 10, 0, 95, 0, 95, 1, F_sem_efeito}; 
move shadow_ball = {"Shadow Ball", "fantasma", 15, 1, 80, 0, 100, 1, F_shadow_ball};         
move earth_power = {"Earth Power", "terra", 10, 1, 90, 0, 100, 1, F_earth_power};       
move protect = {"Protect", "normal", 10, 0, 2, 4, 100, 1, F_protect};                     

//Declaração dos Ataques de Salamence
move fly = {"Fly", "voador", 15, 2, 90, 0, 95, 1, F_fly};              
move rasante = {"Fly", "voador", 15, 1, 90, 0, 95, 1, F_rasante};              
// move outrage = {"Outrage", "dragão", 10, 0, 120, 0, 100, 1};      
move giga_impact = {"Giga Impact", "normal", 5, 0, 150, 0, 90, 1, F_giga_impact}; 
move dual_wingbeat = {"Dual Wingbeat", "voador", 15, 0, 40, 0, 90, 1, F_dual_wingbeat}; 

// Declaração dos Ataques de Lapras
move hydro_pump = {"Hydro Pump", "água", 5, 1, 110, 0, 80, 1, F_sem_efeito};      
move blizzard = {"Blizzard", "gelo", 5, 1, 110, 0, 70, 1, F_blizzard};        
move body_slam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1, F_body_slam};     
move whirlpool = {"Whirlpool", "água", 15, 1, 35, 0, 85, 1, F_whirlpool};       

//Declaração dos Ataques de Pidgeot
move mirror_move = {"Mirror Move", "voador", 15, 2, 0, 0, 100, 1, F_sem_efeito}; 
move u_turn = {"U-turn", "inseto", 20, 0, 70, 0, 100, 1, F_Uturn};          
move quick_attack = {"Quick Attack", "normal", 30, 0, 40, 1, 100, 1, F_sem_efeito}; 
move tailwind = {"Tailwind", "voador", 20, 2, 0, 0, 100, 1, F_Tailwind};       

// Declaração dos Ataques de Muk
move toxic = {"Toxic", "veneno", 10, 2, 0, 0, 90, 1, F_Toxic};            
move sludge_bomb = {"Sludge Bomb", "veneno", 10, 1, 90, 0, 100, 1, F_SludgeBomb}; 
move acid_armor = {"Acid Armor", "veneno", 20, 2, 0, 0, 100, 1, F_AcidArmor};  
//move giga_impact = {"Giga Impact", "normal", 5, 0, 150, 0, 90, 1};  

// Declaração dos Ataques de Alakazam
move future_sight = {"Future Sight", "psíquico", 10, 1, 120, 0, 100, 1, F_future_sight};
move future_sight_pressagio = {"presságio", "psíquico", 10, 1, 120, 0, 100, 1, F_sem_efeito}; // impede que o future sight entre em loop infinito 
move speed_swap = {"Speed Swap", "psíquico", 10, 2, 0, 0, 100, 1, F_SpeedSwap};        
move zen_headbutt = {"Zen Headbutt", "psíquico", 15, 0, 80, 0, 90, 1, F_zen_headbutt};    
move psycho_cut = {"Psycho Cut", "psíquico", 15, 0, 70, 0, 100, 2, F_sem_efeito};   

//Declaração dos Ataques de Tyranitar
move stealth_rock = {"Stealth Rock", "pedra", 10, 2, 0, 0, 100, 1, F_stealth_rock};   
move payback = {"Payback", "sombrio", 10, 0, 50, 0, 100, 1, F_sem_efeito};       
move sand_tomb = {"Sand Tomb", "terra", 15, 2, 35, 0, 85, 1, F_sand_tomb};      
move crunch = {"Crunch", "sombrio", 15, 0, 80, 0, 100, 1, F_crunch};            

//Declaração dos Ataques de Metagross
move metal_claw = {"Metal Claw", "ferro", 15, 0, 50, 0, 95, 1, F_sem_efeito};         
move psyshock = {"Psyshock", "psíquico", 10, 1, 80, 0, 100, 1, F_sem_efeito};        
move steel_beam = {"Steel Beam", "ferro", 5, 1, 140, 0, 95, 1, F_SteelBeam};         
move meteor_mash = {"Meteor Mash", "ferro", 15, 0, 90, 0, 90, 1, F_MeteorMash};       

//Declaração dos Ataques de Greninja
move water_shuriken = {"Water Shuriken", "água", 15, 1, 15, 0, 100, 1, F_WaterShuriken}; 
move cut = {"Cut", "normal", 30, 0, 50, 0, 95, 1, F_sem_efeito};                   
move aerial_ace = {"Aerial Ace", "voador", 20, 0, 60, 0, 100, 1, F_sem_efeito};     
move double_team = {"Double Team", "normal", 15, 2, 0, 0, 100, 1, F_DoubleTeam};    

//Declaração dos Ataques de Pinsir
move x_scissor = {"X-Scissor", "inseto", 15, 0, 80, 0, 100, 1, F_sem_efeito};       
move false_swipe = {"False Swipe", "normal", 10, 0, 40, 0, 100, 1, F_FalseSwipe};    
move dig = {"Dig", "terra", 10, 0, 80, 0, 100, 1, F_dig};            
move bulk_up = {"Bulk Up", "luta", 20, 2, 0, 0, 100, 1, F_BulkUp};           

//Declaração dos Ataques de Electivire
move thunder = {"Thunder", "elétrico", 10, 1, 110, 0, 70, 1, F_Thunder};         
move thunder_wave = {"Thunder Wave", "elétrico", 20, 0, 0, 0, 90, 1, F_ThunderWave};  
move thunder_punch = {"Thunder Punch", "elétrico", 15, 0, 75, 0, 100, 1, F_ThunderPunch}; 
move supercell_slam = {"Supercell Slam", "elétrico", 5, 0, 100, 0, 95, 1, F_sem_efeito}; 

//Declaração dos Ataques de Primarina
move chilling_water = {"Chilling Water", "água", 15, 1, 50, 0, 100, 1, F_ChillingWater}; 
move draining_kiss = {"Draining Kiss", "fada", 15, 1, 50, 0, 100, 1, F_sem_efeito};
move moonblast = {"Moonblast", "fada", 15, 1, 95, 0, 100, 1, F_Moonblast};         
move aqua_jet = {"Aqua Jet", "água", 30, 0, 40, 1, 100, 1, F_sem_efeito}; //água e 40           

//Declaração dos Ataques de Honchkrow
//move u_turn = {"U-turn", "inseto", 20, 0, 70, 0, 100, 1};             
move night_shade = {"Night Shade", "fantasma", 15, 1, 0, 0, 100, 1, F_sem_efeito};    
move heat_wave = {"Heat Wave", "fogo", 5, 1, 95, 0, 90, 1, F_HeatWave};            
move confuse_ray = {"Confuse Ray", "fantasma", 10, 2, 0, 0, 100, 1, F_ConfuseRay};    

//Declaração dos Ataques de Chandelure
move substitute = {"Substitute", "normal", 10, 2, 0, 0, 100, 1, F_sem_efeito};      
//move shadow_ball = {"Shadow Ball", "fantasma", 15, 1, 80, 0, 100, 1};  
move flamethrower = {"Flamethrower", "fogo", 15, 1, 90, 0, 100, 1, F_sem_efeito};    
move fire_spin = {"Fire Spin", "fogo", 15, 1, 35, 0, 85, 1, F_sem_efeito};          

//Declaração dos Ataques de Espeon
move psych_up = {"Psych Up", "normal", 15, 2, 0, 0, 100, 1, F_Psych_Up};           
move charm = {"Charm", "fada", 20, 2, 0, 0, 100, 1, F_charm};                  
//move draining_kiss = {"Draining Kiss", "fada", 15, 1, 50, 0, 100, 1};  
//move body_slam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1};        

//Declaração dos Ataques de Cubone
move Bonemerang = {"Bonemerang", "terra", 10, 0, 50, 0, 90, 1, F_sem_efeito};
move Dig = {"Dig", "terra", 10, 0, 80, 0, 100, 1, F_sem_efeito};
move Earthquake = {"Earthquake", "terra", 10, 0, 100, 0, 100, 1, F_sem_efeito};
move Sandstorm = {"Sandstorm", "pedra", 10, 2, 0, 0, 0, 0, F_sem_efeito};

//Declaração dos Ataques de Ninetales de Alola
move AuroraVeil = {"Aurora Veil", "gelo", 20, 2, 0, 0, 0, 0, F_sem_efeito};
move FreezeDry = {"Freeze-Dry", "gelo", 10, 1, 70, 0, 100, 1, F_sem_efeito};
move Hypnosis = {"Hypnosis", "psíquico", 20, 2, 0, 0, 60, 1, F_sem_efeito};
move Hail = {"Hail", "gelo", 10, 2, 0, 0, 0, 0, F_sem_efeito};

//Declaração dos Ataques de Purugly
move FakeOut = {"Fake Out", "normal", 10, 0, 40, 3, 100, 1, F_sem_efeito};
move BodySlam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1, F_sem_efeito};
move SuckerPunch = {"Sucker Punch", "sombrio", 5, 0, 70, 1, 100, 1, F_sem_efeito};
move UTurn = {"U-turn", "inseto", 20, 0, 70, 0, 100, 1, F_sem_efeito};

//Declaração dos Ataques de Nidoking
move SludgeWave = {"Sludge Wave", "veneno", 10, 1, 95, 0, 100, 1, F_sem_efeito};
move EarthPower = {"Earth Power", "terra", 10, 1, 90, 0, 100, 1, F_sem_efeito};
move IceBeam = {"Ice Beam", "gelo", 10, 1, 90, 0, 100, 1, F_sem_efeito};
move Substitute = {"Substitute", "normal", 10, 2, 0, 0, 0, 0, F_sem_efeito};

//Declaração dos Ataques de Venusaur
move Growth = {"Growth", "normal", 40, 2, 0, 0, 0, 0, F_sem_efeito};
move SludgeBomb = {"Sludge Bomb", "veneno", 10, 1, 90, 0, 100, 1, F_sem_efeito};
move GigaDrain = {"Giga Drain", "grama", 10, 1, 75, 0, 100, 1, F_sem_efeito};
move BulletSeed = {"Bullet Seed", "grama", 30, 0, 25, 0, 100, 1, F_sem_efeito};

//Declaração dos Ataques de Charizard
//move Substitute = {"Substitute", "normal", 10, 2, 0, 0, 0, 0};
move BreakingSwipe = {"Breaking Swipe", "dragão", 5, 0, 60, 0, 100, 1, F_sem_efeito};
move Hurricane = {"Hurricane", "voador", 10, 1, 110, 0, 70, 1, F_sem_efeito};
//move Earthquake = {"Earthquake", "terra", 10, 0, 100, 0, 100, 1};

//Declaração dos Ataques de Gallade
move SwordsDance = {"Swords Dance", "normal", 20, 2, 0, 0, 0, 0, F_sem_efeito};
move DrainPunch = {"Drain Punch", "luta", 10, 0, 75, 0, 100, 1, F_sem_efeito};
move PsychoCut = {"Psycho Cut", "psíquico", 10, 0, 70, 0, 100, 2, F_sem_efeito};
move LeafBlade = {"Leaf Blade", "grama", 10, 0, 90, 0, 100, 2, F_sem_efeito};

//Declaração dos Ataques de Gardevoir
move HealPulse = {"Heal Pulse", "psíquico", 10, 2, 0, 0, 0, 0, F_sem_efeito};
move Psyshock = {"Psyshock", "psíquico", 10, 1, 80, 0, 100, 1, F_sem_efeito};
move Moonblast = {"Moonblast", "fada", 10, 1, 95, 0, 100, 1, F_sem_efeito};
move CalmMind = {"Calm Mind", "psíquico", 40, 2, 0, 0, 0, 0, F_sem_efeito};

//Declaração dos Ataques de Magneton
move Thunderbolt = {"Thunderbolt", "elétrico", 10, 1, 90, 0, 100, 1, F_sem_efeito};
move GyroBall = {"Gyro Ball", "ferro", 5, 0, 0, 0, 100, 1, F_sem_efeito};
move FlashCannon = {"Flash Cannon", "ferro", 10, 1, 80, 0, 100, 1, F_sem_efeito};
move VoltSwitch = {"Volt Switch", "elétrico", 10, 1, 70, 0, 100, 1, F_sem_efeito};

//Declaração dos Ataques de Decidueye
move NastyPlot = {"Nasty Plot", "sombrio", 20, 2, 0, 0, 0, 0, F_sem_efeito};
move ShadowBall = {"Shadow Ball", "fantasma", 10, 1, 80, 0, 100, 1, F_sem_efeito};
move LeafStorm = {"Leaf Storm", "grama", 5, 1, 130, 0, 90, 1, F_sem_efeito};
move Roost = {"Roost", "voador", 10, 2, 0, 0, 0, 0, F_sem_efeito};

//Declaração dos Ataques de Umbreon
move Wish = {"Wish", "normal", 10, 2, 0, 0, 0, 0, F_sem_efeito};
move Protect = {"Protect", "normal", 10, 2, 0, 4, 0, 0, F_sem_efeito};
move FoulPlay = {"Foul Play", "sombrio", 10, 0, 95, 0, 100, 1, F_sem_efeito};
//move BodySlam = {"Body Slam", "normal", 15, 0, 85, 0, 100, 1};

//Declaração dos Ataques de Leavanny
move StruggleBug = {"Struggle Bug", "inseto", 20, 1, 50, 0, 100, 1, F_StruggleBug};
//move LeafBlade = {"Leaf Blade", "grama", 15, 0, 90, 0, 100, 2};
move XScissor = {"X-Scissor", "inseto", 15, 0, 80, 0, 100, 1, F_sem_efeito};
//move LeafStorm = {"Leaf Storm", "grama", 5, 1, 130, 0, 90, 1};

//Declaração dos Ataques de Lucario
//move SwordsDance = {"Swords Dance", "normal", 20, 2, 0, 0, 0, 0};
move MeteorMash = {"Meteor Mash", "ferro", 10, 0, 90, 0, 90, 1, F_sem_efeito};
move CloseCombat = {"Close Combat", "luta", 5, 0, 120, 0, 100, 1, F_sem_efeito};
move BulletPunch = {"Bullet Punch", "ferro", 20, 0, 40, 1, 100, 1, F_sem_efeito};

//Declaração dos Ataques gerais
move confusionHit = {" ", " ", 99, 0, 0, 100, 0, 0, F_confusao};
move falho = {"  ", " ", 99, 0, 0, 0, 0, 0, F_sem_efeito};
campo padrao2 = {" ", 1};
campo padrao1 = {" ", 1};
/* ----------- Declaração dos ataques ----------- */

/* ----------- Declaração da pokedex ----------- */

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

/* ----------- Declaração da pokedex ----------- */


void F_future_sight(player *treinador1, player *treinador2) {
	
	if(((*treinador1).pokemonAtivo->buffsEdebuffs[6] < 0)) {
		printf("\n%s está muito cansado para se mover!", (*treinador1).pokemonAtivo->nome);
		(*treinador1).pokemonAtivo->buffsEdebuffs[6] += 1;
		return;
	}
	
	static int pressagio[2] = {0, 0};
	
	if(pressagio[treinador1->numero] > 0){
		if(pressagio[treinador1->numero] == 2){
			extern int dano(pkmn *agressor, pkmn *alvo, move ataque, player *treinador);
			dano(&pkdex[7], treinador2->pokemonAtivo, future_sight_pressagio, treinador1);
			printf("\nO presságio de Alakazam se realizou!");
			pressagio[treinador1->numero] = 0;
		}
		pressagio[treinador1->numero] += 1;
	}
	
}



#endif
