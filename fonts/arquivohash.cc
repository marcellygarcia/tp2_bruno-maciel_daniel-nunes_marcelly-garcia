#include <iostream>
#include <fstream>
#include "arvoreb.h"
#include "util.h"
#define M_BUCKETS  2000 //quantidade de buckets
#define B_BLOCOS 1//quantidade de blocos
#define DATAFILENAME "HashFile.bin"

using namespace std;
vector <Registro> myblocs;
typedef struct{
  Bloco b[B_BLOCOS];
} Bucket;

int countReg = 0;

Bucket Buckets[M_BUCKETS];
 bool cria_arquivo(){
   FILE* darq = NULL;
   darq = fopen("MyData.bin","w+b");
   if(darq == NULL){
      cout<<"Falha criando arquivo"<<endl;
      return false;
   }  
   ;
   int r  = 0;
   cout<<sizeof(Bloco)<<endl;
   for(unsigned long i = 0;i < M_BUCKETS;i++){
    for(unsigned long j = 0; j <B_BLOCOS;j++ ){
       Bloco *n = new Bloco;
       n->qtdRegistros=0;
       fwrite(&n,sizeof(Bloco),1,darq);
       r++;
       //free(n);
    }
   }
   cout<<"Regs: "<<r<<endl;
   fclose(darq);
   cout<<"Arquivo Criado com sucesso"<<endl;
   return true;
 }

 void imprimeBloco(Bloco b){
  cout<<"Qtd. Regs.: "<<b.qtdRegistros<<endl;
  cout<<(b.regs==NULL)<<endl;
  for(int i = 0; i < b.qtdRegistros; i++) imprime_registro(b.regs[i]);
 }
 bool GravaBuckets(){
  FILE* darq = NULL;
   darq = fopen("MyData.bin","w+b");
   if(darq == NULL){
      cout<<"Falha criando arquivo"<<endl;
      return false;
   }  
   ;
   int r  = 0;
   cout<<sizeof(Bloco)<<endl;
   for(unsigned long i = 0;i < M_BUCKETS;i++){
    for(unsigned long j = 0; j <B_BLOCOS;j++ ){
       
       fwrite(&(Buckets[i].b[j]),sizeof(Bloco),1,darq);
       r++;
       //free(n);
    }
   }
   cout<<"Regs: "<<r<<endl;
   fclose(darq);
   cout<<"Arquivo Criado com sucesso"<<endl;
   return true;
 
 }
 void inc(Registro reg){
    unsigned long nbucket = fhash(reg.id);
    
    cout<<"N. bucket: "<<nbucket<<endl;   
    
    try{ 
     unsigned long i;
      for(i = 0; i < B_BLOCOS; i++){
        if(Buckets[nbucket].b[i].qtdRegistros < 150) break;
      }
      //imprime_registro();
      unsigned long k = Buckets[nbucket].b[i].qtdRegistros;
      Buckets[nbucket].b[i].regs[k] = reg;
      Buckets[nbucket].b[i].qtdRegistros++;
      countReg++;
      //cout<<"dbBloco "<<dbBloco.qtdRegistros<<endl;
      //cout<<"ininc"<<endl;
    }
    catch(...){
      GravaBuckets();
      exit(1);
    }
 }
 
 bool insere_no_arquivo(string filePath){ 
    
    fstream arqInicial;
    string line;
    
    arqInicial.open(filePath,ios::in);
    
    int i = 15;
    Registro reg;
    FILE *narq;
    unsigned long nbucket;;
    while(getline(arqInicial,line)){
        
        reg = extrai_registro(line);
        inc(reg);
        std::cout<<"Registro Inserido "<<endl;
    
    }
  GravaBuckets();  
  return true;
    
}

void le_arquivo (){
    FILE* darq = NULL;
    darq = fopen("MyData.bin","rb");
    if(darq == NULL){
        cout<<"Falha abrindo arquivo"<<endl;
        return;
    } 
    cout<<"Lendo arquivo de dados "<<M_BUCKETS<<endl; 
    for(unsigned long i; i < M_BUCKETS; i++){
      printf("T-BUCKET: %lu\n",i);
      for(unsigned long j = 0; j <B_BLOCOS;j++ ){
        Bloco *nbloco = new bloco;
        fread(nbloco,sizeof(Bloco),1,darq);
        imprimeBloco(*nbloco);
      }
    
    }
    
    fclose(darq);
    
}

void leblocos (){
  cout<<"My blocs: "<<myblocs.size()<<endl;
  for(int i = 0; i < myblocs.size(); i++){
   // Registr
   imprime_registro((Registro)myblocs[i]);
  }
}

void findrec (unsigned long kid){
    FILE* darq = NULL;
    cout<<kid<<endl;
    darq = fopen("MyData.bin","rb+");
    if(darq == NULL){
        cout<<"Falha abrindo arquivo"<<endl;
        return;
    } 
    unsigned long nbucket = fhash(kid);
    cout<<nbucket<<endl;
    fseek(darq,(nbucket)*sizeof(Bucket),SEEK_SET);
    Bloco *nbloco = new bloco;
    fread(nbloco,sizeof(Bloco),B_BLOCOS,darq);
    bool found = false;
    for(unsigned long i = 0; i <B_BLOCOS;i++ ){
      
        //cout<<nbloco->qtdRegistros<<endl;
        for(unsigned long j =0; j < nbloco->qtdRegistros && !found;j++){
            if(nbloco->regs[j].id == kid){
              imprime_registro(nbloco->regs[j]);
              found=true;
            }
        }

        if(!found) cout<<"Registro não encontrado"<<endl;

      }
    fclose(darq);
    
}

