//AUTOR: ALUÍZIO BARBOSA MACIEL NETOl
//DATA: 01/10/2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno
{
	int matricula;
	char nome[30];
	char idade[5];
	
}t_aluno;


//AQUI EU CONTO O NUMERO DE ALUNOS NO ARQUIVO POR LINHA, PARA VOLTAR A QUANTIDADE QUE IREI TER QUE ALOCAR NO VETOR E PARA 
//DÁ O NUMERO MAXIMO DE ELEMENTOS PARA MEU QUICKSORT

int contar(const char **argv){//AQUI EU PEGO COMO PARAMETRO AS ENTRADAS PELO PROMPT
	int qtd = 0;
	FILE *arq;
	char info[100];

	arq = fopen(argv[1],"r");//O NOME DO MEU ARQUIVO VAI SER PASSADA QUANDO EXECUTAR O PROGRAMA NA POSIÇÃO 1 DO MEU VETOR DE STRINGS ARGV

    if(arq == NULL){
        return -1;//RETORNO 0 SE NÃO EXISTIR O ARQUIVO NO DIRETORIO
    }

    while( (fgets(info,100 ,arq))!=NULL ){//CONTO O NUMERO DE ALUNOS E INCREMENTO A QUANTIDADE
    	qtd++;
	}

	fclose(arq);

	return qtd;

}
//RETORNA MEU VETOR DE PESSOAS

t_aluno *lerArquivo(t_aluno *alunos, const char **argv); //PRÓTOTIPO DA FUNÇÃO DE LER OS DADOS DO ARQUIVO

void quick_sort(t_aluno *a, int left, int right);//PROTOTIPO DA FUNÇÃO QUICKSORT

void printar(t_aluno *alunos, int qtd);

int main(int argc, char const *argv[])
{
	
	//CHAMO A FUNÇÃO
	int qtd = contar(argv);

	//SE RETORNAR 0 ARQUIVO NÃO SE XISTIR
	if(qtd < 0){
		printf("\nAquivo não encontrado!\n\n");
		exit(1);
	}

	//ALOCO A MEMORIA COM A QUANTIDADE DE LINHAS(ALUNOS) QUE LI
	t_aluno * alunos = (t_aluno *) calloc (qtd, sizeof(t_aluno));

	//PASSO O VETOR E O NOME DO ARQUIVO
	alunos = lerArquivo(alunos,argv);

	if (alunos == NULL)
	{
		printf("\nArquivo vazio!\n\n");
		exit(1);
	}

	//CHAMO QUICK
	quick_sort(alunos, 0,qtd-1);


	//MOSTRO NA TELA O VETOR
	printar(alunos, qtd);
	
	return 0;
}


void printar(t_aluno *alunos, int qtd){
	printf("\nMatricula, Nome, Idade\n\n");
	for (int j = 0; j < qtd; j++)
	{
		printf("%d, %s, %s\n",alunos[j].matricula, alunos[j].nome, alunos[j].idade);
	}

}


t_aluno *lerArquivo(t_aluno *alunos, const char **argv){

	FILE *arq;
	arq = fopen(argv[1],"r");
	if(arq == NULL){
		printf("Impossivel de abrir arquivo\n" );
	}
	
	char info[100];

	int i = 0;
    
    char *token = NULL;
    while( (fgets(info,100 ,arq))!=NULL ){
    	token = strtok(info,", ");
		alunos[i].matricula = atoi(token);
		token = strtok(NULL,", ");
		strcpy(alunos[i].nome,token);
		token = strtok(NULL,", ");
		strcpy(alunos[i].idade,token);
		i++;
	}
	if(i == 0){
		return NULL;
	}

	fclose(arq);

	return alunos;


}






void quick_sort(t_aluno *a, int left, int right) {
    int i, j, x, y;
     
    i = left;
    j = right;
    x = a[(left + right) / 2].matricula;
     
    while(i <= j) {
        while(a[i].matricula < x && a[i].matricula < a[right].matricula) {
            i++;
        }
        while(a[j].matricula > x && a[j].matricula > a[left].matricula) {
            j--;
        }
        if(i <= j) {
            y = a[i].matricula;
            a[i].matricula = a[j].matricula;
            a[j].matricula = y;
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}