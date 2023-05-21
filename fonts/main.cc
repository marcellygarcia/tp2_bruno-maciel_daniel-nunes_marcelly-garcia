#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "arquivohash.h"
using namespace std;

void nread(){
   FILE* fp = fopen("file.bin","rb+");
   Registro bn[2];
   /*bn.id = 5;
   bn.ano = 2015;
   bn.titulo = "Marcelly Garcia Mariano Moraes";
   fwrite(&bn,sizeof(Registro),1,fp);
   bn.id = 56;
   bn.ano = 355;
   bn.titulo = "Marcelly Garcia Mariano Moraes";
   fwrite(&bn,sizeof(Registro),1,fp);
   */
   fread(&bn,sizeof(Registro),2,fp);
   imprime_registro(bn[0]);
   imprime_registro(bn[1]);
   

  
   

   //fseek( fp,7, SEEK_SET );
   //fputs(" C Programming Language", fp);
   fclose(fp);
   
}
int main () {
   FILE *fp;

   fp = fopen("file.bin","wb+");
   Registro bn;
   bn.id = 5;
   bn.ano = 2015;
   bn.titulo = "Marcelly Garcia Mariano Moraes";
   fwrite(&bn,sizeof(Registro),1,fp);
   bn.id = 56;
   bn.ano = 355;
   //bn.titulo = "Marcelly Garcia Mariano Moraes";
   fwrite(&bn,sizeof(Registro),1,fp);
   

   //fseek( fp,7, SEEK_SET );
   //fputs(" C Programming Language", fp);
   fclose(fp);
   nread();
   return(0);
}