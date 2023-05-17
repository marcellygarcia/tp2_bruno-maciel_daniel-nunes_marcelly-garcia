#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "arvoreb.cc"
using namespace std;
#define M_BUCKETS 150000  //quantidade de buckets
#define B_BLOCOS 1//quantidade de blocos
#define DATAFILENAME "HashFile"
using namespace std;


int int_to_str(string str){
    int num;
    stringstream ss;
    ss<<str;
    ss>>num;

    return num;
}

vector<string> split(string str, char spliter){
    vector<string> splited_str;
    string s = "";
    for(int i = 0; i < str.size(); i++){
        if(str[i]==spliter){
            splited_str.push_back(s.substr(1,s.size()-2));
            s = "";
        } else{
            s+=str[i];
        }
    }
    splited_str.push_back(s);
    /*
    for(int i = 0; i < splited_str.size(); i++){
        cout<<splited_str[i]<<endl;
    }
    */
    return splited_str;

}

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

Registro le_registro(string linha_csv){
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
        nregistro = le_registro(line);
        insere_no_arquivo(nregistro);
        //imprime_registro(nregistro)

    }
    return 0;

}