#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "Arvore.h"

#define bool int
#define true 1
#define false 0
#define MAX_CHARACTER 300


char filename[]  = "db/BDAlunos10e4v1.txt"; //File test
char pesquisa[] = "db/PesqAlunos10e5.txt"; //Arquivo de pesquisa

struct aluno {
	char nome[MAX_CHARACTER];
	char email[MAX_CHARACTER];
	char telefone[MAX_CHARACTER];
};
typedef struct aluno Aluno;

void clean();
void pause();

int main(int argc, char *argv[]) {
	//Criação da arvore
	Arvore * a = criar();
	
	//Menu
	int menu = 0;
	bool carregado = false;
	bool save = false;
	bool exit = false;
	
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
				
				
				menu = menu >= 1 && menu <= 15 ? menu : 0;
				
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
				
				fflush(stdin);
				printf("Nome: ");
				scanf("%[^\n]s",aluno->nome);
				fflush(stdin);
				
				printf("\nE-mail: ");
				scanf("%[^\n]s",aluno->email);
				fflush(stdin);
				
				printf("\nTelefone: ");
				scanf("%[^\n]s",aluno->telefone);
				fflush(stdin);
				
				
				
				inserir(a,maior_no(a)+1,aluno);
				pause();
				
				menu = 0;
				save = true;
				break;
			case 3:
				//Listar todos os alunos (Ordem de matricula)
				clean();
				if(contar_nos(a) != 0){
					//listar_todos(a);
					int maior = maior_no(a);
					int i;
					
					for(i = 1; i <= maior; i++) {
						Aluno * v = buscar(a,i);
						
						if(v != NULL) {
							printf("Matricula: %d\n",i);
							printf("Nome: %s\n",v->nome);
							printf("Email: %s\n",v->email);
							printf("Telefone: %s\n",v->telefone);
							printf("==========================================================================\n");
							
						}
					}
					
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
						Aluno * b = buscar(a,matricula);
						
						printf("Matricula: %d\n",matricula);
						printf("Nome: %s\n",b->nome);
						printf("E-mail: %s\n",b->email);
						printf("Telefone: %s\n",b->telefone);
						printf("=============================================================\n");
					}
					
					printf("\n\n\nTempo decorrido: %f\n\n",(clock() - time) / (double)CLOCKS_PER_SEC);
					
				}
				fclose(arq);
				menu = 0;
				pause();
				break;
			case 5:
				//Consultar aluno por matricula
				clean();
				
				printf("==================================== Gerenciamento de alunos ====================================\n");
				printf("Digite matricula: ");
				int matricula;
				scanf("%d", &matricula);
				clean();
				Aluno * b = buscar(a,matricula);
				if(b != NULL) {
					printf("==================================== Gerenciamento de alunos ====================================\n");
					printf("Matricula: %d\n",matricula);
					printf("Nome: %s\n",b->nome);
					printf("E-mail: %s\n",b->email);
					printf("Telefone: %s\n",b->telefone);
				} else{
					printf("Aluno de matricula %d nao existe!\n", matricula);
				}
				
				menu = 0;
				pause();
				break;
			case 6:
				//Editar aluno por matricula
				clean();
				
				printf("==================================== Gerenciamento de alunos ====================================\n");
				printf("Digite matricula: ");
				int matri;
				scanf("%d", &matri);
				clean();
				Aluno * ba = buscar(a,matri);
				if(ba != NULL) {
					printf("==================================== Gerenciamento de alunos ====================================\n");
					fflush(stdin);
					printf("Novo nome:");
					scanf("%[^\n]s",ba->nome);
					fflush(stdin);
					
					printf("Novo e-mail:");
					scanf("%[^\n]s",ba->email);
					fflush(stdin);
					
					printf("Novo telefone:");
					scanf("%[^\n]s",ba->telefone);
					fflush(stdin);
					
				} else{
					printf("Aluno de matricula %d nao existe!\n", matri);
				}
				
				menu = 0;
				pause();
				break;
			case 7:
				//Remover aluno pela matricula
				clean();
				
				printf("==================================== Gerenciamento de alunos ====================================\n");
				printf("Digite matricula: ");
				int matt;
				scanf("%d", &matt);
				clean();
				Aluno * bba = buscar(a,matt);
				if(bba != NULL) {
					remover(a,matt);
					printf("Aluno removido com sucesso!");
				} else{
					printf("Aluno de matricula %d nao existe!\n", matt);
				}
				
				menu = 0;
				pause();
				break;
			case 8:
				//Remover todos os alunos do arquivo
				
				clean();
				FILE * arqs = fopen(pesquisa,"r");
				
				if(arqs == NULL){
					printf("Erro ao carregar arquivo de pesquisa!");
					
					
				} else {
					
					char linha[11];
					int matriculas;
					
					clock_t times = clock();
					//
					//fgets(linha,sizeof(linha),arq) != NULL
					while((fscanf(arqs,"%d\n", &matriculas))!=EOF) {
						//sscanf(linha,"%d",&matricula);
						remover(a,matriculas);
					}
					printf("Alunos removido com sucesso!");
					printf("\n\n\nTempo decorrido: %f\n\n",(clock() - times) / (double)CLOCKS_PER_SEC);
					
				}
				fclose(arqs);
				menu = 0;
				pause();
				
				break;
			case 9:
				//Remover todos os alunos
				clean();
				if(contar_nos(a) != 0){
					//listar_todos(a);
					int maior = maior_no(a);
					int i;
					
					for(i = 1; i <= maior; i++) {
						remover(a,i);
						
						
					}
					
				} else {
					printf("Nao ha alunos na memoria!\nCarregue o arquivo ou insira um novo aluno!");
				}
				pause();
				menu = 0;
				break;
			case 10:
				//Salvar arvore da memoria no arquivo
				clean();
				menu = exit == true  ? 12 : 0;
				if(carregado == false) {
					printf("Voce ira sobreescrever no banco uma arvore que nao foi carregada, todos os dados no arquivo irao ser sobreescritos.\nDeseja continuar com o procedimento?");
					printf("\n\n1- SIM;\n0- NAO;\n");
					int s;
					scanf("%d",&s);
					if(s == 0) break;
					
				}
				
				FILE * savefile = fopen(filename,"w");
				
				if(savefile != NULL) {
					save = true;
					//Pattern: matricula | Nome do aluno | email | telefone\n
					//Percorre a arvore
					
					int maior = maior_no(a);
					int i;
					
					for(i = 1; i <= maior; i++) {
						Aluno * alunoaq = buscar(a,i);
						if(alunoaq != NULL){
							fprintf(savefile, "%.7ld | %s | %s | %s\n", (long)i,alunoaq->nome,alunoaq->email,alunoaq->telefone);
						}
					}
					
					fclose(savefile);
					printf("Arquivo salvo com sucesso!\n\n");
					
				} else {
					printf("ERROR: erro inesperado no arquivo!");
				}
				
				
				pause();
				
				
				break;
			case 11:
				//Sair
				clean();
				if(save == false) {
				
					printf("Deseja salvar as alterações feita na arvore?\n");
					printf("1 - SIM\n2 - NAO\n\n");
					int d;
					scanf("%d",&d);
					
					menu = d == 1 ? 10 : 0;
					exit = true;
					
				}
				menu = 12;
				
				break;
				
				case 15:
					
					clean();
					printf("Teste");
					isAvl(a);
					printf("\nTeste 2");
					
					pause();
					
					menu = 0;
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
	fclose(file);
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
	printf("\n\n");
	system("pause");
}
