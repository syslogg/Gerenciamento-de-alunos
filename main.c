#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

#define bool int
#define true 1
#define false 0


char filename[]  = "db/BDAlunos10e1v1.txt"; //File test

int main(int argc, char *argv[]) {
	//Criação da arvore
	Arvore * a = criar();
	
	//Menu
	int menu = 0;
	bool carregado = false;
	
	while (menu != 11){
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
				printf("10 - Salvar alterações na lista no arquivo.\n");
				
				
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
				break;
		}
	}
	
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
		//buf é string que contem a linha completa sem formatação
		//pega cada linha e formata inserindo em variaveis temporaria
		sscanf(buf,"%d | %[^|] | %[^|] | %[^\n]",&matricula, nome,email,telefone);
		
		//Retira cada espaço da ultima linha
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
