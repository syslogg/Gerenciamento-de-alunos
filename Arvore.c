#define bool int
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"


struct no {
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

bool buscar(Arvore * arv, int key) {
	return buscar_rec(arv->raiz,key);
}

bool buscar_rec(No * raiz, int key) {
	if(raiz != NULL) {
		if(raiz->key > key) return buscar_rec(raiz->esq, key);
		if(raiz->key < key) return buscar_rec(raiz->dir, key);
		return true;
	}
	return false;
}


void inserir(Arvore * arv, int key) {
	inserir_rec(&arv->raiz,key);

    /*if(arv->raiz == NULL) {
        //Arvore vazia
        No * novo = (No *)malloc(sizeof(No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->key = key;
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

        if(ant->key < key) {
            ant->dir = novo;
        } else {
            ant->esq = novo;
        }
    }*/

}

void inserir_rec(No * * praiz,int key) {
	No * raiz = *praiz;
	if(* praiz == NULL) {
		//Inserir de fato no folha;
		No * novo = (No *) malloc(sizeof(No));
		novo->key = key;
		novo->esq = NULL;
		novo->dir = NULL;
		
		*praiz = novo;
		
	} else {
		//Navegar até o nó folha
		if(raiz->key > key) inserir_rec(&raiz->esq,key);
		if(raiz->key < key) inserir_rec(&raiz->dir,key);
	}
	
}

void imprimir(Arvore * arv) {
    printf("[ ");
    inordem(arv->raiz);
    printf("]\n");
}

void inordem(No * raiz) {
    if(raiz != NULL) {
        inordem(raiz->esq);
        printf("%d ", raiz->key);
        inordem(raiz->dir);
    }
}


