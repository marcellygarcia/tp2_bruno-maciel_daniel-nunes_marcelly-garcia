#include <iostream>
#include <fstream>
#include <sstream>
#include "arquivohash.h"
using namespace std;

int main(const int argc, const char* argv[]){
    if (argc != 2){
        cout<<"erro lendo path do arquivo inicial"<<endl;
        exit(1);
    }
    string filePath = argv[1];
    cria_arquivo();
    insere_no_arquivo(filePath);
    //fecha_arquivo();
    //printf("Registros inseridos\n");
    le_arquivo();

    //leblocos();
    return 0;

}
