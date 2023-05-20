#include <iostream>
#include <fstream>
#include "arvoreb.h"
#include "util.h"
#define M_BUCKETS 200  //quantidade de buckets
#define B_BLOCOS 1//quantidade de blocos
#define DATAFILENAME "HashFile"

using namespace std;

bool cria_arquivo(){
    fstream arquivoHash;
    
    arquivoHash.open(DATAFILENAME, std::fstream::in | std::fstream::out | std::fstream::trunc | std::ios::binary);
    Bloco nbloco; // buffer pra Bloco (ou página, se estiver na MP) com 0 registros
    nbloco.qtdRegistros = 0;
    // escrevendo os buckets no arquivo

    std::cout<<"Criando e inicializando arquivo de dados"<<endl;
    for (unsigned long i=0; i < M_BUCKETS; ++i) {
      for (unsigned long k=0; k < B_BLOCOS; ++k) {
        arquivoHash.write((char*)&nbloco, sizeof(Bloco));
      }
    }

    arquivoHash.close();
    std::cout<<"Arquivo de dados Criado com sucesso"<<endl;
    return true;
}

bool insere_no_arquivo(Registro reg){
    fstream arquivoHash;
    
    arquivoHash.open(DATAFILENAME, std::fstream::in | std::fstream::out | std::fstream::trunc | std::ios::binary);
    Bloco nbloco;
    nbloco.qtdRegistros = 0;
        unsigned long nbucket = fhash(reg.id);

        arquivoHash.seekg(nbucket*B_BLOCOS*(sizeof(Bloco)),std::ios::beg);

        unsigned long currPage;
        for(currPage = 0; currPage < B_BLOCOS; currPage++){
            arquivoHash.read((char*)&nbloco,(sizeof(Bloco)));
            if(nbloco.qtdRegistros < (sizeof(Bloco)/sizeof(Registro))) break;
        }

        if(currPage >= B_BLOCOS)   return false;

        Registro* records = (Registro*) nbloco.dados;
        records[nbloco.qtdRegistros] = reg;
        nbloco.qtdRegistros++;
        cout<<nbucket<<" "<<nbloco.qtdRegistros<<endl;
        arquivoHash.seekp(-(sizeof(Bloco),std::ios::cur)); // voltar para o primeiro byte do bloco encontrado
        
        arquivoHash.write((char*)&nbloco,sizeof(Bloco));
        std::cout<<"Registro Inserido "<<endl;
        for (int i = 0; i < nbloco.qtdRegistros; i++){
          imprime_registro(records[i]);
        };
        char* str = (char*)&nbloco;
        cout<<(*str)<<endl;
        /*for(int m =0; m<bufferPage.qtdRegistros;m++ ){
            imprime_registro(bufferPage.dados[m]);
        }*/
        arquivoHash.close();
      return true;
}

void le_arquivo (){
  fstream arquivoHash;
    
    arquivoHash.open(DATAFILENAME, std::fstream::in);
    Bloco nbloco; 
    nbloco.qtdRegistros = 0;
    for (unsigned long i=0; i < M_BUCKETS; ++i) {
      arquivoHash.seekg(i*B_BLOCOS*(sizeof(Bloco)));
      printf("BUCKET: %lu\n",i);
      for (unsigned long k=0; k < B_BLOCOS; ++k) {
        arquivoHash.read((char*)&nbloco,(sizeof(Bloco)));
        Registro* records = (Registro*) nbloco.dados;
        cout<<nbloco.qtdRegistros<<endl;
        for (int i = 0; i < nbloco.qtdRegistros; i++){
          imprime_registro(records[i]);
        };
      }
    }
    
        arquivoHash.close();
        
}
