#include <iostream>
#include <fstream>
#include <sstream>
#include "arquivohash.h"
#include "util.h"

using namespace std;

int main(const int argc, const char* argv[]){
    if (argc != 2){
        cout<<"erro lendo id a ser encontrado"<<endl;
        exit(1);
    }
    int id_reg = int_to_str(argv[1]);
    findrec(id_reg);

    return 0;

}
