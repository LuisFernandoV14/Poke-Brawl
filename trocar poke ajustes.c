int trocarPoke(player *treinador) {
	
	int escolha;
	printf("\n");
	printatreinador(*treinador);
	
	Inicio:
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
			if((*treinador).rival->pokemonAtivo->hp = 0) {treinador->desmaiados += 1; if(treinador->desmaiados == TIME_SIZE) {return 0;} printf("\nEste pokemon está desmaiado!"); goto Inicio;};
			printf("\n%s enviou %s para lutar!\n\n", (*treinador).nome, (*treinador).pokemonAtivo->nome);
			inicializa((*treinador).pokemonAtivo);
			if(!strcmp(treinador->ladoDaArena->efeitoAtivo, "Stealth Rock")) {danoDaArena(treinador, 1);  return 0;}
			treinador->pokemonAtivo->hp -= checarArena(treinador);			
			return 0;
		}
		
	}
}
