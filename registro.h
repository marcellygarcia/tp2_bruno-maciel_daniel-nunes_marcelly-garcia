#include <iostream>
#include <vector>

using namespace std;

typedef struct registro{
    int id,citacoes,ano;
    string titulo,autores,snippet,atualizacao;
} Registro;

void imprime_registro(Registro rg);

Registro extrai_registro(string linha_csv);
