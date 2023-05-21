#include <iostream>
#include <fstream>
#include <iostream>
#include "bloco.h"
using namespace std;

const int t = 3; // Grau mínimo da árvore B

// Renomeação da estrutura do nó pra tipo
typedef struct no {
    Bloco *blocos;     
    struct no **filhos;
    int id_bloco;   
    int qtBlocos;        
    bool eh_folha;       
} No;

// Criar novo Nó
No* novoNo(bool eh_folha);

// Balancear a árvore
void balanceia_filhos(No* pai, int index, No* filho);

//Insere novo nó em um outro nó cheio
void insere_ncheia(No* node, Bloco novoBloco);

//Insere (padrão)
void insere_arvore(No* raiz, Bloco novoBloco);


