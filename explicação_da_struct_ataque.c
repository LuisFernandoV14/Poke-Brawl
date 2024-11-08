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
	
} golpe;

/* Sobre a categoria do ataque:
eu poderia colocar char categoria em vez de int categoria, porém eu acredito que ia ficar dificil de checar qual forma usar na hora do ataque 
então 1 é fisico (Atk) e 2 é especial (spAtk) 
*/


/* Sobre a prioridade:
ataques com prioridade mais alta (quick attack, extreme speed, etc) sempre vão primeiro
caso dois pokemon usem um golpe com meesma prioridade o pokemon com mais speed age primeiro
*/

/* Sobre o critico:

a maioria dos ataques tem critico 1, porém alguns tem uma taxa maior (como Leaf blade que tem critico 2)
isso não quer dizer que o dano do critico é dobrado e sim que o ataque tem 2 vezes mais chances de ser critico
uma ataque com critico 3 tem 3 vezes mais chances de ser um ataque critico também
*/
