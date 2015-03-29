#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vetor.h"
#include "carta.h"
#include "memo.h"

#define TAM 52
int i;
struct vetor {
	/* TODO aqui */
	/* defina os campos da TAD vetor aqui */

	carta* baralho;   /* baralho - vetor de cartas */
	int n;		/* número de cartas */
};

vetor_t* vetor_cria(void)
{
	struct vetor *vet = (struct vetor*)memo_aloca(sizeof(struct vetor));
	vet->n = 0;
	for(i=0; i<=TAM; i++){
        vet->baralho[i]=memo_aloca(sizeof(struct carta*));
	}
	return vet;
}

void vetor_destroi(vetor_t* vet)
{
    memo_libera(vet->baralho);
    memo_libera(vet);
}

int vetor_numelem(vetor_t *vet)
{   int i;
    while(vet->baralho[i]==NULL){
        vet->n++;
        i++;
    }
	return vet->n;
}
/* insere uma carta no vetor vet, na posição indice.
 * se a carta já existe nessa posição, as cartas subsequentes avançam uma
 * posição.
 * se o vetor não tem mais espaço (cheio), utiliza realloc.
 */
void vetor_insere_carta(vetor_t *vet, int indice, carta c)
{
    if(vet->baralho[indice] != NULL){
        vet->baralho[indice]= c;
    }
}

carta vetor_remove_carta(vetor_t *vet, int indice)
{
    int i;
    carta* c = (struct carta*) memo_aloca(sizeof(carta));
    c = vet->baralho[indice];
    for(i=; i>indice; i--){
        vet->baralho[i--];
    }
	return c;
}

carta vetor_acessa_carta(vetor_t *vet, int indice)
{
	return vet->baralho[indice];
}

bool vetor_valido(vetor_t *vet)
{   if(vet==NULL){
        return false;
    }else{
        return true;
    }
}
