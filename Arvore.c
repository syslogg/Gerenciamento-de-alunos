#define bool int
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"



struct no {
	//Informação
	
	Aluno * info;
	
	int key;
	No * esq;
	No * dir;
};
struct arvore {
	No * raiz;
};

Arvore * criar () {

	Arvore * arv = (Arvore *) malloc(sizeof(Arvore));
	arv->raiz = NULL;

}

Aluno * buscar_rec(No * raiz, int key) {
	if(raiz != NULL) {
		if(raiz-> key == key) return raiz->info;
		
		if(raiz->key > key) return buscar_rec(raiz->esq, key);
		else return buscar_rec(raiz->dir, key);
		//return NULL;
	}
	return NULL;
}

Aluno * buscar(Arvore * arv, int key) {
	return buscar_rec(arv->raiz,key);

}




void inserir(Arvore * arv, int key, Aluno * aluno) {

    if(arv->raiz == NULL) {
        //Arvore vazia
        No * novo = (No *)malloc(sizeof(No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->key = key;
        
        novo->info = aluno;
        
        
        arv-> raiz = novo;
    } else {
        //Arvore não vazia
        No * ant = NULL;
        No * atual = arv->raiz;

        while (atual != NULL) {
            //Navega até o nó folha para inserir
            ant = atual;

            if(atual->key == key) return; // Já existe o elemento

            if(atual->key < key)
				atual = atual->dir;
            else
            	atual = atual->esq;
        	
        }
		
        No * novo = (No *) malloc(sizeof(No));
        novo->key = key;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->info = aluno;

        if(ant->key < key) {
            ant->dir = novo;
        } else {
            ant->esq = novo;
        }
    }

}



void inordem(No * raiz) {
    if(raiz != NULL) {
        inordem(raiz->esq);
        printf("%s ", raiz->key);
        inordem(raiz->dir);
    }
}

void imprimir(Arvore * arv) {
    printf("[ ");
    inordem(arv->raiz);
    printf("]\n");
}


int contar_nos(Arvore * arv) {
	return contar_nos_rec (arv->raiz);
}

int contar_nos_rec (No * raiz) {
	if(raiz == NULL) {
		return 0;
	} else {
		return 1 + contar_nos_rec(raiz->esq) + contar_nos_rec(raiz->dir);
	}
}
int maior_no(Arvore * arv) {
	return maior_no_rec(arv->raiz);
}

int maior_no_rec(No * raiz) {
	if(raiz != NULL) {
		if(raiz->dir == NULL) return raiz->key;
		else return maior_no_rec(raiz->dir);
	}
	return 0;
}

No * remove_atual(No * atual){
	No * no1, * no2;
	
	if(atual->esq == NULL) {
		no2 = atual->dir;
		free(atual);
		return no2;
	}
	
	no1 = atual;
	no2 = atual->esq;
	
	while(no2->dir != NULL){
		no1 = no2;
		no2 = no2->dir;
	}
	if(no1 != atual) {
		no1->dir = no2->esq;
		no2->esq = atual->esq;
		
	}
	no2->dir = atual->dir;
	free(atual);
	return no2;
}

void remover(Arvore * arv, int key) {
	
	No * raiz = arv->raiz;
	
	if (raiz == NULL) return;
	
	No * ant = NULL;
	No * atual = raiz;
	
	while(atual != NULL) {
		if(key == atual->key) {
			if(atual == raiz) {
				raiz = remove_atual(atual);
			} else {
				if(ant->dir == atual) ant->dir = remove_atual(atual);
				else  ant->esq = remove_atual(atual);
				return;
			}	
		}
		ant = atual;
		if(key > atual->key) {
			atual = atual->dir;
		} else {
			atual = atual->esq;
		}
	}
	
}






