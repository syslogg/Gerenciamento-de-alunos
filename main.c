#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Arvore.h"

#define bool int
#define true 1
#define false 0


char filename[]  = "db/BDAlunos10e1v1.txt"; //File test

int main(int argc, char *argv[]) {
	//Cria��o da arvore
	Arvore * a = criar();
	
	//Menu
	int menu = 0;
	bool carregado = false;
	
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
				
				printf("- Adicionar novo aluno:\n\n");
				
				printf("Nome: ");
				scanf("%s",nome);
				fflush(stdin);
				
				printf("\nE-mail: ");
				scanf("%s",email);
				fflush(stdin);
				
				printf("\nTelefone: ");
				scanf("%s",telefone);
				fflush(stdin);
				
				printf("\n\n%d matriculados",contar_nos(a));
				
				pause();
				break;
			case 3:
				//Listar todos os alunos (Ordem de matricula)
				break;
			case 4:
				//Listar todos os alunos pela matricula do arquivo
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
		//buf � string que contem a linha completa sem formata��o
		//pega cada linha e formata inserindo em variaveis temporaria
		sscanf(buf,"%d | %[^|] | %[^|] | %[^\n]",&matricula, nome,email,telefone);
		
		//Retira cada espa�o da ultima linha
		nome[(strlen(nome)-1)] = '\0';
		email[(strlen(email)-1)] = '\0';
		
		//Insere na arvore
		inserir(arv,matricula,nome,email,telefone);
		
	}
	
	return true;
}


void clean() {
	system("cls");
}

void pause(){
	system("pause");
}
