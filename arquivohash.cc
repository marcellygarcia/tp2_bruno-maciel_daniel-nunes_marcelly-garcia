#include <iostream>
#include <fstream>
#include "arvoreb.cc"
#define M_BUCKETS 150000  //quantidade de buckets
#define B_BLOCOS 1//quantidade de blocos
#define DATAFILENAME "HashFile"

using namespace std;
bool cria_arquivo(){
    fstream arquivoHash;
    
    arquivoHash.open(DATAFILENAME, std::fstream::in | std::fstream::out | std::fstream::trunc | std::ios::binary);
    Bloco nbloco; // buffer pra Bloco (ou página, se estiver na MP) com 0 registros
    nbloco.qtdRegistros = 0;
    // escrevendo os buckets no arquivo

    cout<<"Criando e inicializando arquivo de dados"<<endl;
    for (unsigned long i=0; i < M_BUCKETS; ++i) {
      for (unsigned long k=0; k < B_BLOCOS; ++k) {
        arquivoHash.write((char*)&nbloco, sizeof(Bloco));
      }
    }

    arquivoHash.close();
    cout<<"Arquivo de dados Criado com sucesso"<<endl;
    return true;
}

bool insere_no_arquivo(Registro reg){
    fstream arquivoHash;
    
    arquivoHash.open(DATAFILENAME, std::fstream::in | std::fstream::out | std::fstream::trunc | std::ios::binary);
    Bloco nbloco; // buffer pra Bloco (ou página, se estiver na MP) com 0 registros
    nbloco.qtdRegistros = 0;
    // escrevendo os buckets no arquivo
         unsigned long nbucket = fhash(reg.id);

        arquivoHash.seekg(nbucket*B_BLOCOS*(sizeof(Bloco)));

        unsigned long currPage;
        for(currPage = 0; currPage < B_BLOCOS; currPage++){
            arquivoHash.read((char*)&nbloco,(sizeof(Bloco)));
            if(nbloco.qtdRegistros < (sizeof(Bloco)/sizeof(Registro))) break;
        }

        if(currPage >= B_BLOCOS)   return false;

        Registro* records = (Registro*) nbloco.dados;
        records[nbloco.qtdRegistros] = reg;
        nbloco.qtdRegistros++;

        arquivoHash.seekp(-sizeof(Bloco),ios::cur);
        arquivoHash.write((char*)&nbloco,sizeof(Bloco));
        cout<<"Registro Inserido "<<endl;

        /*for(int m =0; m<bufferPage.qtdRegistros;m++ ){
            imprime_registro(bufferPage.dados[m]);
        }*/
        arquivoHash.close();
        return true;
}
