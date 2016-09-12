#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "Arvore.h"

#define bool int
#define true 1
#define false 0
#define MAX_CHARACTER 300


char filename[]  = "db/BDAlunos10e2v1.txt"; //File test
char pesquisa[] = "db/PesqAlunos10e1.txt"; //Arquivo de pesquisa

struct aluno {
	char nome[MAX_CHARACTER];
	char email[MAX_CHARACTER];
	char telefone[MAX_CHARACTER];
};
typedef struct aluno Aluno;

int main(int argc, char *argv[]) {
	//Criação da arvore
	Arvore * a = criar();
	
	//Menu
	int menu = 0;
	bool carregado = false;
	bool save = false;
	
	while (menu != 12){
		switch(menu) {
			case 0:
				//Listagem do menu
				clean();
				printf("-================== Gerenciamento de alunos ==================-\n");
				printf("-=========================== Menu ============================-\n");
				printf("- Escolha uma das opcoes abaixo:\n\n");
				printf((carregado == true ? "1 - Recarregar arquivo\n" : "1 - Carregar arquivo\n"));
				printf("2 - Inserir novo aluno.\n");
				printf("3 - Listar todos os alunos por ordem de matricula.\n");
				printf("4 - Listar alunos contido no arquivo.\n");
				printf("5 - Consultar aluno pela matricula.\n");
				printf("6 - Editar dados de um aluno.\n");
				printf("7 - Remover aluno pela matricula.\n");
				printf("8 - Remover alunos contido no arquivo.\n");
				printf("9 - Remover todos os alunos.\n");
				printf("10 - Salvar alteracoes na lista no arquivo.\n\n");
				printf("11 - Sair.\n\n");
				printf("- Digite um dos numeros acima\n");
				
				
				scanf("%d",&menu);
				
				
				menu = menu >= 1 && menu <= 11 ? menu : 0;
				
				break;
			case 1:
				//Carregar alunos do arquivo
				clean();
				if(carregado == true) {
					printf("Voce realmente deseja recarregar o arquivo?\nQualquer alteracao feita na lista de alunos (adicao, exclusao ou edicao de dados) sera PERDIDA.\nDigite '1' para SIM e '2' para NAO.\n\n");
					int d; 
					scanf("%d",&d);
					if(d != 1){
						menu = 0;
						break;
					} 
						
					
				}
				
				if(CarregarArquivo(a) == false) {
					menu = 11;
				} else {
					menu = 0;
					printf("Banco de dados carregado com sucesso!\n ");
					pause();
					carregado = true;
				}
				break;
			case 2:
				//Inserir novo aluno na memoria
				clean();
				char nome[200];
				char email[200];
				char telefone[200];
				Aluno * aluno = (Aluno *) malloc(sizeof(Aluno));
				printf("- Adicionar novo aluno:\n\n");
				
				printf("Nome: ");
				scanf("%s",aluno->nome);
				fflush(stdin);
				
				printf("\nE-mail: ");
				scanf("%s",aluno->email);
				fflush(stdin);
				
				printf("\nTelefone: ");
				scanf("%s",aluno->telefone);
				fflush(stdin);
				
				
				
				inserir(a,contar_nos(a)+1,aluno);
				pause();
				
				menu = 0;
				save = true;
				break;
			case 3:
				//Listar todos os alunos (Ordem de matricula)
				clean();
				if(contar_nos(a) != 0){
					listar_todos(a);
				} else {
					printf("Nao ha alunos na memoria!\nCarregue o arquivo ou insira um novo aluno!");
				}
				pause();
				menu = 0;
				break;
			case 4:
				//Listar todos os alunos pela matricula do arquivo
				clean();
				FILE * arq = fopen(pesquisa,"r");
				
				if(arq == NULL){
					printf("Erro ao carregar arquivo de pesquisa!");
					
					
				} else {
					
					char linha[11];
					int matricula;
					
					clock_t time = clock();
					//
					//fgets(linha,sizeof(linha),arq) != NULL
					while((fscanf(arq,"%d\n", &matricula))!=EOF) {
						//sscanf(linha,"%d",&matricula);
						No * b = buscar(a,matricula);
						printf("Matricula: %d\n",matricula);
						printf("Nome: %s\n",getNome(b));
						printf("E-mail: %s\n",getEmail(b));
						printf("Telefone: %s\n",getTelefone(b));
						printf("=============================================================\n");
					}
					
					printf("\n\n\nTempo decorrido: %f\n\n",(clock() - time) / (double)CLOCKS_PER_SEC);
					
				}
				menu = 0;
				pause();
				break;
			case 5:
				//Consultar aluno por matricula
				break;
			case 6:
				//Editar aluno por matricula
				break;
			case 7:
				//Remover aluno pela matricula
				break;
			case 8:
				//Remover todos os alunos do arquivo
				break;
			case 9:
				//Remover todos os alunos
				break;
			case 10:
				//Salvar arvore da memoria no arquivo
				break;
			case 11:
				//Sair
				clean();
				printf("Voce realmente deseja sair?\nAlteracoes nao salva no DB serao descartadas\n");
				printf("1 - SIM\n2 - NAO\n\n");
				int d;
				scanf("%d",&d);
				
				menu = d == 1 ? 12 : 0;
				
				break;
		}
	}
	
	clean();
	printf("Desenvolvido inteiramente por Hendy Rodrigues F. Silva\n");
	printf("GitHub: https://github.com/syslogg/Gerenciamento-de-alunos\n\n");
	printf("Obrigado Prof. Murilo Ybanez por avaliar meu trabalho de ED2!\n\n");
	pause();
	
	return 0;
}

bool CarregarArquivo (Arvore * arv) {
	//Carregar dados do Arquivo para arvore;
	clock_t time;
	time = clock();
	FILE * file = fopen(filename, "r");
	
	if(file == NULL) {
		clean();
		printf("Erro: algum problema foi encontrado na leitura do arquivo.");
		return false;
	}
	int matricula;
	char nome[300], email[300], telefone[300],buf[1024];
	
	//Percorre todo o arquivo
	while (fgets(buf,sizeof(buf),file) != NULL){
		//buf é string que contem a linha completa sem formatação
		//pega cada linha e formata inserindo em variaveis temporaria
		sscanf(buf,"%d | %[^|] | %[^|] | %[^\n]",&matricula, nome,email,telefone);
		
		//Retira cada espaço da ultima linha
		nome[(strlen(nome)-1)] = '\0';
		email[(strlen(email)-1)] = '\0';
		printf("Matricula: %d\n",matricula);
		//Insere na arvore
		Aluno * aluno = (Aluno *) malloc(sizeof(Aluno));
		strcpy(aluno->nome,nome);
		strcpy(aluno->email,email);
		strcpy(aluno->telefone,telefone);
		inserir(arv,matricula,aluno);
		
	}
	clean();
	printf("Tempo de carregamento: %f\n\n",(clock() - time) / (double)CLOCKS_PER_SEC);
	pause();
	clean();
	
	return true;
}


void clean() {
	system("cls");
}

void pause(){
	system("pause");
}
