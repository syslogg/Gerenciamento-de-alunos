#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

#define bool int
#define true 1
#define false 0

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

char filename[]  = "db/BDAlunos10e1v1.txt"; //File test

int main(int argc, char *argv[]) {
	//Criação da arvore
	Arvore * a = criar();
	if(CarregarArquivo(a) == false) return 0;
	
	inserir(a,10);
	inserir(a,8);
	inserir(a,11);
	inserir(a,7);
	inserir(a,12);
	
    imprimir(a);
	
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
		//buf é string que contem a linha completa
		
		printf("Nome: %s",buf);
	}
	
	
	
	
	
	
	
	
	return true;
}


void clean() {
	system("cls");
}
