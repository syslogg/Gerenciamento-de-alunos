#define bool int
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"



struct no {
	//Informação
	
	Aluno * info;
	
	int fb;
	
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

/*
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

*/

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

//Insere AVL
void inserir(Arvore * arv, int key, Aluno * aluno){
	inserir_avl_rec(&(arv->raiz),key,aluno);
}

int inserir_avl_rec(No * * raiz, int key, Aluno * aluno) {
	int res;
	
	if(*raiz == NULL) {
		//Arvore vazia ou Nó folha
		No * novo = (No *) malloc(sizeof(No));
		novo->key = key;
		novo->fb = 0;
		novo->info = aluno;
		novo->esq = NULL;
		novo->dir = NULL;
		*raiz = novo;
		return true;
	}
	
	No * atual = *raiz;
	if(key < atual->key) {
		
		if((res=inserir_avl_rec(&(atual->esq),key,aluno)) == 1) {
			if(fb_No(atual) >= 2){
				if(key < (*raiz)->esq->key){
					RotacaoLL(raiz);
				} else {
					RotacaoLR(raiz);
				}
			}
		} 
		
	} else {
		
		if(key > atual->key) {
			
			if((res=inserir_avl_rec(&(atual->dir),key,aluno)) == 1) {
				
				if(fb_No(atual) >= 2){
					
					if((*raiz)->dir->key < key) {
						RotacaoRR(raiz);
					} else {
						RotacaoRL(raiz);
					}
				}
			}
			
		} else {
			return 0;
		}
		
		
	}
	atual->fb = maior(alt_No(atual->esq),alt_No(atual->dir)) +1;
	return res;
}
/*
	else {
			if(key > atual->key) {
				if((res=inserir_avl_rec(&(atual->dir),key,aluno)) == true) {
					if(fb_No(atual) >= 2){
						if((*raiz)->dir->key < key) {
							RotacaoRR(raiz);
						} else {
							RotacaoRL(raiz);
						}
					}
				}
			} else {
				return false;
			}
		}
		atual->fb = maior(alt_No(atual->esq),alt_No(atual->dir)) +1;
		return res;
*/

//Funções auxiliares
int alt_No(No * raiz) {
	if(raiz == NULL) return -1;
	else return raiz->fb;
}

int fb_No(No * raiz) {
	return labs(alt_No(raiz->esq) - alt_No(raiz->dir));
}

int maior (int x, int y) {
	return x > y ? x : y;
}

//Rotações
void RotacaoLL (No * * praiz) {
	//printf("RotacaoRR\n");
	No * no = (*praiz)->esq;
	(*praiz)->esq = no->dir;
	
	no->dir = *praiz;
	
	(*praiz)->fb = maior(alt_No((*praiz)->esq),alt_No((*praiz)->dir)) + 1;
	
	no->fb = maior(alt_No(no->esq),(*praiz)->fb);
	
	(*praiz) = no;
	
}

void RotacaoRR (No * * praiz) {
	No * no = (*praiz)->dir;
	
	(*praiz)->dir = no->esq; //Buxo
	no->esq = *praiz;
	(*praiz)->fb = maior(alt_No((*praiz)->esq),alt_No((*praiz)->dir)) + 1;
	
	no->fb = maior(alt_No(no->dir),(*praiz)->fb);
	
	(*praiz) = no;
	
}

void RotacaoLR(No ** praiz) {
	RotacaoRR(&(*praiz)->esq);
	RotacaoLL(praiz);
}

void RotacaoRL(No ** praiz) {
	RotacaoLL(&(*praiz)->dir);
	RotacaoRR(praiz);
}
















