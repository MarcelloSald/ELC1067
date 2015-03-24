#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void le_alunos(int* matriculasAluno, char** nomes, int* n){

    int matricula, contador, linha = 0;
	char c, nome[50];
    FILE *f1 = fopen("alunos.txt","r");

	if (f1 == NULL){
		printf("F4T4L 3RR0R");
            return;
	}
    while(!feof(f1) != 0 ){
		if(fscanf(f1, "%d", &matricula) <= 0)
            break;
		contador = 0;
		c = fgetc(f1);
		while(c != '\n' && feof(f1) == 0){
			nome[contador] = c;
			contador++;
			c = fgetc(f1);
		}
        nome[contador] = '\0';
        matriculasAluno[linha] = matricula;
        nomes[linha] = (char*) malloc((strlen(nome)+1) * sizeof(char));
        strcpy(nomes[linha], nome);
        linha++;
	}
    *n = linha;
    fclose(f1);
}

void le_notas(float* medias){
    int contador = 0, matricula;
    float n1, n2;

    FILE *f2 = fopen("notas.txt", "r");

    if (f2 == NULL){
		printf("F4T4L 3RR0R");
            return;
	}


    while(!feof(f2) != 0){
        if(fscanf(f2, "%d" "%f" "%f\n", &matricula, &n1, &n2) == 0)
            break;
        medias[contador] = (n1+n2)/2;
        contador++;
    }
    fclose(f2);
}

void imprime(char* pesquisa_nome, char** nomes, int n, float* medias){

    int contador;
    for(contador = 0; contador < n; contador++){
        if(strstr(nomes[contador], pesquisa_nome)!= NULL){
            printf("%.2f %s\n", medias[contador], nomes[contador]);
        }
    }
}

int main(int argc, char** argv){

    int *n;
    char* pesquisa_nome = (char*) malloc(50* sizeof(char));
    float* medias = (float*) malloc(50* sizeof(float));
    int* matriculas = (int*)malloc(50* sizeof(int));
    char** nomes = (char**) malloc(50* sizeof(char*));

    if(argc >1){
        pesquisa_nome = argv[1];
    }

    le_alunos(matriculas, nomes, &n);
    le_notas(medias);
    imprime(pesquisa_nome, nomes, n, medias);

    free(pesquisa_nome);
    free(nomes);
    free(medias);
    free(matriculas);
    return;
}
