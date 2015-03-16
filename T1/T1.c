#include <stdio.h>
#include <string.h>

void ler_alunos(int * matriculas, char nome[][50], int * n) {
    int matricula, i = 0, linha = 0;
    char caracter;
    char name[50];
    FILE * f= fopen("alunos.txt", "r");
    if (f == NULL) {
        printf("F4T4L 3RR0R");
        return;
        }
    while (feof(f) == 0) {
        if (fscanf(f, "%d", &matricula)<=0) {
            break;
        caracter = fgetc(f);
        while (caracter != '\n') {
            name[i] = caracter;
            i++;
            caracter = fgetc(f);
            }
            name[i]='\0';
            matriculas[linha]= matricula;
			strcpy(nome[linha],name);
			linha++;
        }
        *n = linha;
        fclose(f);
        }
}

float medias(int * matricula) {
    int m, linha=0;
    float n1, n2;
    FILE * f = fopen("notas.txt", "r");
    if (f == NULL) {
        printf("F4T4L 3RR0R \n");
        return;
        }
        else{
            if (fscanf(f, "%d", &m)<=0) {
                }
            while (fscanf(f,"%f", &n1) && fscanf(f, "%f", &n2) != EOF){
                matricula[linha]= m;
		        matricula[linha] = (n1 + n2)/2;
		        linha++;

            }
        }
    return 0.0;
    }

void busca_alunos(int* n, char* busca, char nomes[][50], int* matriculasAlunos, int* matriculasNota, float* media){
  int i,j;
        for(i=0;i<*n;i++){
                j=0;
             if(strstr(nomes[i],busca) != NULL){
                while(matriculasAlunos[i] != matriculasNota[j]){
                        j++;
             }
                printf("Aluno:%s Media: %.f\n",nomes[i],media[j]);
        }
    }
}



int main(int argc, char**argv){
	char nome[50];
	char* busca = nome;
	if(argc > 1){
		strcpy(nome, argv[1]);
}
	int matriculasAluno[50];
	int matriculasNota[50];
	char nomes[50][50];
	float media[50];
	int n;

	ler_alunos(matriculasAluno,nomes,&n);
	medias(matriculasAluno);
	busca_alunos(&n,busca,nomes,matriculasAluno,matriculasNota,media);
	return 0;
}
