int main(int argc, char **argv){
	char *nome;
	int matriculas[50];
	char nomes[50][50];
	int n;
	void le_alunos(int* matriculas,char** nomes,int* &n);{
		FILE *f= fopen("alunos.txt", "r");
		int mat; char c; char nomes[50];int i, int linha;
		while (feof(f) !=0){
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
				ctrcpy(nomes[linha], nome);
				linha++;
			}
		*n = linha;
		fclose(f);

	if (argc>1){
		nome=argv[1];
	}
	printf("%s\n", nome);



}
