#include <assert.h>

#include "jogo.h"
#include "memo.h"

#define SOLIT_MAGICO 0x50717
#define DESTRUIDO 0x80000000

bool 
jogo_valido(jogo sol)
{
	if (sol == NULL || sol->magico != SOLIT_MAGICO) {
		return false;
	}
	return true;
}

jogo 
jogo_cria(void)
{
	jogo		sol;
	int		i;

	sol = (jogo) memo_aloca(sizeof(jogo_t));
	assert(sol != NULL);
	sol->magico = SOLIT_MAGICO;

	sol->monte = pilha_cria();
	sol->descartes = pilha_cria();
	for (i = 0; i < 4; i++) {
		sol->ases[i] = pilha_cria();
	}
	for (i = 0; i < 7; i++) {
		sol->pilhas[i] = pilha_cria();
	}
	sol->tela = tela_cria();

	return sol;
}

static void 
jogo_destroi_pilha(pilha p)
{
	while (!pilha_vazia(p)) {
		carta_destroi(pilha_remove_carta(p));
	}
	pilha_destroi(p);
}

void 
jogo_destroi(jogo sol)
{
	int		i;
	assert(jogo_valido(sol));
	jogo_destroi_pilha(sol->monte);
	jogo_destroi_pilha(sol->descartes);
	for (i = 0; i < 4; i++) {
		jogo_destroi_pilha(sol->ases[i]);
	}
	for (i = 0; i < 7; i++) {
		jogo_destroi_pilha(sol->pilhas[i]);
	}
	tela_destroi(sol->tela);
	sol->magico |= DESTRUIDO;
	memo_libera(sol);
}

/* acessores */
tela 
jogo_tela(jogo sol)
{
	assert(jogo_valido(sol));
	return sol->tela;
}

pilha 
jogo_monte(jogo sol)
{
	assert(jogo_valido(sol));
	return sol->monte;
}

pilha 
jogo_descartes(jogo sol)
{
	assert(jogo_valido(sol));
	return sol->descartes;
}

pilha 
jogo_ases(jogo sol, int i)
{
	assert(jogo_valido(sol));
	assert(i >= 0 && i < 4);
	return sol->ases[i];
}

pilha 
jogo_pilha(jogo sol, int i)
{
	assert(jogo_valido(sol));
	assert(i >= 0 && i < 7);
	return sol->pilhas[i];
}

void abre_carta(jogo sol, pilha p){ // ainda nao utilizada, vai economizar codigo nas funçoes abaixo
	if(!pilha_vazia(p)){
		carta c = pilha_remove_carta(p);
		carta_abre(c);
		pilha_insere_carta(p,c);
	}
	jogo_desenha(sol);
}

void monte_para_descarte(jogo sol){ // pronta
	carta c = pilha_remove_carta(jogo_monte(sol));
	carta_abre(c);
	pilha_insere_carta(jogo_descartes(sol),c);
	jogo_desenha(sol);
}

void descarte_para_monte(jogo sol){ //pronta
	while(!pilha_vazia(jogo_descartes(sol))){
		carta c = pilha_remove_carta(jogo_descartes(sol));
		carta_fecha(c);
		pilha_insere_carta(jogo_monte(sol), c);
		jogo_desenha(sol);
	}
}

void descarte_para_ases(jogo sol){
	int npdestino;
	printw("\nDigite a pilha de destino de AS");
	npdestino = tela_le(sol->tela);
	npdestino= npdestino-49;
	tela_atualiza(sol->tela);
	if(npdestino != 0 && npdestino != 1 && npdestino != 2 && npdestino != 3){
		printw("\nJogada Invalida");
		tela_atualiza(sol->tela);
		printw("\nDigite uma pilha de 1 a 4");
		npdestino = tela_le(sol->tela);
		npdestino= npdestino-49;
	}
	pilha p = jogo_ases(sol,npdestino);
	carta c = pilha_remove_carta(jogo_descartes(sol));
	if(pilha_vazia(p)){
		if(carta_valor(c) == 1){
			pilha_insere_carta(jogo_ases(sol,npdestino),c);
			jogo_desenha(sol);
			return;
	}else{
		printw ("\nJogada Invalida");
		}
	}
	if(!pilha_vazia(p)){
		carta as = pilha_remove_carta(jogo_ases(sol,npdestino)); // carta que esta no monte de as
		if (carta_valor(c) == carta_valor(as)+1 && carta_naipe(c) == carta_naipe(as)){
		pilha_insere_carta(jogo_ases(sol,npdestino),as);
		pilha_insere_carta(jogo_ases(sol,npdestino),c);
		jogo_desenha(sol);
	}else{
		printw("\nJogada invalida");
		pilha_insere_carta(jogo_ases(sol,npdestino),as);
		pilha_insere_carta(jogo_descartes(sol),c);
		}
	}
}


void descarte_para_jogo(jogo sol){ // move as cartas do descarte para as 7 pilhas
	int npdestino;
	printw ("\n Digite o numero da pilha pra a qual deseja mover");
	npdestino = tela_le(sol-> tela);
	npdestino = npdestino - 49;
	if(npdestino != 0 && npdestino != 1 && npdestino != 2 && npdestino != 3 && npdestino != 4 && npdestino != 5 && npdestino !=6 && npdestino != 7 ){
		printw("\nJogada Invalida");
		tela_atualiza(sol->tela);
		printw("\nDigite uma pilha de 1 a 7");
		npdestino = tela_le(sol->tela);
		npdestino= npdestino-49;
	}
	pilha p = jogo_pilha(sol,npdestino);
	carta c = pilha_remove_carta(jogo_descartes(sol));
	if(pilha_vazia(p)){
		if(carta_valor(c) == 13){ //se for rei insere na pilha vazia
		pilha_insere_carta(jogo_pilha(sol,npdestino),c);
		jogo_desenha(sol);
		return;
	}else{
		printw("\nJogada Invalida");
		}
	}
	if(!pilha_vazia(p)){
		carta jogo = pilha_remove_carta(jogo_pilha(sol,npdestino)); // carta que esta em uma das 7 pilhas
		if(carta_valor(c) == carta_valor(jogo)-1 && carta_naipe(c) != carta_naipe(jogo)){
		pilha_insere_carta(jogo_pilha(sol,npdestino),jogo);
		pilha_insere_carta(jogo_pilha(sol,npdestino),c);
		jogo_desenha(sol);
	}else{
		printw("\nJogada Invalida");
		pilha_insere_carta(jogo_pilha(sol,npdestino),jogo);
		pilha_insere_carta(jogo_descartes(sol),c);
		}
	}
}
