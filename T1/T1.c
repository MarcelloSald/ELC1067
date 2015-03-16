#include <stdio.h>
#include <string.h>

void main(int argc, char ** argv){
    int matriculasAluno[50];
	int matriculasNota[50];
	char nomes[50][50], nome[50], c;
	float media, n1[50], n2[50];
	int n = 0, j = 0;

    if(argc < 2){
		return;
    }

    FILE * f1 = fopen("alunos.txt", "r");
    if (f1 == NULL) {
        printf("F4T4L 3RR0R");
        return;
    }

    while (!feof(f1)) {
        if (fscanf(f1, "%d", &matriculasAluno[n]) <= 0) {
            break;
        }

        c = fgetc(f1);

        while (c != '\n') {
            nomes[n][j] = c;
            j++;
            c = fgetc(f1);
        }
        nomes[n][j] = '\0';
        j = 0;
        n++;
    }

    fclose(f1);

    FILE * f2 = fopen("notas.txt", "r");
    if (f2==NULL){
        printf("F4TAL 3RR0R \n");
        return;
    } else{
        n = 0;
        while (!feof(f2)) {
            if (fscanf(f2, "%d %f %f", &matriculasAluno[n], &n1[n], &n2[n]) <= 0) {
                break;
            }

            n++;
        }

        fclose(f2);
    }

    for (j = 0; j < n; j++) {
        if (strstr(nomes[j], argv[1]) != NULL) {
            printf("%.2f %s\n", (n1[j] + n2[j]) / 2, nomes[j]);
        }
    }
}
