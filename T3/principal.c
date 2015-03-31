#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* Inclui definições de TADs. */
#include "vetor.h"
#include "carta.h"
#include "memo.h"

int main(int argc, char** argv)
{
	const int ncartas = 20;
	int i;
	vetor_t *baralho = NULL;
        carta c;

	/* semente para números aleatórios */
	srand(time(NULL));

	printf("0 - criando vetor\n");
	/* inicializa TAD vetor */
	baralho = vetor_cria();

	/* insere cartas */
	for(i= 0; i < ncartas; i++){
		/* cria uma carta de valor aleatório, naipe aleatório */
		c = carta_cria( (rand()%13)+1, (rand()%4) );
		vetor_insere_carta( baralho, i, c );
		printf("carta insere %d valor '%s' naipe '%s' (baralho com %d cartas)\n",
			i, carta_valor_str(c), carta_naipe_str(c), vetor_numelem(baralho));
	}

	/* testa inserir/remover ao abrir cartas */
	printf("1 - iniciando teste do vetor\n");
	for(i= 0; i < ncartas; i++){
		c = vetor_remove_carta( baralho, i );
		if(c == NULL){
			printf("ERRO ao remover carta (pos=%d)\n", i);
			exit(-1);
		}
		carta_abre(c);
		vetor_insere_carta( baralho, i, c);
		c = vetor_acessa_carta( baralho, i );
		/* se a carta não está aberta, erro! */
		if( carta_aberta(c)  == false )
			printf("ERRO: carta %d valor '%s' naipe '%s' não foi aberta\n",
				i, carta_valor_str(c), carta_naipe_str(c));
	}

	/* remove valores do baralho e libera */
	printf("2 - destruindo vetor\n");
	for(i= 0; i < ncartas; i++){
		/* retira sempre da primeira posição do vetor */
		c = vetor_remove_carta( baralho, 0 );
		if(c == NULL){
			printf("ERRO ao remover carta (pos=%d)\n", i);
			exit(-1);
		}
		printf("carta remove %d valor '%s' naipe '%s' (baralho com %d cartas)\n",
			i, carta_valor_str(c), carta_naipe_str(c), vetor_numelem(baralho) );
		carta_destroi(c);
	}
	vetor_destroi( baralho );

	/* relatório de memória */
	memo_relatorio();

	return 0;
}
