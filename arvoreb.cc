#include <iostream>
#include <fstream>
#include <iostream>
#include "arvoreb.h"
using namespace std;


// Função auxiliar para criar um novo nó da árvore B
No* novoNo(bool eh_folha) {
    No* newNode = new No;
    newNode->blocos = new Bloco[2 * t - 1];
    newNode->filhos = new No*[2 * t];
    newNode->qtBlocos = 0;
    newNode->eh_folha = eh_folha;
    return newNode;
}

// Função auxiliar para dividir um filho cheio
void divide_filhos(No* pai, int index, No* filho) {
    No* newNode = novoNo(filho->eh_folha);
    newNode->qtBlocos = t - 1;

    for (int i = 0; i < t - 1; i++) {
        newNode->blocos[i] = filho->blocos[i + t];
    }

    if (!filho->eh_folha) {
        for (int i = 0; i < t; i++) {
            newNode->filhos[i] = filho->filhos[i + t];
        }
    }

    filho->qtBlocos = t - 1;

    for (int i = pai->qtBlocos; i > index; i--) {
        pai->filhos[i + 1] = pai->filhos[i];
    }

    pai->filhos[index + 1] = newNode;

    for (int i = pai->qtBlocos - 1; i >= index; i--) {
        pai->blocos[i + 1] = pai->blocos[i];
    }

    pai->blocos[index] = filho->blocos[t - 1];
    pai->qtBlocos++;
}

// Função auxiliar para inserir uma chave e um ponteiro na árvore B

void insere_ncheia(No* node, Bloco novoBloco){
    int i = node->qtBlocos-1;
    if (node->eh_folha) {
        while (i >= 0 && node->blocos[i].id_bloco > novoBloco.id_bloco) {
            node->blocos[i + 1] = node->blocos[i];
            i--;
        }

        node->blocos[i + 1] = novoBloco;
        node->qtBlocos++;
    } else {
        while (i >= 0 && node->blocos[i].id_bloco > novoBloco.id_bloco) {
            i--;
        }

        if (node->filhos[i + 1]->qtBlocos == (2 * t - 1)) {
            divide_filhos(node, i + 1, node->filhos[i + 1]);

            if (node->blocos[i + 1].id_bloco < novoBloco.id_bloco) {
                i++;
            }
        }

        insere_ncheia(node->filhos[i + 1], novoBloco);

    }
}

void insere_arvore(No* raiz, Bloco novoBloco) {
    if (raiz->qtBlocos == (2 * t - 1)) {
        No* newRaiz = novoNo(false);
        newRaiz->filhos[0] = raiz;
        divide_filhos(newRaiz, 0, raiz);
        insere_ncheia(newRaiz, novoBloco);
        raiz = newRaiz;
    } else {
        insere_ncheia(raiz, novoBloco);
    }
}


