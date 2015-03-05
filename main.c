#include <stdio.h>
#include <stdlib.h>

int main(void){
	FILE *f;
	int num_mat;
	char nome[100];
	printf("Digite a matricula:\n");
	scanf("%i", &num_mat);
	printf("Digite o nome:\n");
	scanf("%s", nome);
	f = fopen("saida.txt", "w");
	fprintf(f, "%d %s\n", num_mat, nome);
	fclose(f);
	return;
}
