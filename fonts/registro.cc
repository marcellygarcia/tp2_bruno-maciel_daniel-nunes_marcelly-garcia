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
Registro* novo_registro(){
    Registro* nregistro = (Registro*) malloc(sizeof(Registro));
    nregistro->id = 0;
    nregistro->titulo=  "titulo";
    nregistro->ano= 0;
    nregistro->autores = "autores";
    nregistro->citacoes = 0;
    nregistro->atualizacao = "//";
    nregistro->snippet = "snippet";
    return  nregistro;
    
}
Registro extrai_registro(string linha_csv){  
    vector<string> vline = split(linha_csv,';');
    Registro nregistro;// = novo_registro();
  //  imprime_registro((nregistro));
   if(vline.size() >0) nregistro.id = int_to_str(vline[0]);
   if(vline.size() >1) nregistro.titulo=  vline[1];
   if(vline.size() >2) nregistro.ano= int_to_str(vline[2]);
   if(vline.size() >3) nregistro.autores = vline[3];
   if(vline.size() >4) nregistro.citacoes = int_to_str(vline[4]);
   if(vline.size() >5) nregistro.atualizacao = vline[5];
   if(vline.size() >6) nregistro.snippet = vline[6];
    //imprime_registro((nregistro));
    return nregistro;
}
