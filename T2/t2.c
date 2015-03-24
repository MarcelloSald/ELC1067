#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int le_alunos(int *matriculasAluno, char **nomes, int *n){
    char c, nome[50];
    int i=0, j=0;
    FILE * f1 = fopen("alunos.txt", "r");
    if (f1 == NULL) {
        printf("F4T4L 3RR0R");
        return;
    }else{
        i=0;
        while (!feof(f1)) {
            nomes[i] = (char*) malloc(50*sizeof(char));
            if (fscanf(f1, "%d", &matriculasAluno[i]) <= 0) {
                break;
            }

            c = fgetc(f1);

            while (c != '\n') {
                nomes[i][j] = c;
                j++;
                c = fgetc(f1);
            }
            nomes[i][j] = '\0';
            j = 0;
            i++;
        }
    }
    fclose(f1);
}

void le_notas(int *matriculasNota, float *notas){
    int contador;
    float n1, n2;

    FILE * f2 = fopen("notas.txt", "r");
    if (f2==NULL){
        printf("F4TAL 3RR0R \n");
        return;
    } else{
        contador = 0;
        while(!feof(f2)){
            if(fscanf(f2,"%d %f %f ",&matriculasNota[contador],&n1,&n2) != 3){
                printf("F4T4L 3RR0R");
                return;
            }
            notas[contador++]=(n1+n2)/2;
            if (contador>=50){
                matriculasNota = (int*) realloc(matriculasNota, 50*sizeof(int));
                notas = (float*) realloc(notas, 50*sizeof(float));
            }
        }
    }
        fclose(f2);
}
void imprime(int *matriculasAluno, int *matriculasNota, float *notas, char **nomes, char *pesquisa_nome){
    int i, j, k;
    char m[50];
    strtoupper(pesquisa_nome);
    while(!matriculasAluno[i]<0){
        j=0;
        strcpy(m, nomes[i]);
        strtoupper(m);
    }
    if(strstr(m, pesquisa_nome)!=NULL){
            k++;
            while(matriculasAluno[i] != matriculasNota[j]){
                j++;
            if(k==1){
                printf(" MEDIA: %.3f ..... NOME: %s\n", notas[j], nomes[i]);
        }
        i++;
    }
    if(k==0)
        printf("Nome nao consta no arquivo/ ");
    }
}

void main(int argc, char ** argv){

    int i, n;
    int *matriculasAluno = (int*) malloc(50*sizeof(int));
    int *matriculasNota = (int*) malloc(50*sizeof(int));
    float *notas = (float*) malloc(50*sizeof(float));
    char **nomes = (char**) malloc(50*sizeof(char*));
    char *pesquisa_nome = (char*)(50*sizeof(char));
    int tamanho=0;

    if(argc < 2){
        strcpy(pesquisa_nome, argv[1]);
        printf(" Nome pesquisado: %s \n", pesquisa_nome);
    }
    le_alunos(matriculasAluno, nomes, &n);
    le_notas(matriculasNota, notas);
    imprime(matriculasAluno, matriculasNota, notas, nomes, pesquisa_nome);

    free(pesquisa_nome);
    free(matriculasAluno);
    free(matriculasNota);
    free(notas);

    for(i=0; i<n; i++)
        free(nomes[i]);
    free(nomes);
    return;
}
