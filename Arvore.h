#define bool int
#define true 1
#define false 0

typedef struct no No;
typedef struct arvore Arvore;

//Instancia
Arvore * criar();
void destruir(Arvore * arv);

//Inserir/Remover
void inserir(Arvore * arv, int key, char * nome, char * email, char * telefone);
void remover(Arvore * arv, int key);

//Buscas
No * buscar(Arvore * arv, int key);
char * getNome (No * no);
char * getEmail (No * no);
char * getTelefone(No * no);

//Imprimir - In Ordem
void imprimir(Arvore * arv);
