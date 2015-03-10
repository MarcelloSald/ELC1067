#include <stdio.h>
#include <stdlib.h>

int main(void){
	FILE *f;
	int num_mat;
	char nome[100];
	f = fopen("saida.txt", "r");
	fprintf(f, "%d %s\n", num_mat, nome);
	fclose(f);
	return;
}
