#define bool int
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

#define MAX_CHARACTER 300

struct no {
	//Informação
	char nome[MAX_CHARACTER];
	char email[MAX_CHARACTER];
	char telefone[MAX_CHARACTER];
	
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

No * buscar_rec(No * raiz, int key) {
	if(raiz != NULL) {
		if(raiz-> key == key) return raiz;
		
		if(raiz->key > key) return buscar_rec(raiz->esq, key);
		else return buscar_rec(raiz->dir, key);
		//return raiz;
	}
	return raiz;
}

No * buscar(Arvore * arv, int key) {
	return buscar_rec(arv->raiz,key);
}




void inserir(Arvore * arv, int key, char * nome, char * email, char * telefone) {
	//inserir_rec(&arv->raiz,key, nome, email, telefone);

    if(arv->raiz == NULL) {
        //Arvore vazia
        No * novo = (No *)malloc(sizeof(No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->key = key;
        
        strcpy(novo->nome,nome);
		strcpy(novo->email,email);
		strcpy(novo->telefone,telefone);
        
        
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
        strcpy(novo->nome,nome);
		strcpy(novo->email,email);
		strcpy(novo->telefone,telefone);

        if(ant->key < key) {
            ant->dir = novo;
        } else {
            ant->esq = novo;
        }
    }

}

void inserir_rec(No * * praiz,int key, char * nome, char * email, char * telefone) {
	No * raiz = *praiz;
	if(* praiz == NULL) {
		//Inserir de fato no folha;
		No * novo = (No *) malloc(sizeof(No));
		novo->key = key;
		novo->esq = NULL;
		novo->dir = NULL;
		
		//ADD Informacao na arvore
		strcpy(novo->nome,nome);
		strcpy(novo->email,email);
		strcpy(novo->telefone,telefone);
		
		*praiz = novo;
		
	} else {
		//Navegar até o nó folha
		if(raiz->key > key) inserir_rec(&raiz->esq,key,nome, email, telefone);
		if(raiz->key < key) inserir_rec(&raiz->dir,key,nome, email, telefone);
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
        printf("%s ", raiz->nome);
        inordem(raiz->dir);
    }
}

void listar_todos(Arvore * arv) {
	listar_todos_rec(arv->raiz);
}

void listar_todos_rec(No * raiz) {
	if(raiz !=NULL) {
		listar_todos_rec(raiz->esq);
		printf("Matricula: %d\n", raiz->key);
		printf("Nome: %s\n", raiz->nome);
		printf("E-mail: %s\n", raiz->email);
		printf("Telefone: %s\n", raiz->telefone);
		printf("=====================================\n\n");
		listar_todos_rec(raiz->dir);
	}
}

int getMatricula (No * no) {
	return no->key;
}
char * getNome (No * no) {
	return no->nome;
}
char * getEmail (No * no) {
	return no->email;
}
char * getTelefone(No * no) {
	return no->telefone;
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


