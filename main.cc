#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "arquivohash.h"
using namespace std;

int main(const int argc, const char* argv[]){
    if (argc != 2){
        cout<<"erro lendo path do arquivo inicial"<<endl;
        exit(1);
    }
    string filePath = argv[1];
    fstream arqInicial;
    string line;
    Registro nregistro;
    
    arqInicial.open(filePath,ios::in);
    cria_arquivo();
    int i = 5;
    while(getline(arqInicial,line)){
        getline(arqInicial,line);
        //cout<<line<<endl;
        nregistro = extrai_registro(line);
        insere_no_arquivo(nregistro);
        //imprime_registro(nregistro)

    }
    return 0;

}