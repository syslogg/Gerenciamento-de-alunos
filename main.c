#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

#define bool int
#define true 1
#define false 0

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	//Criação da arvore
	Arvore * a = criar();
	CarregarArquivo(a);
	
	inserir(a,10);
	inserir(a,8);
	inserir(a,11);
	inserir(a,7);
	inserir(a,12);
	
    imprimir(a);

	return 0;
}

void CarregarArquivo (Arvore * arv) {
	//Carregar dados do Arquivo para arvore;
}
