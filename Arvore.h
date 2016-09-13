#define bool int
#define true 1
#define false 0

typedef struct no No;
typedef struct arvore Arvore;
typedef struct aluno Aluno;

//Instancia
Arvore * criar();
void destruir(Arvore * arv);

//Inserir/Remover
void inserir(Arvore * arv, int key, Aluno * aluno);
void remover(Arvore * arv, int key);

//Buscas
Aluno * buscar(Arvore * arv, int key);
/*
char * getNome (No * no);
char * getEmail (No * no);
char * getTelefone(No * no);
int getMatricula (No * no);
*/

//Utilidades
int contar_nos(Arvore * arv);
int maior_no(Arvore * arv);

//Imprimir - In Ordem
void imprimir(Arvore * arv);
int maior_no(Arvore * arv);
