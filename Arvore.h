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
void inserir(Arvore * arv, int key);
void remover(Arvore * arv, int key);

//Buscas
bool buscar(Arvore * arv, int key);

//Imprimir - In Ordem
void imprimir(Arvore * arv);
