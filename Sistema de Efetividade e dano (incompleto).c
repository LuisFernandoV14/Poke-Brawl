#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

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
	char tipo1[10];
	char tipo2[10];
	char efeitoFixo[20];
	
} pkmn;

typedef struct ataque
{
	int pp;
	int categoria;
	int poder;
	int prioridade; 
	int accuracy; 
	int critico; 
	char nome[25];
	char tipo[10];
} move;


// ((((2*LEVEL/5+2)*ATKSTAT*ATKPOWER/DEFSTAT)/50)+2) IFS: *STAB*WEAKNESS/RESISTANCE*CRITICAL*OTHER*(MARGIN/100)

// ((((2*LEVEL/5+2)*SPATKSTAT*ATKPOWER/SPDEFSTAT)/50)+2) IFS: *STAB*WEAKNESS/RESISTANCE*CRITICAL*OTHER*(MARGIN/100)

// funcao dar dano

float checarFraquezas(move ataque, char tipo[])
{

	switch (ataque.tipo[0])
	{
		case 'n': // normal
			if (!(strcmp(tipo, "fantasma"))) {return 0;}			  
			if (!(strcmp(tipo, "pedra"))) {return 0.5;}
			if (!(strcmp(tipo, "aço"))) {return 0.5;}
			return 1;
		break;
		
		case 'l': // luta
			if (!(strcmp(tipo, "fantasma"))) {return 0;}	
			if (!(strcmp(tipo, "veneno"))) {return 0.5;}
			if (!(strcmp(tipo, "voador"))) {return 0.5;}			  
			if (!(strcmp(tipo, "psiquico"))) {return 0.5;}
			if (!(strcmp(tipo, "inseto"))) {return 0.5;}
			if (!(strcmp(tipo, "fada"))) {return 0.5;}
			if (!(strcmp(tipo, "normal"))) {return 2;}
			if (!(strcmp(tipo, "gelo"))) {return 2;}
			if (!(strcmp(tipo, "pedra"))) {return 2;}
			if (!(strcmp(tipo, "sombrio"))) {return 2;}
			if (!(strcmp(tipo, "aço"))) {return 2;}
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
			if (!(strcmp(tipo, "aço"))) {return 2;}
			return 1;
		break;
		
		case 's': // sombrio
			if (!(strcmp(tipo, "luta"))) {return 0.5;}			  
			if (!(strcmp(tipo, "dragão"))) {return 0.5;}
			if (!(strcmp(tipo, "fada"))) {return 0.5;}
			if (!(strcmp(tipo, "psiquico"))) {return 2;}
			if (!(strcmp(tipo, "fantasma"))) {return 2;}
			return 1;
		break;
		
		case 'd': // dragão
			if (!(strcmp(tipo, "fada"))) {return 0;}
			if (!(strcmp(tipo, "aço"))) {return 0.5;}			  
			if (!(strcmp(tipo, "dragão"))) {return 2;}
			return 1;
		break;
		
		case 'e': // elétrico
			if (!(strcmp(tipo, "terra"))) {return 0;}
			if (!(strcmp(tipo, "elétrico"))) {return 0.5;}			  
			if (!(strcmp(tipo, "grama"))) {return 0.5;}			  
			if (!(strcmp(tipo, "dragão"))) {return 0.5;}			  
			if (!(strcmp(tipo, "agua"))) {return 2;}
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
			if (!(strcmp(tipo, "aço"))) {return 0.5;}			  
			if (!(strcmp(tipo, "fada"))) {return 0.5;}			  
			if (!(strcmp(tipo, "grama"))) {return 2;}
			if (!(strcmp(tipo, "psiquico"))) {return 2;}
			if (!(strcmp(tipo, "sombrio"))) {return 2;}
			return 1;
		break;
		
		
		case 'f': // fogo, fada e fantasma
			switch (ataque.tipo[2])
			{
				case 'g': // fogo
					if (!(strcmp(tipo, "fogo"))) {return 0.5;}
					if (!(strcmp(tipo, "agua"))) {return 0.5;}
					if (!(strcmp(tipo, "pedra"))) {return 0.5;}
					if (!(strcmp(tipo, "dragao"))) {return 0.5;}
					if (!(strcmp(tipo, "grama"))) {return 2;}
					if (!(strcmp(tipo, "gelo"))) {return 2;}
					if (!(strcmp(tipo, "inseto"))) {return 2;}
					if (!(strcmp(tipo, "aço"))) {return 2;}
					return 1;
				break;
				
				case 'd': //fada
					if (!(strcmp(tipo, "fogo"))) {return 0.5;}
					if (!(strcmp(tipo, "veneno"))) {return 0.5;}
					if (!(strcmp(tipo, "aço"))) {return 0.5;}
					if (!(strcmp(tipo, "luta"))) {return 2;}
					if (!(strcmp(tipo, "fantasma"))) {return 2;}
					if (!(strcmp(tipo, "dragão"))) {return 2;}
					return 1;
				break;
				
				case 'n': //fantasma
					if (!(strcmp(tipo, "normal"))) {return 0;}
					if (!(strcmp(tipo, "sombrio"))) {return 0.5;}
					if (!(strcmp(tipo, "psiquico"))) {return 2;}
					if (!(strcmp(tipo, "fantasma"))) {return 2;}
					return 1;
				break;
			}
		break;
		
		case 'p': // pedra e psiquico
			switch (ataque.tipo[1])
			{
				case 'e': // pedra
					if (!(strcmp(tipo, "luta"))) {return 0.5;}			  
					if (!(strcmp(tipo, "terra"))) {return 0.5;}
					if (!(strcmp(tipo, "aço"))) {return 0.5;}
					if (!(strcmp(tipo, "fogo"))) {return 2;}
					if (!(strcmp(tipo, "gelo"))) {return 2;}
					if (!(strcmp(tipo, "voador"))) {return 2;}
					if (!(strcmp(tipo, "inseto"))) {return 2;}
					return 1;
				break;
				
				case 's': // psiquico
					if (!(strcmp(tipo, "sombrio"))) {return 0;}
					if (!(strcmp(tipo, "psiquico"))) {return 0.5;}
					if (!(strcmp(tipo, "aço"))) {return 0.5;}
					if (!(strcmp(tipo, "luta"))) {return 2;}
					if (!(strcmp(tipo, "veneno"))) {return 2;}
					return 1;
				break;				
			}
		break;
		
		case 'a': // agua e aço
			switch (ataque.tipo[2])
			{
				case 'u': // agua
					if (!(strcmp(tipo, "agua"))) {return 0.5;}			  
					if (!(strcmp(tipo, "grama"))) {return 0.5;}
					if (!(strcmp(tipo, "dragão"))) {return 0.5;}
					if (!(strcmp(tipo, "fogo"))) {return 2;}
					if (!(strcmp(tipo, "terra"))) {return 2;}
					if (!(strcmp(tipo, "pedra"))) {return 2;}
					return 1;
				break;
				
				case 'o': // aço
					if (!(strcmp(tipo, "fogo"))) {return 0.5;}
					if (!(strcmp(tipo, "agua"))) {return 0.5;}
					if (!(strcmp(tipo, "elétrico"))) {return 0.5;}
					if (!(strcmp(tipo, "aço"))) {return 0.5;}
					if (!(strcmp(tipo, "gelo"))) {return 2;}
					if (!(strcmp(tipo, "pedra"))) {return 2;}
					if (!(strcmp(tipo, "fada"))) {return 2;}
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
					if (!(strcmp(tipo, "aço"))) {return 0.5;}
					if (!(strcmp(tipo, "dragão"))) {return 0.5;}
					if (!(strcmp(tipo, "terra"))) {return 2;}
					if (!(strcmp(tipo, "pedra"))) {return 2;}
					if (!(strcmp(tipo, "agua"))) {return 2;}			  
					return 1;
				break;
				
				case 'l': // gelo
					if (!(strcmp(tipo, "fogo"))) {return 0.5;}
					if (!(strcmp(tipo, "agua"))) {return 0.5;}
					if (!(strcmp(tipo, "aço"))) {return 0.5;}
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
					if (!(strcmp(tipo, "aço"))) {return 0.5;}
					if (!(strcmp(tipo, "grama"))) {return 2;}
					if (!(strcmp(tipo, "luta"))) {return 2;}
					if (!(strcmp(tipo, "inseto"))) {return 2;}			  			  
					return 1;
				break;
				
				case 'n': // veneno
					if (!(strcmp(tipo, "aço"))) {return 0;}
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

float pegarFraqueza(move ataque, pkmn alvo)
{
	if (!(strcmp(alvo.tipo1, alvo.tipo2))) {return checarFraquezas(ataque, alvo.tipo1);}
	
	return checarFraquezas(ataque, alvo.tipo1) * checarFraquezas(ataque, alvo.tipo2); 
}

void dano(pkmn agressor, pkmn *alvo, move ataque)
{
	srand(time(NULL));

	printf("\n%s usou %s contra %s\n", agressor.nome, ataque.nome, (*alvo).nome);
	
	int level = 100;
	
	float margin = 80 + rand() % 21;
	// printf("\n\nMARGEM: %f\n\n", margin); (tava dando erro aqui mas eu ja resolvi)
	
	float dano = ((((2*100/5+2)*agressor.ataque*ataque.poder/(*alvo).defesa)/50)+2);
	
	float efetividade;
	efetividade = pegarFraqueza(ataque, *alvo);
	// printf("\n\EFETIVIDADE: %f\n\n", efetividade); (testes)
	
	// printf("\n\nDANO PADRAO: %f\n\n", dano); (testes)
	
	if(!(strcmp(agressor.tipo1, ataque.tipo)) || !(strcmp(agressor.tipo2, ataque.tipo))){	
	dano *= 1.5;
	}
	
	// printf("\n\nDANO STAB: %f\n\n", dano); (testes)
	
	switch(ataque.critico){
		case 1:
			if(rand() % 16 == 14) {dano *= 2;} // uma em 16 chances de ser critico
		break;
		
		case 2:
			if(rand() % 8 == 7) {dano *= 2;} // uma em 8 chances de ser critico
		break;
		
		case 3:
			if(rand() % 4 == 1) {dano *= 2;} // uma em 4 chances de ser critico
		break;
		
		case 4:
			dano *= 2; // 100% de ser critico
		break;
	}
	// printf("\n\nDANO CRITICO: %f\n\n", dano); (testes)
	
	dano *= (margin/100);
	// printf("\n\nDANO MARGEM: %f\n\n", dano); (testes)
	
	dano *= efetividade;
	// printf("\n\nDANO EFETIVIDADE: %f\n\n", dano); (testes)
	
	if (efetividade >= 2) {printf("\n\n%s é super efetivo contra %s!\n", ataque.nome, (*alvo).nome);}
	if (efetividade == 0) {printf("\n\n%s não tem efeito contra %s...\n", ataque.nome, (*alvo).nome);}
	if (efetividade == 0.5) {printf("\n\n%s não é muito efetivo contra %s...\n", ataque.nome, (*alvo).nome);}
	(*alvo).hp -= (int)dano;
	
	if ((*alvo).hp == 0)
	{
		strcpy((*alvo).efeitoFixo, "derrotado");	
	}

}


int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	pkmn leavanny = {"Leavanny", 29, 75, 103, 80, 70, 80, 92, "grama", "inseto"};
	pkmn emboar = {"Emboar", 1, 110, 123, 65, 100, 65, 65, "fogo", "lutador"};
	
	move blastBurn = {10, 1, 150, 0, 90, 1, "Blast Burn", "fogo"};
	move leafBlade = {10, 1, 90, 0, 100, 2, "Leaf Blade", "grama"};
	
	printf("\nHP da Leavanny: %d\n", leavanny.hp);
	printf("\nHP do Emboar: %d\n", emboar.hp);
	
	dano(leavanny, &emboar, leafBlade);
	dano(emboar, &leavanny, blastBurn);
	
	printf("\nHP da Leavanny: %d\n", leavanny.hp);
	printf("\nHP do Emboar: %d\n", emboar.hp);
	
}

