#include <iostream>
#include <vector>
#include "registro.h"
#include "util.h"
using namespace std;

void imprime_registro(Registro rg){
    cout<<"ID: "<<rg.id<<endl;
    cout<<"Titulo: "<<rg.titulo<<endl;
    cout<<"Ano: "<<rg.ano<<endl;
    cout<<"Autores: "<<rg.autores<<endl;
    cout<<"Citacoes: "<<rg.citacoes<<endl;
    cout<<"Atualização: "<<rg.atualizacao<<endl;
    cout<<"Snippet: "<<rg.snippet<<endl;
    cout<<"-------------------------------------------------"<<endl;    
}

Registro extrai_registro(string linha_csv){
    vector<string> vline = split(linha_csv,';');
    Registro nregistro;
    nregistro.id = int_to_str(vline[0]);
    nregistro.titulo=  vline[1];
    nregistro.ano= int_to_str(vline[2]);
    nregistro.autores = vline[3];
    nregistro.citacoes = int_to_str(vline[4]);
    nregistro.atualizacao = vline[5];
    nregistro.snippet = vline[6];
    return nregistro;
}
