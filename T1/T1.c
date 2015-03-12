#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
	char *nome;
	int matriculas[50];
	char nomes[50][50];
	int n;
	FILE *f=fopen("aluno.txt", "r");
	if (f==NULL){
		printf("Arquivo inexistente\n\n");
		return 1;
	}
	FILE *f2=("notas.txt", "r");
	if (f == NULL){
		printf("Arquivo de notas inexistente\n\n");
		return 1;
	}
	void le_alunos(int* matriculas,char** nomes,int* &n){
		int mat; char c; char nomes[50];int i, int linha;
		if(fscanf(f, "%d", &mat) ==0){
			break;
			i=0;
		}
		fscanf(f, "%d", &mat);
		c= fgetc(f);
		while(c != '\n'){
			nome[i]=c;
			c=fgetc(f);
			i++;
		}
		nome[i]= '\0';
		matriculas[linha]=mat;
		strcpy(nomes[linha], nome);
		linha++;
		*n = linha;
		fclose(f);
		if (argc>1){
			nome=argv[1];
		}
		printf("%s\n", nome);
	}
}

